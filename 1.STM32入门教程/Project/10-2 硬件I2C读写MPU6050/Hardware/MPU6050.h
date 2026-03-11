#ifndef __MPU6050_H
#define __MPU6050_H

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_Init(void);
void MPU6050_GetData(int16_t *Accx, int16_t *Accy, int16_t *Accz,
					 int16_t *Gyrox, int16_t *Gyroy, int16_t *Gyroz);
uint8_t MPU6050_GetID(void);

#endif
