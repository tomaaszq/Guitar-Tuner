################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./ff/ff.obj" \
"./ff/diskio.obj" \
"./tskDecode.obj" \
"./sdcard.obj" \
"./read_samples.obj" \
"./oled.obj" \
"./menu_control.obj" \
"./md_aic3204.obj" \
"./main.obj" \
"./led_blinking.obj" \
"./keys.obj" \
"./decode.obj" \
"./common.obj" \
"./MP3Deccfg_c.obj" \
"./MP3Deccfg.obj" \
"./xdais/src/api/alg_malloc.obj" \
"./xdais/src/api/alg_create.obj" \
"./xdais/src/api/alg_control.obj" \
-l"mp3_tni_rev3.l55l" \
-l"cslVC5515L.lib" \
-l"libc.a" \
"../mp3_link.cmd" \
"../csl/lib/cslVC5515L.lib" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include xdais/src/api/subdir.mk
-include ff/subdir.mk
-include csl/lib/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MP3Dec.out

# Tool invocations
MP3Dec.out: $(GEN_CMDS) $(CMD_SRCS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large -z -m"MP3Dec.map" --warn_sections -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/lib" -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" -i"C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/lib" -i"C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/lib" -i"C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/lib/c5500" -i"C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/lib" --reread_libs --rom_model -o "MP3Dec.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_CMDS__QTD)$(GEN_SRCS__QTD)$(C5500_EXECUTABLE_OUTPUTS__QTD) "MP3Dec.out"
	-$(RM) ".\xdais\src\api\alg_control.obj" ".\xdais\src\api\alg_create.obj" ".\xdais\src\api\alg_malloc.obj" ".\MP3Deccfg.obj" ".\MP3Deccfg_c.obj" ".\common.obj" ".\decode.obj" ".\keys.obj" ".\led_blinking.obj" ".\main.obj" ".\md_aic3204.obj" ".\menu_control.obj" ".\oled.obj" ".\read_samples.obj" ".\sdcard.obj" ".\tskDecode.obj" ".\ff\diskio.obj" ".\ff\ff.obj" 
	-$(RM) ".\MP3Deccfg.pp" 
	-$(RM) ".\xdais\src\api\alg_control.pp" ".\xdais\src\api\alg_create.pp" ".\xdais\src\api\alg_malloc.pp" ".\MP3Deccfg_c.pp" ".\common.pp" ".\decode.pp" ".\keys.pp" ".\led_blinking.pp" ".\main.pp" ".\md_aic3204.pp" ".\menu_control.pp" ".\oled.pp" ".\read_samples.pp" ".\sdcard.pp" ".\tskDecode.pp" ".\ff\diskio.pp" ".\ff\ff.pp" 
	-@echo ' '

post-build:
	-@echo 'Generate FLASH-Image'
	-C:/Program Files (x86)/Texas Instruments/MP3Dec/.burn_image/make_image.bat
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
