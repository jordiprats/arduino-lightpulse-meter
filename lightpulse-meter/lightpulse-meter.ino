int LDR = 5;
int LDRValue = 0;
int LDRprevi = 0;

int diferencia=20;
int going_up=0;
int count=0;
 
void setup()
{
  Serial.begin(9600);
  //pinMode(13, OUTPUT);
    
  LDRprevi = analogRead(LDR);
  Serial.println("arduino READY");
}
 
void loop()
{
  LDRValue = analogRead(LDR);
  //Serial.println(LDRValue);
    
  if (LDRValue-LDRprevi > diferencia) 
  {
    if(!going_up)
    {
      count++;
      if (count==4000)
      {
        Serial.print("1 ");
        Serial.println(count);
        count=0;
      }
      else
      {
        Serial.print("0 ");
        Serial.println(count);
      }
    }
    //digitalWrite(13, HIGH); 
    going_up=1;
  }
  else
  {
    //digitalWrite(13, LOW);
    if(LDRprevi-LDRValue > diferencia)
    {
      going_up=0;
    }
  }
  
  delay(10);
  LDRprevi=LDRValue;
}
