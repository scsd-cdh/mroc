/*
 * spectrophotometry.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_SPECTROPHOTOMETRY_H_
#define SRC_PERIPHERALS_SPECTROPHOTOMETRY_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    W470NM, W570NM, W630NM, W850NM
} Spec_LightSourceWavelength;

typedef struct
{
    uint16_t measurement;
} Spec_DetectorDescriptor;

typedef struct
{
    bool led_on;
    uint16_t brightness;
    Spec_LightSourceWavelength wavelength;
} Spec_LightSourceDescriptor;

#endif /* SRC_PERIPHERALS_SPECTROPHOTOMETRY_H_ */
