#include "key.h"              
#include "stm32f1xx_hal.h"

volatile unsigned char ScanKey = 0; 
unsigned char lastkey; 
unsigned char bufKey;  
unsigned int count = 0; 





void BUTTON_Scan(void)	  
{
unsigned char key;	

  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == 0)   
    key = 1;
  else  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == 0)    
    key = 2;
	else  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == 0)    
    key =3;
	else  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14) == 0)    
    key = 4;
	else  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0)    
    key = 5;
	else  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0)    
    key = 6;
  else  key = 0;


  if (key) 
 { 
    if(key==lastkey)
    {
        if (count < (800)) count++;

        if (count == 20) 
        {
            bufKey = key;
            return;
        }

        else if (count == 800) 
        {
            count = 800+10;
            bufKey=0; 
            ScanKey = key+16;
            return;
        }
	}
    else { lastkey=key; count=0; }
 } 
  else  
  {
   if(bufKey) 
   {
    ScanKey = bufKey;
    bufKey=0;
   }
   count=0;
  }
}

unsigned char BUTTON_GetKey(void) 
{
  unsigned char key = ScanKey; 
  ScanKey = 0;
  return key;
}