################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../common.c \
../decode.c \
../keys.c \
../led_blinking.c \
../main.c \
../md_aic3204.c \
../menu_control.c \
../oled.c \
../read_samples.c \
../sdcard.c \
../tskDecode.c 

TCF_SRCS += \
../MP3Dec.tcf 

CMD_SRCS += \
../mp3_link.cmd 

GEN_SRCS += \
./MP3Deccfg.cmd \
./MP3Deccfg.s?? \
./MP3Deccfg_c.c 

GEN_CMDS += \
./MP3Deccfg.cmd 

OBJS += \
./MP3Deccfg.obj \
./MP3Deccfg_c.obj \
./common.obj \
./decode.obj \
./keys.obj \
./led_blinking.obj \
./main.obj \
./md_aic3204.obj \
./menu_control.obj \
./oled.obj \
./read_samples.obj \
./sdcard.obj \
./tskDecode.obj 

S??_DEPS += \
./MP3Deccfg.pp 

C_DEPS += \
./MP3Deccfg_c.pp \
./common.pp \
./decode.pp \
./keys.pp \
./led_blinking.pp \
./main.pp \
./md_aic3204.pp \
./menu_control.pp \
./oled.pp \
./read_samples.pp \
./sdcard.pp \
./tskDecode.pp 

OBJS__QTD += \
".\MP3Deccfg.obj" \
".\MP3Deccfg_c.obj" \
".\common.obj" \
".\decode.obj" \
".\keys.obj" \
".\led_blinking.obj" \
".\main.obj" \
".\md_aic3204.obj" \
".\menu_control.obj" \
".\oled.obj" \
".\read_samples.obj" \
".\sdcard.obj" \
".\tskDecode.obj" 

S??_DEPS__QTD += \
".\MP3Deccfg.pp" 

GEN_SRCS__QTD += \
".\MP3Deccfg.cmd" \
".\MP3Deccfg.s??" \
".\MP3Deccfg_c.c" 

C_DEPS__QTD += \
".\MP3Deccfg_c.pp" \
".\common.pp" \
".\decode.pp" \
".\keys.pp" \
".\led_blinking.pp" \
".\main.pp" \
".\md_aic3204.pp" \
".\menu_control.pp" \
".\oled.pp" \
".\read_samples.pp" \
".\sdcard.pp" \
".\tskDecode.pp" 

TCF_SRCS_QUOTED += \
"../MP3Dec.tcf" 

GEN_CMDS_QUOTED += \
-l"./MP3Deccfg.cmd" 

C_SRCS_QUOTED += \
"../common.c" \
"../decode.c" \
"../keys.c" \
"../led_blinking.c" \
"../main.c" \
"../md_aic3204.c" \
"../menu_control.c" \
"../oled.c" \
"../read_samples.c" \
"../sdcard.c" \
"../tskDecode.c" 


# Each subdirectory must supply rules for building sources it contributes
MP3Deccfg.cmd: ../MP3Dec.tcf
	@echo 'Building file: $<'
	@echo 'Invoking: TConf Script Compiler'
	"C:/Program Files (x86)/Texas Instruments/xdctools_3_16_02_32/tconf" -b -Dconfig.importPath="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages;" "$<"
	@echo 'Finished building: $<'
	@echo ' '

MP3Deccfg.s??: MP3Deccfg.cmd
MP3Deccfg_c.c: MP3Deccfg.cmd

MP3Deccfg.obj: ./MP3Deccfg.s?? $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="MP3Deccfg.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

MP3Deccfg_c.obj: ./MP3Deccfg_c.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="MP3Deccfg_c.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

common.obj: ../common.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="common.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

decode.obj: ../decode.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="decode.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

keys.obj: ../keys.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="keys.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

led_blinking.obj: ../led_blinking.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="led_blinking.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

md_aic3204.obj: ../md_aic3204.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="md_aic3204.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

menu_control.obj: ../menu_control.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="menu_control.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

oled.obj: ../oled.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="oled.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

read_samples.obj: ../read_samples.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="read_samples.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

sdcard.obj: ../sdcard.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="sdcard.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

tskDecode.obj: ../tskDecode.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="tskDecode.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


