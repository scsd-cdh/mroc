################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./extern/bme280.obj" \
"./src/app/app.obj" \
"./src/app/cmd/cmd_handler.obj" \
"./src/app/cmd/cmd_register.obj" \
"./src/app/exp/exp_instrument.obj" \
"./src/app/exp/exp_state_manager.obj" \
"./src/drivers/adc12_b.obj" \
"./src/drivers/cs.obj" \
"./src/drivers/eusci_a_spi.obj" \
"./src/drivers/eusci_b_i2c.obj" \
"./src/drivers/gpio.obj" \
"./src/drivers/pmm.obj" \
"./src/drivers/rtc_b.obj" \
"./src/drivers/rtc_c.obj" \
"./src/drivers/swi2c.obj" \
"./src/drivers/swi2c_master.obj" \
"./src/drivers/wdt_a.obj" \
"./src/main.obj" \
"./src/peripherals/bipump.obj" \
"./src/peripherals/bme280.obj" \
"./src/peripherals/heater.obj" \
"./src/peripherals/lmt01.obj" \
"./src/peripherals/mpq3326.obj" \
"./src/peripherals/opt4003.obj" \
"./src/peripherals/pump.obj" \
"./src/peripherals/valve.obj" \
"../lnk_msp430fr5989.cmd" \
$(GEN_CMDS__FLAG) \
-llibmpu_init.a \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include extern/subdir_vars.mk
-include src/app/subdir_vars.mk
-include src/app/cmd/subdir_vars.mk
-include src/app/exp/subdir_vars.mk
-include src/drivers/subdir_vars.mk
-include src/subdir_vars.mk
-include src/peripherals/subdir_vars.mk
-include subdir_rules.mk
-include extern/subdir_rules.mk
-include src/app/subdir_rules.mk
-include src/app/cmd/subdir_rules.mk
-include src/app/exp/subdir_rules.mk
-include src/drivers/subdir_rules.mk
-include src/subdir_rules.mk
-include src/peripherals/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
mroc.out 

EXE_OUTPUTS__QUOTED += \
"mroc.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "mroc.out"

# Tool invocations
mroc.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --advice:power=all --advice:hw_config=all --define=__MSP430FR5989__ --define=_MPU_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 -z -m"mroc.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"C:/ti/ccs1260/ccs/ccs_base/msp430/include" -i"C:/ti/ccs1260/ccs/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/ti/ccs1260/ccs/ccs_base/msp430/lib/FR59xx" -i"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/lib" -i"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --priority --reread_libs --define=_MPU_ENABLE --diag_wrap=off --display_error_number --warn_sections --xml_link_info="mroc_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "mroc.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "extern\bme280.obj" "src\app\app.obj" "src\app\cmd\cmd_handler.obj" "src\app\cmd\cmd_register.obj" "src\app\exp\exp_instrument.obj" "src\app\exp\exp_state_manager.obj" "src\drivers\adc12_b.obj" "src\drivers\cs.obj" "src\drivers\eusci_a_spi.obj" "src\drivers\eusci_b_i2c.obj" "src\drivers\gpio.obj" "src\drivers\pmm.obj" "src\drivers\rtc_b.obj" "src\drivers\rtc_c.obj" "src\drivers\swi2c.obj" "src\drivers\swi2c_master.obj" "src\drivers\wdt_a.obj" "src\main.obj" "src\peripherals\bipump.obj" "src\peripherals\bme280.obj" "src\peripherals\heater.obj" "src\peripherals\lmt01.obj" "src\peripherals\mpq3326.obj" "src\peripherals\opt4003.obj" "src\peripherals\pump.obj" "src\peripherals\valve.obj" 
	-$(RM) "extern\bme280.d" "src\app\app.d" "src\app\cmd\cmd_handler.d" "src\app\cmd\cmd_register.d" "src\app\exp\exp_instrument.d" "src\app\exp\exp_state_manager.d" "src\drivers\adc12_b.d" "src\drivers\cs.d" "src\drivers\eusci_a_spi.d" "src\drivers\eusci_b_i2c.d" "src\drivers\gpio.d" "src\drivers\pmm.d" "src\drivers\rtc_b.d" "src\drivers\rtc_c.d" "src\drivers\swi2c.d" "src\drivers\swi2c_master.d" "src\drivers\wdt_a.d" "src\main.d" "src\peripherals\bipump.d" "src\peripherals\bme280.d" "src\peripherals\heater.d" "src\peripherals\lmt01.d" "src\peripherals\mpq3326.d" "src\peripherals\opt4003.d" "src\peripherals\pump.d" "src\peripherals\valve.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

