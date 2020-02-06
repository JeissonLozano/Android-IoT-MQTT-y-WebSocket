/*
 * mod_uart.h
 *
 *  Created on: Sep 4, 2013
 *      Author: fabianrcm
 */

#ifndef MOD_UART_H_
#define MOD_UART_H_

#include "mod_core.h"


#ifdef __MSP430_HAS_USCI__
#include <stdint.h>
#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_usci_xx.h"

#endif


#define uart_software_txdelaybit		DCO_frec_MHz*1000000/uart_swd_frec-9//
#define uart_software_rxdelaybit		DCO_frec_MHz*1000000/uart_swd_frec-14//12-15
#define uart_swd_delay05bit		DCO_frec_MHz*500000/uart_swd_frec-5


void uartSetup(baudrate_arg0,uint8_t user_modes);
void uartPutc(uint8_t dato_uart);
void uartPuts(char message []);
uint8_t uartGetc(void);



void uartSoftSetup(void);
void uartSoftPutc(uint8_t data_uart);
void uartSoftPuts(char message []);
inline uint8_t uartSoftGetc(void);

inline uint8_t uartSoftGetc(void){
	uint8_t data_uart=0,pos_uart=0x01,count_uart=8;
	delay_cycles((uart_software_rxdelaybit)/5);
	while(count_uart){
		delay_cycles(uart_software_rxdelaybit);
		data_uart |= pinDigReadWith(uart_software_rx,pos_uart);
		pos_uart=pos_uart<<1;
		count_uart--;
	}
	delay_cycles(uart_software_rxdelaybit);
	return data_uart;
}



#endif /* MOD_UART_H_ */

