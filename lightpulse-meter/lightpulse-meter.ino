int LDR = 5;     //analog pin to which LDR is connected
int LDRValue = 0;      //that’s a variable to store LDR values
int LDRprevi = 0;

int diferencia=10;

int going_up=0;

int count=0;
 
void setup()
{
  Serial.begin(9600);
  //pinMode(13, OUTPUT);     //we mostly use 13 because there is already a built in yellow LED in arduino which shows output when 13 pin is enabled
    
  LDRprevi = analogRead(LDR);
}
 
void loop()
{
  LDRValue = analogRead(LDR);
  //Serial.println(LDRValue);
    
  if (LDRValue-LDRprevi > diferencia) 
  {
    if(going_up)
    {
      Serial.print("PUM"); Serial.print(count); Serial.println(""); Serial.println("");
      count++;
    }
    //digitalWrite(13, HIGH); 
    going_up=1;
  }
  else
  {
    //digitalWrite(13, LOW);
    going_up=0;
  }
  
  delay(100);
  LDRprevi=LDRValue;
}
