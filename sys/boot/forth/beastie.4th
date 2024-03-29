\ Copyright (c) 2003 Scott Long <scottl@freebsd.org>
\ Copyright (c) 2003 Aleksander Fafula <alex@fafula.com>
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
\ $FreeBSD: stable/9/sys/boot/forth/beastie.4th 254953 2013-08-27 06:31:50Z dteske $

marker task-beastie.4th

include /boot/delay.4th

variable logoX
variable logoY

\ Initialize logo placement to defaults
46 logoX !
4  logoY !

: beastie-logo ( x y -- ) \ color BSD mascot (19 rows x 34 columns)

2dup at-xy ."               [31m,        ," 1+
2dup at-xy ."              /(        )`" 1+
2dup at-xy ."              \ \___   / |" 1+
2dup at-xy ."              /- [37m_[31m  `-/  '" 1+
2dup at-xy ."             ([37m/\/ \[31m \   /\" 1+
2dup at-xy ."             [37m/ /   |[31m `    \" 1+
2dup at-xy ."             [34mO O   [37m) [31m/    |" 1+
2dup at-xy ."             [37m`-^--'[31m`<     '" 1+
2dup at-xy ."            (_.)  _  )   /" 1+
2dup at-xy ."             `.___/`    /" 1+
2dup at-xy ."               `-----' /" 1+
2dup at-xy ."  [33m<----.[31m     __ / __   \" 1+
2dup at-xy ."  [33m<----|====[31mO)))[33m==[31m) \) /[33m====|" 1+
2dup at-xy ."  [33m<----'[31m    `--' `.__,' \" 1+
2dup at-xy ."               |        |" 1+
2dup at-xy ."                \       /       /\" 1+
2dup at-xy ."           [36m______[31m( (_  / \______/" 1+
2dup at-xy ."         [36m,'  ,-----'   |" 1+
     at-xy ."         `--{__________)[37m"

	\ Put the cursor back at the bottom
	0 25 at-xy
;

: beastiebw-logo ( x y -- ) \ B/W BSD mascot (19 rows x 34 columns)

	2dup at-xy ."               ,        ," 1+
	2dup at-xy ."              /(        )`" 1+
	2dup at-xy ."              \ \___   / |" 1+
	2dup at-xy ."              /- _  `-/  '" 1+
	2dup at-xy ."             (/\/ \ \   /\" 1+
	2dup at-xy ."             / /   | `    \" 1+
	2dup at-xy ."             O O   ) /    |" 1+
	2dup at-xy ."             `-^--'`<     '" 1+
	2dup at-xy ."            (_.)  _  )   /" 1+
	2dup at-xy ."             `.___/`    /" 1+
	2dup at-xy ."               `-----' /" 1+
	2dup at-xy ."  <----.     __ / __   \" 1+
	2dup at-xy ."  <----|====O)))==) \) /====|" 1+
	2dup at-xy ."  <----'    `--' `.__,' \" 1+
	2dup at-xy ."               |        |" 1+
	2dup at-xy ."                \       /       /\" 1+
	2dup at-xy ."           ______( (_  / \______/" 1+
	2dup at-xy ."         ,'  ,-----'   |" 1+
	     at-xy ."         `--{__________)"

	\ Put the cursor back at the bottom
	0 25 at-xy
;

: fbsdbw-logo ( x y -- ) \ "FreeBSD" logo in B/W (13 rows x 21 columns)

	\ We used to use the beastie himself as our default... until the
	\ eventual complaint derided his reign of the advanced boot-menu.
	\ 
	\ This is the replacement of beastie to satiate the haters of our
	\ beloved helper-daemon (ready to track down and spear bugs with
	\ his trident and sporty sneakers; see above).
	\ 
	\ Since we merely just changed the default and not the default-
	\ location, below is an adjustment to the passed-in coordinates,
	\ forever influenced by the proper location of beastie himself
	\ kept as the default loader_logo_x/loader_logo_y values.
	\ 
	5 + swap 6 + swap

	2dup at-xy ."  ______" 1+
	2dup at-xy ." |  ____| __ ___  ___ " 1+
	2dup at-xy ." | |__ | '__/ _ \/ _ \" 1+
	2dup at-xy ." |  __|| | |  __/  __/" 1+
	2dup at-xy ." | |   | | |    |    |" 1+
	2dup at-xy ." |_|   |_|  \___|\___|" 1+
	2dup at-xy ."  ____   _____ _____" 1+
	2dup at-xy ." |  _ \ / ____|  __ \" 1+
	2dup at-xy ." | |_) | (___ | |  | |" 1+
	2dup at-xy ." |  _ < \___ \| |  | |" 1+
	2dup at-xy ." | |_) |____) | |__| |" 1+
	2dup at-xy ." |     |      |      |" 1+
	     at-xy ." |____/|_____/|_____/"

	\ Put the cursor back at the bottom
	0 25 at-xy
;

