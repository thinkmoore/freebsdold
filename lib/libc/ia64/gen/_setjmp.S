//
// Copyright (c) 1999, 2000
// Intel Corporation.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
// 
//    This product includes software developed by Intel Corporation and
//    its contributors.
// 
// 4. Neither the name of Intel Corporation or its contributors may be
//    used to endorse or promote products derived from this software
//    without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY INTEL CORPORATION AND CONTRIBUTORS ``AS IS''
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL INTEL CORPORATION OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
// 
//

//
// Module Name:
//
//  setjmp.s
//
// Abstract:
//
//  Contains an implementation of setjmp and longjmp for the
//  IA-64 architecture.

    .file   "setjmp.s"

#include <machine/asm.h>
__FBSDID("$FreeBSD: stable/9/lib/libc/ia64/gen/_setjmp.S 118034 2003-07-25 22:36:48Z marcel $");

#define     LOCORE
#include    <machine/setjmp.h>

// int _setjmp(struct jmp_buffer *)
//
//  Setup a non-local goto.
//
// Description:
//
//  SetJump stores the current register set in the area pointed to
//  by "save".  It returns zero.  Subsequent calls to "LongJump" will
//  restore the registers and return non-zero to the same location.
//
// On entry, r32 contains the pointer to the jmp_buffer
//

ENTRY(_setjmp, 1)
    add     r10 = J_PREDS, r32  // skip Unats & pfs save area
    add     r11 = J_BSP, r32
    //
    //  save immediate context
    //
    mov     r2 = ar.bsp         // save backing store pointer
    mov     r3 = pr             // save predicates
    flushrs
    ;;
    //
    // save user Unat register
    //
    mov     r16 = ar.lc         // save loop count register
    mov     r14 = ar.unat       // save user Unat register

    st8     [r10] = r3, J_LC-J_PREDS
    st8     [r11] = r2, J_R4-J_BSP
    ;;
    st8     [r10] = r16, J_R5-J_LC
    st8     [r32] = r14, J_NATS // Note: Unat at the 
                                // beginning of the save area
    mov     r15 = ar.pfs
    ;;
    //
    //  save preserved general registers & NaT's
    //
    .mem.offset 0,0
    st8.spill   [r11] = r4, J_R6-J_R4
    .mem.offset 8,0
    st8.spill   [r10] = r5, J_R7-J_R5
    ;;
    .mem.offset 16,0
    st8.spill   [r11] = r6, J_SP-J_R6
    .mem.offset 24,0
    st8.spill   [r10] = r7, J_F3-J_R7 
    ;;
    st8.spill   [r11] = sp, J_F2-J_SP
    mov	    r16 = ar.rsc
    ;;
    //
    // save spilled Unat and pfs registers
    //
    mov     r2 = ar.unat        // save Unat register after spill
    mov	ar.rsc = r0
    ;;
    st8     [r32] = r2, J_PFS-J_NATS    // save unat for spilled regs
    mov     r17 = ar.rnat
    ;;
    st8     [r32] = r15, J_RNAT-J_PFS	// save pfs
    mov	    ar.rsc = r16
    //
    //  save floating registers 
    //
    stf.spill   [r11] = f2, J_F4-J_F2
    stf.spill   [r10] = f3, J_F5-J_F3 
    ;;
    stf.spill   [r11] = f4, J_F16-J_F4
    stf.spill   [r10] = f5, J_F17-J_F5 
    ;;
    stf.spill   [r11] = f16, J_F18-J_F16
    stf.spill   [r10] = f17, J_F19-J_F17 
    ;;
    stf.spill   [r11] = f18, J_F20-J_F18
    stf.spill   [r10] = f19, J_F21-J_F19 
    ;;
    stf.spill   [r11] = f20, J_F22-J_F20
    stf.spill   [r10] = f21, J_F23-J_F21 
    ;;
    stf.spill   [r11] = f22, J_F24-J_F22
    stf.spill   [r10] = f23, J_F25-J_F23 
    ;;
    stf.spill   [r11] = f24, J_F26-J_F24
    stf.spill   [r10] = f25, J_F27-J_F25 
    ;;
    stf.spill   [r11] = f26, J_F28-J_F26
    stf.spill   [r10] = f27, J_F29-J_F27 
    ;;
    stf.spill   [r11] = f28, J_F30-J_F28
    stf.spill   [r10] = f29, J_F31-J_F29 
    ;;
    stf.spill   [r11] = f30, J_FPSR-J_F30
    stf.spill   [r10] = f31, J_B0-J_F31     // size of f31 + fpsr
    ;;
    st8     [r32] = r17
    //
    // save FPSR register & branch registers
    //
    mov     r2 = ar.fpsr    // save fpsr register
    mov     r3 = b0 
    ;;
    st8     [r11] = r2, J_B1-J_FPSR
    st8     [r10] = r3, J_B2-J_B0
    mov     r2 = b1
    mov     r3 = b2 
    ;;
    st8     [r11] = r2, J_B3-J_B1
    st8     [r10] = r3, J_B4-J_B2
    mov     r2 = b3
    mov     r3 = b4 
    ;;
    st8     [r11] = r2, J_B5-J_B3
    st8     [r10] = r3
    mov     r2 = b5 
    ;;
    st8     [r11] = r2
    ;;
    //
    // return
    //
    mov     r8 = r0         // return 0 from setjmp
    mov     ar.unat = r14   // restore unat
    br.ret.sptk b0

