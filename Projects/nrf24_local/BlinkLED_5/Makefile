TEMPLATEROOT = ../..

#Build folder
BUILD = 	./build
SRC = 		./src
OBJPATH = 		./obj

# compilation flags for gdb

CFLAGS  = -O1 -g
ASFLAGS = -g 

# object files

OBJS = $(STARTUP)

OBJS += BlinkLED_4.o
OBJS += stm32f10x_gpio.o stm32f10x_rcc.o time_stm32.o

# include common make file

include $(TEMPLATEROOT)/Makefile.mk


