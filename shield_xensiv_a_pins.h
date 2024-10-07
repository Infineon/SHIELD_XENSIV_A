/******************************************************************************
 * \file shield_xensiv_a_pins.h
 *
 * Description: This file contains the pin definitions for the SHIELD_XENSIV_A
 *              shield board.
 *
 ******************************************************************************
 ******************************************************************************
 * \copyright
 * Copyright 2024 Cypress Semiconductor Corporation
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include "cybsp.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** Humidity, Orientation, Magnetometer, Pressure,
 * CO2 Sensor I2C pins
 */

/** Pin for the shared I2C SCL signal */
#define SHIELD_XENSIV_A_PIN_I2C_SCL         (CYBSP_I2C_SCL)
/** Pin for the shared I2C SDA signal */
#define SHIELD_XENSIV_A_PIN_I2C_SDA         (CYBSP_I2C_SDA)

/** TFT display, Radar sensor SPI pins */
/** Pin for the SPI SCK signal */
#define SHIELD_XENSIV_A_PIN_SPI_SCK         (CYBSP_SPI_CLK)
/** Pin for the SPI MISO signal */
#define SHIELD_XENSIV_A_PIN_SPI_MISO        (CYBSP_SPI_MISO)
/** Pin for the SPI MOSI signal */
#define SHIELD_XENSIV_A_PIN_SPI_MOSI        (CYBSP_SPI_MOSI)
/** Pin for the SPI CS signal */
#define SHIELD_XENSIV_A_PIN_SPI_CS          (CYBSP_SPI_CS)
/** Pin for the SPI CS selection signal */
#define SHIELD_XENSIV_A_PIN_SPI_CS_SEL0     (CYBSP_D9)

/** Pin for the sensor interrupt signals */
#define SHIELD_XENSIV_A_PIN_SEN_INT         (CYBSP_D7)

/** Radar Sensor pins */
/** Pin for the radar sensor selection signal */
#define SHIELD_XENSIV_A_PIN_RADAR_SEL       (CYBSP_D6)
/** Pin for the radar GPIO1 or P_DET signal */
#define SHIELD_XENSIV_A_PIN_RADAR_GPIO1     (CYBSP_D5)
/** Pin for the radar GPIO2 or T_DET signal */
#define SHIELD_XENSIV_A_PIN_RADAR_GPIO2     (CYBSP_D4)
/** Pin for the radar shield open drain LED signal */
#define SHIELD_XENSIV_A_PIN_RS_OD_LED       (CYBSP_J2_12)
/** Pin for the radar ADC1 signal */
#define SHIELD_XENSIV_A_PIN_RADAR_ADC1      (CYBSP_J2_2)
/** Pin for the radar ADC2 signal */
#define SHIELD_XENSIV_A_PIN_RADAR_ADC2      (CYBSP_J2_4)
/** Pin for the radar reset signal */
#define SHIELD_XENSIV_A_PIN_RADAR_RST       (CYBSP_A2)
/** Pin for the radar interrupt signal */
#define SHIELD_XENSIV_A_PIN_RADAR_INT       (CYBSP_A1)

/** Pin for the main reset signal */
#define SHIELD_XENSIV_A_PIN_MAIN_RST        (CYBSP_D2)

/** Pin for the magnetometer sensor interrupt signal */
#define SHIELD_XENSIV_A_PIN_MAG_INT         (CYBSP_J2_10)
/** Pin for the motion sensor interrupt 1 signal */
#define SHIELD_XENSIV_A_PIN_IMU_INT_1       (CYBSP_J2_6)
/** Pin for the motion sensor interrupt 2 signal */
#define SHIELD_XENSIV_A_PIN_IMU_INT_2       (CYBSP_J2_8)

/** PDM Microphone pins */
/** Pin for the PDM Data */
#define SHIELD_XENSIV_A_PIN_PDM_DATA        (CYBSP_A5)
/** Pin for the PDM Clock */
#define SHIELD_XENSIV_A_PIN_PDM_CLK         (CYBSP_A4)

/** Pin for the PAS CO2 power enable signal */
#define SHIELD_XENSIV_A_PIN_CO2_PWR_EN      (CYBSP_A3)

/** Pin for the TFT display command signal */
#define SHIELD_XENSIV_A_PIN_SPI_DC_DS       (CYBSP_A0)

/** \} group_board_libs_pins */

#if defined(__cplusplus)
}
#endif

/* [] END OF FILE */
