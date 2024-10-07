/******************************************************************************
 * \file shield_xensiv_a.c
 *
 * Description: Implementation file of the shield support library.
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


#include "shield_xensiv_a.h"
#ifdef EMWIN_ENABLED
#include "GUI.h"
#include "LCDConf.h"
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

/******************************************************************************
* Macros
******************************************************************************/
/* SPI baud rate in Hz */
#define SPI_FREQ_HZ                (1200000UL)
/* SPI transfer bits per frame */
#define BITS_PER_FRAME             (8)

/******************************************************************************
* Global variables
******************************************************************************/
typedef enum
{
    _SHIELD_XENSIV_A_INITIALIZED_NONE             = 0x00,
    _SHIELD_XENSIV_A_INITIALIZED_HUMIDITY         = 0x01,
    _SHIELD_XENSIV_A_INITIALIZED_MOTION           = 0x02,
    _SHIELD_XENSIV_A_INITIALIZED_MAGNETOMETER     = 0x04,
    _SHIELD_XENSIV_A_INITIALIZED_PRESSURE         = 0x08,
    _SHIELD_XENSIV_A_INITIALIZED_PDM              = 0x10,
    _SHIELD_XENSIV_A_INITIALIZED_DISPLAY          = 0x20
} shield_xensiv_a_initialized_t;

static cyhal_i2c_t                      _shield_i2c;
static cyhal_spi_t                      _shield_spi;
static cyhal_pdm_pcm_t                  _shield_pdm_pcm;
static cyhal_i2c_t*                     _shield_i2c_ptr;
static cyhal_spi_t*                     _shield_spi_ptr;
static mtb_bmi270_t                     motion_sensor;
static mtb_bmm350_t                     mag_sensor;
static xensiv_dps3xx_t                  pressure_sensor;
static xensiv_pasco2_t                  co2_sensor;
static shield_xensiv_a_initialized_t    _shield_initialized = _SHIELD_XENSIV_A_INITIALIZED_NONE;

const mtb_st7735s_pins_t tft_pins =
{
    .dc       = SHIELD_XENSIV_A_PIN_SPI_DC_DS,
    .rst      = SHIELD_XENSIV_A_PIN_MAIN_RST
};


