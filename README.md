# stm32_stepper_motor

## How to use
1. Configure the pin mode in stm32CubeMX.
    1. Set PA5 to GPIO_OUTPUT and name it C595_SCK
    2. Set PA7 to GPIO_OUTPUT and name it C595_DATA
    3. Set PB0 to GPIO_OUTPUT and name it C505_EN
2. Put motor.c and motor.h in your project directory
3. Include motor.h on the top of the main.c
4. Use "motor_drive(direction , speed)" to drive the motor and set the direction and speed. 