###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = 80C52
COMPILER = "Keil for 8051"
TARGET = Debug
SHELL = C:\Windows\system32\cmd.exe

## Tools general options
CCFLAGS=ROM(SMALL) BROWSE DEBUG CODE OBJECTEXTEND PREPRINT

## Processing Tools
CC=C51.exe
LD=BL51.exe
ASM=A51.exe
#  D:/HQ USER/MY/倒计时钟(STC89C52RC单片机+旋转编码器+TM1637/80C52_1/Debug/Debug.OMF: TOOL=LD
#     D:/HQ USER/MY/倒计时钟(STC89C52RC单片机+旋转编码器+TM1637/80C52_1/Debug/main.OBJ: TOOL=CC
#        D:/HQ USER/MY/倒计时钟(STC89C52RC单片机+旋转编码器+TM1637/80C52_1/main.c

# Build tree:
all:	Debug

Debug:	Debug.OMF

Debug.OMF:	main.OBJ 
	"..\..\..\..\..\Program Files (x86)\Labcenter Electronics\Proteus 8 Professional\Tools\MAKE\RunTool.exe" --good-exits=0,1 --executable=$(LD) "main.OBJ" TO "Debug.OMF" $(LDFLAGS) 

main.OBJ:	../main.c 
	"..\..\..\..\..\Program Files (x86)\Labcenter Electronics\Proteus 8 Professional\Tools\MAKE\RunTool.exe" --good-exits=0,1 --executable=$(CC) "..\main.c" $(CCFLAGS)  OBJECT("main.OBJ")

# tidy - delete all temporary files which are not involved in the target generation
tidy:
	rm -rf Debug.M51
	rm -rf ./main.lst
	rm -rf ./main.I

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.OMF
	rm -rf main.OBJ
