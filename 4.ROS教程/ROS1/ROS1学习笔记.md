# 第一节课：ROS是什么

## 1.手机操作系统

### 1.1 以前的手机开发模式

![手机操作系统](images/01_ROS是什么/手机操作系统.png)

### 1.2 后来的手机开发模式

- **Android：**

  - Linux——>Android：

  - Android在Linux内核的基础上添加了原生App，并集成了一个虚拟环境可以运行Java开发的应用；
  - 开发者只要将应用上传到应用商店即可下载；

- **IOS：**
  - 一个完整的iphone操作系统，运行方式同Android；



## 2.机器人操作系统

### 2.1 以前的机器人开发模式

- 每造一台机器人就需要从硬件到软件重新开发一遍；

### 2.2 后来的机器人开发模式

- **“模块化”的开发方式：**
  - 每个传感器对应一个特定的程序模块、每个执行器对应一个特定的程序模块、每个算法对应一个特定的程序模块;
  - 下次再开发机器人时，只需要把它们组合起来就可以跑了；
- **“分布式”的开发方式：**
  - 每个模块可以独立运行在不同的电脑;
  - 比如用单独的电脑运行视觉算法，这样整体的效率就大大提高了；

![ROS与安卓的比较](images/01_ROS是什么/ROS与安卓的比较.png)

### 2.3 ROS的介绍

- **ROS的模式**
  - 每个**“launch”**文件是一个乐高房子；
  - 每个node相当于一个乐高砖块；

- **ROS的开发方式：**

  - 从官方**APT源**中下载安装包；
  - 从**Github**中下载源码；
  - 自己按照**接口规范**写源码并编译运行；

  ![ROS的开发方式](images/01_ROS是什么/ROS的开发方式.png)



# 第二节课：如何学习ROS

## 1.搭建环境

- 目的：**安装Ubuntu＋安装ROS**；

- ROS版本选择：ROS的版本更新主要是为了适应Ubuntu更新中大量依赖库的更新，两者的更新基本保持统一步调；



## 2.学习的方式

- 自己买一个机器人；
- 基于ROS自带的仿真环境进行学习；



# 第三节课：Ubuntu系统的安装

Ubuntu系统的安装主要可以有以下几种选择：

- 虚拟机方式；
- 双系统的方式；
- WSL的方式；
- 安装在树莓派上；



# 第四节课：Ubuntu使用入门

## 4.1 程序菜单和任务栏

- 左下角——>开始；
- 添加到收藏夹——>任务栏；

![程序菜单与任务栏](images/04_Ubuntu使用入门/程序菜单与任务栏.png)



## 4.2 输入法中英文切换

- Shift或Alt＋Space；
- 若不行就自行安装中文包；



## 4.3 Ubuntu文件系统

- **主目录：**
  - 即HOME目录；
  - 可通过：cd ~快速回到主目录
- **根目录/：**
  - 整个系统的系统盘；
- 大部分时间都只需要在主目录下操作即可；

![文件系统](images/04_Ubuntu使用入门/文件系统.png)



## 4.4 连接无线网

- 非虚拟机：像平常电脑一样连接WiFi即可；

- 虚拟机：只要主机连接了WiFi，它就会连接；

- 注意几种连接方式的不同（NAT、桥接等）、如何给虚拟机配置代理（ip地址）



## 4.5 终端程序和常用指令

- **终端程序的开启：**
  - 在开始菜单中启动；
  - 快捷键：Ctrl+Alt+T；

- **ls指令：**
  - 列出当前文件夹的内容；
  - 列出所有文件包括隐藏文件：**ls -a**；

- **mkdir指令：**
  - **mkdir [文件夹名称]**；
  - 用于在当前文件夹在创建文件夹；

- **cd指令：**
  - **cd [相对路径/绝对路径]**；
  - 用于切换目录；
  - 注意“cd ..”是返回父目录；

- **Tab键：**
  - 自动补全；



## 4.6 文本编辑器——gedit

- **edit命令：**
  - **gedit [文件名称]**；
  - 是一个文本编辑器（Windows中的记事本）；
  - 我们要改某个文件的内容都是通过这个指令来改的；

- **其他文本编辑器：**
  - vim；
  - nano；



## 4.7 source指令

