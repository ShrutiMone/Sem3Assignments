#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>

void delay()
{
    for (int i = 0; i < 2000; i++)
    {
        for (int j = 0; j < 2000; j++);
    }
}

void __interrupt() RB1_isr()
{
    if (INTCON3bits.INT1IF == 1)
    {
        INTCONbits.GIE = 0;
        PORTAbits.RA4 = 1;
        delay();
        PORTAbits.RA4 = 0;
    }
    INTCON3bits.INT1IF = 0;
    INTCONbits.GIE = 1;
}

void main (void)
{
    TRISAbits.TRISA4 = 0;
    TRISBbits.TRISB1 = 1;
    INTCON2bits.INTEDG1 = 0;
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    while(1);
}