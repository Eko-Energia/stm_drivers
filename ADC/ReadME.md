Title:
    STM32 Peripherial ADC driver

Decription:
    Directory contains source and header files, which were build to help others in working with ADC.
    
    Main purpose of ADC driver (STM32 peripherial) is to store functions and macros whiich will simplify workflow with ADC. Least but not last purpose is to make all firmwares of Perła, universal. This will help in locating, analyziing and debuging errors in software.


    NOTE:
    Drivers in being built using registers and low-level features of ADC controller embedded in STM32 cores. Driver is universal for almost all ttype of STM32 cores

Application:
    Author of this driver will provide documentation with detailed description of main purpose of functionalities. In IDE programmer can obtain common description of functions. Detailed decription of parameters and return values will be located in documentation.

Files listing: 
    1. Inc/adc_driver.h - function prototypes, macros, structs 2. Inc/stm32_family.h - macros of stm32 families definition 3. Src/adc_driver.c - functions' bodies, variables' definitions

Status:
    General:
        Driver build is done. Code needs tests and review.
        Using drtiver's features without Kacper Lasota permission is forbidden.

    Detailed:
        1. Inc/adc_driver.h   [DONE]
        2. Inc/stm32_family.h [DONE]
        3. Src/adc_driver.c   [DONE]

Author:
    Bartosz Rychlicki
    bartoszrychl@student.agh.edu.pl


    AGH Eko-Energy
    Software department