- **source指令：**
  - **source [文件名]**；
  - 它会执行这个文件中的一系列指令；

- **.sh文件：**
  - 一般会把一连串的指令写在.sh文件中；
  - echo指令是打印显示；



## 4.8 终端启动脚本——.bashrc文件

- **~/.bashrc：**
  - 是一个文件，位于主文件夹里，但是是一个隐藏文件；
  - 其中rc是run command的意思；

- **作用：**
  - 终端的**初始化脚本**；
  - 每次执行终端程序时，都会首先执行这个脚本，完成一些**环境变量的赋值操作**；
  - 在ROS中，可以在该文件下加入ROS的初始化指令；

 

## 4.9 执行管理员权限

- **sudo指令：**
  - 在某一条指令前面加上sudo就可以以管理员权限运行；

- **从APT源上下载安装包：**
  - sudo install [软件包名称]；



# 第五节课：ROS系统安装

## 5.0 版本选择：

- 安装的Ubuntu版本是20.04，与之对应的ROS版本是Noetic；
- 与Ubuntu的离线安装不同，ROS的安装就像安装应用一样，需要联网在线安装；



## 5.1 ROS官方安装步骤

- ROS的官方网站：[ROS官网](https://www.ros.org/)；

- Noetic版本的官方安装教程：[Noetic版本ROS的官方教程](https://wiki.ros.org/noetic/Installation/Ubuntu)；

![ROS官方安装教程](images/05_ROS系统安装/ROS官方安装教程.png) 

- **配置Ubuntu的远程仓库**
  - 安装ROS需要先配置Ubuntu的远程仓库；
  - 但一般在安装系统时就配置好了，所以这里不需要再配置；
  - 这里可以选择添加清华源的链接到配置文件中；



## 5.2 导入ROS安装源

- ROS是一个包含了非常多包的一个集合，这些包都放在一个地方进行管理，那就是**ROS安装源**；
- 我们需要先将ROS的**安装源地址**添加到Ubuntu的**APT包管理器源列表**；
- 这个列表写明了有什么“应用商店”，在初始条件下系统中写有了Ubuntu的官方应用商店，即APT官方源；
- 它会告诉APT包管理器下载ROS包的下载地址；
- 其实就是相当于告诉Ubuntu：我可以从哪些源里面下载软件包，用安卓的角度来说就是给Ubuntu安装了一个ROS的应用商店；

![添加ROS的安装源](images/05_ROS系统安装/第二步_添加ROS的安装源.png)

- 官方给的链接是国外的链接，可以点击下方的**Mirrors**选择国内镜像；
- 一共有四个镜像，这里选择中科大，把命令复制到终端执行即可；

![添加中科大源](images/05_ROS系统安装/第二步_添加中科大源.png)

- 最终的运行效果如下：

![第二步最终效果](images/05_ROS系统安装/第二步最终效果.png)



## 5.3 设置安装密钥

- 第三步是进行密钥安装，复制一下两行代码在终端运行即可，如下图所示：

![第三步_添加安装密钥](images/05_ROS系统安装/第三步_添加安装密钥.png) 

- 方框中是两条指令：
  - 第一条是安装curl这个工具，复制#前面内容到终端执行；
  - 第二条可分两部分：
    - 管道符前面是从ROS的Github仓库中下载GPG公钥；
    - 管道符后面是将该公钥添加到apt的系统可信密钥库中；
    - 主要是为了后续验证ROS软件包的合法性做准备，防止下载到被篡改的文件；
- 运行两行代码后，若返回“OK”即代表成功安装了密钥。

---

**专栏：Linux中的软件安装**

Linux中的下载可以分为：普通文件下载和APT包管理器安装软件

- **普通下载**：即通过**curl/wget**下载压缩包、文档，它不需要密钥，可随意从任何网站下载，需要用户自己判断安全性；

- **APT包管理器安装软件：这种方式可以分为从Ubuntu官方软件源下载和从第三方软件源下载**
  - 前者在系统安装时已经默认预装了官方的**GPG密钥**，不需手动添加；
  - 后者需要手动添加该第三方的**GPG密钥**，否则APT会拒绝从这个源安装软件；
  - **这种GPG密钥就是git在提交Github时的一种密钥配对协议；**

---



## 5.4 下载安装ROS

- 接下来安装ROS，分别执行下面两句代码，安装完成即证明ROS安装成功。

![安装ROS系统](images/05_ROS系统安装/第四步_安装ROS系统.png) 

 

## 5.5 环境参数设置

- 接下来需要将ROS的环境设置脚本添加到终端程序的初始化脚本里，即.bashrc文件；
- 我们要做的就是在.bashrc文件中source一下ROS的环境设置脚本即可；
- 这样每次打开终端它都会执行一遍ROS的环境参数设置，完成ROS的初始化；

![设置环境参数](images/05_ROS系统安装/第五步_设置环境参数.png)

- 分别在终端执行这两句代码即可；
- 如果要测试是否安装成功，可以在终端执行：roscore，出现下面信息表示成功启动了ROS的核心：

![验证ROS是否安装成功](\images/05_ROS系统安装/第五步_验证ROS是否安装成功.png)

 

## 5.6 rosdep初始化

- 最后还需要对ROS的依赖包工具进行初始化，方便以后下载第三方的扩展软件包；
- 在终端执行下面三条指令，即可完成rosdep的初始化，其中中间框的之前已经安装过了不需要再装；

![初始化依赖包](images/05_ROS系统安装/第六步_初始化依赖包.png)



# 第六节课：应用商店APT源

## 1.APT工具介绍

- **定义：**
  - APT是Ubuntu自带的一套软件包下载工具；
  - 可以使用它从网上的源服务器下载指定的软件包并自动安装；
  - 与手机上的应用商店很类似；

- **APT的源列表：**
  - Ubuntu安装时，默认APT的源服务器只有Ubuntu的官方源（应用商店）；
  - 我们可以通过编辑APT的源列表增加新的应用商店；
  - **前面添加的ROS的源，就是添加了ROS的应用商店（前面是中科大的源）**；

![APT源列表](images/06_应用商店APT源/APT的源列表.png)



## 2.ROS的“应用商店”

### 2.1 应用商店长什么样

- 应用商店是通俗的叫法，实际上是**存放ROS的各种包的源服务器**，就像**Github那样的托管平**台;
- 网址为：[ROS应用商店网站](https://index.ros.org)

![ROS官方源列表](images/06_应用商店APT源/ROS官方源列表.png)

- 可点击**Package List**，网页将展示几乎**所有的ROS的资源，包括软件库、依赖包、源码**等等；

- 当然，我们需要选择我们对应的系统，我们选择了自己的版本：noetic；

- 这些软件包我们都可以通过apt命令来安装，安装的格式是：

  - ```bash
    sudo apt install ros-[ros版本]-name
    ```

![Noetic的PagageList](images/06_应用商店APT源/Noetic的PakageList.png)

### 2.2 每个软件包长什么样

- 我们选择里面的一个包：**rqt_robot_steering**，双击这个包进入它的界面；
  - 可以看到它们有关于这个包的**基本信息、包的源码信息以及对于这个包的关于作者等的介绍；**
  - **Website**界面有关于这个包的详细介绍；

![某个ROS包的界面](images/06_应用商店APT源/某个包的界面.png) 

- 点击右侧的**Website**，进入这个包的具体演示界面，它会详细的描述楚这个包的作用以及如何使用：

![包的Website页面](images/06_应用商店APT源/包的Website页面.png)



## 3.运行一个ROS实例

### 3.1 rqt_robot_steering实例

以上一小节的**rqt_robot_steering**这个软件包为例，讲解如何**运行一个ROS实例**。

- **安装rqt_robot_steering软件包**

  - ```bash
    sudo apt install ros-noetic-rqt-robot-steering
    ```

  - 终端运行上面指令以安装软件包；

- **运行ROS内核**

  - 另外打开一个终端，运行如下指令：

  - ```bash
    roscore
    ```

- **运行rqt_robot_steering软件包**

  - 在原来的终端中运行：

  - ```bash
    rosrun rqt_robot_steering rqt_robot_steering
    ```

  - 两个rqt_robot_steering：

    - 前面一个是包名称；
    - 后面一个是节点名称；

![运行rqt_robot_steering实例](images/06_应用商店APT源/运行rqt_robot_steering实例.png) 

### 3.2 turtlesim实例

- **再开一个终端，输入指令安装小乌龟：**

  - ```Bash
    sudo apt install ros-noetic-turtlesim
    ```

- **接着在这一个终端运行小乌龟：**

  - ```bash
    rosrun turtlesim turtlesim_node
    ```

![运行turtlesim实例](images/06_应用商店APT源/运行turtlesim实例.png) 

### 3.3 用rqt_robot_steering控制turtlesim

- 这样，小乌龟出来了，rqt_robot_steering软件包的控制界面也出来了；
- 在软件包界面的输入栏前面加上turtle1（任意写，不然不会启动）；
- 我们就可以用竖直杆控制速度，水平杆控制旋转的方向来完成仿真实验了；



# 第七节课：开源自由市场Github

## 7.1 Github应用商店

- 除了ROS的官方应用商店，Github中也有很多优质的ROS软件包；
- ROS本身和index.ros上的大部分软件包在Github都开放了源代码；

 

## 7.2 Github与index.ros的不同

- Github中的软件包都是以**源代码的形式**开源，我们下载下来后还需要**编译**才能运行；
- 所以需要先建立一个**工作空间，来进行源代码编译**；
- 所谓工作空间就是建立一个**符合某种要求的目录结构，编译器会按照这个目录建构去检索源代码完成编译**；

 

## 7.3 建立目录结构并安装Git工具

### 7.3.1 建立目录结构

- 目录结构：**HOME——>catkin_ws——>src**；

- 下载的源代码就需要放在src目录里才能正常编译，所以在终端分别执行：

  ```bash
  mkdir catkin_ws
  
  cd catkin_ws
  
  mkdir src
  
  cd src
  ```

- 这样就创建好工作空间了，后续我们自己写的源代码也会放在这个工作空间中；
- **catkin是ROS1中的编译器，catkin_ws就是catkin workplace的意思**；

### 7.3.2 安装Git工具

- 从GitHub下载或上传文件需要用到**git工具**，在终端执行：
- 注意，这句终端执行目录需要在**src目录**下执行；

```bash
sudo apt install git
```

![创建工作目录并安装Git工具](images/07_开源自由市场Github/创建工作空间并安装git工具.png)



## 7.4 下载源码包

- 完成上述工作后就可以进行源码的下载了；
- 在GitHub搜索栏中搜索：**wpr_simulation**，找到**6-robot**这一项；
- 点击进入选择**Code按钮**，复制弹出来的一串网址：https://github.com/6-robot/wpr_simulation.git；
- 接着回到终端，执行命令：

```bash
git clone https://github.com/6-robot/wpr_simulation.git
```

- 这样就可以把源代码下载到我们的**src文件夹下了（要保证在src文件夹执行）**；

![Git克隆源代码](images/07_开源自由市场Github/克隆Github源代码.png)

 

## 7.5 查看下载内容并进行编译

### 7.5.1 查看文件内容

- **wpr_simulation目录：**
  - 如下图所示即为我们从GitHub上clone下来的文件，全部文件在wpr_simulation文件夹下；

<img src="images/07_开源自由市场Github/wpr_simulation结构目录.png" alt="包的结构目录" style="zoom:150%;" />

- **scripts文件夹：**
  - 先看**scripts**文件夹，可以看到它里面放了一些**脚本文件(.sh文件)和python程序**；
  - 这些文件主要是完成**依赖包的安装和为机器人映射端口**，这类操作一般进行**一次**即可；

<img src="images/07_开源自由市场Github/scripts目录.png" alt="scripts目录" style="zoom: 150%;" />

### 7.5.2 安装依赖包

- **依赖包文件：**

  - 在scripts文件夹下可以看到有**install_for_noetic.sh**文件；
  - 这个就是用于给noetic系统**安装这个项目的依赖包**的执行文件；

- **安装依赖包：**

  - 在这个文件夹下右键，选择在终端打开，然后输入执行下面的指令，输入密码即可安装依赖包；

  ```bash
  ./install_for_noetic.sh
  ```

### 7.5.3 编译

- 安装好依赖包后，回到工作空间的入口地址：**catkin_ws**；
- 然后输入指令，它将会编译**src文件夹下的所有源代码**：

```bash
catkin_make
```

- **注意：catkin_make命令必须要在catkin_ws目录下运行。而不是src子目录**；

![编译源代码](images/07_开源自由市场Github/编译源代码.png)



## 7.6 运行包的功能

### 7.6.1 加载包的环境参数到终端命令

- 首先需要**将catkin_ws工作空间里的环境参数加载到终端里**，否则运行指令会提示找不到软件包；
- 即**用source指令载入工作空间的环境设置**，终端中执行：

```bash
source ~/catkin_ws/devel/steup.bash
```

### 7.6.2 运行编译好的ROS程序

- 完成上一步后，即可运行程序，输入指令：

```bash
roslaunch wpr_simulation wpb_simple.launch
```

- 然后就会得到如下界面：

![仿真器启动页面](images/07_开源自由市场Github/仿真器启动页面.png) 

- 这就是我们后面会经常用到的**仿真环境Gazebo**；
- 再次打开上一节课的**rqt_robot_steering**，删除前面的turtle1，就可以用这个工具控制机器人的运动了；

![rqt控制仿真器](images/07_开源自由市场Github/用rqt_robot_steering控制wpr_simulation.png) 



## 7.7 将环境参数初始化指令添加到终端初始化脚本中

- 我们当然希望每次启动终端，它就会自动的帮我们初始化环境参数；
- 我们只需要**把source指令加入到~/.bashrc文件**即可；
- 终端中输入：

```bash
gedit ~/.bashrc
```

- 在弹出的文本编辑器中，划到末尾，加上：

```bash
source ~/catkin_ws/devel/setup.bash
```

- 这样，每次启动终端它就会自动帮我们初始化;

 

## 7.8 修改ROS软件包的源代码

以之前的小乌龟为例，讲解如何**从index.ros到GitHub再自己修改源代码并编译**。

- 打开index.ros，并搜索turtlesim：

![ros.index中寻找包](images/07_开源自由市场Github/ros.index中寻找包.png) 

- 点击第一个，然后点击它的GitHub链接：

![index跳转Github](images/07_开源自由市场Github/index跳转Github.png) 

- 进入Github，点击Code，复制链接：

![img](images/07_开源自由市场Github/复制Github链接.png) 

- 打开终端，切换到src目录下，安装源码：

<img src="images/07_开源自由市场Github/安装源码.png" alt="安装源码" style="zoom:150%;" />

- 切换版本
  - 由于下载默认是ROS2的版本，需要将它切换为ROS1版本，否则会编译报错，依次进行如下操作：
    - 先进入小海龟的文件夹：**cd ros_tutorials/**；
    - 然后切换版本：**git checkout noetic-devel**；

![切换版本](images/07_开源自由市场Github/切换版本.png)

- 编译
  - 切换版本后我们可以进行编译，同样的执行下面代码：
    - 切换回入口：cd ~/catkin_ws；
    - 编译：catkin_make；

- 把小海龟跑起来
  - 编译完成后我们既可以运行这个小海龟了：
    - 先是启动ros内核：**roscore**；
    - 然后新开窗口，运行小海龟：**rosrun turtlesim turtlesim_node**；

![运行小乌龟](images/07_开源自由市场Github/运行小乌龟.png)

- 修改源代码

  - 打开**"~/catkin_ws/src/ros_tutorials/turtlesim/src/tutrle_frame.cpp"**文件；
  - 修改如下几个地方：改变框的大小和名字还有背景颜色，再次编译并运行；

  ![修改源码](images/07_开源自由市场Github/修改源码.png)

  - 可以看到它的框的大小、名字还有背景颜色都变了；
  - **这就是ROS中修改源代码整个流程和逻辑；**

  ![再次运行小乌龟](images/07_开源自由市场Github/再次运行小乌龟.png)

 

## 7.9 总结

- 这节课讲了**如何从Github中下载源码并进行编译然后运行**；
- 并展示了**如何修改源码增加自己想要的功能**；
- 这就是真正实现工程时的开发逻辑和流程；



# 第八节课：代码神器Visual Studio Code



# 第九节课：超级终端Terminator



# 第十节课：Node节点和Package包



# 第十一节课：年轻人的第一个Node节点



# 第十二节课：Topic话题和Message消息



# 第十三节课：Publisher发布者的C++实现



# 第十四节课：Subscriber订阅者的C++实现































