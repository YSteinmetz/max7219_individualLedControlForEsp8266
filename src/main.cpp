#include <Arduino.h>
#include <SPI.h>

/*
    MAX7219 individual led control

    The code has been tested on a nodeMCU 1.0 (ESP-12E Module) with a MAX7219 Chip.
    If don't work, please check the connections.
    Connect the MAX7219 device to the following pins on the ESP8266:

    GPIO    NodeMCU   Name  |   Uno
   ===================================
     15       D8       SS   |   D10
     13       D7      MOSI  |   D11
     12       D6      MISO  |   D12
     14       D5      SCK   |   D13

   
*/

#define SS_PIN D8

void setup() {
  Serial.begin(9600);
  Serial.println("Max7219 individual led control");

  SPI.begin();
  SPI.setFrequency(10000); //10KHz
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);
}

void loop() {
  
  //Ask for the user input
  /*
    Options:
      W. for wake up the max7219
      S. for shutdown the max7219

      T. for test mode
      N. for normal mode

      M. to write the address and the data to send
  */
  //send the command list to the user
  Serial.println("");
  Serial.println("");
  Serial.println("Please select a option:");
  Serial.println("W. for wake up the max7219");
  Serial.println("S. for shutdown the max7219");
  Serial.println("T. for test mode");
  Serial.println("N. for normal mode");
  Serial.println("M. to write the address and the data to send");

  //read the user input
  while(!Serial.available());
  char option = Serial.read();

  //execute the user command
  switch(option){
    case 'W':
      
      Serial.println("#####################");
      Serial.println("");
      Serial.println("Waking up the max7219");
      Serial.println("");
      Serial.println("#####################");
      //Some white lines
      Serial.println("");
      Serial.println("");

      digitalWrite(SS_PIN, LOW);
      SPI.transfer(0x0C);
      SPI.transfer(0x01);
      digitalWrite(SS_PIN, HIGH);

      delay(1000);
      break;
    case 'S':
      Serial.println("#####################");
      Serial.println("");
      Serial.println("Shutting down the max7219");
      Serial.println("");
      Serial.println("#####################");
      //Some white lines
      Serial.println("");
      Serial.println("");

      digitalWrite(SS_PIN, LOW);
      SPI.transfer(0x0C);
      SPI.transfer(0x00);
      digitalWrite(SS_PIN, HIGH);

      delay(1000);
      break;
    case 'T':
      Serial.println("#####################");
      Serial.println("");
      Serial.println("Entering in the test mode");
      Serial.println("");
      Serial.println("#####################");
      
      //Some white lines
      Serial.println("");
      Serial.println("");

      digitalWrite(SS_PIN, LOW);
      SPI.transfer(0x0F);
      SPI.transfer(0x01);
      digitalWrite(SS_PIN, HIGH);

      delay(1000);
      break;
    case 'N':
      Serial.println("#####################");
      Serial.println("");
      Serial.println("Entering in the normal mode");
      Serial.println("");
      Serial.println("#####################");
      //Some white lines
      Serial.println("");
      Serial.println("");

      digitalWrite(SS_PIN, LOW);
      SPI.transfer(0x0F);
      SPI.transfer(0x00);
      digitalWrite(SS_PIN, HIGH);

      delay(1000);
      break;
    case 'M':
    /*
      //read the address
      Serial.println("Please enter the address:");
      while(!Serial.available());
      char address = Serial.read();

      //read the data
      Serial.println("Please enter the data:");
      while(!Serial.available());
      char data = Serial.read();

      //send the data
      digitalWrite(SS_PIN, LOW);
      SPI.transfer(address);
      SPI.transfer(data);
      digitalWrite(SS_PIN, HIGH);
      break;

    */
      Serial.println("#####################");
      Serial.println("");
      Serial.println("In development");
      Serial.println("");
      Serial.println("#####################");

      delay(1000);
      break;
    default:
      Serial.println("#####################");
      Serial.println("");
      Serial.println("Invalid option");
      Serial.println("");
      Serial.println("#####################");

      delay(1000);
      break;
  }

}

