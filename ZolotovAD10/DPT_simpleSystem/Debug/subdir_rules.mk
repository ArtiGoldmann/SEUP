################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv7/tools/compiler/c2000_6.2.0/include" --include_path="C:/Users/User/OneDrive/Documents/GitRep/MPEI/SUEP/ZolotovAD10/DPT_simpleSystem/include" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


