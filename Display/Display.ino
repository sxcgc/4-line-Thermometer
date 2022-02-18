#define shift(x) (x)>13?(x)-4:(x)
#define SET 1
#define RESET 0
uint8_t Pin_Match[10] = {0,0,9,3,7,5,4,2,8,6};
typedef union{
  double a;
  uint8_t b[4];
}UART_type;
unsigned char list[12]={ 0xFC, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0x02, 0x00 };
                        //0     1     2     3      4    5     6     7     8     9     '-'     ' ' 
int BitPin1 = 13;
int BitPin2 = 12;
int BitPin3 = 11;
int BitPin4 = 10;
int LED_a_Pin = 9;
int LED_b_Pin = 3;
int LED_c_Pin = 7;
int LED_d_Pin = 5;
int LED_e_Pin = 4;
int LED_f_Pin = 2;
int LED_g_Pin = 8;
int LED_dp_Pin = 6;
int i=0;
int index;
int Flag;
UART_type ReciveData,Res;
void setup() {
  // put your setup code here, to run once:
  pinMode(BitPin1,OUTPUT);
  pinMode(BitPin2,OUTPUT);
  pinMode(BitPin3,OUTPUT);
  pinMode(BitPin4,OUTPUT);
  pinMode(LED_a_Pin,OUTPUT);
  pinMode(LED_b_Pin,OUTPUT);
  pinMode(LED_c_Pin,OUTPUT);
  pinMode(LED_d_Pin,OUTPUT);
  pinMode(LED_e_Pin,OUTPUT);
  pinMode(LED_f_Pin,OUTPUT);
  pinMode(LED_g_Pin,OUTPUT);
  pinMode(LED_dp_Pin,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    if(index<4){
      ReciveData.b[index++] = Serial.read();  
    }
    else if(index<8){
      Res.b[(index++)%4] = Serial.read();
    }
    else if (index == 8)
    {
      index = 0;
    }
    if( Serial.available() == 1)
    {
      Flag = SET;
    }
  }
  if(Flag)
  {
    Flag = RESET;
    Serial.print("R = ");
    Serial.print(Res.a,3);
    Serial.print(" Ohm");
    
    Serial.println(ReciveData.a);
  }
  Display_Num(ReciveData.a);
  // put your main code here, to run repeatedly:
}

void LED_ShowNum(int data,int Point)
{
  unsigned char temp;
  if(data == '-')
    temp = list[10];
  else
    temp = list[data];
  if(Point == SET){
    temp = temp + 1;
  }
 
  for (int i = 0;i<8;i++)
  {
    if(temp&(0x80>>i))
      digitalWrite(Pin_Match[i+2],HIGH);
    else
      digitalWrite(Pin_Match[i+2],LOW);
  }
}

void BitSelect(int BitPin,int Level){
  if(Level == 1){
    digitalWrite(shift(BitPin),LOW);
    digitalWrite(shift(BitPin+1),HIGH);
    digitalWrite(shift(BitPin+2),HIGH);
    digitalWrite(shift(BitPin+3),HIGH);
  }
  else
  {
    digitalWrite(shift(BitPin),HIGH);
    digitalWrite(shift(BitPin+1),HIGH);
    digitalWrite(shift(BitPin+2),HIGH);
    digitalWrite(shift(BitPin+3),HIGH);
  }

}
  
void Display(int BitPin,int data,int Point)
{
  if(data == 0&&BitPin == 2)
    data = 11;
  LED_ShowNum(data,Point);
  
  switch(BitPin)
  {
    case 1:BitSelect(BitPin1,SET);break;
    case 2:BitSelect(BitPin2,SET);break;
    case 3:BitSelect(BitPin3,SET);break;
    case 4:BitSelect(BitPin4,SET);break;
  }
  delay(1);
  BitSelect(BitPin1,RESET);
}
void Display_Num(float num)
{
  num += 0.05;
  if(num>=100){
    Display(1,((int)abs(num)/100)%10,RESET);
    Display(2,((int)abs(num)/10)%10,RESET);
    Display(3,((int)abs(num))%10,SET);
    Display(4,(int)(abs(num)*10)%10,RESET);
  }
  else{
    if(num<0){
      Display(1,'-',RESET);
    
    }
    else{
      Display(1,11,RESET);
    }
    Display(2,((int)abs(num)/10)%10,RESET);
    Display(3,((int)abs(num))%10,SET);
    Display(4,(int)(abs(num)*10)%10,RESET);
  }
}

