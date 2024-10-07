# SHIELD_XENSIV_A sensor shield API Reference Guide

# Shield

## General Description

Basic set of APIs for interacting with the SHIELD_XENSIV_A shield board.

This provides pin definitions and initialization code for the shield. Initialization of the shield configures the internal peripherals to allow them to be used.

**Note:** This library is intended to work with emWin middleware for display operation and currently supports a single instance of the display.

## Functions

cy_rslt_t `shield_xensiv_a_init(cyhal_i2c_t* i2c_instance, cyhal_spi_t* spi_instance, const cyhal_pdm_pcm_cfg_t* pdm_pcm_cfg, cyhal_clock_t* audio_clock_inst)`
>Initializes the shield board and all peripherals present on it. The initialization of all the sensors takes  up to 3 seconds, as it waits for the CO2 sensor to be ready.

cyhal_i2c_t* `shield_xensiv_a_get_humidity_sensor(void)`
>Gives the user access to the I2C object used for the humidity sensor.

mtb_bmi270_t* `shield_xensiv_a_get_motion_sensor(void)`
>Gives the user access to the motion sensor object.

mtb_bmm350_t* `shield_xensiv_a_get_mag_sensor(void)`
>Gives the user access to the magnetometer sensor object.

xensiv_dps3xx_t* `shield_xensiv_a_get_pressure_sensor(void)`
>Gives the user access to the pressure sensor object.

cyhal_pdm_pcm_t* `shield_xensiv_a_get_pdm(void)`
>Gives the user access to the PDM object used with the microphone. This will return null if the arguments to setup the PDM interface were not provided.

xensiv_pasco2_t* `shield_xensiv_a_get_co2_sensor(void)`
>Gives the user access to the CO2 sensor object.

void `shield_xensiv_a_free(void)`
>Frees up any resources allocated as part of `shield_xensiv_a_init()`.

## Function Documentation

#### shield_xensiv_a_init()
- cy_rslt_t `shield_xensiv_a_init(cyhal_i2c_t* i2c_instance,
                               cyhal_spi_t* spi_instance,
                               const cyhal_pdm_pcm_cfg_t* pdm_pcm_cfg,
                               cyhal_clock_t* audio_clock_inst)`

> **Summary:** Initializes the shield board and all peripherals present on it. The initialization of all the sensors takes  up to 3 seconds, as it waits for the CO2 sensor to be ready.
>
> **Parameter:**
>  Parameters            |  Description
>  :-------              |  :------------
>  i2c_instance          |  An optional I2C instance to use for communicating with the sensors on the shield. If NULL, a new instance will be allocated internally.
>  spi_instance          |  An optional SPI instance to use for communicating with the display and sensors on the shield. If NULL, a new instance will be allocated internally.
>  pdm_pcm_cfg           |  The configuration for the PDM object used with the microphone. If NULL, the PDM object will not be initialized.
>  audio_clock_inst      |  The audio clock used with the microphone. If NULL, the PDM object will not be initialized.
>
> Return:
>  - cy_rslt_t           :  CY_RSLT_SUCCESS if properly initialized, else an error indicating what went wrong.

#### shield_xensiv_a_get_humidity_sensor()
- cyhal_i2c_t* shield_xensiv_a_get_humidity_sensor(void)

> **Summary:** Gives the user access to the I2C object used for the humidity sensor.
>
> Returns:
> - A reference to the I2C object used for the humidity sensor.

#### shield_xensiv_a_get_motion_sensor()
- mtb_bmi270_t* `shield_xensiv_a_get_motion_sensor(void)`

> **Summary:** Gives the user access to the motion sensor object.
>
> Returns:
> - A reference to the motion sensor object on this shield.

#### shield_xensiv_a_get_mag_sensor()
- mtb_bmm350_t* `shield_xensiv_a_get_mag_sensor(void)`

> **Summary:** Gives the user access to the magnetometer sensor object.
>
> Returns:
> - A reference to the magnetometer sensor object on this shield.

#### shield_xensiv_a_get_pressure_sensor()
- xensiv_dps3xx_t* `shield_xensiv_a_get_pressure_sensor(void)`

> **Summary:** Gives the user access to the pressure sensor object.
>
> Returns:
> - A reference to the pressure sensor object on this shield.

#### shield_xensiv_a_get_pdm()
- cyhal_pdm_pcm_t* `shield_xensiv_a_get_pdm(void)`

> **Summary:** Gives the user access to the PDM object used with the microphone. This will return null if the arguments to setup the PDM interface were not provided.
>
> Returns:
> - A reference to the PDM microphone object on this shield.

#### shield_xensiv_a_get_co2_sensor()
- xensiv_pasco2_t* `shield_xensiv_a_get_co2_sensor(void)`

> **Summary:** Gives the user access to the CO2 sensor object.
>
> Returns:
> - A reference to the CO2 sensor object on this shield.

