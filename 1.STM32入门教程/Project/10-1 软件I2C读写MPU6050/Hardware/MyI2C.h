#ifndef __MYI2C_
#define __MYI2C_

void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2c_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2c_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);

#endif
