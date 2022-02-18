typedef union{
  double a;
  unsigned char b[4];
}UART_type;
UART_type data;
int i;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  data.a = -15.1;
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.write(data.b,4);
  delay(1000);
}
