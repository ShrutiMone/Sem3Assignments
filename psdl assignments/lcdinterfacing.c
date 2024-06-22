#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>

#define LCD_RS PORTAbits.RA0
#define LCD_EN PORTAbits.RA1

void delay ()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 100; j++);
}

void SendInstruction(unsigned char command)
{
    LCD_RS = 0; // RS low : Instruction
    PORTB = command;
    LCD_EN = 1; // EN High
    delay();
    LCD_EN = 0; // EN Low; command sampled at EN falling edge
    delay();
}

void SendData(unsigned char data)
{
    LCD_RS = 1; // RS HIGH : DATA
    PORTB = data;
    LCD_EN = 1; // EN High
    delay();
    LCD_EN = 0; // EN Low; data sampled at EN falling edge
    delay();
}

void main()
{
    ADCON1 = 0x0F;
    TRISB = 0;
    TRISAbits.TRISA0 = 0;  // For register select pin
    TRISAbits.TRISA1 = 0;  // For Enable pin
    SendInstruction(0x38); // 8 bit mode, 2 line,5x7 dots
    SendInstruction(0x01); // Clear display
    
    for (int i = 0; i < 100; i++)
        delay();

    SendInstruction(0x80); // set address to 1st line
    char *msg1 = "12345";
    
    while (*msg1 != '\0')
    {
        SendData(*msg1);
        msg1++;
    }

    for (int i = 0; i < 100; i++)
        delay();

    SendInstruction(0xC0); // move cursor to second line
    char *msg2 = "name";
    int i = 0;

    while (msg2[i] != '\0')
    {
        SendData(msg2[i]);
        i++;
    }

    for (int i = 0; i < 100; i++)
        delay();

    while (1);
}