;
;       led_0000.s  --  blink leds (set value 0000 and 1111 to four led gpio in a loop)
;       
;	Author:		li ming <admin@lumit.org>
;	Date:		2005-5-20
;	Copyleft: 	http://www.lumit.org
;	
	
; 
; ARM ASM Code for ADS 1.2
;

	AREA LED, CODE
	
	ldr	r0, =0x03FF5000
	ldr	r1, =0x0003FFFF		; set all 18 gpios' direction to output
	str	r1, [r0]
	
loop

; 
; hardware connection		
; IO17 	IO04 	IO05 	IO06	(gpio)
; D6   	D7   	D8   	D9 	(led)
; so output value = 0x00000000 = (0b0000 0000  0000 0000  0000 0000  0000 0000)
;

	ldr	r1, =0x00000000		; show led = 0000	
	ldr	r0, =0x03FF5008
	str	r1, [r0]

; delay for some time
	ldr	r1, =0x0000FFFF
delay1	
	sub	r1, r1, #1
	cmp 	r1, #0
	bne	delay1

; 
; hardware connection
; IO17 	IO04 	IO05 	IO06	(gpio)
; D6   	D7   	D8   	D9 	(led)
; so output value = 0x00020070 = (0b0000 0000  0000 0010  0000 0000  0111 0000)
; 
	ldr	r1, =0x00020070		; show led = 1111	
	ldr	r0, =0x03FF5008
	str	r1, [r0]

; delay for some time
	ldr	r1, =0x0000FFFF
delay2
	sub	r1, r1, #1
	cmp 	r1, #0
	bne	delay2
	
	B	loop
	
	END