END(_setjmp)


//
// void _longjmp(struct jmp_buffer *, int val)
//
//  Perform a non-local goto.
//
// Description:
//
//  LongJump initializes the register set to the values saved by a
//  previous 'SetJump' and jumps to the return location saved by that
//  'SetJump'.  This has the effect of unwinding the stack and returning
//  for a second time to the 'SetJump'.
//

	WEAK_ALIAS(_longjmp,___longjmp)
ENTRY(___longjmp, 2)
    mov     r14 = ar.rsc        // get user RSC conf
    mov     r8 = r33            // return value
    add     r10 = J_PFS, r32    // get address of pfs
    ;;
    mov     ar.rsc = r0
    add     r11 = J_NATS, r32
    add     r17 = J_RNAT, r32
    ;;
    ld8     r15 = [r10], J_BSP-J_PFS    // get pfs
    ld8     r2 = [r11], J_LC-J_NATS     // get unat for spilled regs
    mov     r31 = r32
    ;;
    loadrs
    mov     ar.unat = r2
    cmp.eq  p6,p0=0,r8			// Return value 0?
    ;;
    ld8     r16 = [r10], J_PREDS-J_BSP  // get backing store pointer
    ld8     r17 = [r17]			// ar.rnat
    mov     ar.pfs = r15
    ;;
    mov     ar.bspstore = r16
(p6) add    r8 = 1, r0
    ;;
    mov     ar.rnat = r17
    mov     ar.rsc = r14        // restore RSC conf

    ld8     r3 = [r11], J_R4-J_LC       // get lc register
    ld8     r2 = [r10], J_R5-J_PREDS    // get predicates
    ;;
    mov     pr = r2, -1
    mov     ar.lc = r3
    //
    //  restore preserved general registers & NaT's
    //
    ld8.fill    r4 = [r11], J_R6-J_R4
    ;;
    ld8.fill    r5 = [r10], J_R7-J_R5 
    ld8.fill    r6 = [r11], J_SP-J_R6
    ;;
    ld8.fill    r7 = [r10], J_F2-J_R7
    ld8.fill    sp = [r11], J_F3-J_SP
    ;;
    //
    //  restore floating registers 
    //
    ldf.fill    f2 = [r10], J_F4-J_F2
    ldf.fill    f3 = [r11], J_F5-J_F3 
    ;;
    ldf.fill    f4 = [r10], J_F16-J_F4
    ldf.fill    f5 = [r11], J_F17-J_F5 
    ;;
    ldf.fill    f16 = [r10], J_F18-J_F16
    ldf.fill    f17 = [r11], J_F19-J_F17
    ;;
    ldf.fill    f18 = [r10], J_F20-J_F18
    ldf.fill    f19 = [r11], J_F21-J_F19
    ;;
    ldf.fill    f20 = [r10], J_F22-J_F20
    ldf.fill    f21 = [r11], J_F23-J_F21
    ;;
    ldf.fill    f22 = [r10], J_F24-J_F22
    ldf.fill    f23 = [r11], J_F25-J_F23 
    ;;
    ldf.fill    f24 = [r10], J_F26-J_F24
    ldf.fill    f25 = [r11], J_F27-J_F25
    ;;
    ldf.fill    f26 = [r10], J_F28-J_F26
    ldf.fill    f27 = [r11], J_F29-J_F27
    ;;
    ldf.fill    f28 = [r10], J_F30-J_F28
    ldf.fill    f29 = [r11], J_F31-J_F29 
    ;;
    ldf.fill    f30 = [r10], J_FPSR-J_F30
    ldf.fill    f31 = [r11], J_B0-J_F31 ;;

    //
    // restore branch registers and fpsr
    //
    ld8     r16 = [r10], J_B1-J_FPSR    // get fpsr
    ld8     r17 = [r11], J_B2-J_B0      // get return pointer
    ;;
    mov     ar.fpsr = r16
    mov     b0 = r17
    ld8     r2 = [r10], J_B3-J_B1
    ld8     r3 = [r11], J_B4-J_B2
    ;;
    mov     b1 = r2
    mov     b2 = r3
    ld8     r2 = [r10], J_B5-J_B3
    ld8     r3 = [r11]
    ;;
    mov     b3 = r2
    mov     b4 = r3
    ld8     r2 = [r10]
    ld8     r21 = [r31]         // get user unat
    ;;
    mov     b5 = r2
    mov     ar.unat = r21

    //
    // invalidate ALAT
    //
    invala ;;

    br.ret.sptk b0

END(___longjmp)
