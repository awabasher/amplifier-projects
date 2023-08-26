/*
 * Copyright (c) 2016-2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,

 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_tirtos.c ========
 */

#include "extra.h"

#include <stdint.h>

/* Example/Board Header files */
#include "Board.h"
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <xdc/runtime/Timestamp.h>

#include <time.h>

/* Stack size in bytes */
#define THREADSTACKSIZE    2048

/*
 *  ======== main ========
 */

volatile int b;

int main(void)
{
    /* Call driver init functions */
    Board_initGeneral();

    GPIO_init();
    UART_init();

    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;

    /* UART_MODE_BLOCKING does not work when called from main() as
     * the SYS/BIOS task scheduler has not started and so it cannot
     * block on a semaphore in UARTCC26XX.c (Line 1135)
     *
     * Therefore, we use UART_MODE_CALLBACK.  This returns
     * immediately (possibly before the UART write is done) and so
     * is semi-functional.
     *
     * Note: The callback function will never be called.
     *
     * Note: any function called from main() experiences similar
     * issues.  To use MODE_BLOCKING, you must start the task
     * scheduler using BIOS_start() and then call printf from a
     * task, SWI or HWI context.  See example 2 (hellotask_gcc)
     */
    uartParams.writeMode = UART_MODE_CALLBACK;

    uart = UART_open(Board_UART0, &uartParams);
    if (uart == NULL)
    {
        //Open failed
        while (1)
            ;
    }

    UART_printf(uart, "Hello World!\r\n");
    UART_printf(uart, "Hello Universe!\r\n");

    /*
     * Need to wait a while for the previous prints to clear as there's no callbacks / blocking.
     */
    volatile int b = 1000000;
    while(b--);

    UART_printf(uart, "4 times 5 is %i\r\n", 20);

    return (0);
}
