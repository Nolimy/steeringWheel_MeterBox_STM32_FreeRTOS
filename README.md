# LY streeringWheel MeterBox

# 关于本项目

本人的本科毕业设计，一款基于STM32F407的大学生方程式赛车方向盘，具体实现功能如下：

1. 采集整车跑动数据（实车模式）以及模拟器数据（模拟器数据），并在仪表上进行实时显示。
2. 通过4G网络，对实车的跑动数据进行实时上传，实现无线数据传输功能。
3. 能够对实车的跑动数据进行采集和保存，方便技术人员对跑动数据进行复盘和分析。
4. 实现控制器功能，能够控制如神力科莎（Assetto Corsa）、神力科莎：争锋（Assetto Corsa Competizione）、F1系列等模拟类赛车游戏。
5. 为了保证实车的可用性，需要具备高亮度的屏幕保证仪表在阳光下的可视效果。
6. 具备可编程按键，实时调整车辆状态。

本项目适用于[大学生方程式赛事](http://www.formulastudent.com.cn/)(👈戳我了解)，因此方向盘外形是依照大学生方程式赛事规则进行设计的。功能上，实车模式开发基于[河北工程大学凌云车队](https://lingyun.site)(👈戳我了解)凌云Ⅸ号电动方程式赛车。模拟器功能基于[神力科莎](https://store.steampowered.com/app/244210/Assetto_Corsa/)(👈戳我了解)进行测试。

---

# 关于开源协议

本项目是开源项目：你可以再分发之和/或依照由自由软件基金会发布的 GNU 通用公共许可证修改之，无论是版本 3 许可证，还是（按你的决定）任何以后版都可以。

发布该项目是希望它能有用，但是并无保障;甚至连可销售和符合某个特定的目的都不保证。请参看 GNU 通用公共许可证，了解详情。

你应该随程序获得一份 GNU 通用公共许可证的复本。如果没有，请看[https://www.gnu.org/licenses/](https://www.gnu.org/licenses/&gt;%E3%80%82)

![gplv3-with-text-136x68.png](readme%20md/gplv3-with-text-136x68.png)

---

# 关于结构设计

方向盘的外形和结构依照大学生方程式赛事规则进行设计：

![steeringWheel_2023_Release v2_back_up.png](readme%20md/steeringWheel_2023_Release_v2_back_up.png)

![steeringWheel_2023_Release v2_back.png](readme%20md/steeringWheel_2023_Release_v2_back.png)

![20230214153308.png](readme%20md/20230214153308.png)

![steeringWheel_2023_Release svg.png](readme%20md/steeringWheel_2023_Release_svg.png)

---

方向盘盘体宽度为250mm，高度170mm。屏幕尺寸为3.5英寸。盘体正面有8个可编程控制器按键。背面安装两个换挡拨片。方向盘上壳体和下壳体使用碳纤维板进行CNC加工，其余零部件如握把、屏幕安装罩、方向盘边缘外壳、换挡拨片连杆及换挡拨片壳体使用黑色树脂进行3D打印加工。

另外设计了一个兼容罗技G27基座的方向盘转接器，所以在我的github仓库中出现了两个3D模型，一个是使用了实车的快拆器（4滚珠），一个是使用了连接到G27的3D打印的方向盘转接器。

BOM配料单请戳👉[我](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Steering_Wheel_BOM.xlsx)

[https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Steering_Wheel_BOM.xlsx](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Steering_Wheel_BOM.xlsx)

完整装配模型请戳（实车）👉[我https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Model/steeringWheel_2023_Release v13.step](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Model/steeringWheel_2023_Release%20v13.step)

模拟器：👉[我https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Model/steeringWheel_2023_Simulator_For_G27 v3.step](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Model/steeringWheel_2023_Simulator_For_G27%20v3.step)

3D打印服务推荐嘉立创旗下三维猴：[https://www.sanweihou.com/](https://www.sanweihou.com/), 三维猴提供在线报价，CNC加工，3D打印等一站式服务。

---

# 如何使用

方向盘分为三种模式：待机模式、实车模式和模拟器模式。方向盘上电后，默认为待机模式。当方向盘收到CAN报文，则为实车模式；当方向盘收到串口报文，则为模拟器模式。在待机模式下，电脑可以识别出方向盘为USB设备，但是手柄按键无响应，此时需要使用Simhub的自定义串口设备功能给方向盘发送串口报文，方可进入模拟器模式，模拟器模式手柄按键有响应。因此，使用模拟器模式需要同时使用simhub的自定义串口设备功能。

待机模式下，SLM（换挡LED模块）12颗LED灯珠全部为蓝色。

## 大学生方程式实车使用

方向盘默认使用的是125kbps的波特率，波特率可以使用CubeMX对波特率进行配置和修改，具体CAN协议请根据自家车队的实际情况，修改BSP/CAN中的代码。

## 模拟器使用

### 方向盘连接

模拟器使用需要配合[Simhub](https://www.simhubdash.com/)进行使用。将方向盘使用USB接口连接电脑后，电脑会识别出一个虚拟串口设备和控制器设备：

![在“设置”中的“蓝牙和其他设备”中可以查看到方向盘的LY_Wheel_Controller外设。](readme%20md/LY_Controller.png)

在“设置”中的“蓝牙和其他设备”中可以查看到方向盘的LY_Wheel_Controller外设。

![在“设备管理器”中可以查看到方向盘的虚拟串口设备及其端口号。](readme%20md/USB_Serial.png)

在“设备管理器”中可以查看到方向盘的虚拟串口设备及其端口号。

方向盘控制器的校准，点击“蓝牙和其他设备”右侧的“设备和打印机”:

![controller_config.png](readme%20md/controller_config.png)

找到”LY_Wheel_Controller”，右键，点击 “游戏控制器设置”，然后点击“属性”.

![controller.png](readme%20md/controller.png)

在测试页中，可以对方向盘的按键进行测试。（默认待机模式下按下方向盘按钮是没有任何反应的）

![controller_.png](readme%20md/controller_.png)

### Simhub配置

方向盘的显示功能需要simhub配合使用，可以访问[https://www.simhubdash.com/](https://www.simhubdash.com/)下载simhub软件。这是一个非常强大的软件，支持多种模拟器游戏的数据采集，支持包括汽车仪表、arduino、G力座椅等多种外设。

安装好simhub后，打开设置界面：

![simhub1.png](readme%20md/simhub1.png)

点击插件功能：

![simhub2.png](readme%20md/simhub2.png)

打开”Custom serial devices“插件：

![simhub3.png](readme%20md/simhub3.png)

重新打开simhub后，左侧菜单中会出现”Custom Serial Devices”按钮：

![simhub4.png](readme%20md/simhub4.png)

![simhub5.png](readme%20md/simhub5.png)

根据设备管理器中显示的方向盘的[串口端口](https://www.notion.so/LY-streeringWheel-MeterBox-ad02f9fb1d354ffdb82a4e431bca5e7d)，选择serial port，我这里使用的是COM15。

![simhub6.png](readme%20md/simhub6.png)

添加游戏数据打包json脚本，将以下javaScript代码粘贴到”Uptate messages“中：

```jsx
function getCurrentLapTime(){
	var lapTime = $prop('CurrentLapTime');
	lapTime = lapTime.toString();
	if(lapTime == "00:00:00")
	{
		return lapTime;
	}
	else
		lapTime = lapTime.toString().slice(3,11);
	return lapTime;
}
function getRPM(){
	var rpm = $prop('DataCorePlugin.GameData.NewData.Rpms');
	rpm = format(rpm,"0");
	return rpm;
}
function getSpeed(){
	var speed = $prop('SpeedKmh');
	speed = format(speed, '0');
	return speed;
}
function getGear(){
	var gear = $prop('Gear');
	return gear;
}
function getBestLapTime(){
	var bestLapTime = $prop('BestLapTime');
	bestLapTime = bestLapTime.toString();
	if(bestLapTime == "00:00:00")
	{
		return bestLapTime;
	}
	else
		bestLapTime = bestLapTime.toString().slice(3,11);
	return bestLapTime;
}
function getFuel(){
	var fuel = $prop('FuelPercent');
	fuel = format(fuel, '0');
	return fuel;
}
function getRedLine(){
	var redLine = $prop('CarSettings_CurrentGearRedLineRPM');
	return redLine;
}
function getBrake(){
	var brake = $prop('Brake');
	brake = format(brake, '0');
	return brake;
}
function getThrottle(){
	var throttle = $prop('Throttle');
	throttle = format(throttle, '0');
	return throttle;
}
function getLap()
{
	lap = $prop('CurrentLap');
	return lap;
}
var speed = getSpeed();
var carData = "{\"speed\":" + getSpeed() + ",\"rpm\":" + getRPM() + ",\"cLapTime\":" +"\"" + getCurrentLapTime() + "\"," +"\"gear\":" + "\"" +getGear() + "\"" + ",\"bLapTime\":" +"\"" + getBestLapTime() + "\""+ ",\"fuel\":"+ getFuel() + ",\"redLineRPM\":"+ getRedLine()
  + ",\"brake\":" + getBrake() + ",\"throttle\":"+ getThrottle()  + ",\"lap\":"+ getLap() +"}";
return carData;
```

点击”Edit”:

![simhub7.png](readme%20md/simhub7.png)

点击”Computed value“：

![simhub8.png](readme%20md/simhub8.png)

勾选”Use JavaScript”:

![simhub9.png](readme%20md/simhub9.png)

将[代码](https://www.notion.so/LY-streeringWheel-MeterBox-ad02f9fb1d354ffdb82a4e431bca5e7d)粘贴到文本框中：

![simhub10.png](readme%20md/simhub10.png)

正常情况下Raw result中可以生成完整的json字符串。最后点击连接按钮，稍等片刻，就可以看到方向盘的SLM的全部蓝灯熄灭，此时进入模拟器模式。这时进行[手柄按键测试](https://www.notion.so/LY-streeringWheel-MeterBox-ad02f9fb1d354ffdb82a4e431bca5e7d)，可以看到按钮可以被正常检测到。

![steeringWheel.jpg](readme%20md/steeringWheel.jpg)

### 游戏内配置

以”Assetto Corsa“为例，在保证simhub后台运行的条件下，启动游戏。进入控制设置，将模拟器键位改成识别到的控制器按键键位，如下图：

![asseto Corsa1.png](readme%20md/asseto_Corsa1.png)

接下来启动游戏，就可以拥有和实车方向盘一样的体验了。

![QQ截图20230304174214.png](readme%20md/QQ%25E6%2588%25AA%25E5%259B%25BE20230304174214.png)

# 系统框架

![steeringWheel system structure chart.drawio (1).svg](readme%20md/steeringWheel_system_structure_chart.drawio_(1).svg)

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

完整的硬件工程已经开源在[嘉立创开源广场平台](https://oshwhub.com/lingyunracingteam/fang-xiang-pan-xiang-mu-_fpc-bei-mian-xia-jie-_v2-5)，PCB使用四层板，尺寸在100mm*100mm以内，嘉立创平台可免费打样（JLC YYDS）。

PS:本项目硬件部分完全由嘉立创EDA专业版设计。

# 软件部分

## 关于图形界面

图形界面使用LVGL图形库，UI设计使用LVGL官方的SquareLine工具，SquareLine能直观的进行UI设计并将UI设计导出为C文件和H文件。

![SquareLine.png](readme%20md/SquareLine.png)

## 关于数据采集

未完待续。。。