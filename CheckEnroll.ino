int TX=1;
int RX=0;
int enrollid=0;
bool useid=true;
void setup() {
 Serial.begin(9600);
}

void loop() {
  while(useid==true){
    useid=CheckEnrolled(enrollid);
    if(useid==true) enrollid++;
  }
}
bool CheckEnrolled(int id)
{ 
  char LEDON [12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x12,0x00,0x13,0x01};
  char LEDOFF[12]={0x55,0xAA,0x01,0x00,0x00,0x00,0x00,0x00,0x12,0x00,0x12,0x01};
  char CheckEnrolled[12]={0x55,0xAA,0x01,0x00,id,0x00,0x00,0x00,0x21,0x00,(0x21+id),0x01};
  char CheckBuffer[12];
  int i=0;
  
  Serial.write(CheckEnrolled,sizeof(CheckEnrolled)); 
  delay(1000);
  if(Serial.available()>0){
    while(i<12){
      CheckBuffer[i]=Serial.read();
      i++;
      delay(5);
    } 
   }
   delay(1000);
  if(CheckBuffer[8]==0x30){
    Serial.write(LEDON,sizeof(LEDON));
    delay(1000);
    return false;
  }
  if(CheckBuffer[8]==0x31){
    Serial.write(LEDON,sizeof(LEDON));
    delay(1000);
    Serial.write(LEDOFF,sizeof(LEDOFF));
    delay(1000);
    return true;
  }
}
