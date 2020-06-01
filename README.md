# water_temperature_control
 Project about water temperature control.(From circulums design of Control Engneering Fundamentals)<br>

## Software Environment
* Toolchain/IDE : MDK-ARM V5
* standard lib

## Note
* 外设：按键、DS18B20温度传感器、LCD1602显示屏
* 使用TIM3作为系统时钟(timer.c)
* 由于系统简单，无需加入freeRTOS进行任务调度
* 用PWM来确定继电器通断的频率
