#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>

void Delay();

void main (void)
{
    TRISB = 0;
    PORTB = 0xAA;

    while (1)
    {
//        PORTB = 0x01;
//        Delay();
//        PORTB = 0x02;
//        Delay();
//        PORTB = 0x04;
//        Delay();
//        PORTB = 0x08;
//        Delay();
//        PORTB = 0x10;
//        Delay();
//        PORTB = 0x20;
//        Delay();
//        PORTB = 0x40;
//        Delay();
//        PORTB = 0x80;
//        Delay();
        
        PORTB = ~PORTB;
        Delay(200);
    }

    return;
}

//void Delay()
//{
//    T0CON = 0x07;
//    TMR0 = 18720;
//    INTCONbits.TMR0IF = 0;
//    T0CONbits.TMR0ON = 1;
//    while (INTCONbits.TMR0IF == 0);
//    INTCONbits.TMR0IF = 0;
//    T0CONbits.TMR0ON = 0;
//    return;
//}

void Delay(unsigned int t)
{
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < 200; j++);
    }
}