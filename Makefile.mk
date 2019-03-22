# name of executable
BUILDNAME = $(notdir $(CURDIR))

# debug path
DEBUGPATH = $(TEMPLATEROOT)/Debug

#Build name files

ELF=$(BUILDNAME).elf  
                
BIN=$(BUILDNAME).bin
HEX=$(BUILDNAME).hex
SYM=$(BUILDNAME).sym
DMP=$(BUILDNAME).dmp

DELF=debug.elf

#Verificar essas flags
#LD_OPTIONS=-nostartfiles -EL --gc-sections
#LDLIBS		+= -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

#Adicionar includes extras tipo heades no src e library em project

#Adicionar memory information

LD_OBJS=$(patsubst %,$(OBJPATH)/%, $(OBJS))

# Library path
LIBROOT = $(TEMPLATEROOT)/STM32F10x_StdPeriph_Lib_V3.5.0
# Tools

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
NM=arm-none-eabi-nm
DP=arm-none-eabi-objdump
# Code Paths

DEVICE=$(LIBROOT)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
CORE=$(LIBROOT)/Libraries/CMSIS/CM3/CoreSupport
PERIPH=$(LIBROOT)/Libraries/STM32F10x_StdPeriph_Driver

# Search path for standard files

vpath %.c $(TEMPLATEROOT)
vpath %.s $(TEMPLATEROOT)
vpath %.c $(SRC)


# Search path for perpheral library

vpath %.c $(CORE)
vpath %.c $(PERIPH)/src
vpath %.c $(DEVICE)

# Search path for Library

vpath %.c $(TEMPLATEROOT)/LibraryDiscovering/ff9/src
vpath %.c $(TEMPLATEROOT)/LibraryDiscovering/ff9/src/option
vpath %.c $(TEMPLATEROOT)/LibraryDiscovering

#  Processor specific
PTYPE = STM32F10X_MD
LDSCRIPT = $(TEMPLATEROOT)/stm32_flash.ld
STARTUP= startup_stm32f10x_md.o system_stm32f10x.o 

# Compilation Flags

FULLASSERT = -DUSE_FULL_ASSERT 
HSE_VALUE = -DHSE_VALUE=8000000L

LDFLAGS+= -T$(LDSCRIPT) -mthumb -mcpu=cortex-m3
LDFLAGS+= --specs=nosys.specs
LDFLAGS+= -Wl,--gc-sections


CFLAGS+= -ggdb -mcpu=cortex-m3 -mthumb 
CFLAGS+= -I$(TEMPLATEROOT) -I$(DEVICE) -I$(CORE) -I$(PERIPH)/inc -I.
CFLAGS+= -D$(PTYPE) -DUSE_STDPERIPH_DRIVER $(FULLASSERT) $(HSE_VALUE)
CFLAGS+= -I$(TEMPLATEROOT)/LibraryDiscovering/ff9/src -I$(TEMPLATEROOT)/LibraryDiscovering
CFLAGS+= -Wall -Wundef -Wredundant-decls #-Wmissing-prototypes


# Build executable 
all : $(ELF) $(BIN) $(HEX) $(SYM)
	cp $(BUILD)/$(BUILDNAME).elf $(DEBUGPATH)/$(DELF) 
	@echo "Done Compiling."
	@python $(TEMPLATEROOT)/Utils/gen_stm32_meminfo.py $(BUILD)/$(SYM)

dump : $(ELF)
	@$(DP) -D $(BUILD)/$< > $(BUILD)/$(BUILDNAME).dmp


$(ELF) : $(LD_OBJS)
	@echo Compiling $@
	@$(LD) $(LDFLAGS) -o $(BUILD)/$@ $(LD_OBJS) $(LDLIBS)


$(BIN): $(ELF)
	@echo Converting to $@
	@$(CP) -Obinary $(BUILD)/$< $(BUILD)/$@
	
$(HEX): $(ELF)
	@echo Converting to $@
	@$(CP) -Oihex $(BUILD)/$< $(BUILD)/$@

$(SYM): $(ELF)
	@$(NM) -g $(BUILD)/$< > $(BUILD)/$@

# compile and generate dependency info

$(OBJPATH)/%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@
	@$(CC) -MM $(CFLAGS) $< > $(OBJPATH)/$*.d

$(OBJPATH)/%.o: %.s
	@$(CC) -c $(CFLAGS) $< -o $@
	@$(CC) -MM $(CFLAGS) $< > $(OBJPATH)/$*.d


flash:
	@echo Writing to flash.
	st-flash write $(BUILD)/$(BIN) 0x8000000

erase:
	@echo Erasing flash.
	st-flash erase

clean:
	@echo Cleaning...
	rm -f $(OBJPATH)/*  $(BUILD)/* $(DEBUGPATH)/*
	@echo Done Cleaning.

debug: $(ELF)
	arm-none-eabi-gdb $(ELF)


# pull in dependencies
-include $(OBJS:.o=.d)




