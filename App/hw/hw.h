/*
 * hw.h
 *
 *  Created on: May 25, 2025
 *      Author: User
 */

#ifndef HW_HW_H_
#define HW_HW_H_

#include "def.h"
#include "i2c.h"

void hwInit(void);

void I2C_Write(I2C_HandleTypeDef *i2c, uint8_t addr, uint8_t reg, uint8_t data);
void I2C_Read(I2C_HandleTypeDef *i2c, uint8_t addr, uint8_t reg, uint8_t *data);
void I2C_ReadBytes(I2C_HandleTypeDef *i2c, uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);

#endif /* HW_HW_H_ */