/******************************************************************************
* shield_xensiv_a_init
******************************************************************************/
cy_rslt_t shield_xensiv_a_init(cyhal_i2c_t* i2c_instance,
                               cyhal_spi_t* spi_instance,
                               const cyhal_pdm_pcm_cfg_t* pdm_pcm_cfg,
                               cyhal_clock_t* audio_clock_inst)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    if (NULL == i2c_instance)
    {
        static const cyhal_i2c_cfg_t i2c_cfg =
        {
            .is_slave        = false,
            .address         = 0,
            .frequencyhal_hz = 400000
        };
        result = cyhal_i2c_init(&_shield_i2c, SHIELD_XENSIV_A_PIN_I2C_SDA,
                                SHIELD_XENSIV_A_PIN_I2C_SCL, NULL);
        if (CY_RSLT_SUCCESS == result)
        {
            _shield_i2c_ptr = &_shield_i2c;
            result  = cyhal_i2c_configure(&_shield_i2c, &i2c_cfg);
        }
    }
    else
    {
        _shield_i2c_ptr = i2c_instance;
    }

    if (CY_RSLT_SUCCESS == result)
    {
        if (NULL == spi_instance)
        {
            result = cyhal_spi_init(&_shield_spi, SHIELD_XENSIV_A_PIN_SPI_MOSI,
                                    SHIELD_XENSIV_A_PIN_SPI_MISO,
                                    SHIELD_XENSIV_A_PIN_SPI_SCK,
                                    SHIELD_XENSIV_A_PIN_SPI_CS,
                                    NULL, BITS_PER_FRAME,
                                    CYHAL_SPI_MODE_00_MSB, false);
            if (CY_RSLT_SUCCESS == result)
            {
                _shield_spi_ptr = &_shield_spi;
                result = cyhal_spi_set_frequency(&_shield_spi, SPI_FREQ_HZ);
            }
        }
        else
        {
            _shield_spi_ptr = spi_instance;
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = mtb_sht3x_init(_shield_i2c_ptr, MTB_SHT35_ADDRESS_DEFAULT);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        _shield_initialized |= _SHIELD_XENSIV_A_INITIALIZED_HUMIDITY;
        result = mtb_bmi270_init_i2c(&motion_sensor, _shield_i2c_ptr, MTB_BMI270_ADDRESS_SEC);
        if (CY_RSLT_SUCCESS == result)
        {
            result = mtb_bmi270_config_default(&motion_sensor);
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        _shield_initialized |= _SHIELD_XENSIV_A_INITIALIZED_MOTION;
        result = mtb_bmm350_init_i2c(&mag_sensor, _shield_i2c_ptr, MTB_BMM350_ADDRESS_DEFAULT);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        _shield_initialized |= _SHIELD_XENSIV_A_INITIALIZED_MAGNETOMETER;
        result = xensiv_dps3xx_mtb_init_i2c(&pressure_sensor, _shield_i2c_ptr,
                                            XENSIV_DPS3XX_I2C_ADDR_ALT);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        _shield_initialized |= _SHIELD_XENSIV_A_INITIALIZED_PRESSURE;
        if ((NULL != audio_clock_inst) && (NULL != pdm_pcm_cfg))
        {
            result = cyhal_pdm_pcm_init(&_shield_pdm_pcm, SHIELD_XENSIV_A_PIN_PDM_DATA,
                                        SHIELD_XENSIV_A_PIN_PDM_CLK, audio_clock_inst,
                                        pdm_pcm_cfg);
            if (CY_RSLT_SUCCESS == result)
            {
                _shield_initialized |= _SHIELD_XENSIV_A_INITIALIZED_PDM;
            }
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = mtb_st7735s_init_spi(_shield_spi_ptr, &tft_pins);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        _shield_initialized |= _SHIELD_XENSIV_A_INITIALIZED_DISPLAY;
        result = cyhal_gpio_init(SHIELD_XENSIV_A_PIN_CO2_PWR_EN, CYHAL_GPIO_DIR_OUTPUT,
                                 CYHAL_GPIO_DRIVE_STRONG, true);
        if (CY_RSLT_SUCCESS == result)
        {
            result = xensiv_pasco2_mtb_init_i2c(&co2_sensor, _shield_i2c_ptr);
        }
    }

    if (CY_RSLT_SUCCESS != result)
    {
        shield_xensiv_a_free();
    }

    return result;
}


/******************************************************************************
* shield_xensiv_a_get_humidity_sensor
******************************************************************************/
cyhal_i2c_t* shield_xensiv_a_get_humidity_sensor(void)
{
    return _shield_i2c_ptr;
}


/******************************************************************************
* shield_xensiv_a_get_motion_sensor
******************************************************************************/
mtb_bmi270_t* shield_xensiv_a_get_motion_sensor(void)
{
    return &motion_sensor;
}


/******************************************************************************
* shield_xensiv_a_get_mag_sensor
******************************************************************************/
mtb_bmm350_t* shield_xensiv_a_get_mag_sensor(void)
{
    return &mag_sensor;
}


/******************************************************************************
* shield_xensiv_a_get_pressure_sensor
******************************************************************************/
xensiv_dps3xx_t* shield_xensiv_a_get_pressure_sensor(void)
{
    return &pressure_sensor;
}


/******************************************************************************
* shield_xensiv_a_get_pdm
******************************************************************************/
cyhal_pdm_pcm_t* shield_xensiv_a_get_pdm(void)
{
    return ((_shield_initialized & _SHIELD_XENSIV_A_INITIALIZED_PDM) > 0)
        ? &_shield_pdm_pcm
        : NULL;
}


/******************************************************************************
* shield_xensiv_a_get_co2_sensor
******************************************************************************/
xensiv_pasco2_t* shield_xensiv_a_get_co2_sensor(void)
{
    return &co2_sensor;
}


/******************************************************************************
* shield_xensiv_a_free
******************************************************************************/
void shield_xensiv_a_free(void)
{
    if ((_shield_initialized & _SHIELD_XENSIV_A_INITIALIZED_HUMIDITY) > 0)
    {
        mtb_sht3x_free(_shield_i2c_ptr);
    }

    if ((_shield_initialized & _SHIELD_XENSIV_A_INITIALIZED_MOTION) > 0)
    {
        mtb_bmi270_free_pin(&motion_sensor);
    }
    if ((_shield_initialized & _SHIELD_XENSIV_A_INITIALIZED_MAGNETOMETER) > 0)
    {
        mtb_bmm350_free_pin(&mag_sensor);
    }
    if ((_shield_initialized & _SHIELD_XENSIV_A_INITIALIZED_PRESSURE) > 0)
    {
        xensiv_dps3xx_free(&pressure_sensor);
    }
    if ((_shield_initialized & _SHIELD_XENSIV_A_INITIALIZED_PDM) > 0)
    {
        cyhal_pdm_pcm_free(&_shield_pdm_pcm);
    }
    if ((_shield_initialized & _SHIELD_XENSIV_A_INITIALIZED_DISPLAY) > 0)
    {
        mtb_st7735s_free();
    }

    _shield_initialized = _SHIELD_XENSIV_A_INITIALIZED_NONE;

    if (_shield_i2c_ptr == &_shield_i2c)
    {
        cyhal_i2c_free(_shield_i2c_ptr);
    }
    _shield_i2c_ptr = NULL;

    if (_shield_spi_ptr == &_shield_spi)
    {
        cyhal_spi_free(_shield_spi_ptr);
    }
    _shield_spi_ptr = NULL;
}


#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
