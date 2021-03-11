#include"..\lib\main.h"
#include"..\lib\LCD4bit.h"

sbit Relay = P3^6;
sbit Buzz =P3^7;
unsigned char code keypad[4][3]={'1','2','3','4','5','6','7','8','9','*','0','#'};
unsigned char pass[6]={'1','4','1','0','0','0'};
unsigned char check[6];
//----------------------------------------------------------------------------------

void warning()
{
    unsigned char count = 10;
    while(count--)
    {
         Buzz= 1;
         Delay_ms(200);
         Buzz =0;
         Delay_ms(200);
    }
}
unsigned char quetphim()
{
   unsigned char c, r;
   P1=0x0F;
   Delay_us(2);
   if(P1!=0x0F)   //Ðieu kien này có nghia gì?
   {
      for(c=0;c<3;c++)                     //Tien hanh quet tung cot
      {
         P1=~(0x01<<(4+c));
         Delay_ms(1);
         for(r=0;r<4;r++)          //Tien hanh kiem tra tung hang
         {
            if((P1&(0x01<<r))==0)
            {
               while((P1&(0x01<<r))==0);
               return keypad[r][c]; //Hàm này làm gì?
            }
         }
      }
   }
   return 0;
}
unsigned char sosanh(unsigned char a[], unsigned char b[])
{
   unsigned char i;
   for(i=0;i<6;i++)
   {
      if(a[i]!=b[i]) return 0;
   }
   return 1;
}
void main()
{
   unsigned char key=0,i=0,j=0;
   LCD_Init();
   Relay=0;
   Buzz = 0;

   while(1)
   {
      LCD_Clear();
      LCD_Gotoxy(0,0);
      LCD_Puts("ENTER PASSWORD:");
      LCD_Gotoxy(0,1);
      i=0;
      while(i<6)
      {
          key=quetphim();
          if(key)
          {
             LCD_Gotoxy(i,1);
             LCD_PutChar(key);
             check[i]=key;
             key=0;
             i++;
           }
       }

       if(sosanh(pass,check))
       {
          LCD_Gotoxy(0,1);
          LCD_Puts("TRUE...");
          Relay=1;
          Delay_ms(3000);
          Relay=0;
          j=0;
       }
       else
       {
          j++;
          if(j>=3)
          {
              LCD_Gotoxy(0,1);
              LCD_Puts("Warning...");
              warning();
              j=0;
          }
          else
          {
              LCD_Gotoxy(0,1);
              LCD_Puts("Error...");
              Delay_ms(500);
          }
       }
  }
}