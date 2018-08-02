int TX=1;
int RX=0;
char OPEN[12]={0x55,0xAA,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x01};
char LEDON[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x12,0x00,0x13,0x01};
char enro[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x23,0x00,0x24,0x01};
char Buffer[12];
char OPENBuffer[12];
char LEDBuffer[12];
int j=0;

void setup() {
 Serial.begin(9600);
 delay(100);
 Serial.write(OPEN,sizeof(OPEN));
 delay(1000);
 if(Serial.available()>0){
    while(j<12){
      OPENBuffer[j]=Serial.read();
      Serial.print(OPENBuffer[j],HEX);
      j++;
      delay(5);
    } 
  }
  j=0;
  delay(1000);
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
 j=0;
// delay(100);


 EnrollStart(0);
 delay(1000);
 Serial.write(enro,sizeof(enro));
 Serial.print(enro[8],HEX); 
 delay(1000);
  if(Serial.available()>0){
    while(j<12){
      Buffer[j]=Serial.read();
      Serial.print(Buffer[j],HEX);
      j++;
      delay(5);
    }
   }
 j=0;
 delay(100);
}

int EnrollStart(int id)
{
  char EnrollStart[12]={0x55,0xAA,0x01,0x00,0x00+id,0x00,0x00,0x00,0x22,0x00,0x22+id,0x01};
  char EnrollStartBuffer[12];
  int i=0;
  Serial.write(EnrollStart,sizeof(EnrollStart));
  delay(1000);
  if(Serial.available()>0){
    while(i<12){
      EnrollStartBuffer[i]=Serial.read();
      Serial.print(EnrollStartBuffer[i],HEX);
      i++;
      delay(5);
    } 
   }
  i=0;
  delay(100);
}


void loop() {
  delay(10000);

}
