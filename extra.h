/*
 * extra.h
 *
 *  Created on: 19 Dec 2017
 *      Author: scott
 */

#ifndef EXTRA_H_
#define EXTRA_H_

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <xdc/runtime/Types.h>

#include <ti/drivers/UART.h>

void UART_printf(UART_Handle uart, const char *fmt, ...);

void UART_readFlush(UART_Handle uart);

//BIOS Task library
#include <ti/sysbios/knl/Task.h>
//main thread
extern void mainThread(UArg a1, UArg a2);

extern UART_Handle uart;

#endif /* EXTRA_H_ */
