/*-
 * Copyright (c) 2003 Peter Wemm.
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: stable/9/sys/amd64/amd64/support.S 249532 2013-04-16 06:20:35Z kib $
 */

#include "opt_ddb.h"

#include <machine/asmacros.h>
#include <machine/intr_machdep.h>
#include <machine/pmap.h>

#include "assym.s"

	.text

/*
 * bcopy family
 * void bzero(void *buf, u_int len)
 */

/* done */
ENTRY(bzero)
	movq	%rsi,%rcx
	xorl	%eax,%eax
	shrq	$3,%rcx
	cld
	rep
	stosq
	movq	%rsi,%rcx
	andq	$7,%rcx
	rep
	stosb
	ret
END(bzero)
	
/* Address: %rdi */
ENTRY(pagezero)
	movq	$-PAGE_SIZE,%rdx
	subq	%rdx,%rdi
	xorl	%eax,%eax
1:
	movnti	%rax,(%rdi,%rdx)
	movnti	%rax,8(%rdi,%rdx)
	movnti	%rax,16(%rdi,%rdx)
	movnti	%rax,24(%rdi,%rdx)
	addq	$32,%rdx
	jne	1b
	sfence
	ret
END(pagezero)

ENTRY(bcmp)
	movq	%rdx,%rcx
	shrq	$3,%rcx
	cld					/* compare forwards */
	repe
	cmpsq
	jne	1f

	movq	%rdx,%rcx
	andq	$7,%rcx
	repe
	cmpsb
1:
	setne	%al
	movsbl	%al,%eax
	ret
END(bcmp)

/*
 * bcopy(src, dst, cnt)
 *       rdi, rsi, rdx
 *  ws@tools.de     (Wolfgang Solfrank, TooLs GmbH) +49-228-985800
 */
ENTRY(bcopy)
	xchgq	%rsi,%rdi
	movq	%rdx,%rcx

	movq	%rdi,%rax
	subq	%rsi,%rax
	cmpq	%rcx,%rax			/* overlapping && src < dst? */
	jb	1f

	shrq	$3,%rcx				/* copy by 64-bit words */
	cld					/* nope, copy forwards */
	rep
	movsq
	movq	%rdx,%rcx
	andq	$7,%rcx				/* any bytes left? */
	rep
	movsb
	ret

	/* ALIGN_TEXT */
1:
	addq	%rcx,%rdi			/* copy backwards */
	addq	%rcx,%rsi
	decq	%rdi
	decq	%rsi
	andq	$7,%rcx				/* any fractional bytes? */
	std
	rep
	movsb
	movq	%rdx,%rcx			/* copy remainder by 32-bit words */
	shrq	$3,%rcx
	subq	$7,%rsi
	subq	$7,%rdi
	rep
	movsq
	cld
	ret
END(bcopy)
	
/*
 * Note: memcpy does not support overlapping copies
 */
ENTRY(memcpy)
	movq	%rdx,%rcx
	shrq	$3,%rcx				/* copy by 64-bit words */
	cld					/* copy forwards */
	rep
	movsq
	movq	%rdx,%rcx
	andq	$7,%rcx				/* any bytes left? */
	rep
	movsb
	ret
END(memcpy)

/*
 * pagecopy(%rdi=from, %rsi=to)
 */
ENTRY(pagecopy)
	movq	$-PAGE_SIZE,%rax
	movq	%rax,%rdx
	subq	%rax,%rdi
	subq	%rax,%rsi
1:
	prefetchnta (%rdi,%rax)
	addq	$64,%rax
	jne	1b
2:
	movq	(%rdi,%rdx),%rax
	movnti	%rax,(%rsi,%rdx)
	movq	8(%rdi,%rdx),%rax
	movnti	%rax,8(%rsi,%rdx)
	movq	16(%rdi,%rdx),%rax
	movnti	%rax,16(%rsi,%rdx)
	movq	24(%rdi,%rdx),%rax
	movnti	%rax,24(%rsi,%rdx)
	addq	$32,%rdx
	jne	2b
	sfence
	ret
