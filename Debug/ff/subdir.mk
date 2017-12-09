################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ff/diskio.c \
../ff/ff.c 

OBJS += \
./ff/diskio.obj \
./ff/ff.obj 

C_DEPS += \
./ff/diskio.pp \
./ff/ff.pp 

OBJS__QTD += \
".\ff\diskio.obj" \
".\ff\ff.obj" 

C_DEPS__QTD += \
".\ff\diskio.pp" \
".\ff\ff.pp" 

C_SRCS_QUOTED += \
"../ff/diskio.c" \
"../ff/ff.c" 


# Each subdirectory must supply rules for building sources it contributes
ff/diskio.obj: ../ff/diskio.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="ff/diskio.pp" --obj_directory="ff" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ff/ff.obj: ../ff/ff.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="ff/ff.pp" --obj_directory="ff" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


