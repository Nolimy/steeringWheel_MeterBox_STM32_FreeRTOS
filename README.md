# LY streeringWheel MeterBox

# 关于本项目

这个项目是我的本科毕业设计课题，一款基于STM32F407的功能强大的大学生方程式赛车方向盘，具体实现功能如下：

1. 采集整车跑动数据（实车模式）以及模拟器数据（模拟器数据），并在仪表上进行实时显示。
2. 通过4G网络，对实车的跑动数据进行实时上传，实现无线数据传输功能。
3. 能够对实车的跑动数据进行采集和保存，方便技术人员对跑动数据进行复盘和分析。
4. 实现控制器功能，能够控制如神力科莎（Assetto Corsa）、神力科莎：争锋（Assetto Corsa Competizione）、F1系列等模拟类赛车游戏。
5. 为了保证实车的可用性，需要具备高亮度的屏幕保证仪表在阳光下的可视效果。
6. 具备可编程按键，实时调整车辆状态。

本项目适用于[大学生方程式赛事](http://www.formulastudent.com.cn/)(👈戳我了解)，因此方向盘外形是依照大学生方程式赛事规则进行设计的。功能上，实车模式开发基于[河北工程大学凌云车队](https://lingyun.site)(👈戳我了解)凌云Ⅸ号电动方程式赛车。模拟器功能基于[神力科莎](https://store.steampowered.com/app/244210/Assetto_Corsa/)(👈戳我了解)进行测试。

---

# 关于结构设计

方向盘的外形和结构依照大学生方程式赛事规则进行设计：

![steeringWheel_2023_Release v2_back_up.png](readme%20md/steeringWheel_2023_Release_v2_back_up.png)

![steeringWheel_2023_Release v2_back.png](readme%20md/steeringWheel_2023_Release_v2_back.png)

---

![20230214153308.png](readme%20md/20230214153308.png)

![steeringWheel_2023_Release_front.png](readme%20md/steeringWheel_2023_Release_front.png)

方向盘盘体宽度为250mm，高度170mm。屏幕尺寸为3.5英寸。盘体正面有8个可编程控制器按键。背面安装两个换挡拨片。方向盘上壳体和下壳体使用碳纤维板进行CNC加工，其余零部件如握把、屏幕安装罩、方向盘边缘外壳、换挡拨片连杆及换挡拨片壳体使用黑色树脂进行3D打印加工。

BOM配料单请戳👉[我](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Steering_Wheel_BOM.xlsx)

[https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Steering_Wheel_BOM.xlsx](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Steering_Wheel_BOM.xlsx)

完整装配模型请戳👉[我https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Model/steeringWheel_2023_Release v13.step](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Model/steeringWheel_2023_Release%20v13.step)

3D打印服务推荐嘉立创旗下三维猴：[https://www.sanweihou.com/](https://www.sanweihou.com/), 三维猴提供在线报价，CNC加工，3D打印等一站式服务。

---

# 关于电路设计

主控使用STM32F407ZET6(裆燃也可以使用ROM更大的STM32F407ZGT6)，鉴于STM32系列芯片的价格偏高，大家也可以选择其他的如GD32等国产芯片进行替代（目前我还没有测试过）。

![STM32F407.png](readme%20md/STM32F407.png)

无线数传功能上，使用4G模块，采用移远的BC260Y，使用串口与STM32主控进行通信，将主控采集到的数据通过MQTT发送给服务器。

![BC260Y.png](readme%20md/BC260Y.png)

屏幕使用了柯达科的KD035HVFMD145-01（[datasheet](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Hardware/Datasheet/LCD/1707022343KD035HVFMD145-01%20SPEC%20V1.0.pdf)）,屏幕使用ST7796s控制器，MCU通过8080时序对屏幕进行控制。该屏幕的亮度最高为950尼特，基本满足了阳光下的可视需求。

![LCD.png](readme%20md/LCD.png)

换挡提示灯条使用WS2812B LED，通过STM32的TIM定时器 DMA对LED进行控制。

![WS2812B.png](readme%20md/WS2812B.png)

使用NXP的TJA1050收发器，对实车跑动数据使用CAN进行采集。

![CAN原理图.png](readme%20md/CAN%25E5%258E%259F%25E7%2590%2586%25E5%259B%25BE.png)

方向盘为USB复合设备，通过USB虚拟串口，对模拟器的跑动数据进行采集。此功能依赖于Simhub软件。同时，还包括一路joystick控制器功能，能够对游戏中的车辆进行控制，如换挡，DRS等功能。