END(pagecopy)

/* fillw(pat, base, cnt) */  
/*       %rdi,%rsi, %rdx */
ENTRY(fillw)
	movq	%rdi,%rax   
	movq	%rsi,%rdi
	movq	%rdx,%rcx
	cld
	rep
	stosw
	ret
END(fillw)

/*****************************************************************************/
/* copyout and fubyte family                                                 */
/*****************************************************************************/
/*
 * Access user memory from inside the kernel. These routines should be
 * the only places that do this.
 *
 * These routines set curpcb->pcb_onfault for the time they execute. When a
 * protection violation occurs inside the functions, the trap handler
 * returns to *curpcb->pcb_onfault instead of the function.
 */

/*
 * copyout(from_kernel, to_user, len)  - MP SAFE
 *         %rdi,        %rsi,    %rdx
 */
ENTRY(copyout)
	movq	PCPU(CURPCB),%rax
	movq	$copyout_fault,PCB_ONFAULT(%rax)
	testq	%rdx,%rdx			/* anything to do? */
	jz	done_copyout

	/*
	 * Check explicitly for non-user addresses.  If 486 write protection
	 * is being used, this check is essential because we are in kernel
	 * mode so the h/w does not provide any protection against writing
	 * kernel addresses.
	 */

	/*
	 * First, prevent address wrapping.
	 */
	movq	%rsi,%rax
	addq	%rdx,%rax
	jc	copyout_fault
/*
 * XXX STOP USING VM_MAXUSER_ADDRESS.
 * It is an end address, not a max, so every time it is used correctly it
 * looks like there is an off by one error, and of course it caused an off
 * by one error in several places.
 */
	movq	$VM_MAXUSER_ADDRESS,%rcx
	cmpq	%rcx,%rax
	ja	copyout_fault

	xchgq	%rdi,%rsi
	/* bcopy(%rsi, %rdi, %rdx) */
	movq	%rdx,%rcx

	shrq	$3,%rcx
	cld
	rep
	movsq
	movb	%dl,%cl
	andb	$7,%cl
	rep
	movsb

done_copyout:
	xorl	%eax,%eax
	movq	PCPU(CURPCB),%rdx
	movq	%rax,PCB_ONFAULT(%rdx)
	ret

	ALIGN_TEXT
copyout_fault:
	movq	PCPU(CURPCB),%rdx
	movq	$0,PCB_ONFAULT(%rdx)
	movq	$EFAULT,%rax
	ret
END(copyout)

/*
 * copyin(from_user, to_kernel, len) - MP SAFE
 *        %rdi,      %rsi,      %rdx
 */
ENTRY(copyin)
	movq	PCPU(CURPCB),%rax
	movq	$copyin_fault,PCB_ONFAULT(%rax)
	testq	%rdx,%rdx			/* anything to do? */
	jz	done_copyin

	/*
	 * make sure address is valid
	 */
	movq	%rdi,%rax
	addq	%rdx,%rax
	jc	copyin_fault
	movq	$VM_MAXUSER_ADDRESS,%rcx
	cmpq	%rcx,%rax
	ja	copyin_fault

	xchgq	%rdi,%rsi
	movq	%rdx,%rcx
	movb	%cl,%al
	shrq	$3,%rcx				/* copy longword-wise */
	cld
	rep
	movsq
	movb	%al,%cl
	andb	$7,%cl				/* copy remaining bytes */
	rep
	movsb

done_copyin:
	xorl	%eax,%eax
	movq	PCPU(CURPCB),%rdx
	movq	%rax,PCB_ONFAULT(%rdx)
	ret

	ALIGN_TEXT
copyin_fault:
	movq	PCPU(CURPCB),%rdx
	movq	$0,PCB_ONFAULT(%rdx)
	movq	$EFAULT,%rax
	ret
END(copyin)

