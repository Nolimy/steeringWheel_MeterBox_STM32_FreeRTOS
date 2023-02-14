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

![背面](README_md_files/b6490f50-ac3c-11ed-a83f-e5b4ea8247db_20230214155347.jpeg?v=1&type=image&token=V1:uPyrtLfuoX9Gf8YNbS66Tf_nTc3vJGR6n8Ltcy9P-p0)

![输入图片描述](README_md_files/d20c4c70-ac3c-11ed-a83f-e5b4ea8247db_20230214155434.jpeg?v=1&type=image&token=V1:hZbUcnhfFrpEFSsxWEsi8dpReqXUMu8zdpUomGgmLNI)

![输入图片描述](README_md_files/db4f5ca0-ac3c-11ed-a83f-e5b4ea8247db_20230214155449.jpeg?v=1&type=image&token=V1:EZTy8AwpmqXvu3b18-Adg4PVoRo2cFnMy6XEuh_xiMY)
![输入图片描述](README_md_files/e8f68a40-ac3c-11ed-a83f-e5b4ea8247db_20230214155512.jpeg?v=1&type=image&token=V1:VGK9DjiI64mcqvocUUSUgPAOOBzWkaJQGFHlk-u016U)
---



方向盘盘体宽度为250mm，高度170mm。屏幕尺寸为3.5英寸。盘体正面有8个可编程控制器按键。背面安装两个换挡拨片。方向盘上壳体和下壳体使用碳纤维板进行CNC加工，其余零部件如握把、屏幕安装罩、方向盘边缘外壳、换挡拨片连杆及换挡拨片壳体使用黑色树脂进行3D打印加工。

BOM配料单请戳👉[我](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Steering_Wheel_BOM.xlsx)

[https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Steering_Wheel_BOM.xlsx](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Steering_Wheel_BOM.xlsx)

完整装配模型请戳👉[我https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Model/steeringWheel_2023_Release v13.step](https://github.com/Nolimy/steeringWheel_MeterBox_STM32_FreeRTOS/blob/main/Model/steeringWheel_2023_Release%20v13.step)

3D打印服务推荐嘉立创旗下三维猴：[https://www.sanweihou.com/](https://www.sanweihou.com/), 三维猴提供在线报价，CNC加工，3D打印等一站式服务。

---

# 关于电路设计

主控使用STM32F407ZET6(裆燃也可以使用ROM更大的STM32F407ZGT6)，鉴于STM32系列芯片的价格偏高，大家也可以选择其他的如GD32等国产芯片进行替代（本人没有测试过）。

无线数传功能上，使用4G模块，采用移远的BC260Y，使用串口与STM32主控进行通信，将主控采集到的数据通过MQTT发送给服务器。
