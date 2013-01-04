;
;	startup.s   -   first startup file for bootloader 
;
;	Author: 	li ming <admin@lumit.org>
;	Date:		2005-5-24
;	Copyleft:	http://www.lumit.org
;

	AREA	SelfBoot,	CODE,	READONLY

;**************************************************************************************************
; <ResetEntry> here is the very entry for the whoe bootloader
ResetEntry
	ldr	r0, =0x03FF5000
	ldr	r1, =0x0003FFFF		; set all 18 gpios' direction to output
	str	r1, [r0]

; ++++++++++++++++++++++++++++++++
; here we light leds to value = "1000" to show bootloader start	
	ldr	r1, =0x00020000		; show led = 1000	
	ldr	r0, =0x03FF5008
	str	r1, [r0]
; ++++++++++++++++++++++++++++++++

	b	SYS_RST_HANDLER

;**************************************************************************************************
; ASIC Address Definition
; <InitMemory> here we init memory register and setup SDRAM 
BASE_ADDR	EQU		0x3FF0000

; System Manager Registers
SYSCFG		EQU		(BASE_ADDR+0x0000)

SDRAM_ITF	EQU		0x80000000
SFR_BASE	EQU		0x3ff	;0x3ff0000
SRAM_BASE	EQU		0x3f8	;0x3f80000
CACHE_ALL	EQU		0x10
CACHE_EN	EQU		2

CLKCON		EQU		(BASE_ADDR+0x3000)
EXTACON0	EQU		(BASE_ADDR+0x3008)
EXTACON1	EQU		(BASE_ADDR+0x300C)
EXTDBWTH	EQU		(BASE_ADDR+0x3010)
ROMCON0		EQU		(BASE_ADDR+0x3014)
	
InitMemory
; ++++++++++++++++++++++++++++++++
	ldr	r1, =0x00000010		; show led = 0100
	ldr	r0, =0x03FF5008
	str	r1, [r0]
; ++++++++++++++++++++++++++++++++
	
	ldr	r0, =SYSCFG
	ldr	r1, =SDRAM_ITF :OR: SFR_BASE<<16 :OR: SRAM_BASE<<6 :OR: CACHE_ALL :OR: CACHE_EN	
	str	r1, [r0]
	
	ldr	r0, =CLKCON
	ldr	r1, =0
	str	r1, [r0]
	
	ldr	r0, =EXTACON0
	ldr	r1, =0x0fff0fff
	str	r1, [r0]
	ldr	r0, =EXTACON1
	ldr	r1, =0x0fff0fff	
	str	r1, [r0]
	
	ldr	r0, =EXTDBWTH
	ldr	r1, =0xffff556
	str r1, [r0]

	adr	r0, MemCfgPara
	ldmia	r0, {r1-r11}
	ldr	r0, =ROMCON0	
	stmia	r0, {r1-r11}

; ++++++++++++++++++++++++++++++++
	ldr	r1, =0x00000070		; show led = 0111	
	ldr	r0, =0x03FF5008
	str	r1, [r0]
; ++++++++++++++++++++++++++++++++
	
	mov	pc, r14
	

;**************************************************************************************************
RomBaseAddr	EQU		0
RomEndAddr	EQU		&20
RamBaseAddr	EQU		&100
RamEndAddr	EQU		&200	
	
MemCfgPara
	DCD	RomBaseAddr<<10 :OR RomEndAddr<<20 :OR: &60	;&10840060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	RamBaseAddr<<10 :OR: RamEndAddr<<20 :OR: &398	;&10000398
	DCD	&10040398
	DCD	&10040398
	DCD	&10040398
	DCD	&ce2983fd	
		
;**************************************************************************************************
; <InitSystem> here we begin to init system 
InitSystem
; ++++++++++++++++++++++++++++++++	
	ldr	r1, =0x00020010		; show led = 1100
	ldr	r0, =0x03FF5008
	str	r1, [r0]
