# FreeRTOS学习笔记

本笔记是基于B站韦东山的《FreeRTOS入门与工程实践》课程整理的：

- 视频链接：[视频链接](https://www.bilibili.com/video/BV1Jw411i7Fz?p=4&vd_source=b7453c324b64db9c455fd1d20572810d)；
- 官网资源：[官网资源](https://rtos.100ask.net/zh/FreeRTOS/DShanMCU-F103/)；

本笔记的组织形式：

- 与课程不完全一致，对于一些推销类课时不做记录，且对于一些课程的标题进行了更清晰的描述；
- 每个课时的标号与课程保持一致，采用**x-x**的形式；

---



# 0-1 课程配套硬件介绍

本课程主要由硬件和软件两部分构成，课程的内容就是在硬件的基础上去实现这个软件项目的效果，分别介绍如下：

- **硬件部分：**

  - 硬件是韦东山开发的**瑞士军刀开发板**；
  - 开发板的具体样子如下图所示：

  <img src="3.images/0-1课程配套硬件介绍/DShanMCU-F103.png" alt="开发板" style="zoom: 67%;" />

  - 板子的原理图和PCB文件可在文件夹`1.课程资料\2.闲鱼发货\2.底板\韦东山瑞士军刀RTOS底板PCB`下找到；

- **软件部分：**

  - 软件部分基于开源项目NWatch；
  - NWatch的项目地址如下：[NWatch项目地址](https://github.com/ZakKemble/NWatch)；

  ![NWatch页面](3.images/0-1课程配套硬件介绍/NWatch页面.png)

---



# 1-1 单片机的工作方式与FreeRTOS简介

---

## 1.内容介绍

- 本节对应了教程资料**第二章——单片机程序设计模式。**
- 单片机的工作方式主要可分为**裸机开发和多任务系统**，本小节分别介绍；
- 本节内容以下方图片的场景进行讲解：

![场景假设](3.images/1-1单片机的工作方式与FreeRTOS简介/场景假设.png)



## 2.裸机开发模式

### 2.1 轮询模式

- 在main函数中是一个while循环，里面依次调用2个函数，这两个函数相互之间有影响；
- 使用轮询模式编写程序简单，但要求while循环里调用到的函数要执行得非常快；

```c
// 经典单片机程序: 轮询
void main()
{
	while (1)
	{
		喂一口饭();
		回一个信息();
	}
}

```

### 2.2 前后台——中断驱动模式

- **所谓“前后台”就是使用中断程序；**
- 假设收到同事发来的信息时，电脑会发出“滴”的一声，这时候妈妈才需要去回复信息；

```c
// 前后台程序
void main()
{
	while (1)
	{
		// 后台程序
		喂一口饭();
	}
}

// 前台程序
void 滴_中断()
{
	回一个信息();
}

```

- 可以进一步优化，两个事件都通过中断驱动：
  - 当两个中断不同时发生时，之间没有影响；
  - 当两者同时发生时，必定会相互影响；
  - **此时while循环是空的；**

```c
// 前后台程序
void main()
{
	while (1)
	{
		// 后台程序
	}
}

// 前台程序
void 滴_中断()
{
	回一个信息();
}

// 前台程序
void 啊_中断()
{
	喂一口饭();
}
```

### 2.3 定时器驱动

- 定时器驱动模式，是前后台模式的一种，可以按照不用的频率执行各种函数；
- **此时main函数中的while循环是空的；**
- 这种方式的前提是每个函数的执行时间不能超过一个定时器周期，否则两个函数发生影响；

```c
// 前后台程序: 定时器驱动
void main()
{
	while (1)
	{
		// 后台程序
	}
}

// 前台程序: 每 1 分钟触发一次中断
void 定时器_中断()
{
	static int cnt = 0;
	cnt++;
	if (cnt % 2 == 0)
	{
		喂一口饭();
	}
	else if (cnt % 5 == 0)
	{
		回一个信息();
	}
}
```

### 2.4 基于状态机

- 使用状态机模式，可以解决裸机程序的难题；
- 假设有 A、B 两个都很耗时的函数，这样可以降低它们相互之间的影响；
- 但是很多场景里，**函数 A、B 并不容易拆分为多个状态**，并且这些状态执行的时间并不好控制；

```c
// 状态机
void main()
{
	while (1)
	{
		喂一口饭();
		回一个信息();
	}
}

void 喂一口饭(void)
{
	static int state = 0;
	switch (state)
	{
		case 0:
		{
			/* 舀饭 */
			state++;
			break;
		}
		case 1:
     	{
			/* 喂饭 */
			state++;
			break;
		}
		case 2:
		{
			/* 舀菜 */
			state++;
			break;
		}
		case 3:
		{
			/* 喂菜 */
			state = 0;
			break;
		}
	}
}

void 回一个信息(void)
{
	static int state = 0;

	switch (state)
	{
		case 0:
		{
			/* 查看信息 */
			state++;
			break;
		}
		case 1:
		{
			/* 打字 */
			state++;
			break;
		}
		case 2:
		{
			/* 发送 */
			state = 0;
			break;
		}
	}
}
```



## 3.多任务系统

### 3.1 多任务模式

- **机理介绍：**

  - 多任务系统会依次给这些任务分配时间：你执行一会，我执行一会，如此循环；
  - 只要切换的间隔足够短，用户会“感觉这些任务在同时运行”；
  - 其时间切片如下图所示：

  ![多任务模式的时间切片](3.images/1-1单片机的工作方式与FreeRTOS简介/多任务模式下的时间切片.png)

- **软件编写：**

  - main函数中创建 2 个任务；，然后启动调度器，之后，这 2 个任务就会交叉执行了；

  - 基于多任务系统编写程序时，反而更简单了：

    - 上面是“喂饭任务”的代码；

    - 下面是“回信息任务”的代码；
    - **编写它们时甚至都不需要考虑它和其他函数的相互影响；**

```c
// RTOS 程序
喂饭任务()
{
	while (1)
	{
		喂一口饭();
	}
}

回信息任务()
{
	while (1)
	{
		回一个信息();
	}
}

void main()
{
	// 创建 2 个任务
	create_task(喂饭任务);
	create_task(回信息任务);

	// 启动调度器
	start_scheduler();
}
```

### 3.2 多任务系统中的通讯问题

在多任务系统中，不同任务之间需要通讯，**通讯问题可分为互斥操作与同步操作。**

#### 3.2.1 互斥操作

- 多任务系统中，**多个任务可能会“同时”访问某些资源**，需要增加保护措施以防止混乱，这就是互斥操作；

- **用全局变量实现互斥操作1：**

  - 如下方代码所示，两个任务都要用同一个串口进行打印，它们之间是互斥的；
  - 在下方代码中，通过全局变量的方式进行互斥操作的保护；
  - 但是在任务切换中很可能在刚进入if判断后就发生了切换，所以用全局变量保护互斥操作会存在很大的偶然性；

  ```c
  // RTOS 程序
  int g_canuse = 1;
  
  void uart_print(char *str)
  {
  	if (g_canuse)
  	{
  		g_canuse = 0;
  		printf(str);
  		g_canuse = 1;
  	}
  }
  
  task_A()
  {
  	while (1)
  	{
  		uart_print("0123456789\n");
  	}
  }
  
  task_B()
  {
  	while (1)
  	{
  		uart_print("abcdefghij");
  }
  
  }
  
  void main()
  {
  	// 创建 2 个任务
  	create_task(task_A);
  	create_task(task_B);
  	// 启动调度器
  	start_scheduler();
  }
  ```

- **用全局变量实现互斥操作2：**

  - 在原来的基础上做修改，如下方代码所示；
  - 但是由于“减1”这个操作在底层的汇编实现上需要三步，所以仍然可能存在冲突的风险；

  ```c
  void uart_print(char *str)
  {
      g_canuse--;				① 减一
      if( g_canuse == 0 )		② 判断
      {
          printf(str);		③ 打印
      }
      g_canuse++;				④ 加一
  }
  ```

- 所以，为了解决多任务系统中的互斥操作问题，FreeRTOS内部封装了API，后续利用FreeRTOS提供的API就能解决这些问题；

#### 3.2.2 同步操作

- 若任务之间有依赖关系，如任务A执行了某个操作之后，需要任务B进行后续的处理，这就是同步操作；

- **全局变量实现同步操作1：**

  - 下方代码中，在任务A没有设置flag为1之前，任务B的代码都只是去判断flag；
  - 而任务A、B的函数是依次轮流运行的，假设系统运行了100秒，其中任务A总共运行了50秒，任务B总共运行了50秒；
  - **任务A在努力处理复杂的运算，任务B仅仅是浪费CPU资源；**

  ```c
  // RTOS程序
  int flag = 0;
  
  void task_A()
  {
      while (1)
      {
          // 做某些复杂的事情，完成后把flag设置为1
          flag = 1;
      }
  }
  
  void task_B()
  {
      while (1)
      {
          if (flag)
          {
              // 做后续的操作
          }
      }
  }
  
  void main()
  {
      // 创建2个任务
      create_task(task_A);
      create_task(task_B);
      // 启动调度器
      start_scheduler();
  }
  ```

- **FreeRTOS中处理同步操作：**

  - 如下方代码所示，可以通过FreeRTOS提供的信号量，来实现A、B任务之间的同步操作；
  - 在此期间，**任务B会被阻塞，不参与调度，知道任务A完成并释放信号量；**

  ```c
  // RTOS程序
  void task_A()
  {
      while (1)
      {
          // 做某些复杂的事情
          // 释放信号量,会唤醒任务B;
      }
  }
  
  void task_B()
  {
      while (1)
      {
          // 等待信号量, 会让任务B阻塞
          // 做后续的操作
      }
  }
  
  void main()
  {
      // 创建2个任务
      create_task(task_A);
      create_task(task_B);
      // 启动调度器
      start_scheduler();
  }
  ```


---



# 1-2 项目展示

- 整个工程包括3个项目：音乐播放、打砖块游戏、汽车游戏；

- 最后整个项目完成的程序的整体框架如下图所示：

![程序框架](3.images/1-2项目展示/程序框架.png)

---



# 2-1 开发板使用

## 1.内容介绍

- 本节内容对应了**教程资料的第三章和第四章；**
- 本节内容涉及的工程有：
  - **00_FreeRTOS_Template**
    - 由STM32CubeMX创建的添加了DshanMCU-F103驱动代码的空白的FreeRTOS工程；
    - 这个工程主要提供给学者学习由STM32CubeMX创建的FreeRTOS的工程结构；
  - **00_Driver_Test**
    - 开发板测试的FreeRTOS工程；
    - 这个工程是本节的主要工程，用于测试开发板的各个模块；
    - 这个工程只是在00_FreeRTOS_Template工程的基础上，在freertos.c文件中添加了驱动代码；



## 2.开发板介绍与硬件连接

- DshanMCU-103上有4个插针，它们分别是GND、SWCLK、SWDIO、3.3V；
- ST-Link上有10个插针，它们的功能在外壳上有标注；接线方法如下图所示：

![连接STLink](3.images/2-1开发板使用/STLink连接.png)

- 连接好的实物图如下（ST-Link的USB口要插到电脑上）：

![连接好的实物图](3.images/2-1开发板使用/连接好的实物图.png)



## 3.打开工程

- 测试开发板的项目工程是**00_Driver_Test**；
- 打开文件夹，选择MDK-ARM，然后用Keil打开：

![工程项目](3.images/2-1开发板使用/工程项目.png)



## 4.修改代码

- 本工程主要涉及的文件是freertos.c，除了这个文件外，其他文件与空白工程的文件完全相同；
- 在该文件中有一个默认任务，这个任务由STM32CubeMX自动生成；
- 这个任务主要做的事情是初始化LCD，然后在循环中添加了驱动的测试代码；
- 由于每个测试函数内部都是一个死循环（可自己打开驱动源码查看），所以在测试开发板时，只能取消注释一个测试函数，逐个完成模块的测试；

![工程修改](3.images/2-1开发板使用/工程使用.png)



## 5.注意事项

- 有些模块的引脚是共用的，所以它们要么不能同时接，要么不能同时使用；

- 可参照教程资料的第四章，里面有详细的说明，可将它们列表如下：

| 模块1            | 模块2                | 备注                       |
| ---------------- | -------------------- | -------------------------- |
| M2(DS18B20)      | M10(DHT11温湿度模块) | 不能同时接                 |
| M4(红外发射模块) | M9(蜂鸣器)           | 不能同时接                 |
| M6(超声波模块)   | M12(Flash模块)       | 可以同时接，但是要互斥访问 |

![冲突模块](3.images/2-1开发板使用/冲突模块.png)



# 2-2 模块使用说明与STM32CubeMX配置

## 1.内容介绍

- 本节内容对应**课程资料的第五章——模块使用说明与 STM32CubeMX 配置；**
- **前面的00_Driver_Test工程就是这个课程的模板教程，可在这个工程的基础上跟着教程一步步完善工程；**
- 本小节的内容主要是讲解整个项目从零搭建的思路，具体的搭建过程见2-3节；



## 2.项目搭建的思路说明

- **驱动代码**

  - 在这个开发板上，要使用各个模块，需要用到各个模块的驱动代码；
  - 对于每一个模块，课程都提供了对应的驱动代码，路径在：`.\2.Project\01_Driver_Test\Project\Drivers\DshanMCU-F103`；

- **外设**

  - 要使用上面的驱动代码来驱动模块，需要用到STM32的各个外设和它们打交道；
  - 比如对于OLED而言，它需要用到I2C1，那就需要对I2C1这个外设进行配置；

- **初始化**

  - 初始化指的是初始化外设，这个工作由STM32CubeMX来做；
  - 由于驱动代码底层是用HAL库来写的，所以需要用STM32CubeMX来做初始化；

  ![驱动代码的底层HAL依赖](3.images/2-2模块使用说明与STM32CubeMX配置/驱动代码的HAL库依赖.png)



# 2-3 自己创建FreeRTOS工程

## 1.内容介绍

- 本节内容对应课程资料的：
  - **第五章——模块使用说明与 STM32CubeMX 配置；**
  - **第六章——创建FreeRTOS工程；**

- 本节主要介绍如何基于STM32CubeMX创建一个FreeRTOS工程，包括驱动代码的移植和默认任务的改写；



## 2.工程创建

具体如何创建一个工程请详细查看教程资料，在此不再赘述。

![工程结构](3.images/2-3自己创建FreeRTOS工程/工程结构.png)



## 3.工程移植

在完成空白的FreeRTOS项目的创建后，接下来移植LED和OLED的驱动代码，这里已经假设前面的工程创建中完成了GPIO和I2C的初始化，具体见教程第六章。

- **LED的移植**

  - 首先需要添加驱动文件driver_led.c和driver_led.h文件，其具体过程见教程；
  - 接着就可以在freertos.c文件中添加测试代码：

  ```c
  /* USER CODE BEGIN Header */
  #include "driver_led.h"
  
  /* USER CODE END Header_StartDefaultTask */
  void StartDefaultTask(void *argument)
  {
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for(;;)
    {
      //osDelay(1);
  	  Led_Test();
    }
    /* USER CODE END StartDefaultTask */
  }
  
  ```

- **OLED的移植**

  - LCD的项目移植与LED相同，只是需要添加的驱动文件较多；
  - 驱动文件有：ascii_font.c、driver_lcd.c、driver_lcd.h、driver_led.c、driver_led.h、driver_timer.c和driver_timer.h；
  - 接着就可以在上面的基础上测试OLED的测试函数：

  ```c
  /* USER CODE BEGIN Header */
  #include "driver_led.h"
  #include "driver_lcd.h"
  
  /* USER CODE END Header_StartDefaultTask */
  void StartDefaultTask(void *argument)
  {
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for(;;)
    {
      //osDelay(1);
  	//LCD_Test();
  	  Led_Test();
    }
    /* USER CODE END StartDefaultTask */
  }
  
  ```

- 本完整工程对应着Project文件夹下的**01_FreeRTOS_Create_LCD_LED**；



## 4.说明

- 强烈建议就在**00_FreeRTOS_Template**或**00_Driver_Test**工程的基础上进行开发；
- 两者的区别主要就是freertos.c文件中是否加入了驱动代码；
- 对于想要从零构建这个项目的学者，需要具有一定的STM32基础以及STM32CubeMX的基础；
- 若在原来两个工程的基础上开发，只需要创建一个新的文件夹，该文件夹以项目名称命名，然后把前面任何一个项目的整个Project文件夹拷贝下来即可；



# 3-1 创建第一个多任务程序





















