#### shield_xensiv_a_free()
- void `shield_xensiv_a_free(void)`
>**Summary:** Frees up any resources allocated as part of `shield_xensiv_a_init()`.

# Pins

## General Description

Pin mapping of the GPIOs used by shield peripherals.

## Macros

#define `SHIELD_XENSIV_A_PIN_I2C_SCL         (CYBSP_I2C_SCL)`
>Pin for the shared I2C SCL signal.

#define `SHIELD_XENSIV_A_PIN_I2C_SDA         (CYBSP_I2C_SDA)`
>Pin for the shared I2C SDA signal.

#define `SHIELD_XENSIV_A_PIN_SPI_SCK         (CYBSP_SPI_CLK)`
>Pin for the SPI SCK signal.

#define `SHIELD_XENSIV_A_PIN_SPI_MISO        (CYBSP_SPI_MISO)`
>Pin for the SPI MISO signal.

#define `SHIELD_XENSIV_A_PIN_SPI_MOSI        (CYBSP_SPI_MOSI)`
>Pin for the SPI MOSI signal

#define `SHIELD_XENSIV_A_PIN_SPI_CS          (CYBSP_SPI_CS)`
>Pin for the SPI CS signal.

#define `SHIELD_XENSIV_A_PIN_SPI_CS_SEL0     (CYBSP_D9)`
>Pin for the SPI CS selection signal.

#define `SHIELD_XENSIV_A_PIN_SEN_INT         (CYBSP_D7)`
>Pin for the sensor interrupt signals.

#define `SHIELD_XENSIV_A_PIN_RADAR_SEL       (CYBSP_D6)`
>Pin for the radar sensor selection signal.

#define `SHIELD_XENSIV_A_PIN_RADAR_GPIO1     (CYBSP_D5)`
>Pin for the radar GPIO1 or P_DET signal.

#define `SHIELD_XENSIV_A_PIN_RADAR_GPIO2     (CYBSP_D4)`
>Pin for the radar GPIO2 or T_DET signal.

#define `SHIELD_XENSIV_A_PIN_RS_OD_LED       (CYBSP_J2_12)`
>Pin for the radar shield open drain LED signal.

#define `SHIELD_XENSIV_A_PIN_RADAR_ADC1      (CYBSP_J2_2)`
>Pin for the radar ADC1 signal.

#define `SHIELD_XENSIV_A_PIN_RADAR_ADC2      (CYBSP_J2_4)`
>Pin for the radar ADC2 signal.

#define `SHIELD_XENSIV_A_PIN_RADAR_RST       (CYBSP_A2)`
>Pin for the radar reset signal.

#define `SHIELD_XENSIV_A_PIN_RADAR_INT       (CYBSP_A1)`
>Pin for the radar interrupt signal.

#define `SHIELD_XENSIV_A_PIN_MAIN_RST        (CYBSP_D2)`
>Pin for the main reset signal.

#define `SHIELD_XENSIV_A_PIN_MAG_INT         (CYBSP_J2_10)`
>Pin for the magnetometer sensor interrupt signal.

#define `SHIELD_XENSIV_A_PIN_IMU_INT_1       (CYBSP_J2_6)`
>Pin for the motion sensor interrupt 1 signal.

#define `SHIELD_XENSIV_A_PIN_IMU_INT_2       (CYBSP_J2_8)`
>Pin for the motion sensor interrupt 2 signal.

#define `SHIELD_XENSIV_A_PIN_PDM_DATA        (CYBSP_A5)`
>Pin for the PDM Data.

#define `SHIELD_XENSIV_A_PIN_PDM_CLK         (CYBSP_A4)`
>Pin for the PDM Clock.

#define `SHIELD_XENSIV_A_PIN_CO2_PWR_EN      (CYBSP_A3)`
>Pin for the PAS CO2 power enable signal.

#define `SHIELD_XENSIV_A_PIN_SPI_DC_DS       (CYBSP_A0)`
>Pin for the TFT display command signal.

# Humidity and Temperature Sensor

The humidity and temperature sensor is handled by the sensor-humidity-sht3x library, details are available at https://github.com/infineon/sensor-humidity-sht3x.

# Motion Sensor

The motion sensor is handled by the sensor-motion-bmi270 library, details are available at https://github.com/infineon/sensor-motion-bmi270.

# Magnetometer Sensor

The magnetometer sensor is handled by the sensor-orientation-bmm350 library, details are available at https://github.com/infineon/sensor-orientation-bmm350.

# Pressure Sensor

The pressure sensor is handled by the sensor-xensiv-dps3xx library, details are available at https://github.com/infineon/sensor-xensiv-dps3xx.

# PAS CO2 Sensor

The CO2 sensor is handled by the sensor-xensiv-pasco2 library, details are available at https://github.com/infineon/sensor-xensiv-pasco2.

# 0.96 TFT Display

The display is handled by the display-tft-st7735s library, details are available at https://github.com/infineon/display-tft-st7735s.

---
© 2024, Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation.
