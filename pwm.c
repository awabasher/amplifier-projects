#include "extra.h"

#include <stdint.h>
#include <stddef.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Types.h>

#include "Board.h"
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>

//PWM period in microseconds
#define PWM_PER_US 25

//PWM duty cycle in microseconds
#define PWM_INIT_DUTY (PWM_PER_US / 2)

//Sleep for 1 millisecond (1 tick is 10us)
#define SLEEP_1MS 100

void mainThread(UArg a1, UArg a2)
{
    PWM_Handle pwm1;

    GPIO_init();
    UART_init();

    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    //Only needed in UART_DATA_TEXT mode
    //uartParams.readReturnMode = UART_RETURN_FULL;
    //Same?
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;
    uart = UART_open(Board_UART0, &uartParams);
    if (uart == NULL)
    {
        //Open failed
        while (1)
            ;
    }

    UART_printf(uart, "UART initialised\r\n");

    UART_printf(uart, "Initialising PWM output on pin DIO21...");

    PWM_init();
    PWM_Params pwmparams;
    PWM_Params_init(&pwmparams);
    pwmparams.dutyUnits = PWM_DUTY_US;
    pwmparams.dutyValue = PWM_INIT_DUTY;
    pwmparams.periodUnits = PWM_PERIOD_US;
    pwmparams.periodValue = PWM_PER_US;
    pwm1 = PWM_open(Board_PWM2, &pwmparams);
    if (pwm1 == NULL)
    {
        /* Board_PWM0 did not open */
        UART_printf(uart, "Error initialising PWM 2\r\n");
        while (1)
            ;
    }

    PWM_start(pwm1);

    UART_printf(uart, "\tDone.\r\n");

    while (1)
    {
        //TODO: Using Task_sleep and PWM_setDuty, complete the questions in the lab sheet

        //e.g: Sleep for 1 second
        //Task_sleep(SLEEP_1MS * 1000)

        //e.g: Set PWM duty to 15us on, 10us off
        //off time = period - on time
        //10us = 25us - 15us
        //PWM_setDuty(pwm1, 15)
    }

    return;
}
