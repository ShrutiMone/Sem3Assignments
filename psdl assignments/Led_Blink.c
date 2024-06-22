
#include <xc.h>
#include<pic18f4550.h>

void MSDelay(unsigned int time)
{
    unsigned int i,j;
    for(i=0;i<time;i++)
    {
    for(j=0;j<1000;j++);
    }
    
     
}
void main(void)
{
    
    TRISB=0X00;
  
    PORTB=0XFF;
    while(1)
    {
         
        
      
       PORTB=~PORTB;
        MSDelay(500);
    }
}