#include <src/drivers/drivers.h>
#include "hk_condition.h"

static volatile uint16_t powerSupplySense;
static volatile uint16_t bipumpSense;
static volatile uint16_t heaterSense;

void HK_ConditionInit(Hk_ConditionDescriptor* descriptor) {

    // Power supply sense
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN2,
        GPIO_TERNARY_MODULE_FUNCTION
    );

    // Heater sense
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN3,
        GPIO_TERNARY_MODULE_FUNCTION
    );

    // Bipump sense
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P9,
        GPIO_PIN0,
        GPIO_TERNARY_MODULE_FUNCTION
    );

    ADC12_B_initParam initParam = {0};
    initParam.sampleHoldSignalSourceSelect =    ADC12_B_SAMPLEHOLDSOURCE_SC;
    initParam.clockSourceSelect =               ADC12_B_CLOCKSOURCE_ADC12OSC;
    initParam.clockSourceDivider =              ADC12_B_CLOCKDIVIDER_1;
    initParam.clockSourcePredivider =           ADC12_B_CLOCKPREDIVIDER__1;
    initParam.internalChannelMap =              ADC12_B_NOINTCH;
    ADC12_B_init(ADC12_B_BASE, &initParam);
    ADC12_B_enable(ADC12_B_BASE);

    ADC12_B_setupSamplingTimer(ADC12_B_BASE,
          ADC12_B_CYCLEHOLD_16_CYCLES,
          ADC12_B_CYCLEHOLD_4_CYCLES,
          ADC12_B_MULTIPLESAMPLESDISABLE);

    ADC12_B_configureMemoryParam powerSupplyMemoryParam = {0};
    powerSupplyMemoryParam.memoryBufferControlIndex =     ADC12_B_MEMORY_0;
    powerSupplyMemoryParam.inputSourceSelect =            ADC12_B_INPUT_A2;
    powerSupplyMemoryParam.refVoltageSourceSelect =       ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
    powerSupplyMemoryParam.endOfSequence =                ADC12_B_NOTENDOFSEQUENCE;
    powerSupplyMemoryParam.windowComparatorSelect =       ADC12_B_WINDOW_COMPARATOR_DISABLE;
    powerSupplyMemoryParam.differentialModeSelect =       ADC12_B_DIFFERENTIAL_MODE_DISABLE;

    ADC12_B_configureMemoryParam heaterSupplyMemoryParam = {0};
    heaterSupplyMemoryParam.memoryBufferControlIndex =     ADC12_B_MEMORY_1;
    heaterSupplyMemoryParam.inputSourceSelect =            ADC12_B_INPUT_A3;
    heaterSupplyMemoryParam.refVoltageSourceSelect =       ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
    heaterSupplyMemoryParam.endOfSequence =                ADC12_B_NOTENDOFSEQUENCE;
    heaterSupplyMemoryParam.windowComparatorSelect =       ADC12_B_WINDOW_COMPARATOR_DISABLE;
    heaterSupplyMemoryParam.differentialModeSelect =       ADC12_B_DIFFERENTIAL_MODE_DISABLE;

    ADC12_B_configureMemoryParam pumpSupplyMemoryParam = {0};
    pumpSupplyMemoryParam.memoryBufferControlIndex =     ADC12_B_MEMORY_2;
    pumpSupplyMemoryParam.inputSourceSelect =            ADC12_B_INPUT_A8;
    pumpSupplyMemoryParam.refVoltageSourceSelect =       ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
    pumpSupplyMemoryParam.endOfSequence =                ADC12_B_NOTENDOFSEQUENCE;
    pumpSupplyMemoryParam.windowComparatorSelect =       ADC12_B_WINDOW_COMPARATOR_DISABLE;
    pumpSupplyMemoryParam.differentialModeSelect =       ADC12_B_DIFFERENTIAL_MODE_DISABLE;


    ADC12_B_configureMemory(ADC12_B_BASE, &powerSupplyMemoryParam);
    ADC12_B_configureMemory(ADC12_B_BASE, &heaterSupplyMemoryParam);
    ADC12_B_configureMemory(ADC12_B_BASE, &pumpSupplyMemoryParam);
    ADC12_B_clearInterrupt(ADC12_B_BASE, 0, ADC12_B_IFG0);
    ADC12_B_enableInterrupt(ADC12_B_BASE, ADC12_B_IE0, 0, 0);

    descriptor->voltage_reference_current_sensing = 0;
    descriptor->pump_current_sensing = 0;
    descriptor->heater_current_sensing = 0;
}

void HK_Update() {
    ADC12_B_startConversion(ADC12_B_BASE, ADC12_B_MEMORY_0, ADC12_B_SINGLECHANNEL);
    ADC12_B_startConversion(ADC12_B_BASE, ADC12_B_MEMORY_1, ADC12_B_SINGLECHANNEL);
    ADC12_B_startConversion(ADC12_B_BASE, ADC12_B_MEMORY_2, ADC12_B_SINGLECHANNEL);
}

void HK_Read(Hk_ConditionDescriptor* descriptor) {
    descriptor->voltage_reference_current_sensing = powerSupplySense;
    descriptor->pump_current_sensing = bipumpSense;
    descriptor->heater_current_sensing = heaterSense;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC12_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(ADC12_VECTOR)))
#endif
void ADC12_ISR(void)
{
    switch(__even_in_range(ADC12IV,12))
    {
        case 12:                                 // Vector 12: ADC12BMEM0
            powerSupplySense = ADC12_B_getResults(ADC12_B_BASE, ADC12_B_MEMORY_0);
            break;
        case 14:                                 // Vector 14: ADC12BMEM1
            heaterSense = ADC12_B_getResults(ADC12_B_BASE, ADC12_B_MEMORY_1);
            break;
        case 16:                                 // Vector 16: ADC12BMEM2
            bipumpSense = ADC12_B_getResults(ADC12_B_BASE, ADC12_B_MEMORY_2);
            break;
        case 18: break;                          // Vector 18: ADC12BMEM3
        default: break;
    }
}

