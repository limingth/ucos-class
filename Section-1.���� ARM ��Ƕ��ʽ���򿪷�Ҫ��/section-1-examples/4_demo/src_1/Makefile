#
#       makefile  --  a simple demo of system bootloader 
#       
#	Author:		li ming <admin@lumit.org>
#	Date:		2005-5-24
#	Copyleft: 	http://www.lumit.org
#

PRJ = demo_printf

OUTPUT_DIR = debug

START_OBJ = startup.o
OBJS = $(OUTPUT_DIR)\startup.o $(OUTPUT_DIR)\uart.o $(OUTPUT_DIR)\main.o

AXF = $(OUTPUT_DIR)\$(PRJ).axf
BIN = $(OUTPUT_DIR)\$(PRJ).bin
LST = $(OUTPUT_DIR)\$(PRJ).lst

all: $(BIN)
	dir $(BIN)
	
jf: $(BIN)
	-lumit-sjf4510-1.1.0.exe $(BIN)
		
.SUFFIXES: .s .c
.s{$(OUTPUT_DIR)}.o:	
	@echo + compiling s file ... $<
	armasm -g $< -o $@ 
	@echo ------------------------------------------------------

.c{$(OUTPUT_DIR)}.o:
	@echo + compiling c file ... $<
	armcc -O1 -g+ -c $< -o $@
	@echo ------------------------------------------------------

$(AXF): $(OBJS)
	@echo + linking o file ... $(OBJS)
	armlink $(OBJS) -ro-base 0x8000 -first $(START_OBJ) -o $(AXF)
	@echo ------------------------------------------------------

$(BIN): $(AXF) 
	@echo + fromelf axf file ... $(AXF)
	fromelf -c -bin -output $(BIN) $(AXF)
	fromelf -c -d -o $(LST) $(AXF)
	@echo ------------------------------------------------------
	
c clean:
	@echo + deleting all files ... 	
	-del $(OBJS)
	-del $(AXF) $(BIN) $(UUE)
	@echo ------------------------------------------------------
