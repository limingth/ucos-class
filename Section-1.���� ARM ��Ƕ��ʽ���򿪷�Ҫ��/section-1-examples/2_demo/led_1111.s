;
;       led_0000.s  --  turn on  leds (set value 1111 to four led gpio )
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
	
; 
; hardware connection
; IO17 	IO04 	IO05 	IO06	(gpio)
; D6   	D7   	D8   	D9 	(led)
; so output value = 0x00020070 = (0b0000 0000  0000 0010  0000 0000  0111 0000)
; 

	ldr	r1, =0x00020070		; show led = 1111	
loop
	ldr	r0, =0x03FF5008
	str	r1, [r0]

	B	loop
	
	END