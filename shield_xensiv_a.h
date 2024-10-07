/******************************************************************************
 * \file shield_xensiv_a.h
 *
 * Description: This file is the top level interface for the SHIELD_XENSIV_A
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

#include "shield_xensiv_a_pins.h"
#include "cyhal.h"
#include "mtb_sht3x.h"
#include "mtb_bmi270.h"
#include "mtb_bmm350.h"
#include "xensiv_dps3xx_mtb.h"
#include "mtb_st7735s.h"
#include "cyhal_pdmpcm.h"
#include "xensiv_pasco2_mtb.h"

#if defined(__cplusplus)
extern "C"
{
#endif


/******************************************************************************
* Function Name: shield_xensiv_a_init
******************************************************************************
* Summary: Initializes the shield board and all peripherals present on it.
*          The initialization of all the sensors takes 3 seconds, as it
*          includes a waiting period for the CO2 sensor to become ready.
*
* Parameters:
*  i2c_instance      An optional I2C instance to use for communicating with
*                    the sensors on the shield. If NULL, a new instance will
*                    be allocated internally
*  spi_instance      An optional SPI instance to use for communicating with
*                    the display and sensors on the shield. If NULL, a new
*                    instance will be allocated internally
*  pdm_pcm_cfg       Configuration for the PDM object used with the microphone
*  audio_clock_inst  Audio clock used with the microphone
*
* Return:
*  Status of initialization
*
******************************************************************************/
cy_rslt_t shield_xensiv_a_init(cyhal_i2c_t* i2c_instance,
                               cyhal_spi_t* spi_instance,
                               const cyhal_pdm_pcm_cfg_t* pdm_pcm_cfg,
                               cyhal_clock_t* audio_clock_inst);



/******************************************************************************
* Function Name: shield_xensiv_a_get_humidity_sensor
******************************************************************************
* Summary: Gives the user access to the I2C object used for the humidity sensor.
*
* Parameters: None
*
* Return:
*  A reference to the I2C object used for the humidity sensor.
*
******************************************************************************/
cyhal_i2c_t* shield_xensiv_a_get_humidity_sensor(void);



/******************************************************************************
* Function Name: shield_xensiv_a_get_motion_sensor
******************************************************************************
* Summary: Gives the user access to the BMI270 motion sensor object.
*
* Parameters: None
*
* Return:
*  A reference to the motion sensor object on the shield
*
******************************************************************************/
mtb_bmi270_t* shield_xensiv_a_get_motion_sensor(void);



/******************************************************************************
* Function Name: shield_xensiv_a_get_mag_sensor
******************************************************************************
* Summary: Gives the user access to the BMM350 magnetometer sensor object.
*
* Parameters: None
*
* Return:
*  A reference to the magnetometer sensor object on the shield
*
******************************************************************************/
mtb_bmm350_t* shield_xensiv_a_get_mag_sensor(void);



/******************************************************************************
* Function Name: shield_xensiv_a_get_pressure_sensor
******************************************************************************
* Summary: Gives the user access to the DPS368 pressure sensor object
*
* Parameters: None
*
* Return:
*  A reference to the pressure sensor object on the shield
*
******************************************************************************/
xensiv_dps3xx_t* shield_xensiv_a_get_pressure_sensor(void);



/******************************************************************************
* Function Name: shield_xensiv_a_get_pdm
******************************************************************************
* Summary: Gives the user access to the PDM object used with the microphone.
*          This will return null if the arguments to setup the PDM interface
*          were not provided.
*
* Parameters: None
*
* Return: A reference to the PDM microphone object on the shield
*
******************************************************************************/
cyhal_pdm_pcm_t* shield_xensiv_a_get_pdm(void);



/******************************************************************************
* Function Name: shield_xensiv_a_get_co2_sensor
******************************************************************************
* Summary: Gives the user access to the PAS CO2 sensor object.
*
* Parameters: None
*
* Return:
*  A reference to the CO2 sensor object on the shield
*
******************************************************************************/
xensiv_pasco2_t* shield_xensiv_a_get_co2_sensor(void);



/******************************************************************************
* Function Name: shield_xensiv_a_free
******************************************************************************
* Summary: Frees up any resources allocated by shield_xensiv_a_init()
*
* Parameters: None
*
* Return: None
*
******************************************************************************/
void shield_xensiv_a_free(void);

#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