; ++++++++++++++++++++++++++++++++

	mov	r12, r14
	
	bl	InitMemory
	
	mov	pc, r12	

;**************************************************************************************************
; <RemapMemory> here we begin to remap SDRAM and Flash address
RemapMemory
; ++++++++++++++++++++++++++++++++	
	ldr	r1, =0x0002030		; show led = 1110
	ldr	r0, =0x03FF5008
	str	r1, [r0]
; ++++++++++++++++++++++++++++++++

	adr	r0, RemapMemPara
	ldmia	r0, {r1-r11}
	ldr	r0, =ROMCON0
	stmia	r0, {r1-r11}
	nop
	nop
;	ldr	r0, =IRQ_SVC_VECTOR
;	ldr	r1, =IRQ_SERVICE		;IRQ_SVC_VECTOR in ram, so set it after remap
;	str r1, [r0]
	
	mov	pc, r14	

RemapMemPara
	DCD	&12040060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10000398
	DCD	&10040398
	DCD	&10040398
	DCD	&10040398
	DCD	&ce2983fd		
	
;**************************************************************************************************
	IMPORT	|Image$$RO$$Base|	; ROM code start	
	IMPORT	|Image$$RO$$Limit|	; RAM data starts after ROM program
	IMPORT	|Image$$RW$$Base|	; Pre-initialised variables
	IMPORT	|Image$$ZI$$Base|	; uninitialised variables
	IMPORT	|Image$$ZI$$Limit|	; End of variable RAM space
	
BaseOfROM	DCD	|Image$$RO$$Base|
TopOfROM	DCD	|Image$$RO$$Limit|
BaseOfBSS	DCD	|Image$$RW$$Base|
BaseOfZero	DCD	|Image$$ZI$$Base|
EndOfBSS	DCD	|Image$$ZI$$Limit|

SYS_RST_HANDLER
	
	bl	InitSystem

; ++++++++++++++++++++++++++++++++
	ldr	r1, =0x00020070		; show led = 1111
	ldr	r0, =0x03FF5008
	str	r1, [r0]
; ++++++++++++++++++++++++++++++++
		
	adr	r0, ResetEntry
	mov	r3, #(RamBaseAddr<<16)
	ldr	r1, BaseOfROM	
	ldr	r2, TopOfROM	
	add	r1, r1, r3
	add	r2, r2, r3
0	
	ldmia	r0!, {r4-r11}
	stmia	r1!, {r4-r11}
	cmp	r1, r2
	bcc	%B0
	
	sub	r1, r1, r2
	sub	r0, r0, r1	
	ldr	r1, BaseOfBSS
	ldr	r2, BaseOfZero
	add	r1, r1, r3	
	add	r2, r2, r3	
1	
	cmp	r1,	r2	
	ldrcc	r4, [r0], #4
	strcc	r4, [r1], #4	
	bcc	%B1
	
	mov	r0,	#0
	ldr	r2,	EndOfBSS
	add	r2, r2, r3
3	
	cmp	r1,	r2
	strcc	r0, [r1], #4
	bcc	%B3						
	
	adr	r0, ResetEntry
	ldr	r1, =RemapMemory	
	ldr	r2, BaseOfROM
	sub	r2, r1, r2
	add	r0, r0, r2
	add	r1, r2, r3
	mov	r2,	#32
0	
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	subs	r2, r2,	#1
	bne	%B0
	
	; Set up SVC stack
	mov	r0, #0xd3                ; make svc mode with all irqs disabled
	msr	cpsr_cxsf, r0		 
	MOV 	sp, #0x80000

F_Bit		EQU 	0x40
Mode_Svc	EQU	0x13
			
	MOV	r0, #Mode_Svc:OR:F_Bit
	MSR	cpsr_c, r0
		
	ldr	lr,	GotoMain			 	
	b	RemapMemory		 		

	GBLS	MainEntry
MainEntry	SETS	"main"
	IMPORT	$MainEntry
	
GotoMain	DCD	$MainEntry
	
;**************************************************************************************************
	END
	