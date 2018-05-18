/**
******************************************************************************
* @file    x_cube_mems_lis3mdl.h
* @author  AST / EST
* @version V0.0.1
* @date    9-December-2014
* @brief   Implementation file for component LIS3MDL
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
*/
 
/* Includes ------------------------------------------------------------------*/
#include "mbed.h"
#include "lis3mdl.h"
#include "lis3mdl_platform.h"
#include <math.h>
 
/* Methods -------------------------------------------------------------------*/
 
LIS3MDL::LIS3MDL (PinName sda, PinName scl) : _i2c(sda, scl) {
        LIS3MDLInitialized = 0;
        Init();
}
/**
 * @brief Read data from LIS3MDL Magnetic sensor and calculate Magnetic in microTeslas.
 * @param float *pfData
 * @retval None.
 */
void LIS3MDL::readMag(void)
{
   
    float sensitivity = 0;
   
 
    GetAxesRaw();
/*
        case LIS3MDL_M_FS_4:
          sensitivity = 0.14;
          break;
        case LIS3MDL_M_FS_8:
          sensitivity = 0.29;
          break;
        case LIS3MDL_M_FS_12:
          sensitivity = 0.43;
          break;
        case LIS3MDL_M_FS_16:
          sensitivity = 0.58;
          break;
      }
    }*/
    sensitivity = 0.12207;
    mx = mx_raw * sensitivity;
    my = my_raw * sensitivity;
    mz = mz_raw * sensitivity;
  
}
 
/**
 * @brief Read raw data from LIS3MDL Magnetic sensor output register.
 * @param float *pfData
 * @retval None.
 */
void LIS3MDL::GetAxesRaw()
{
    char data[6];
    
    char subAddressXL = LIS3MDL_M_OUT_X_L_M;
    
    _i2c.write(LIS3MDL_M_MEMS_ADDRESS, &subAddressXL, 1, true);
    _i2c.read(LIS3MDL_M_MEMS_ADDRESS, data, 6);
 
    mx_raw = data[0] | (data[1] << 8);
    my_raw = data[2] | (data[3] << 8);
    mz_raw = data[4] | (data[5] << 8);
}
 
/**
 * @brief  Read ID address of HTS221
 * @param  Device ID address
 * @retval ID name
 */
uint8_t LIS3MDL::ReadID(void)
{
    char data[1];
    int ret;
    char subAddress = LIS3MDL_M_WHO_AM_I_ADDR;
    
    /* Read WHO I AM register */
    _i2c.write(LIS3MDL_M_MEMS_ADDRESS, &subAddress, 1, true);
    ret=_i2c.read(LIS3MDL_M_MEMS_ADDRESS, data, 1);
 
    /* Return the ID */
    return ((ret == 0) ? (uint8_t)data[0] : 0);
}
 
/**
 * @brief  Set HTS221 Initialization.
 * @param  InitStruct: it contains the configuration setting for the HTS221.
 * @retval None
 */
void LIS3MDL::Init() {
    
    char tmp1[2];
    
    /****** Magnetic sensor *******/
 
    /* Conversion mode selection */
      tmp1[0] = LIS3MDL_M_CTRL_REG3_M;
      tmp1[1] = 0x00;
      
      _i2c.write(LIS3MDL_M_MEMS_ADDRESS, tmp1, 2);
   
 
        //OM=UHP for XY
        //FAST_ODR enabled - 155Hz
      tmp1[0] = LIS3MDL_M_CTRL_REG1_M;
      tmp1[1] = 0x8E;
 
      _i2c.write(LIS3MDL_M_MEMS_ADDRESS, tmp1, 2);
    
      /* Full scale selection */
      tmp1[0] = LIS3MDL_M_CTRL_REG2_M;
      tmp1[1] = 0x00;
 
      _i2c.write(LIS3MDL_M_MEMS_ADDRESS, tmp1, 2);
    
      /*Fast Z*/
      tmp1[0] = LIS3MDL_M_CTRL_REG4_M;
      tmp1[1] = 0x0C;
 
      _i2c.write(LIS3MDL_M_MEMS_ADDRESS, tmp1, 2);
    
    /******************************/
    
      if(ReadID() == I_AM_LIS3MDL_M)
      {
          LIS3MDLInitialized = 1;
      }
    
 
    return;
}