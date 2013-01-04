#
#       makefile  --  test led project and show how to use makefile
#       
#	Author:		li ming <admin@lumit.org>
#	Date:		2004-8-17
#	Copyleft: 	http://www.lumit.org
#

#************************************************************
# display a hint of how to make first target
all:
	@echo Hint: you can type "make l0" to build first target

#************************************************************
# compile and link led_0000.s, then convert .axf -> .bin file
l0:
	armasm led_0000.s -o led_0000.o
	armlink -ro-base 0x0 -entry 0x0 led_0000.o -o led_0000.axf 
	fromelf led_0000.axf -bin -output led_0000.bin
	
#************************************************************
# compile and link led_1111.s, then convert .axf -> .bin file
l1:	
	armasm led_1111.s -o led_1111.o
	armlink -ro-base 0x0 -entry 0x0 led_1111.o -o led_1111.axf 
	fromelf led_1111.axf -bin -output led_1111.bin

#************************************************************
# compile and link led_blink.s, then convert .axf -> .bin file	
lb:	
	armasm led_blink.s -o led_blink.o
	armlink -ro-base 0x0 -entry 0x0 led_blink.o -o led_blink.axf 
	fromelf led_blink.axf -bin -output led_blink.bin
	
#************************************************************
# burn led_0000.bin into flash
j0:
	-lumit-sjf4510-1.1.0.exe led_0000.bin

#************************************************************
# burn led_1111.bin into flash
j1:
	-lumit-sjf4510-1.1.0.exe led_1111.bin


#************************************************************
# burn led_blink.bin into flash
jb:
	-lumit-sjf4510-1.1.0.exe led_blink.bin

#************************************************************
# clean up all temp file except source file
clean:	
	-del /F *.o
	-del /F *.axf	
	-del /F *.bin
	-del /F *.bak
