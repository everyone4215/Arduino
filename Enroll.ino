int TX=1;
int RX=0;
char OPEN[12]={0x55,0xAA,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x01};
char LEDON[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x12,0x00,0x13,0x01};
char enro1[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x23,0x00,0x24,0x01};
char enro2[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x24,0x00,0x25,0x01};
char enro3[12]={0x55,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x25,0x00,0x26,0x01};
char OPENBuffer[12];
char LEDBuffer[12];
char Buffer1[12];
char Buffer2[12];
char Buffer3[12];
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
     j=0;
   }
 delay(100);
 
 Enroll();
 
}

void Enroll()
{
  bool useid=true;
  int id =0;
  delay(100);
  while(useid==true){
    useid=CheckEnrolled(id);
    if(useid==true)
    {
     id++;
    }
  }
  EnrollStart(id);
  
  Serial.print("Press finger to Enroll #");
  Serial.println(id);
  delay(100);
  while(IsPressFinger() == false) {delay(800);}
  delay(100);
  bool bret = CaptureFinger();
  Serial.println(bret);
  
  if (bret != false)
  {
    Serial.println("Remove finger");
    delay(1000);
    Serial.write(enro1,sizeof(enro1));
    delay(1000);
    if(Serial.available()>0){
    while(j<12){
      Buffer1[j]=Serial.read();
      Serial.print(Buffer1[j],HEX);
      j++;
      delay(5);
    }
    }
    j=0;
    delay(100);
    while(IsPressFinger() == true) delay(100);
    Serial.println("Press same finger again");
    while(IsPressFinger() == false) delay(100);
    delay(1000);
    bret = CaptureFinger();
    //delay(1000);
    if (bret != false)
    {
      Serial.println("Remove finger");
      delay(1000);
      Serial.write(enro2,sizeof(enro2));
      delay(1000);
      if(Serial.available()>0){
      while(j<12){
        Buffer2[j]=Serial.read();
        Serial.print(Buffer2[j],HEX);
        j++;
        delay(5);
      }
      }
      j=0;
      delay(100);
      while(IsPressFinger() == true) delay(100);
      Serial.println("Press same finger again");
      while(IsPressFinger() == false) delay(100);
      delay(1000);
      bret = CaptureFinger();

      if(bret != false)
      {
        Serial.println("Remove finger");
        delay(1000);
        Serial.write(enro3,sizeof(enro3));
        delay(1000);
        if(Serial.available()>0){
          while(j<12){
          Buffer3[j]=Serial.read();
          Serial.print(Buffer3[j],HEX);
          j++;
          delay(5);
          }
        }
          j=0;
        Serial.println("Sueessful Enroll!!");
      }
     else Serial.println("Failed to capture three finger");
    }
    else Serial.println("Failed to capture second finger");
  }
  else Serial.println("Failed to capture first finger");
}

bool CheckEnrolled(int id)
{ 
  char CheckEnrolled[12]={0x55,0xAA,0x01,0x00,0x00+id,0x00,0x00,0x00,0x21,0x00,0x21+id,0x01};
  char CheckBuffer[12];
  int i=0;
  
  Serial.write(CheckEnrolled,sizeof(CheckEnrolled)); 
  delay(1000);
  if(Serial.available()>0){
    while(i<12){
      CheckBuffer[i]=Serial.read();
      Serial.print(CheckBuffer[i],HEX);
      i++;
      delay(5);
    } 
   }
  i=0;
  delay(100);
  if(CheckBuffer[8]==0x31){
    return false;
  }
  if(CheckBuffer[8]==0x30){
    return true;
  }
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
  delay(1000);
}
