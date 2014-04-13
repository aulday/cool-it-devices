/* This is a simple test for two way traffic via bluetooth 
   but you can try it first using the USB cable to the serial 
   monitor without the bluetooth module connected.
   
   Note that some bluetooth modules come set to a different baud rate.
   This means you need to alter the command
                Serial.begin(9600) accordingly
   Same goes for the setting in the bottom right corner on the 
   serial monitor */             

int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V

int val = 0;           // variable to store the value read
int lastval=0;
char inMsg[4];
int inPos=0;
boolean bFirstTime = true;

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting BT link...");
//    Serial.println("OK then, you first, say something.....");
//    Serial.println("Go on, type something in the space above and hit Send,");
//    Serial.println("or just hit the Enter key");
}
 
void loop()
{
//  while(Serial.available()==0)
//  {}

//  Serial.println("");
//  Serial.println("I heard you say:");

  if( bFirstTime == true)
  {
    Serial.println("GO");    
    bFirstTime = false;
  }
  
  inPos=0;
  while(Serial.available()>0)
  {
//    Serial.write(Serial.read());// note it is Serial.WRITE
//    Serial.println(Serial.read());
    inMsg[inPos] = Serial.read();
    inPos++;
  }
  if (inPos>0)
  {
    inMsg[inPos]='\0';
//    Serial.print(inMsg);
    Serial.write(val);// note it is Serial.WRITE
    Serial.write(val+1);// note it is Serial.WRITE
  }
  
  val = analogRead(analogPin)/4;    // read the input pin
  if (val<lastval-4 || val > lastval+4)
  {
//    Serial.println("X");             // debug value
    lastval=val;
  }

}



