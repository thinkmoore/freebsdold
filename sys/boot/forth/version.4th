\ Copyright (c) 2006-2013 Devin Teske <dteske@FreeBSD.org>
\ All rights reserved.
\ 
\ Redistribution and use in source and binary forms, with or without
\ modification, are permitted provided that the following conditions
\ are met:
\ 1. Redistributions of source code must retain the above copyright
\    notice, this list of conditions and the following disclaimer.
\ 2. Redistributions in binary form must reproduce the above copyright
\    notice, this list of conditions and the following disclaimer in the
\    documentation and/or other materials provided with the distribution.
\ 
\ THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
\ ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
\ IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
\ ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
\ FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
\ DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
\ OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
\ HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
\ LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
\ OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
\ SUCH DAMAGE.
\ 
\ $FreeBSD: stable/9/sys/boot/forth/version.4th 254953 2013-08-27 06:31:50Z dteske $

marker task-version.4th

variable versionX
variable versionY

\ Default $loader_version value if not overridden or using tribute screen
: str_loader_version ( -- C-ADDR/U|-1 ) s" FreeBSD `Nakatomi Socrates' 9.2" ;

\ Initialize text placement to defaults
80 versionX !	\ NOTE: this is the ending column (text is right-justified)
24 versionY !

: print_version ( -- )

	\ Get the text placement position (if set)
	s" loader_version_x" getenv dup -1 <> if
		?number drop versionX ! -1
	then drop
	s" loader_version_y" getenv dup -1 <> if
		?number drop versionY ! -1
	then drop

	\ Default version if none was set
	s" loader_version" getenv dup -1 = if
		drop
		\ Default version if no logo is requested
		s" loader_logo" getenv dup -1 = if
			drop str_loader_version
		else
			2dup s" tribute" compare-insensitive 0= if
				2drop
				s" tribute-logo" sfind if
					drop exit \ see beastie tribute-text
				else
					drop str_loader_version
				then
			else 2dup s" tributebw" compare-insensitive 0= if
				2drop
				s" tributebw-logo" sfind if
					drop exit \ see beastie tribute-text
				else
					drop str_loader_version
				then
			else
				2drop str_loader_version
			then then
		then
	then dup -1 = if
		drop exit \ default version (above) is disabled
	then

	\ Right justify the text
	dup versionX @ swap - versionY @ at-xy

	\ Print the version (optionally in cyan)
	loader_color? if
		." [36m" type ." [37m"
	else
		type
	then
;