/*
 * casuword32.  Compare and set user integer.  Returns -1 or the current value.
 *        dst = %rdi, old = %rsi, new = %rdx
 */
ENTRY(casuword32)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-4,%rax
	cmpq	%rax,%rdi			/* verify address is valid */
	ja	fusufault

	movl	%esi,%eax			/* old */
#ifdef SMP
	lock
#endif
	cmpxchgl %edx,(%rdi)			/* new = %edx */

	/*
	 * The old value is in %eax.  If the store succeeded it will be the
	 * value we expected (old) from before the store, otherwise it will
	 * be the current value.
	 */

	movq	PCPU(CURPCB),%rcx
	movq	$0,PCB_ONFAULT(%rcx)
	ret
END(casuword32)

/*
 * casuword.  Compare and set user word.  Returns -1 or the current value.
 *        dst = %rdi, old = %rsi, new = %rdx
 */
ENTRY(casuword)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-4,%rax
	cmpq	%rax,%rdi			/* verify address is valid */
	ja	fusufault

	movq	%rsi,%rax			/* old */
#ifdef SMP
	lock
#endif
	cmpxchgq %rdx,(%rdi)			/* new = %rdx */

	/*
	 * The old value is in %eax.  If the store succeeded it will be the
	 * value we expected (old) from before the store, otherwise it will
	 * be the current value.
	 */

	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)
	movq	$0,PCB_ONFAULT(%rcx)
	ret
END(casuword)

/*
 * Fetch (load) a 64-bit word, a 32-bit word, a 16-bit word, or an 8-bit
 * byte from user memory.  All these functions are MPSAFE.
 * addr = %rdi
 */

ALTENTRY(fuword64)
ENTRY(fuword)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-8,%rax
	cmpq	%rax,%rdi			/* verify address is valid */
	ja	fusufault

	movq	(%rdi),%rax
	movq	$0,PCB_ONFAULT(%rcx)
	ret
END(fuword64)	
END(fuword)

ENTRY(fuword32)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-4,%rax
	cmpq	%rax,%rdi			/* verify address is valid */
	ja	fusufault

	movl	(%rdi),%eax
	movq	$0,PCB_ONFAULT(%rcx)
	ret
END(fuword32)

/*
 * fuswintr() and suswintr() are specialized variants of fuword16() and
 * suword16(), respectively.  They are called from the profiling code,
 * potentially at interrupt time.  If they fail, that's okay; good things
 * will happen later.  They always fail for now, until the trap code is
 * able to deal with this.
 */
ALTENTRY(suswintr)
ENTRY(fuswintr)
	movq	$-1,%rax
	ret
END(suswintr)
END(fuswintr)

ENTRY(fuword16)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-2,%rax
	cmpq	%rax,%rdi
	ja	fusufault

	movzwl	(%rdi),%eax
	movq	$0,PCB_ONFAULT(%rcx)
	ret
END(fuword16)

ENTRY(fubyte)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-1,%rax
	cmpq	%rax,%rdi
	ja	fusufault

	movzbl	(%rdi),%eax
	movq	$0,PCB_ONFAULT(%rcx)
	ret
END(fubyte)

	ALIGN_TEXT
fusufault:
	movq	PCPU(CURPCB),%rcx
	xorl	%eax,%eax
	movq	%rax,PCB_ONFAULT(%rcx)
	decq	%rax
	ret

/*
 * Store a 64-bit word, a 32-bit word, a 16-bit word, or an 8-bit byte to
 * user memory.  All these functions are MPSAFE.
 * addr = %rdi, value = %rsi
 */
ALTENTRY(suword64)
ENTRY(suword)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-8,%rax
	cmpq	%rax,%rdi			/* verify address validity */
	ja	fusufault

	movq	%rsi,(%rdi)
	xorl	%eax,%eax
	movq	PCPU(CURPCB),%rcx
	movq	%rax,PCB_ONFAULT(%rcx)
	ret
END(suword64)
END(suword)

