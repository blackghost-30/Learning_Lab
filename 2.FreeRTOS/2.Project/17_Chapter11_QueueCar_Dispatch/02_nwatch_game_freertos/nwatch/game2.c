/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */
#include <stdlib.h>
#include <stdio.h>

#include "cmsis_os.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "semphr.h"                     // ARM.FreeRTOS::RTOS:Core

#include "draw.h"
#include "resources.h"

#include "driver_lcd.h"
#include "driver_rotary_encoder.h"
#include "driver_ir_receiver.h"
#include "driver_mpu6050.h"

#define CAR_COUNT	3
#define CAR_WIDTH	12
#define CAR_LENGTH	15
#define ROAD_SPEED	6

#define NOINVERT	false
#define INVERT		true

static uint32_t g_xres, g_yres, g_bpp;
static uint8_t *g_framebuffer;

/* 汽车结构体 */
struct car {
	int x;
	int y;
	int control_key;
};

/* 3辆汽车实例 */
struct car g_cars[3] = {
	{0, 0, IR_KEY_1},
	{0, 17, IR_KEY_2},
	{0, 34, IR_KEY_3},
	
};

static const byte carImg[] ={
	0x40,0xF8,0xEC,0x2C,0x2C,0x38,0xF0,0x10,0xD0,0x30,0xE8,0x4C,0x4C,0x9C,0xF0,
	0x02,0x1F,0x37,0x34,0x34,0x1C,0x0F,0x08,0x0B,0x0C,0x17,0x32,0x32,0x39,0x0F,
};

static const byte clearImg[30] ={0};

static const byte roadMarking[] ={
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
};

#if 0
void car_test(void)
{
	g_framebuffer = LCD_GetFrameBuffer(&g_xres, &g_yres, &g_bpp);
    draw_init();
    draw_end();
	
	/* 前面两个参数是位置，后面两个参数是大小 */
	draw_bitmap(0, 0, carImg, 15, 16, NOINVERT, 0);
    draw_flushArea(0, 0, 15, 16);
	
	draw_bitmap(0, 16, roadMarking, 8, 1, NOINVERT, 0);
    draw_flushArea(0, 16, 8, 1);
	
	while(1);
}
#endif

/* 汽车变换逻辑 */
/* 显示汽车 */
static void ShowCar(struct car *pcar)
{
	draw_bitmap(pcar->x, pcar->y, carImg, 15, 16, NOINVERT, 0);
    draw_flushArea(pcar->x, pcar->y, 15, 16);
}

/* 隐藏汽车 */
static void HideCar(struct car *pcar)
{
	draw_bitmap(pcar->x, pcar->y, clearImg, 15, 16, NOINVERT, 0);
    draw_flushArea(pcar->x, pcar->y, 15, 16);
}

static void CarTask(void *params)
{
	struct car *pcar = params;
	struct ir_data idata;
	
	/* 创建自己的队列 */
	QueueHandle_t xQueueIR = xQueueCreate(10, sizeof(struct ir_data));
	
	/* 注册队列 */
	RegisterQueueHandle(xQueueIR);
	
	/* 先显示汽车 */
	ShowCar(pcar);
	
	while(1)
	{
		/* 读取按键值:读队列 */
		xQueueReceive(xQueueIR, &idata, portMAX_DELAY);
		
		/* 控制汽车往右移动 */
		if (idata.val == pcar->control_key)
		{
			if (pcar->x < g_xres - CAR_LENGTH)
			{
				/* 隐藏汽车 */
				HideCar(pcar);
				
				/* 调整位置 */
				pcar->x += 20;
				if (pcar->x > g_xres - CAR_LENGTH)
				{
					pcar->x = g_xres - CAR_LENGTH;
				}
				
				/* 重新显示汽车 */
				ShowCar(pcar);
			}
		}
	}
}

void car_game(void)
{
	int x;
	int i, j;
	
	g_framebuffer = LCD_GetFrameBuffer(&g_xres, &g_yres, &g_bpp);
    draw_init();
    draw_end();
	
	/* 画出路标 */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 8; j ++)
		{
			draw_bitmap(16 * j, 16 + 17 * i, roadMarking, 8, 1, NOINVERT, 0);
			draw_flushArea(16 * j, 16 + 17 * i, 8, 1);
		}
		
	}
	
#if 0
	/* 前面两个参数是位置，后面两个参数是大小 */
	/* 画出3辆汽车 */
	for (i = 0; i < 3; i ++)
	{
		draw_bitmap(g_cars[i].x, g_cars[i].y, carImg, 15, 16, NOINVERT, 0);
		draw_flushArea(g_cars[i].x, g_cars[i].y, 15, 16);
	}
#endif	
	
	/* 创建3辆汽车的任务 */
	xTaskCreate(CarTask, "car1", 128, &g_cars[0], osPriorityNormal, NULL);
	xTaskCreate(CarTask, "car2", 128, &g_cars[1], osPriorityNormal, NULL);
	xTaskCreate(CarTask, "car3", 128, &g_cars[2], osPriorityNormal, NULL);
}
