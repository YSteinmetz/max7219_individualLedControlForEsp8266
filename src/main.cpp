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


int convertUserInput(char input);

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

  char address, data;
  
  //Ask for the user input
  /*
    Options:
      W. for wake up the max7219
      S. for shutdown the max7219

      T. for test mode
      N. for normal mode

      M. to write the address and the data to send

      O. to turn on all the leds
      F. to turn off all the leds

      D. no decode mode
      I. for the minimum intensity
      H. for the maximum intensity

      L. to scan limit
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
  Serial.println("O. to turn on all the leds");
  Serial.println("F. to turn off all the leds");
  Serial.println("D. no decode mode");
  Serial.println("I. for the minimum intensity");
  Serial.println("H. for the maximum intensity");
  Serial.println("L. to scan limit");


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
    
      //read the address
      Serial.println("Please enter the address:");
      while(!Serial.available());
      address = Serial.read();

      //read the data
      Serial.println("Please enter the data:");
      while(!Serial.available());
      data = Serial.read();

      //send the data
      digitalWrite(SS_PIN, LOW);
      SPI.transfer(convertUserInput(address));
      SPI.transfer(convertUserInput(data));
      digitalWrite(SS_PIN, HIGH);
      break;

    
      Serial.println("#####################");
      Serial.println("");
      Serial.println("In development");
      Serial.println("");
      Serial.println("#####################");

      delay(1000);
      break;

    case 'O':

      Serial.println("#####################");
      Serial.println("");
      Serial.println("Turning on all the leds");
      Serial.println("");
      Serial.println("#####################");

      //Some white lines
      Serial.println("");
      Serial.println("");

      for(int i = 1; i <= 8; i++){
        digitalWrite(SS_PIN, LOW);
        SPI.transfer(i);
        SPI.transfer(0x0F);
        digitalWrite(SS_PIN, HIGH);
        delay(1000);
      }

      delay(1000);
      break;

    case 'F':
      
        Serial.println("#####################");
        Serial.println("");
        Serial.println("Turning off all the leds");
        Serial.println("");
        Serial.println("#####################");
  
        //Some white lines
        Serial.println("");
        Serial.println("");
  
        for(int i = 1; i <= 8; i++){
          digitalWrite(SS_PIN, LOW);
          SPI.transfer(i);
          SPI.transfer(0x00);
          digitalWrite(SS_PIN, HIGH);
          delay(1000);
        }
  
        delay(1000);
        break;

    case 'D':
        
          Serial.println("#####################");
          Serial.println("");
          Serial.println("No decode mode");
          Serial.println("");
          Serial.println("#####################");
    
          //Some white lines
          Serial.println("");
          Serial.println("");
    
          digitalWrite(SS_PIN, LOW);
          SPI.transfer(0x09);
          SPI.transfer(0x00);
          digitalWrite(SS_PIN, HIGH);
    
          delay(1000);
          break;

    case 'I':

          Serial.println("#####################");
          Serial.println("");
          Serial.println("Minimum intensity");
          Serial.println("");
          Serial.println("#####################");
    
          //Some white lines
          Serial.println("");
          Serial.println("");
    
          digitalWrite(SS_PIN, LOW);
          SPI.transfer(0x0A);
          SPI.transfer(0x00);
          digitalWrite(SS_PIN, HIGH);
    
          delay(1000);
          break;

    case 'H':

          Serial.println("#####################");
          Serial.println("");
          Serial.println("Maximum intensity");
          Serial.println("");
          Serial.println("#####################");
    
          //Some white lines
          Serial.println("");
          Serial.println("");
    
          digitalWrite(SS_PIN, LOW);
          SPI.transfer(0x0A);
          SPI.transfer(0x0F);
          digitalWrite(SS_PIN, HIGH);
    
          delay(1000);
          break;

    case 'L':

          Serial.println("#####################");
          Serial.println("");
          Serial.println("Scan limit");
          Serial.println("");
          Serial.println("#####################");
    
          //Some white lines
          Serial.println("");
          Serial.println("");
    
          digitalWrite(SS_PIN, LOW);
          SPI.transfer(0x0B);
          SPI.transfer(0x07);
          digitalWrite(SS_PIN, HIGH);
    
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

int convertUserInput(char input){
  switch(input){
    case '1':
      return 0x01;
      break;
    case '2':
      return 0x02;
      break;
    case '3':
      return 0x03;
      break;
    case '4':
      return 0x04;
      break;
    case '5':
      return 0x05;
      break;
    case '6':
      return 0x06;
      break;
    case '7':
      return 0x07;
      break;
    case '8':
      return 0x08;
      break;
    case '9':
      return 0x09;
      break;
    case 'A':
      return 0x0A;
      break;
    case 'B':
      return 0x0B;
      break;
    case 'C':
      return 0x0C;
      break;
    case 'D':
      return 0x0D;
      break;
    case 'E':
      return 0x0E;
      break;
    case 'F':
      return 0x0F;
      break;
    case '0':
      return 0x00;
      break;
    case 'a':
      return 0x0A;
      break;
    case 'b':
      return 0x0B;
      break;
    case 'c':
      return 0x0C;
      break;
    case 'd':
      return 0x0D;
      break;
    case 'e':
      return 0x0E;
      break;
    case 'f':
      return 0x0F;
      break;
    default:
      return 0x00;
      break;
  }
}