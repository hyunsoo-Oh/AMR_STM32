/*
 * hmc5883l.h
 *
 *  Created on: Jun 4, 2025
 *      Author: User
 */

#ifndef DEVICES_IMU_HMC5883L_H_
#define DEVICES_IMU_HMC5883L_H_

// -----------------------------------------------------------------------------
// HMC5883L 기본 정보
// -----------------------------------------------------------------------------
#define HMC5883L_ADDRESS           0x1E << 1    // HMC5883L I2C 주소
#define HMC5883L_ID_REG_A          0x0A         // Identification Register A
#define HMC5883L_ID_REG_B          0x0B         // Identification Register B
#define HMC5883L_ID_REG_C          0x0C         // Identification Register C

// -----------------------------------------------------------------------------
// HMC5883L 레지스터 정의
// -----------------------------------------------------------------------------
#define HMC5883L_CONFIG_A          0x00  // Configuration Register A
#define HMC5883L_CONFIG_B          0x01  // Configuration Register B
#define HMC5883L_MODE              0x02  // Mode Register
#define HMC5883L_DATA_X_MSB        0x03  // Data Output X MSB Register
#define HMC5883L_DATA_X_LSB        0x04  // Data Output X LSB Register
#define HMC5883L_DATA_Z_MSB        0x05  // Data Output Z MSB Register
#define HMC5883L_DATA_Z_LSB        0x06  // Data Output Z LSB Register
#define HMC5883L_DATA_Y_MSB        0x07  // Data Output Y MSB Register
#define HMC5883L_DATA_Y_LSB        0x08  // Data Output Y LSB Register
#define HMC5883L_STATUS            0x09  // Status Register

// HMC5883L 설정 값
#define HMC5883L_CONFIG_A_75HZ     0x18  // 75Hz 샘플링, 정상 측정
#define HMC5883L_CONFIG_B_1_3GA    0x20  // ±1.3 Ga 게인
#define HMC5883L_MODE_CONTINUOUS   0x00  // 연속 측정 모드
#define HMC5883L_MODE_SINGLE       0x01  // 단일 측정 모드

// 초기화 함수
void HMC5883L_Init(void);

// 데이터 읽기 함수
void HMC5883L_ReadMag(int16_t mag_data[3]);

// 유틸리티 함수
float HMC5883L_GetHeading(int16_t mx, int16_t my);
void HW290_PrintData(HW290_Data_t *data);

#endif /* DEVICES_IMU_HMC5883L_H_ */
