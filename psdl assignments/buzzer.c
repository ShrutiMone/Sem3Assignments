#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>

int buzz_on = 0;
int count = 0;

void main(void)
{
    TRISAbits.TRISA5 = 0;

    TMR1 = 0x6D84;
    T1CON = 0xB0;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    T1CONbits.TMR1ON = 1;
    while (1);
}

void __interrupt() timerl_isr()
{
    if (PIR1bits.TMR1IF == 1)
    {
        INTCONbits.GIE = 0;
        count++;
        if (buzz_on == 0 && count == 40)
        {
            buzz_on = 1;
            PORTAbits.RA5 = 1;
            count = 0;
        }
        if (buzz_on == 1 && count == 10)
        {
            buzz_on = 0;
            PORTAbits.RA5 = 0;
            count = 0;
        }
        PIR1bits.TMR1IF = 0;
        TMR1 = 0x6D84;
        INTCONbits. GIE = 1;
    }
}