: tribute-art ( x y -- ) \ see tribute[bw]-logo

	\ Disable the brand art (we're going to use that space)
	s" set loader_brand=none" evaluate

	\ Blank out the frame of the menu and move the title to left
	s" set loader_menu_title=" evaluate
	s" set loader_menu_frame=none" evaluate

	\ Move the menu to the center of the screen
	s" set loader_menu_x=26" evaluate
	s" set loader_menu_y=12" evaluate
	s" set loader_menu_timeout_x=21" evaluate
	s" set loader_menu_timeout_y=24" evaluate

	2 - swap 39 - swap \ top-left (see `fbsdbw-logo' comments above)

	2dup at-xy 11 spaces ." ,d      b." 1+
	2dup at-xy ."         ,d88]      [88b." 1+
	2dup at-xy ."      ,d888P" 34 emit ."  ,d88b. " 34 emit ." Y888b." 1+
	2dup at-xy ."  , <888P" 34 emit ."  ,dP" 34 emit ." ,db." 34 emit
	           ." Yb. " 34 emit ." Y888> ," 1+
	2dup at-xy ." <88b.~ ,d888  " 34 emit ." YP" 34 emit
	           ."   888b. ~,d88>" 1+
	2dup at-xy ."  ," 34 emit ." Y888888P" 34 emit ." ,db.,db." 34 emit
	           ." Y888888P" 34 emit ." ," 1+
	2dup at-xy ." <88b." 34 emit ." YP" 34 emit ."  _ " 34 emit
	           ." YP" 34 emit 34 emit ." YP" 34 emit ."  _ " 34 emit
	           ." YP" 34 emit ." ,d88>" 1+
	2dup at-xy ."   " 34 emit ." Y88b.,dP          Yb.,d88P" 34 emit 1+
	     at-xy ."      " 34 emit ." YP" 34 emit ."               " 34 emit
	           ." YP" 34 emit ." "
;

: tribute-text ( x y -- ) \ see tribute[bw]-logo

	swap 2 - swap \ beastie adjustment (see `fbsdbw-logo' comments above)

	2dup at-xy ." CEO Workstation" 1+
	1+
	2dup at-xy ." Nakatomi Socrates FreeBSD 9.2" 1+
	2dup at-xy ." Z-Level Central Core" 1+
	1+
	     at-xy ." Preliminary Clearance Approved."
;

: tribute-logo ( x y -- ) \ color Socrates tribute (16 rows x 32 columns)

	\ Produce the tribute art in bright green
	2dup at-xy ." [32;1m" 2dup tribute-art ." [37m"

	\ Produce the tribute text in regular green
	2dup at-xy ." [32m" 2dup tribute-text ." [37m"

	\ Distinguish the ``Free'' in tribute-text
	2 + swap 16 + swap at-xy ." Free"

 	\ Put the cursor back at the bottom
 	0 25 at-xy
;

: tributebw-logo ( x y -- ) \ Socrates tribute (16 rows x 32 columns)

	\ Produce the tribute art and text
	2dup tribute-art tribute-text

 	\ Put the cursor back at the bottom
 	0 25 at-xy
;

: orb-logo ( x y -- ) \ color Orb mascot (15 rows x 30 columns)

	3 + \ beastie adjustment (see `fbsdbw-logo' comments above)

	2dup at-xy ."  [31m```                        [31;1m`[31m" 1+
	2dup at-xy ." s` `.....---...[31;1m....--.```   -/[31m" 1+
	2dup at-xy ." +o   .--`         [31;1m/y:`      +.[31m" 1+
	2dup at-xy ."  yo`:.            [31;1m:o      `+-[31m" 1+
	2dup at-xy ."   y/               [31;1m-/`   -o/[31m" 1+
	2dup at-xy ."  .-                  [31;1m::/sy+:.[31m" 1+
	2dup at-xy ."  /                     [31;1m`--  /[31m" 1+
	2dup at-xy ." `:                          [31;1m:`[31m" 1+
	2dup at-xy ." `:                          [31;1m:`[31m" 1+
	2dup at-xy ."  /                          [31;1m/[31m" 1+
	2dup at-xy ."  .-                        [31;1m-.[31m" 1+
	2dup at-xy ."   --                      [31;1m-.[31m" 1+
	2dup at-xy ."    `:`                  [31;1m`:`" 1+
	2dup at-xy ."      [31;1m.--             `--." 1+
	     at-xy ."         .---.....----.[37m"

 	\ Put the cursor back at the bottom
 	0 25 at-xy
;

: orbbw-logo ( x y -- ) \ B/W Orb mascot (15 rows x 32 columns)

	3 + \ beastie adjustment (see `fbsdbw-logo' comments above)

	2dup at-xy ."  ```                        `" 1+
	2dup at-xy ." s` `.....---.......--.```   -/" 1+
	2dup at-xy ." +o   .--`         /y:`      +." 1+
	2dup at-xy ."  yo`:.            :o      `+-" 1+
	2dup at-xy ."   y/               -/`   -o/" 1+
	2dup at-xy ."  .-                  ::/sy+:." 1+
	2dup at-xy ."  /                     `--  /" 1+
	2dup at-xy ." `:                          :`" 1+
	2dup at-xy ." `:                          :`" 1+
	2dup at-xy ."  /                          /" 1+
	2dup at-xy ."  .-                        -." 1+
	2dup at-xy ."   --                      -." 1+
	2dup at-xy ."    `:`                  `:`" 1+
	2dup at-xy ."      .--             `--." 1+
	     at-xy ."         .---.....----."

 	\ Put the cursor back at the bottom
 	0 25 at-xy
;

\ This function draws any number of beastie logos at (loader_logo_x,
\ loader_logo_y) if defined, else (46,4) (to the right of the menu). To choose
\ your beastie, set the variable `loader_logo' to the respective logo name.
\ 
\ Currently available:
\ 
\ 	NAME        DESCRIPTION
\ 	beastie     Color ``Helper Daemon'' mascot (19 rows x 34 columns)
\ 	beastiebw   B/W ``Helper Daemon'' mascot (19 rows x 34 columns)
\ 	fbsdbw      "FreeBSD" logo in B/W (13 rows x 21 columns)
\ 	orb         Color ``Orb'' mascot (15 rows x 30 columns) (2nd default)
\ 	orbbw       B/W ``Orb'' mascot (15 rows x 32 columns)
\ 	tribute     Color ``Tribute'' (must fit 19 rows x 34 columns) (default)
\ 	tributebw   B/W ``Tribute'' (must fit 19 rows x 34 columns)
\ 
\ NOTE: Setting `loader_logo' to an undefined value (such as "none") will
\       prevent beastie from being drawn.
\ 
: draw-beastie ( -- ) \ at (loader_logo_x,loader_logo_y), else (46,4)

	s" loader_logo_x" getenv dup -1 <> if
		?number 1 = if logoX ! then
	else
		drop
	then
	s" loader_logo_y" getenv dup -1 <> if
		?number 1 = if logoY ! then
	else
		drop
	then

	s" loader_logo" getenv dup -1 = if
		logoX @ logoY @
		loader_color? if
			orb-logo
		else
			orbbw-logo
		then
		drop exit
	then

	2dup s" beastie" compare-insensitive 0= if
		logoX @ logoY @ beastie-logo
		2drop exit
	then
	2dup s" beastiebw" compare-insensitive 0= if
		logoX @ logoY @ beastiebw-logo
		2drop exit
	then
	2dup s" fbsdbw" compare-insensitive 0= if
		logoX @ logoY @ fbsdbw-logo
		2drop exit
	then
	2dup s" orb" compare-insensitive 0= if
		logoX @ logoY @ orb-logo
		2drop exit
	then
	2dup s" orbbw" compare-insensitive 0= if
		logoX @ logoY @ orbbw-logo
		2drop exit
	then
	2dup s" tribute" compare-insensitive 0= if
		logoX @ logoY @
		s" tribute-logo" sfind if
			execute
		else
			drop orb-logo
		then
		2drop exit
	then
	2dup s" tributebw" compare-insensitive 0= if
		logoX @ logoY @
		s" tributebw-logo" sfind if
			execute
		else
			drop orbbw-logo
		then
		2drop exit
	then

	2drop
;

: clear-beastie ( -- ) \ clears beastie from the screen
	logoX @ logoY @
	2dup at-xy 34 spaces 1+		2dup at-xy 34 spaces 1+
	2dup at-xy 34 spaces 1+		2dup at-xy 34 spaces 1+
	2dup at-xy 34 spaces 1+		2dup at-xy 34 spaces 1+
	2dup at-xy 34 spaces 1+		2dup at-xy 34 spaces 1+
	2dup at-xy 34 spaces 1+		2dup at-xy 34 spaces 1+
	2dup at-xy 34 spaces 1+		2dup at-xy 34 spaces 1+
	2dup at-xy 34 spaces 1+		2dup at-xy 34 spaces 1+
	2dup at-xy 34 spaces 1+		2dup at-xy 34 spaces 1+
	2dup at-xy 34 spaces 1+		2dup at-xy 34 spaces 1+
	2dup at-xy 34 spaces		2drop

	\ Put the cursor back at the bottom
	0 25 at-xy
;

: beastie-start ( -- ) \ starts the menu
	s" beastie_disable" getenv
	dup -1 <> if
		s" YES" compare-insensitive 0= if
			exit
		then
	else
		drop
	then

	s" loader_delay" getenv
	-1 = if
		s" include /boot/menu.rc" evaluate
	else
		drop
		." Loading Menu (Ctrl-C to Abort)" cr
		s" set delay_command='include /boot/menu.rc'" evaluate
		s" set delay_showdots" evaluate
		delay_execute
	then
;
