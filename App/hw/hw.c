/*
 * hw.c
 *
 *  Created on: May 25, 2025
 *      Author: User
 */

#include "hw.h"

void hwInit(void)
{

}

void I2C_Write(I2C_HandleTypeDef *i2c, uint8_t addr, uint8_t reg, uint8_t data)
{
	HAL_I2C_Mem_Write(i2c, addr, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
}

void I2C_Read(I2C_HandleTypeDef *i2c, uint8_t addr, uint8_t reg, uint8_t *data)
{
	HAL_I2C_Mem_Read(i2c, addr, reg, I2C_MEMADD_SIZE_8BIT, data, 1, 100);
}

void I2C_ReadBytes(I2C_HandleTypeDef *i2c, uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
	HAL_I2C_Mem_Read(i2c, addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, 100);
}
