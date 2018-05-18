/**
******************************************************************************
* @file    LIS3MDL.H
* @author  BCC
* @version V0.0.1
* @date    6-OCT-2016
* @brief   Header file for component LIS3MDL
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*
* v0.0.1 - copied from https://github.com/vzaccaria/stm32l053/tree/master/example2/lib/nucleo-sensor-shield/Components/LIS3MDL
*
*/
 
#ifndef __LIS3MDL_H
#define __LIS3MDL_H
 
/* Includes ------------------------------------------------------------------*/
#include "mbed.h"
 
 
/* Classes -------------------------------------------------------------------*/
 
class LIS3MDL
{
public:
    /** Constructor
     * @param 
     */
    LIS3MDL (PinName sda, PinName scl);
    float mx, my, mz;
    int16_t mx_raw, my_raw, mz_raw;
 
    void readMag();
    void GetAxesRaw();
    void    Init();
    uint8_t   ReadID(void);
    void      RebootCmd(void);
 
private:
    
    uint8_t isInitialized(void)
    {
        return LIS3MDLInitialized;
    }
    
    I2C _i2c;
    uint8_t LIS3MDLInitialized;
};
 
#endif