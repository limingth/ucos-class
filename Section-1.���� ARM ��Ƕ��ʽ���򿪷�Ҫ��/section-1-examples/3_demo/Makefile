#
#       makefile  --  a simple demo of system bootloader 
#       
#	Author:		li ming <admin@lumit.org>
#	Date:		2005-5-24
#	Copyleft: 	http://www.lumit.org
#

#************************************************************
# system bootloader
all:	
	armasm startup.s -o startup.o
	armcc -c main.c -o main.o 
	armlink startup.o main.o -ro-base 0x0 -entry 0x0 -first startup.o -o l-boot.axf 
	fromelf l-boot.axf -bin -output l-boot.bin
	
#************************************************************
# burn bootloader.bin into flash
jb:
	-lumit-sjf4510-1.1.0.exe l-boot.bin

#************************************************************
# clean up all temp file except source file
clean:	
	-del /F *.o
	-del /F *.axf	
	-del /F *.bin
	-del /F *.bak