void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void blink(unsigned long interval)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
  digitalWrite(LED_BUILTIN, LOW);
  delay(interval/2);
}

void loop() {

  if(Serial.available() > 1)
  {
    byte data[2];
    byte numRead;
    numRead = Serial.readBytes(data,2);
    if(numRead == 2)
    {
      blink(500);
      int val = data[0] << 8 | data[1];
      if(val == 512)
        Serial.println(val);
       else
        Serial.println("harrumph");
    }
    
  }

}
