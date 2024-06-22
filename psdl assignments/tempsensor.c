#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>

#define LCD_RS PORTAbits.RA0
#define LCD_EN PORTAbits.RA1

void delay ()
{
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++);
}

void SendInstruction (int command)
{
    LCD_RS = 0;         // RS low : Instruction
    PORTB = command;
    LCD_EN = 1;         // EN High
    delay();
    LCD_EN = 0;         // EN Low; command sampled at EN falling edge
    delay();
}

void SendData (int data)
{
    LCD_RS = 1;         // RS HIGH : DATA
    PORTB = data;
    LCD_EN = 1;         // EN High
    delay();
    LCD_EN = 0;         // EN Low; data sampled at EN falling edge
    delay();
}

int Read_Temp (void)
{
    ADCON0 = 0b00011101;                // ADC on; Select channel;
    ADCON0bits.GO_DONE = 1;             // Start Conversion
    while (ADCON0bits.GO_DONE == 1);    // Wait till A/D conversion is complete
    return ADRES;                       // Return ADC result
}

void main()
{
    ADCON1 = 0x0F;
    TRISB = 0;
    TRISAbits.TRISA0 = 0;               // For register select pin
    TRISAbits.TRISA1 = 0;               // For Enable pin
    SendInstruction(0x38);              // 8 bit mode, 2 line,5x7 dots
    SendInstruction(0x01);              // Clear display
    
    for (int i = 0; i < 1000; i++)
        delay();
    
    SendInstruction(0x80);              // set address to 1st line
    unsigned int temp;
    
    while (1)
    {
        temp = Read_Temp();
        temp = ((temp * 500) / 1023);
        SendData(temp / 10 + 48);
        SendData(temp % 10 + 48);

        for (int i = 0; i < 1000; i++)
            delay();
    }
}