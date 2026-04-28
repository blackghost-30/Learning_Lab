#ifndef __MYCAN_H_
#define __MYCAN_H_

extern CanRxMsg MyCAN_RxMsg;
extern uint8_t MyCAN_RxFlag;

void MyCAN_Init(void);
void MyCAN_Transmit(CanTxMsg *TxMessage);

#endif
