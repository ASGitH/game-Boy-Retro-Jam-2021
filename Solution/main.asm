;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.7 #12016 (MINGW64)
;--------------------------------------------------------
	.module main
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _initializeGame
	.globl _gameCoreLoop
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	G$main$0$0	= .
	.globl	G$main$0$0
	C$main.c$5$0_0$86	= .
	.globl	C$main.c$5$0_0$86
;main.c:5: int main(){
;	---------------------------------
; Function main
; ---------------------------------
_main::
	C$main.c$6$1_0$86	= .
	.globl	C$main.c$6$1_0$86
;main.c:6: initializeGame();
	call	_initializeGame
	C$main.c$8$1_0$86	= .
	.globl	C$main.c$8$1_0$86
;main.c:8: while (TRUE) { gameCoreLoop(); }
00102$:
	call	_gameCoreLoop
	C$main.c$10$1_0$86	= .
	.globl	C$main.c$10$1_0$86
;main.c:10: return 0;
	C$main.c$11$1_0$86	= .
	.globl	C$main.c$11$1_0$86
;main.c:11: }
	C$main.c$11$1_0$86	= .
	.globl	C$main.c$11$1_0$86
	XG$main$0$0	= .
	.globl	XG$main$0$0
	jr	00102$
	.area _CODE
	.area _CABS (ABS)
