/*
 * mod_spi.c
 *
 *  Created on: Apr 7, 2016
 *      Author: semm
 */


#include "mod_spi.h"



void spiUCA0Init(uint8_t regConf, uint8_t clkDiv){
	  /*
	   * spiUCA0Init(FIRST_CHANGE + IDDLE_HIGH + MSB_FIRST + MODE_MASTER + DATA_8BITS, 1);
	   */
	  pinEnaFunc01(spi_simo);pinEnaFunc01(spi_somi);pinEnaFunc01(spi_clk);

	  UCA0CTL0 |= regConf + UCSYNC;  // 3-pin, 8-bit SPI master
	  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	  UCA0BR0 |= clkDiv;                          //
	  UCA0BR1 = 0;                              //
	  UCA0MCTL = 0;                             // No modulation
	  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}
uint8_t spiUCA0Transfer(uint8_t dataToSend){
	while (!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = dataToSend;
	while (!(IFG2 & UCA0RXIFG));
	return UCA0RXBUF;
}

void spiUCB0Init(uint8_t regConf, uint8_t clkDiv){
	  /*
	   * spiUCB0Init(FIRST_CHANGE + IDDLE_HIGH + MSB_FIRST + MODE_MASTER + DATA_8BITS, 1);
	   */
	  pinEnaFunc01(spi_simo);pinEnaFunc01(spi_somi);pinEnaFunc01(spi_clk);

	  UCB0CTL0 |= regConf + UCSYNC;  // 3-pin, 8-bit SPI master
	  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	  UCB0BR0 |= clkDiv;                          //
	  UCB0BR1 = 0;                              //
	  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

uint8_t spiUCB0Transfer(uint8_t dataToSend){
	while (!(IFG2 & UCB0TXIFG));
	UCB0TXBUF = dataToSend;
	while (!(IFG2 & UCB0RXIFG));
	return UCB0RXBUF;
}