ENTRY(suword32)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-4,%rax
	cmpq	%rax,%rdi			/* verify address validity */
	ja	fusufault

	movl	%esi,(%rdi)
	xorl	%eax,%eax
	movq	PCPU(CURPCB),%rcx
	movq	%rax,PCB_ONFAULT(%rcx)
	ret
END(suword32)

ENTRY(suword16)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-2,%rax
	cmpq	%rax,%rdi			/* verify address validity */
	ja	fusufault

	movw	%si,(%rdi)
	xorl	%eax,%eax
	movq	PCPU(CURPCB),%rcx		/* restore trashed register */
	movq	%rax,PCB_ONFAULT(%rcx)
	ret
END(suword16)

ENTRY(subyte)
	movq	PCPU(CURPCB),%rcx
	movq	$fusufault,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS-1,%rax
	cmpq	%rax,%rdi			/* verify address validity */
	ja	fusufault

	movl	%esi,%eax
	movb	%al,(%rdi)
	xorl	%eax,%eax
	movq	PCPU(CURPCB),%rcx		/* restore trashed register */
	movq	%rax,PCB_ONFAULT(%rcx)
	ret
END(subyte)

/*
 * copyinstr(from, to, maxlen, int *lencopied) - MP SAFE
 *           %rdi, %rsi, %rdx, %rcx
 *
 *	copy a string from from to to, stop when a 0 character is reached.
 *	return ENAMETOOLONG if string is longer than maxlen, and
 *	EFAULT on protection violations. If lencopied is non-zero,
 *	return the actual length in *lencopied.
 */
ENTRY(copyinstr)
	movq	%rdx,%r8			/* %r8 = maxlen */
	movq	%rcx,%r9			/* %r9 = *len */
	xchgq	%rdi,%rsi			/* %rdi = from, %rsi = to */
	movq	PCPU(CURPCB),%rcx
	movq	$cpystrflt,PCB_ONFAULT(%rcx)

	movq	$VM_MAXUSER_ADDRESS,%rax

	/* make sure 'from' is within bounds */
	subq	%rsi,%rax
	jbe	cpystrflt

	/* restrict maxlen to <= VM_MAXUSER_ADDRESS-from */
	cmpq	%rdx,%rax
	jae	1f
	movq	%rax,%rdx
	movq	%rax,%r8
1:
	incq	%rdx
	cld

2:
	decq	%rdx
	jz	3f

	lodsb
	stosb
	orb	%al,%al
	jnz	2b

	/* Success -- 0 byte reached */
	decq	%rdx
	xorl	%eax,%eax
	jmp	cpystrflt_x
3:
	/* rdx is zero - return ENAMETOOLONG or EFAULT */
	movq	$VM_MAXUSER_ADDRESS,%rax
	cmpq	%rax,%rsi
	jae	cpystrflt
4:
	movq	$ENAMETOOLONG,%rax
	jmp	cpystrflt_x

cpystrflt:
	movq	$EFAULT,%rax

cpystrflt_x:
	/* set *lencopied and return %eax */
	movq	PCPU(CURPCB),%rcx
	movq	$0,PCB_ONFAULT(%rcx)

	testq	%r9,%r9
	jz	1f
	subq	%rdx,%r8
	movq	%r8,(%r9)
1:
	ret
END(copyinstr)

/*
 * copystr(from, to, maxlen, int *lencopied) - MP SAFE
 *         %rdi, %rsi, %rdx, %rcx
 */
ENTRY(copystr)
	movq	%rdx,%r8			/* %r8 = maxlen */

	xchgq	%rdi,%rsi
	incq	%rdx
	cld
1:
	decq	%rdx
	jz	4f
	lodsb
	stosb
	orb	%al,%al
	jnz	1b

	/* Success -- 0 byte reached */
	decq	%rdx
	xorl	%eax,%eax
	jmp	6f
4:
	/* rdx is zero -- return ENAMETOOLONG */
	movq	$ENAMETOOLONG,%rax

