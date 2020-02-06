/*
 * mod_usci_xx.h
 *
 *  Created on: 1/02/2014
 *      Author: sandra
 */

#ifndef MOD_USCI_XX_H_
#define MOD_USCI_XX_H_
#include "../mod_user_defs.h"


/*UCAxCTL0, USCI_Ax Control Register 0
 * For UART Asynchronous Mode
 */
#define PARITY_ENA			UCPEN//0x80 BIT7
#define PARITY_DIS			0x00
#define EVENPARITY			UCPAR//0x40 BIT6
#define ODD_PARITY			0x00
#define MSB_FIRST			UCMSB//0x20 BIT5
#define LSB_FIRST			0x00
#define DATA_7BITS			UC7BIT//0x10 BIT4
#define DATA_8BITS			0x00
#define STOP_2BITS			UCSPB//0x08 BIT3
#define STOP_1BIT			0x00
#define MODE_UART_AUTOBR	UCMODE1+UCMODE0//0x06 BIT2+BIT1 UART mode with automatic baud rate detection
#define MODE_MP_ADDRBIT		UCMODE1//0x04 BIT2      Address-bit multiprocessor mode
#define MODE_MP_IDLE		UCMODE0//0x02 BIT1      Idle-line multiprocessor mode
#define MODE_UART			0x00//0x00 UART mode		//0x04 Address-bit multiprocessor mode
#define SYNC_SPI			UCSYNC//0x01 BIT0
#define ASYNC_UART			0x00

/*UCAxCTL1, USCI_Ax Control Register 1
 * For UART Asynchronous Mode
 */
#define CLKSOURCE_INT			UCSSEL1+UCSSEL0//0xC0 BIT7+BIT6  SMCLK
#define CLKSOURCE_AUX			UCSSEL0//0x40 BIT6 ACLK
#define CLKSOURCE_EXT			0x00// UCLK
#define ERROR_INTERRUPT_ENA 	UCRXEIE//0x20 BIT5 RX Error interrupt enable
#define ERROR_INTERRUPT_DES		0x00
#define BREAK_INTERRUPT_ENA		UCBRKIE//0x10 BIT4 Break interrupt enable
#define BREAK_INTERRUPT_DES		0x00
#define SLEEP_MODE_ENA			UCDORM//0x08//BIT3 Dormant (Sleep) Mode
#define SLEEP_MODE_DIS			0x00
#define MP_MODE_ADDR2TX			UCTXADDR//0x04 BIT2
#define MP_MODE_BREAK2TX		UCTXBRK//0x02 BIT2      Send next Data as Address
#define RESET_UART_ENA			UCSWRST //0x01 BIT0 USCI Software Reset

#define baudrate_arg0			uint8_t var_br0,uint8_t var_br1,uint8_t var_mctl
#define uart_hwd_rx_int_flag	0x01
#define uart_hwd_tx_int_flag	0x02








inline void USCI_A0_EnaInt(uint8_t reg_mask);
inline void USCI_A0_DisInt(uint8_t reg_mask);

inline void USCI_A0_EnaInt(uint8_t reg_mask){
	IFG2 &= ~(reg_mask);
    IE2 |= reg_mask;
}
inline void USCI_A0_DisInt(uint8_t reg_mask){
	IFG2 &= ~(reg_mask);
    IE2 &= ~(reg_mask);
}





/*DE LA TABLA COOMONLY BAUD RATES SE TOMA (UCBRSx)(UCBRx)
* Y DE LA PAGINA MSPGCC  (UMCTLx)(UBRx0)(UBRx0)
* */
#if DCO_frec_MHz==1
#define baudrate_1200      0x41,0x03,0x00
#define baudrate_2400      0xA0,0x01,0x00
#define baudrate_4800      0xD0,0x00,0x00
#define baudrate_9600      0x68,0x00,0x00
#define baudrate_19200     0x34,0x00,0x00
#define baudrate_38400     0x1A,0x00,0x00
#define baudrate_57600     0x11,0x00,0x00
#define baudrate_115200    0x08,0x00,0x00//3%
#endif

#if DCO_frec_MHz==8

#define baudrate_1200      0x0A,0x1A,0x00
#define baudrate_2400      0x05,0x0D,0x00
#define baudrate_4800      0x82,0x06,0x00
#define baudrate_9600      0x41,0x03,0x00
#define baudrate_19200     0xA0,0x01,0x00
#define baudrate_38400     0xD0,0x00,0x00
#define baudrate_57600     0x8A,0x00,0x00
#define baudrate_115200    0x45,0x00,0x00
#define baudrate_230400    0x22,0x00,0x00//1.5%
#define baudrate_460800    0x11,0x00,0x00//2.8%
#define baudrate_614400    0x0D,0x00,0x00//1.6%
#define baudrate_921600    0x08,0x00,0x00//7.4%

#endif

#if DCO_frec_MHz==12

#define baudrate_1200      0x10,0x27,0x00
#define baudrate_2400      0x88,0x13,0x00
#define baudrate_4800      0xC4,0x09,0x00
#define baudrate_9600      0xE2,0x04,0x00
#define baudrate_19200     0x71,0x02,0x00
#define baudrate_38400     0x38,0x01,0x00
#define baudrate_57600     0xD0,0x00,0x00
#define baudrate_115200    0x68,0x00,0x00
#define baudrate_230400    0x34,0x00,0x00//
#define baudrate_460800    0x1A,0x00,0x00//1.6%
#define baudrate_614400    0x13,0x00,0x00//2.4%
#define baudrate_921600    0x0D,0x00,0x00//1.6%
#define baudrate_1228800   0x09,0x00,0x00//4.8%
#define baudrate_3000000   0x04,0x00,0x00//0.0%
#define baudrate_6000000   0x02,0x00,0x00//0.0%

#endif

#if DCO_frec_MHz==16

#define baudrate_1200      0x15,0x34,0x00
#define baudrate_2400      0x0A,0x1A,0x00
#define baudrate_4800      0x05,0x0D,0x00
#define baudrate_9600      0x82,0x06,0x00
#define baudrate_19200     0x41,0x03,0x00//09
#define baudrate_38400     0xA0,0x01,0x00
#define baudrate_57600     0x15,0x01,0x00
#define baudrate_115200    0x8A,0x00,0x00
#define baudrate_230400    0x45,0x00,0x00//
#define baudrate_460800    0x22,0x00,0x00//1.5%
#define baudrate_614400    0x1A,0x00,0x00//1.6%
#define baudrate_921600    0x11,0x00,0x00//2.8%
#define baudrate_1228800   0x0D,0x00,0x00//1.6%

#endif



#endif /* MOD_USCI_XX_H_ */
