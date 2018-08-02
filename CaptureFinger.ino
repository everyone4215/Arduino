int TX=1;
int Rx=0;
char LEDON [12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x12,0x00,0x13,0x01};
char OPEN[12]={0x55,0xAA,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x01};
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

 bool bret=CaptureFinger();
 Serial.println(bret);
}

bool CaptureFinger()
{
 int i=0;
 char CaptureFinger[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x60,0x00,0x61,0x01};
 char Capturebuffer[12];
 bool id,id2;
 Serial.write(CaptureFinger,sizeof(CaptureFinger));
 delay(1000);
 if(Serial.available()>0){
    while(i<12){
      Capturebuffer[i]=Serial.read();
      Serial.print(Capturebuffer[i],HEX);
      i++;
      delay(5);
    }
  }
 i=0;
   if(Capturebuffer[8]==0x30)
   {
    Serial.println("yes");  //按壓
    id2=true;
    return id2; 
   }
   else if(Capturebuffer[8]==0x31)
   {
    Serial.println("no");  //不押
    id=false;
    return id; 
   }
}

void loop() {
  delay(10000);
}