6:

	testq	%rcx,%rcx
	jz	7f
	/* set *lencopied and return %rax */
	subq	%rdx,%r8
	movq	%r8,(%rcx)
7:
	ret
END(copystr)

/*
 * Handling of special amd64 registers and descriptor tables etc
 * %rdi
 */
/* void lgdt(struct region_descriptor *rdp); */
ENTRY(lgdt)
	/* reload the descriptor table */
	lgdt	(%rdi)

	/* flush the prefetch q */
	jmp	1f
	nop
1:
	movl	$KDSEL,%eax
	movl	%eax,%ds
	movl	%eax,%es
	movl	%eax,%fs	/* Beware, use wrmsr to set 64 bit base */
	movl	%eax,%gs
	movl	%eax,%ss

	/* reload code selector by turning return into intersegmental return */
	popq	%rax
	pushq	$KCSEL
	pushq	%rax
	MEXITCOUNT
	lretq
END(lgdt)

/*****************************************************************************/
/* setjump, longjump                                                         */
/*****************************************************************************/

ENTRY(setjmp)
	movq	%rbx,0(%rdi)			/* save rbx */
	movq	%rsp,8(%rdi)			/* save rsp */
	movq	%rbp,16(%rdi)			/* save rbp */
	movq	%r12,24(%rdi)			/* save r12 */
	movq	%r13,32(%rdi)			/* save r13 */
	movq	%r14,40(%rdi)			/* save r14 */
	movq	%r15,48(%rdi)			/* save r15 */
	movq	0(%rsp),%rdx			/* get rta */
	movq	%rdx,56(%rdi)			/* save rip */
	xorl	%eax,%eax			/* return(0); */
	ret
END(setjmp)

ENTRY(longjmp)
	movq	0(%rdi),%rbx			/* restore rbx */
	movq	8(%rdi),%rsp			/* restore rsp */
	movq	16(%rdi),%rbp			/* restore rbp */
	movq	24(%rdi),%r12			/* restore r12 */
	movq	32(%rdi),%r13			/* restore r13 */
	movq	40(%rdi),%r14			/* restore r14 */
	movq	48(%rdi),%r15			/* restore r15 */
	movq	56(%rdi),%rdx			/* get rta */
	movq	%rdx,0(%rsp)			/* put in return frame */
	xorl	%eax,%eax			/* return(1); */
	incl	%eax
	ret
END(longjmp)

/*
 * Support for reading MSRs in the safe manner.
 */
ENTRY(rdmsr_safe)
/* int rdmsr_safe(u_int msr, uint64_t *data) */
	movq	PCPU(CURPCB),%r8
	movq	$msr_onfault,PCB_ONFAULT(%r8)
	movl	%edi,%ecx
	rdmsr			/* Read MSR pointed by %ecx. Returns
				   hi byte in edx, lo in %eax */
	salq	$32,%rdx	/* sign-shift %rdx left */
	movl	%eax,%eax	/* zero-extend %eax -> %rax */
	orq	%rdx,%rax
	movq	%rax,(%rsi)
	xorq	%rax,%rax
	movq	%rax,PCB_ONFAULT(%r8)
	ret

/*
 * Support for writing MSRs in the safe manner.
 */
ENTRY(wrmsr_safe)
/* int wrmsr_safe(u_int msr, uint64_t data) */
	movq	PCPU(CURPCB),%r8
	movq	$msr_onfault,PCB_ONFAULT(%r8)
	movl	%edi,%ecx
	movl	%esi,%eax
	sarq	$32,%rsi
	movl	%esi,%edx
	wrmsr			/* Write MSR pointed by %ecx. Accepts
				   hi byte in edx, lo in %eax. */
	xorq	%rax,%rax
	movq	%rax,PCB_ONFAULT(%r8)
	ret

/*
 * MSR operations fault handler
 */
	ALIGN_TEXT
msr_onfault:
	movq	$0,PCB_ONFAULT(%r8)
	movl	$EFAULT,%eax
	ret
