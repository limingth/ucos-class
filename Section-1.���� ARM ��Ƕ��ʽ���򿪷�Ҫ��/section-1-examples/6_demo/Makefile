#
#       makefile   -    a simple demo of arm develop
#       
#	Author:		li ming <admin@lumit.org>
#	Date:		2005-6-3
#	Copyleft: 	http://www.lumit.org
#

PRJ = demo_6

OUTPUT_DIR = debug

OBJS = $(OUTPUT_DIR)\main.o

AXF = $(OUTPUT_DIR)\$(PRJ).axf
BIN = $(OUTPUT_DIR)\$(PRJ).bin
LST = $(OUTPUT_DIR)\$(PRJ).lst
UUE = $(OUTPUT_DIR)\$(PRJ).uue

all: $(BIN) $(UUE) 
	dir $(BIN)
	
.SUFFIXES: .s .c
.s{$(OUTPUT_DIR)}.o:	
	@echo + compiling s file ... $<
	armasm -g $< -o $@ 
	@echo ------------------------------------------------------

.c{$(OUTPUT_DIR)}.o:
	@echo + compiling c file ... $<
	armcc -O0 -g+ -c $< -o $@
	@echo ------------------------------------------------------

$(AXF): $(OBJS) Makefile
	@echo + linking o file ... $(OBJS)
	armlink $(OBJS) -ro-base 0x8000 -entry __main -o $(AXF)
	@echo ------------------------------------------------------

$(BIN): $(AXF) 
	@echo + fromelf axf file ... $(AXF)
	fromelf -bin -output $(BIN) $(AXF)
	fromelf -c -d -s -t -z -o $(LST) $(AXF)
	@echo ------------------------------------------------------
	
$(UUE): $(BIN)
	@echo + uuencode bin file ... $(BIN)
	uuencode $(BIN) $(UUE)
	@echo ------------------------------------------------------

c clean:
	@echo + deleting all files ... 	
	-del $(OBJS)
	-del $(AXF) $(BIN) $(UUE)
	@echo ------------------------------------------------------
