#include <DHT22.h>
// Only used for sprintf
#include <stdio.h>

// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_PIN 7

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

//Reciever Sketch
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

short int data[3];
short int msg[5];
RF24 radio(9,10);
const uint64_t pipes[6] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL,0xF0F0F0F0C4LL,0xF0F0F0F0C5LL,0xF0F0F0F0C6LL };

void setup(){
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(1,pipes[1]);//read from tran1
//radio.openWritingPipe(pipes[2]);//write to tran1
//------open pipe to other rf24----//
radio.openReadingPipe(2,pipes[3]);//read from tran2
//radio.openWritingPipe(pipes[2]);//write to tran2
radio.startListening();
}

void loop(void){
  
    
  for(int l=0;l<20;l++)
  {
delay(100);    
radio.startListening();
delay(100);
if (radio.available()){
bool done = false;
done = radio.read(msg, 5);
for(int i=0;i<5;i++){
Serial.print(msg[i]);}
/* you would use a method here to check the value of the first byte, so then you know if its from glove one of two as it will be byte value of 1 or 2. Then do something…*/

Serial.println("");
}
else{Serial.println("No radio available");


}
  }
  delay(2000);

{ 
    DHT22_ERROR_t errorCode;

    // The sensor can only be read from every 1-2s, and requires a minimum
    // 2s warm-up after power-on.


   // Serial.print("Requesting data...");
    errorCode = myDHT22.readData();
    switch(errorCode)
    {
    case DHT_ERROR_NONE:
     // Serial.print("Got Data ");
//      Serial.print(myDHT22.getTemperatureC());
//      Serial.print("C ");
//      Serial.print(myDHT22.getHumidity());
//      Serial.println("%");
      // Alternately, with integer formatting which is clumsier but more compact to store and
      // can be compared reliably for equality:
      //	  
      char buf[128];
 //     sprintf(buf, "Integer-only reading: Temperature %hi.%01hi C, Humidity %i.%01i %% RH",
 //     myDHT22.getTemperatureCInt()/10, abs(myDHT22.getTemperatureCInt()%10),
 //     myDHT22.getHumidityInt()/10, myDHT22.getHumidityInt()%10);
 //     Serial.println(buf);
      break;
    case DHT_ERROR_CHECKSUM:
      Serial.print("check sum error ");
//      Serial.print(myDHT22.getTemperatureC());
//      Serial.print("C ");
//      Serial.print(myDHT22.getHumidity());
//      Serial.println("%");
      break;
    case DHT_BUS_HUNG:
      Serial.println("BUS Hung ");
      break;
    case DHT_ERROR_NOT_PRESENT:
      Serial.println("Not Present ");
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      Serial.println("ACK time out ");
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      Serial.println("Sync Timeout ");
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      Serial.println("Data Timeout ");
      break;
    case DHT_ERROR_TOOQUICK:
      Serial.println("Polled to quick ");
      break;
    }
    
    Serial.print("00");
    Serial.print(myDHT22.getTemperatureCInt());
    Serial.print(myDHT22.getHumidityInt());
    Serial.println("");    
  }

}
