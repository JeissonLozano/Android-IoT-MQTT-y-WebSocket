/*
 * mod_spi.h
 *
 *  Created on: Apr 7, 2016
 *      Author: semm
 */

#ifndef MOD_LIBRARY_MOD_SPI_H_
#define MOD_LIBRARY_MOD_SPI_H_

#include <stdint.h>
#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_usci_xx.h"

#define FIRST_CHANGE	0
#define FIRST_CAPTURE	UCCKPH
#define IDDLE_HIGH		UCCKPL
#define IDDLE_LOW		0
#define MSB_FIRST		UCMSB
//#define LSB_FIRST		0
#define MODE_MASTER		UCMST
#define MODE_SLAVE		0
//#define DATA_8BITS		0
#define DATA_7BITS		UC7BIT


void spiUCA0Init(uint8_t regConf, uint8_t clkDiv);
uint8_t spiUCA0Transfer(uint8_t dataToSend);

void spiUCB0Init(uint8_t regConf, uint8_t clkDiv);
uint8_t spiUCB0Transfer(uint8_t dataToSend);




#endif /* MOD_LIBRARY_MOD_SPI_H_ */
