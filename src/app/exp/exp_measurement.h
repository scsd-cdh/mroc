/*
 * exp_measurement.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_APP_EXP_EXP_MEASUREMENT_H_
#define SRC_APP_EXP_EXP_MEASUREMENT_H_

#include <src/peripherals/spectrophotometry.h>

typedef struct
{
    Spec_DetectorDescriptor detector;
    Spec_LightSourceDescriptor light_source;
} Exp_MeasurementDescriptor;

#endif /* SRC_APP_EXP_EXP_MEASUREMENT_H_ */
