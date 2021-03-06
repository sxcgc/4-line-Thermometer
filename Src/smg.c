#include "smg.h"

int code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
int p[5];
int SMG_B=0,SMG_P=0;
int TYPE = 1 ;
int location = 3;
double SMG_num;

void SMG_Write_Bit(GPIO_TypeDef* GPIOx, uint16_t cmd)
{
    if(cmd & 0x01)
      HAL_GPIO_WritePin(GPIOx,A_Pin,GPIO_PIN_SET);
    else 
      HAL_GPIO_WritePin(GPIOx,A_Pin,GPIO_PIN_RESET);
    
    if(cmd & 0X02)
      HAL_GPIO_WritePin(GPIOx,B_Pin,GPIO_PIN_SET);
    else 
      HAL_GPIO_WritePin(GPIOx,B_Pin,GPIO_PIN_RESET);
    
    if(cmd & 0x04)
      HAL_GPIO_WritePin(GPIOx,C_Pin,GPIO_PIN_SET);
    else 
      HAL_GPIO_WritePin(GPIOx,C_Pin,GPIO_PIN_RESET);
    
    if(cmd & 0x08)
      HAL_GPIO_WritePin(GPIOx,D_Pin,GPIO_PIN_SET);
    else 
      HAL_GPIO_WritePin(GPIOx,D_Pin,GPIO_PIN_RESET);
    
    if(cmd & 0X10)
      HAL_GPIO_WritePin(GPIOx,E_Pin,GPIO_PIN_SET);
    else 
      HAL_GPIO_WritePin(GPIOx,E_Pin,GPIO_PIN_RESET);
    
    if(cmd & 0X20)
      HAL_GPIO_WritePin(GPIOx,F_Pin,GPIO_PIN_SET);
    else 
      HAL_GPIO_WritePin(GPIOx,F_Pin,GPIO_PIN_RESET);
    
    if(cmd & 0X40)
      HAL_GPIO_WritePin(GPIOx,G_Pin,GPIO_PIN_SET);
    else 
      HAL_GPIO_WritePin(GPIOx,G_Pin,GPIO_PIN_RESET);
    
    if(cmd & 0X80)
      HAL_GPIO_WritePin(GPIOx,DP_Pin,GPIO_PIN_SET);
    else 
      HAL_GPIO_WritePin(GPIOx,DP_Pin,GPIO_PIN_RESET);
    
}

void SMG_select_P(GPIO_TypeDef* GPIOx, uint16_t cmd)
{
  HAL_GPIO_WritePin(GPIOx,D1_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOx,D2_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOx,D3_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOx,D4_Pin,GPIO_PIN_RESET);
  
  switch(cmd)
  {
  case 0:
    HAL_GPIO_WritePin(GPIOx,D1_Pin,GPIO_PIN_SET);
    break;
  case 1:
    HAL_GPIO_WritePin(GPIOx,D2_Pin,GPIO_PIN_SET);
    break;
  case 2:
    HAL_GPIO_WritePin(GPIOx,D3_Pin,GPIO_PIN_SET);
    break;
  case 3:
    HAL_GPIO_WritePin(GPIOx,D4_Pin,GPIO_PIN_SET);
    break; 
  default:
    break;
    
  }
}


void Write_num(double num , int point)
{
  int index=0;
  int flag =0;
  if(num<0){
    flag = 1;
    num = -num;
  }
  int temp = (int)(num * 100);
  p[0] =  temp/10000;
  p[1] = (temp%10000)/1000;
  p[2] = (temp%1000)/100;
  p[3] = (temp%100)/10;
  p[4] = (temp%10);
  for(index =0;index<5;index++)
  {
    if(p[index]!=0)
      break;
  }
  
  index = index > point-1 ? point-1 : index;
  
  SMG_select_P(GPIOA,100);//������ͣ�
  if(SMG_P == point-1)
    SMG_Write_Bit(GPIOB,code[p[SMG_B]]&0x7f);
  else
    SMG_Write_Bit(GPIOB,code[p[SMG_B]]+0x00);
  if(TYPE ==0){
    if(SMG_P < index)
      SMG_Write_Bit(GPIOB,0xff);
    if(SMG_B == 0 && flag == 1)
    {
      SMG_Write_Bit(GPIOB,0xbf);
    }
  }
  SMG_select_P(GPIOA,(SMG_P)%4);
}

/*
num:
type: 0��ʾ�¶� 1��ʾ����
*/

void SMG_Show(double num, int type)
{
  if(type == 0)
  {
    Write_num(num,3);
  }
  else 
  {
    Write_num(num,2);
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == &htim4)
  {
    if(TYPE == 0)
      location = 0;
    else 
      location = 1;
    
    SMG_B = SMG_B>=location + 4 ? location:SMG_B;
    SMG_P = SMG_B-location; 
    SMG_Show( SMG_num,TYPE);
    SMG_B++;
    SMG_P++;
    
  }
}
