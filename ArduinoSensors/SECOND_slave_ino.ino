#include <dht11.h>

dht11 DHT11;

#define DHT11PIN 7

//Transmitter2 sketch
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);
const uint64_t pipes[6] = {
  0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL,0xF0F0F0F0C4LL,0xF0F0F0F0C5LL,0xF0F0F0F0C6LL };

short int temp;
short int humid;
int deviceid = 12;
short int data[3];
void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipes[1]);//write to rec
  //radio.openReadingPipe(1,pipes[1]);//read from rec
}

void loop(void){

   {
  Serial.println("\n");

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
		Serial.println("OK"); 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.println("Checksum error"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.println("Time out error"); 
		break;
    default: 
		Serial.println("Unknown error"); 
		break;
  }

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (°C): ");
  Serial.println((float)DHT11.temperature, 2);

}


  temp = DHT11.temperature, 2;
  humid = DHT11.humidity, 2;


  data[0] = deviceid;
  data[1] = temp;
  data[2] = humid;

  for(int l=0;l<200;l++)
  {
    //   radio.write( &temp, sizeof(temp) );
    // radio.write( &humid, sizeof(humid) );
    radio.write( &data, sizeof(data) );
    delay(100);
  }
}

