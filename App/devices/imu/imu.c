/*
 * imu.c
 *
 *  Created on: Jun 4, 2025
 *      Author: User
 */

#include "mpu6050.h"
#include "hmc5883l.h"

static MPU6050_Config_t cfg = {
	.dlpf_cfg = 0x03,
	.gyro_fs_sel = 0x18,
	.accel_fs_sel = 0x10,
	.smplrt_div = 0x04,
};

static HAL_StatusTypeDef MPU6050_Write(uint8_t reg, uint8_t data)
{
	return I2C_Write(MPU6050_ADDRESS, reg, data);
}
static HAL_StatusTypeDef MPU6050_Read(uint8_t reg, uint8_t *data, uint8_t length)
{
	return I2C_Read(MPU6050_ADDRESS, reg, data, length);
}
// I2C Master 모드를 통한 HMC5883L 제어
static void MPU6050_I2CMaster_WriteReg(uint8_t slave_addr, uint8_t reg, uint8_t data)
{
	// Slave 0 주소 설정 (Write 모드: 7bit 주소)
	MPU6050_Write(MPU6050_I2C_SLV0_ADDR, slave_addr);

	// 쓸 레지스터 주소 설정
	MPU6050_Write(MPU6050_I2C_SLV0_REG, reg);

	// 전송할 데이터 설정
	MPU6050_Write(MPU6050_I2C_SLV0_DO, data);

	// Slave 0 제어: Enable, 1바이트 쓰기
	MPU6050_Write(MPU6050_I2C_SLV0_CTRL, 0x81);

	// 전송 완료 대기
	HAL_Delay(10);
}
static void MPU6050_I2CMaster_ReadReg(uint8_t slave_addr, uint8_t reg, uint8_t length)
{
	// Slave 0 주소 설정 (Read 모드: 7bit 주소 + READ bit)
	MPU6050_Write(MPU6050_I2C_SLV0_ADDR, slave_addr | 0x80);

	// 읽을 레지스터 주소 설정
	MPU6050_Write(MPU6050_I2C_SLV0_REG, reg);

	// Slave 0 제어: Enable, 읽을 바이트 수 설정
	MPU6050_Write(MPU6050_I2C_SLV0_CTRL, 0x80 | length);
}

void MPU6050_Init()
{
	MPU6050_Write(MPU6050_PWR_MGMT_1, 0x00);	// 슬립 모드 해제
	HAL_Delay(100);

	uint8_t who = 0;
	MPU6050_Read(MPU6050_WHO_AM_I, &who, 1);

	if (who == 0x68)
		HAL_UART_Transmit(&huart2, "Success\r\n", sizeof("Success\r\n"), 100);
	else
		HAL_UART_Transmit(&huart2, "Failed\r\n", sizeof("Failed\r\n"), 100);

	MPU6050_Write(MPU6050_CONFIG, cfg.dlpf_cfg);
	MPU6050_Write(MPU6050_SMPLRT_DIV, cfg.smplrt_div);

	MPU6050_Write(MPU6050_ACCEL_CONFIG, cfg.accel_fs_sel);
	MPU6050_Write(MPU6050_GYRO_CONFIG, cfg.gyro_fs_sel);

	MPU6050_Write(MPU6050_USER_CTRL, 0x20);  // I2C Master enable
	HAL_Delay(10);

	MPU6050_Write(MPU6050_I2C_MST_CTRL, 0x0D);	// I2C 마스터 클록 설정 (400kHz)
	HAL_Delay(10);
}

void HMC5883L_Init()
{
	// HMC5883L Configuration Register A 설정 (75Hz, 정상 측정)
	MPU6050_I2CMaster_WriteReg(HMC5883L_ADDRESS >> 1, HMC5883L_CONFIG_A, HMC5883L_CONFIG_A_75HZ);
	HAL_Delay(10);

	// HMC5883L Configuration Register B 설정 (±1.3 Ga)
	MPU6050_I2CMaster_WriteReg(HMC5883L_ADDRESS >> 1, HMC5883L_CONFIG_B, HMC5883L_CONFIG_B_1_3GA);
	HAL_Delay(10);

	// HMC5883L 연속 측정 모드 설정
	MPU6050_I2CMaster_WriteReg(HMC5883L_ADDRESS >> 1, HMC5883L_MODE, HMC5883L_MODE_CONTINUOUS);
	HAL_Delay(10);

	// HMC5883L 데이터 읽기 설정 (6바이트, X,Z,Y 순서)
	MPU6050_I2CMaster_ReadReg(HMC5883L_ADDRESS >> 1, HMC5883L_DATA_X_MSB, 6);

	HAL_UART_Transmit(&huart2, "HMC5883L Init Success (via I2C Master)\r\n",
		sizeof("HMC5883L Init Success (via I2C Master)\r\n"), 100);
}
