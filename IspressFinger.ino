int TX=1;
int RX=0;
int j=0;
char LEDON [12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x12,0x00,0x13,0x01};
char OPEN[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x01};
char OPENBuffer[12];
char LEDBuffer[12];
void setup() {
 Serial.begin(9600);
 delay(100);
 Serial.write(OPEN,sizeof(OPEN));
 delay(1000);
 if(Serial.available()>0)
 {
    while(j<12){
      OPENBuffer[j]=Serial.read();
      Serial.print(OPENBuffer[j],HEX);
      j++;
      delay(5);
    } 
 }
 j=0;
 delay(100);
 Serial.write(LEDON,sizeof(LEDON));
 delay(1000);
 if(Serial.available()>0){
    while(j<12){
      LEDBuffer[j]=Serial.read();
      Serial.print(LEDBuffer[j],HEX);
      j++;
      delay(5);
    } 
   }
 delay(100);
 j=0;

 while(IsPressFinger() ==false) {delay(800);}
}

bool IsPressFinger()
{
  char IsPressFinger[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x26,0x00,0x27,0x01};
  char PressBuffer[12];
  int i=0;
  bool id,id2;
  Serial.write(IsPressFinger,sizeof(IsPressFinger));
  delay(1000);
  
  while(Serial.available()>0){
    if(i<12){
      PressBuffer[i]=Serial.read();
      Serial.print(PressBuffer[i],HEX);
      i++;
      delay(5);
    } 
   }
   i=0;
   if(PressBuffer[10]==0x52) 
   {
      Serial.println("NO");
      id2=false;
      return id2 ;
   }
   else
   {  
      Serial.println("OK");
      id=true;
      return id;     
   }
}

void loop() {
 delay(10000); 
}

