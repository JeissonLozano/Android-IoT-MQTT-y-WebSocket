/*
 * mod_uart.c
 *
 *  Created on: Sep 4, 2013
 *      Author: fabianrcm
 */
#include "mod_uart.h"


#if defined(uart_tx)&&defined(uart_rx)&&defined(__MSP430_HAS_USCI__)

void uartSetup(baudrate_arg0,uint8_t user_modes){
	/*
	 * Uart en pines especificados por el fabricante
	 * uartSetup(baudrate_valor,configuracion)
	 * baudrate_valor=baudrate_19200 o baudrate_9600 o baudrate_115200....
	 * configuracion = DATA_8BITS+PARITY_DIS+STOP_1BIT
	 * ej:
	 * uartSetup(baudrate_19200,DATA_8BITS+PARITY_DIS+STOP_1BIT);
	 */
	  //P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	  //P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
	  pinEnaFunc01(uart_tx);pinEnaFunc01(uart_rx);
	  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	  UCA0BR0 = var_br0;                            // 1MHz 9600
	  UCA0BR1 = var_br1;                            // 1MHz 9600
	  UCA0MCTL = 0;//UCBRS0;                        // Modulation UCBRSx = 1
	  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	  IE2 |= UCA0RXIE;



	/*
	UCA0CTL1 |= RESET_UART_ENA;//Hold USCI state machine
	UCA0CTL1 = CLKSOURCE_INT+RESET_UART_ENA;//clk selection
	UCA0CTL0 = user_modes;//modes configuration
	UCA0MCTL = var_mctl;UCA0BR0 = var_br0;UCA0BR1 = var_br1;//Baudrate configuration
	pinEnaFunc01(uart_tx);pinEnaFunc01(uart_rx);
	USCI_A0_EnaInt(uart_hwd_rx_int_flag);//Activate rx hardware interruption
	UCA0CTL1 &= ~(RESET_UART_ENA);//Restart USCI state machine
	USCI_A0_EnaInt(uart_hwd_rx_int_flag);//Activate rx hardware interruption*/
}

void uartPutc(uint8_t dato_uart){
	/*
	 * Envia un solo valor
	 * uartPutc(Value);
	 */
	while (!(IFG2 & UCA0TXIFG));	// USCI_A0 TX buffer ready?
	UCA0TXBUF = dato_uart;	// TX -> RXed character
}

void uartPuts(char message []){
	/*
	 * uartPuts("Mensaje a enviar por UART");
	 */
	uint8_t i = 0;
	while(message[i] != 0){
		switch (message[i]) {
	    case '\n':
	    	uartPutc(10);
	    	break;
	    case '\r':
	    	uartPutc(13);
	    	break;
	    default:
	    	uartPutc(message[i]);
	    	break;
		}
		i++;
	}
}

uint8_t uartGetc(void){
	while (!(IFG2 & UCA0RXIFG));// USCI_A0 RX buffer Ready?
	return (UCA0RXBUF);
}

#endif





#if defined(uart_software_tx)&&defined(uart_software_rx)
void uartSoftSetup(void){
	/*
	 * Inicializa el UART por Software de acuerdo a la configuración en
	 * la seccion UART de "mod_user_defs.h"
	 */
	pinModeOutput(uart_software_tx);pinDigHigh(uart_software_tx);
	pinModeInput(uart_software_rx);pinEnaPullUp(uart_software_rx);pinEnaIntHighLow(uart_software_rx);
}
void uartSoftPutc( uint8_t data_uart){
	/*
	 * Envia un solo valor (Entero de 8Bits)
	 * uartSoftPutc(Value);
	 */
	pinDigLow(uart_software_tx);
	delay_cycles(4);
	delay_cycles(uart_software_txdelaybit);

	if(0x001 & data_uart){			//Desde aquí
		delay_cycles(2);
		pinDigHigh(uart_software_tx);
	}else{
		pinDigLow(uart_software_tx);
	}								//Hasta aqui hay 9 ciclos de máquina
	delay_cycles(uart_software_txdelaybit);//5

	if(0x002 & data_uart){
		delay_cycles(2);
		pinDigHigh(uart_software_tx);
	}else{
		pinDigLow(uart_software_tx);
	}
	delay_cycles(uart_software_txdelaybit);

	if(0x004 & data_uart){
		delay_cycles(2);
		pinDigHigh(uart_software_tx);
	}else{
		pinDigLow(uart_software_tx);
	}
	delay_cycles(uart_software_txdelaybit);

	if(0x008 & data_uart){
		delay_cycles(2);
		pinDigHigh(uart_software_tx);
	}else{
		pinDigLow(uart_software_tx);
	}
	delay_cycles(uart_software_txdelaybit);

	if(0x010 & data_uart){
		delay_cycles(2);
		pinDigHigh(uart_software_tx);
	}else{
		pinDigLow(uart_software_tx);
	}
	delay_cycles(uart_software_txdelaybit);

	if(0x020 & data_uart){
		delay_cycles(2);
		pinDigHigh(uart_software_tx);
	}else{
		pinDigLow(uart_software_tx);
	}
	delay_cycles(uart_software_txdelaybit);

	if(0x040 & data_uart){
		delay_cycles(2);
		pinDigHigh(uart_software_tx);
	}else{
		pinDigLow(uart_software_tx);
	}
	delay_cycles(uart_software_txdelaybit);

	if(0x080 & data_uart){
		delay_cycles(2);
		pinDigHigh(uart_software_tx);
	}else{
		pinDigLow(uart_software_tx);
	}
	delay_cycles(uart_software_txdelaybit);

	pinDigHigh(uart_software_tx);
	delay_cycles(4);
	delay_cycles(uart_software_txdelaybit);
}

void uartSoftPuts( char message []){
	/*
	 * uartSoftPuts("Mensaje a enviar por UART");
	 */
	uint8_t i = 0;
	while(message[i] != 0){
		switch (message[i]) {
	    case '\n':
	    	uartSoftPutc(10);
	    	break;
	    case '\r':
	    	uartSoftPutc(13);
	    	break;
	    default:
	    	uartSoftPutc(message[i]);
	    	break;
		}
		i++;
	}
}

#endif
