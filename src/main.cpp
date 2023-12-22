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
void transferData(int address, int data);
void sendMessage(String message);



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
      
      sendMessage("Waking up the max7219");
      transferData(0x0C, 0x01);

      break;
    case 'S':

      sendMessage("Shutting down the max7219");
      transferData(0x0C, 0x00);

      break;
    case 'T':

      sendMessage("Entering in the test mode");
      transferData(0x0F, 0x01);

      break;
    case 'N':

      sendMessage("Entering in the normal mode");
      transferData(0x0F, 0x00);

      break;
    case 'M':

      sendMessage("Manual mode");
    
      //read the address
      Serial.println("Please enter the address:");
      while(!Serial.available());
      address = Serial.read();

      delay(500);

      //read the data
      Serial.println("Please enter the data:");
      while(!Serial.available());
      data = Serial.read();

      transferData(convertUserInput(address), convertUserInput(data));

      break;

    case 'O':

      sendMessage("Turning on all the leds");
      for(int i = 1; i <= 8; i++){
        transferData(i, 0x0F);
        delay(1000);
      }
      
      break;

    case 'F':
      
      sendMessage("Turning off all the leds");

      for(int i = 1; i <= 8; i++){

        transferData(i, 0x00);
        delay(1000);

      }
  
      
      break;

    case 'D':
        
      sendMessage("No decode mode");
      transferData(0x09, 0x00);

      break;

    case 'I':

      sendMessage("Minimum intensity");
      transferData(0x0A, 0x00);

      break;

    case 'H':

      sendMessage("Maximum intensity");
      transferData(0x0A, 0x0F);

      break;

    case 'L':

      sendMessage("Scan limit");
      transferData(0x0B, 0x07);
   
      break;

    default:
    
      sendMessage("Invalid option");

      break;
  }

}

void transferData(int address, int data){
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(address);
  SPI.transfer(data);
  digitalWrite(SS_PIN, HIGH);
}

void sendMessage(String message){
  Serial.println("#####################");
  Serial.println("");
  Serial.println(message);
  Serial.println("");
  Serial.println("#####################");

  //Some white lines
  Serial.println("");
  Serial.println("");

  delay(1000);
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