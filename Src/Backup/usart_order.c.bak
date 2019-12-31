#include "usart_order.h"

uint8_t buf[1];
uint8_t Rxbuff[50];
uint8_t Rx_count_UART2,Rx_Num_UART2,Uart2Ready_R;


uint8_t buf1[1];
uint8_t Rxbuff1[50];
uint8_t Rx_count_UART1,Rx_Num_UART1,Uart1Ready_R;


uint8_t Order;
int32_t Move_Flag;

extern stm32_flash_type Adjust,a,b,c;// 0.998223;

void CLR_BUF(uint8_t *array)
{
	uint16_t i;
	for(i=0;i<50;i++)
		array[i] = 0;
}
	

int8_t Find(char *buffer,uint8_t* index,int32_t* number)
{
	char head[5];
	char *indexList[ORDERNUM]={"ASK","ADJ","A","B","C","READ","RESET","MOD3","MOD4","MOD5"};
	char ListHead[10];
	char ListEnd[10];
	uint8_t error;
	uint8_t i;
	if(strchr(buffer,',')!=strrchr(buffer,',')){
		error = 254;
#ifdef ERROR_OUTPUT
	if(error>0)
		printf("error = %08d\r\n",error);
#endif
		return error;
        }
	sscanf(buffer,"%[^+]+%[^=]=%[^,],",head,ListHead,ListEnd);
	*number = 0;
	*index = 255;
	if(strcmp(head,"AT")==0)
	{
		for(i=0;i<ORDERNUM;i++)
		{
			if(strcmp(ListHead,indexList[i])==0)
			{
			  *index = i+1;
				break;
			}
		}
    
		*number = atoi(ListEnd);
		error = 0;
	}
	else 
		error = 255;
	if(*number!=0&&*index!=255)
		printf("OK!\r\n\r\n");
#ifdef ERROR_OUTPUT
	if(error>0)
		printf("error = %08d\r\n",error);
#endif
	return error;
}
//接收完成-》回显-》查找指令表
void open_order(void)
{
  uint8_t len;
  
  if(Uart1Ready_R == SET)
  {	
    Uart1Ready_R = RESET;
    
    len=Rx_Num_UART1;
                            
    HAL_UART_Transmit_IT(&huart1,Rxbuff1,len);
                            
    printf("\r\n");
    
    Find((char*)Rxbuff1,&Order,&Move_Flag); 
    CLR_BUF(Rxbuff1);
  }
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef*UartHandle)
{ 
  
 /* if(UartHandle->Instance==USART2){
    Rxbuff[Rx_count_UART2]=buf[0]; 
    if((Rxbuff[Rx_count_UART2-1]==0x0D)&&(Rxbuff[Rx_count_UART2]==0x0A))
    { 
      Uart2Ready_R=SET; 
      Rx_Num_UART2=++Rx_count_UART2;
      Rx_count_UART2=0;
			open_order();
			switch(Order)
			{
				case 1: 
					alarmNum.doublea = Move_Flag/10.0;
					writeFlashData = alarmNum.intb;
					writeFlashTest();
					break;
				case 2:
					alarmNum.intb = *(__IO uint64_t*)(addr);
					printf("%.1lf",alarmNum.doublea);
					break;
				case 3:
					printf("Version 1.0 beta\r\n");
					break;
			}
			Order = 0;
			Move_Flag = 0;
    } 
    else Rx_count_UART2++; 
    HAL_UART_Receive_IT(&huart2,buf,1);
      //开启下一次接收中断
  }*/
    if(UartHandle->Instance==USART1){
    Rxbuff1[Rx_count_UART1]=buf1[0]; 
    if((Rxbuff1[Rx_count_UART1-1]==0x0D)&&(Rxbuff1[Rx_count_UART1]==0x0A))
    { 
      Uart1Ready_R=SET; 
      Rx_Num_UART1=++Rx_count_UART1;
      Rx_count_UART1=0;
      
      open_order();
      
      switch(Order)
      {
      case 1:
        
        printf("ASK: info all\r\n");
        printf("ADJ: adjust set\r\n");
        printf("A: a set\r\n");
        printf("B: b set\r\n");
        printf("C: c set\r\n");
        printf("READ: read all\r\n");
        printf("RESET: reset all\r\n");        
        printf("ALl input is mul by 1000000\r\nequation: A*x^2+B*x+C\r\n");
        printf("Exp: send AT+A=1000000,\\r\\n\r\n A = 1.00");
        HAL_Delay(4000);
        break;
      case 2:
        Adjust.doublea = Move_Flag/1000000.0;
        writeFlash(addr1,Adjust.intb);
        Adjust.intb = *(__IO uint64_t*)(addr1);       
        printf("Adjust:%lf\r\n",Adjust.doublea);
        HAL_Delay(2000);
        break;
      case 3:
        a.doublea = Move_Flag/1000000.0;
        writeFlash(addr2,a.intb);
        a.intb = *(__IO uint64_t*)(addr2);       
        printf("a:%lf\r\n",a.doublea);
        HAL_Delay(2000);
        break;   
      case 4:
        b.doublea = Move_Flag/1000000.0;
        writeFlash(addr3,b.intb);
        b.intb = *(__IO uint64_t*)(addr3);       
        printf("b:%lf\r\n",b.doublea);
        HAL_Delay(2000);
        break;
      case 5:
        c.doublea = Move_Flag/1000000.0;
        writeFlash(addr4,c.intb);
        c.intb = *(__IO uint64_t*)(addr4);       
        printf("c:%lf\r\n",c.doublea);
        HAL_Delay(2000);
        break;
      case 6: 
        //Adjust.intb = *(__IO uint64_t*)(addr1);       
        //a.intb = *(__IO uint64_t*)(addr2);       
        //b.intb = *(__IO uint64_t*)(addr3);
        //c.intb = *(__IO uint64_t*)(addr4);
        
        printf("Adjust:%lf  ",Adjust.doublea);
        printf("a:%lf   ",a.doublea);
        printf("b:%lf   ",b.doublea);
        printf("c:%lf   ",c.doublea); 
        break;
      case 7:
        Adjust.doublea = 0.998223;
        writeFlash(addr1,Adjust.intb);
        a.doublea = 0;
        writeFlash(addr2,a.intb);
        b.doublea = 1;
        writeFlash(addr3,b.intb);
        c.doublea = 0;
        writeFlash(addr4,c.intb);   
        break;
      }
      Order = 0;
      Move_Flag = 0;
      
    } 
    else Rx_count_UART1++; 
    HAL_UART_Receive_IT(&huart1,buf1,1);
    //开启下一次接收中断
  }
		
	
}



