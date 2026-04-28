/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t uint;
typedef uint32_t ulong;

#define PROGMEM

#define UPT_MOVE_NONE	0
#define UPT_MOVE_RIGHT	1
#define UPT_MOVE_LEFT	2

/* 遥控器数据结构体 */
struct input_data {
	uint32_t dev;
	uint32_t val;		/* UPT_MOVE_NONE,UPT_MOVE_RIGHT,UPT_MOVE_LEFT */ 
};

/* 旋转编码器数据结构体 */
struct rotary_data {
	int32_t cnt;
	int32_t speed;
};

// Quick and easy macro for a for loop
#define LOOP(count, var) for(byte var=0;var<count;var++)



#endif /* TYPEDEFS_H_ */
