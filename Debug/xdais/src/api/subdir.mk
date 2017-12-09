################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xdais/src/api/alg_control.c \
../xdais/src/api/alg_create.c \
../xdais/src/api/alg_malloc.c 

OBJS += \
./xdais/src/api/alg_control.obj \
./xdais/src/api/alg_create.obj \
./xdais/src/api/alg_malloc.obj 

C_DEPS += \
./xdais/src/api/alg_control.pp \
./xdais/src/api/alg_create.pp \
./xdais/src/api/alg_malloc.pp 

OBJS__QTD += \
".\xdais\src\api\alg_control.obj" \
".\xdais\src\api\alg_create.obj" \
".\xdais\src\api\alg_malloc.obj" 

C_DEPS__QTD += \
".\xdais\src\api\alg_control.pp" \
".\xdais\src\api\alg_create.pp" \
".\xdais\src\api\alg_malloc.pp" 

C_SRCS_QUOTED += \
"../xdais/src/api/alg_control.c" \
"../xdais/src/api/alg_create.c" \
"../xdais/src/api/alg_malloc.c" 


# Each subdirectory must supply rules for building sources it contributes
xdais/src/api/alg_control.obj: ../xdais/src/api/alg_control.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="xdais/src/api/alg_control.pp" --obj_directory="xdais/src/api" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

xdais/src/api/alg_create.obj: ../xdais/src/api/alg_create.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="xdais/src/api/alg_create.pp" --obj_directory="xdais/src/api" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

xdais/src/api/alg_malloc.obj: ../xdais/src/api/alg_malloc.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/C5500 Code Generation Tools 4.3.9/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/xdais/src/api" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/decoder/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/ff" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/csl/include" --include_path="C:/Program Files (x86)/Texas Instruments/MP3Dec/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_02_14/packages/ti/rtdx/include/c5500" --diag_warning=225 --large_memory_model --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="xdais/src/api/alg_malloc.pp" --obj_directory="xdais/src/api" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


