#include "mod_libs.h"
#include "string.h"

char BufferTx[50] = " Proyecto", BufferposTx = 0; // Buffer para enviar por UART
char BufferRx[50] = {" "}, BufferposRx = 0; // Buffer para recibir por UART

uint16_t Time = 0;

uint16_t  Adc1Tx = 0, Adc2Tx = 0;
uint16_t BufferLcd[50], bufferposlcd = 0;

short Flag = 0;

char DatoUart = 0;

int main(void) {


    loadBasicSetUp();

    adcInit(pinAna3 + pinAna4);

    lcdInit();
    lcdClear();
    delay_ms(10);

    lcdGotoxy(1, 1);
    lcdPuts("    GUIA 5  \n TEXTO ANDROID ");

    uartSetup(baudrate_115200, 0);

    delay_ms(2000);
    lcdClear();
    delay_ms(10);
    actAllInterrupts();

    while(1){

        Adc1Tx = adcRead(ChannelA3);delay_ms(10);
        Adc2Tx = adcRead(ChannelA4);delay_ms(10);

        BufferposTx = putString(BufferTx, 0, "{A=");
        BufferposTx = putInt16(BufferTx, BufferposTx, Adc1Tx, 4);
        BufferposTx = putString(BufferTx, BufferposTx, ";B=");
        BufferposTx = putInt16(BufferTx, BufferposTx, Adc2Tx, 4);
        BufferposTx = putString(BufferTx, BufferposTx, ";}\n");

        lcdGotoxy(1, 1);
        lcdPuts("\fP1:");
        lcdGotoxy(4, 1);
        lcdPrintInt16(Adc1Tx);

        lcdGotoxy(9, 1);
        lcdPuts("P2: ");
        lcdGotoxy(12, 1);
        lcdPrintInt16(Adc2Tx);

        lcdGotoxy(1, 2);
        lcdPuts(BufferRx); // Mostrar cadena en la LCD


        uartPuts(BufferTx); // Para enviar cadena por UART

        delay_ms(500);
    }
}


#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR_HOOK(void){
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR_HOOK(void){

    DatoUart = uartGetc();

     if(DatoUart == '{')
    {
        BufferposRx = putString(BufferRx, 0, "                ");
        BufferposRx = 0;
        Flag = 0;
    }
     else if (DatoUart == '}')
     {
         Flag = 1;
         BufferposRx = putString(BufferRx, BufferposRx, "\n"); //
     }


     if(Flag == 0)
     {
         BufferRx[BufferposRx -1] = DatoUart;
         BufferposRx++;
     }


    IFG2 &= ~UCA0RXIFG;
}


#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR_HOOK(void){
}

#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR_HOOK(void){
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR_HOOK(void){
}
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR_HOOK(void){
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMERA0_ISR_HOOK(void){

}


#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMERA1_ISR_HOOK(void){

}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR_HOOK(void){
}

