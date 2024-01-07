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

  static int operationMode = 1;
  
  //Ask for the register address
  /*
    (D8 - D9 - D10 - D11)
    Options:
      0 - No-Op
      1 - Digit 0
      2 - Digit 1
      3 - Digit 2
      4 - Digit 3
      5 - Digit 4
      6 - Digit 5
      7 - Digit 6
      8 - Digit 7
      9 - Decode Mode
      A - Intensity
      B - Scan Limit
      C - Shutdown
      F - Display Test

      
  */
  //send the command list to the user
  Serial.println("Select the register address:");
  Serial.println("0 - No-Op");
  Serial.println("1 - Digit 0");
  Serial.println("2 - Digit 1");
  Serial.println("3 - Digit 2");
  Serial.println("4 - Digit 3");
  Serial.println("5 - Digit 4");
  Serial.println("6 - Digit 5");
  Serial.println("7 - Digit 6");
  Serial.println("8 - Digit 7");

  Serial.println("9 - Decode Mode");
  Serial.println("A - Intensity");
  Serial.println("B - Scan Limit");
  Serial.println("C - Shutdown");
  Serial.println("F - Display Test");

  Serial.println("O - Turn on all leds");
  Serial.println("X - Turn off all leds");


  //read the user input
  while(!Serial.available());
  char selectedAddr = Serial.read();

  if(selectedAddr == 'O' || selectedAddr == 'o'){
    //Turn on all leds
    sendMessage("Turn on all leds");
    /*
    transferData(0x0F, 0x01);
    delay(20);
    transferData(0x0C, 0x01);
    delay(20);
    transferData(0x0B, 0x07);
    delay(20);
    transferData(0x0A, 0x0F);
    delay(20);
    */
    transferData(0x09, 0x0F);
    delay(20);
    transferData(0x08, 0x0F);
    delay(20);
    transferData(0x07, 0x0F);
    delay(20);
    transferData(0x06, 0x0F);
    delay(20);
    transferData(0x05, 0x0F);
    delay(20);
    transferData(0x04, 0x0F);
    delay(20);
    transferData(0x03, 0x0F);
    delay(20);
    transferData(0x02, 0x0F);
    delay(20);
    transferData(0x01, 0x0F);
    delay(20);
    transferData(0x00, 0x0F);
    return;
  }
  else if(selectedAddr == 'X' || selectedAddr == 'x'){
    //Turn off all leds
    sendMessage("Turn off all leds");
    /*
    transferData(0x0F, 0x01);
    delay(20);
    transferData(0x0C, 0x01);
    delay(20);
    transferData(0x0B, 0x07);
    delay(20);
    transferData(0x0A, 0x00);
    */
    delay(20);
    transferData(0x09, 0x00);
    delay(20);
    transferData(0x08, 0x00);
    delay(20);
    transferData(0x07, 0x00);
    delay(20);
    transferData(0x06, 0x00);
    delay(20);
    transferData(0x05, 0x00);
    delay(20);
    transferData(0x04, 0x00);
    delay(20);
    transferData(0x03, 0x00);
    delay(20);
    transferData(0x02, 0x00);
    delay(20);
    transferData(0x01, 0x00);
    delay(20);
    transferData(0x00, 0x00);
    delay(20);
    return;
  }

  //convert the user input to hex
  int addr = convertUserInput(selectedAddr);

  //execute the user command
  switch(addr){  

    case 0:
      //No-Op
      sendMessage("No-Op");
      transferData(addr, 0x00);

      break;

    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      
        //Digit
        sendMessage("Digit " + String(addr-1));
        Serial.println("Select the segment to turn on/off (0 (min) - 7 (max)):");

        while(!Serial.available())
          ;
  
        //Code block to create a local scope and avoid variable name conflicts
        {
          char selectedData = Serial.read();
  
          int data = convertUserInput(selectedData);
  
          if (data >= 0x00 && data <= 0x0F){
            Serial.println("Digit value: " + String(data));
            transferData(addr, data);
          }
          else{
            Serial.println("Invalid option");
          }
  
        }
  
        break;

    case 9:
      //Decode Mode
      sendMessage("Decode Mode");
      //(D0 - D1 - D2 - D3 - D4 - D5 - D6 - D7)
      //Options:
      
      // 1 - No decode for digits 0-7
      // 2 - Code B decode for digit 0 No decode for digits 7–1
      // 2 - Code B decode for digits 3–0 No decode for digits 7–4
      // 3 - Code B decode for digits 0-7

      Serial.println("Select the decode mode:");
      Serial.println("1 - No decode for digits 0-7");
      Serial.println("2 - Code B decode for digit 0 No decode for digits 7–1");
      Serial.println("3 - Code B decode for digits 3–0 No decode for digits 7–4");
      Serial.println("4 - Code B decode for digits 0-7");

      while(!Serial.available())
        ;

      //Code block to create a local scope and avoid variable name conflicts
      {
        char selectedData = Serial.read();

        if (selectedData == '1'){
          Serial.println("No decode for digits 0-7");
          transferData(addr, 0x00);
          operationMode = 1;
        }
        else if (selectedData == '2'){
          Serial.println("Code B decode for digit 0 No decode for digits 7–1");
          transferData(addr, 0x01);
          operationMode = 2;
        }
        else if (selectedData == '3'){
          Serial.println("Code B decode for digits 3–0 No decode for digits 7–4");
          transferData(addr, 0x0F);
          operationMode = 3;
        }
        else if (selectedData == '4'){
          Serial.println("Code B decode for digits 0-7");
          transferData(addr, 0xFF);
          operationMode = 4;
        }
        else{
          Serial.println("Invalid option");
        }

      }

      break;

    case 0x0A:
      //Intensity
      sendMessage("Intensity");
      Serial.println("Select the intensity level (0 (min) - F (max)):");

      while(!Serial.available())
        ;

      //Code block to create a local scope and avoid variable name conflicts
      {
        char selectedData = Serial.read();

        int data = convertUserInput(selectedData);

        if (data >= 0x00 && data <= 0x0F){
          Serial.println("Intensity level: " + String(data));
          transferData(addr, data);
        }
        else{
          Serial.println("Invalid option");
        }

      }

      break;

    case 0x0B:
      //Scan Limit
      sendMessage("Scan Limit");
      Serial.println("Select the scan limit (0 (min) - 7 (max)):");

      while(!Serial.available())
        ;

      //Code block to create a local scope and avoid variable name conflicts
      {
        char selectedData = Serial.read();

        int data = convertUserInput(selectedData);

        if (data >= 0x00 && data <= 0x07){
          Serial.println("Scan limit: " + String(data));
          transferData(addr, data);
        }
        else{
          Serial.println("Invalid option");
        }

      }

      break;

    case 0x0C:

      //Shutdown
      sendMessage("Shutdown");
      Serial.println("Select the shutdown mode:");
      Serial.println("0 - Shutdown mode");
      Serial.println("1 - Normal operation");

      while(!Serial.available())
        ;

      //Code block to create a local scope and avoid variable name conflicts
      {
        char selectedData = Serial.read();

        if (selectedData == '0'){
          Serial.println("Shutdown mode");
          transferData(addr, 0x00);
        }
        else if (selectedData == '1'){
          Serial.println("Normal operation");
          transferData(addr, 0x01);
        }
        else{
          Serial.println("Invalid option");
        }

      }

      break;

    case 0x0F:

      //Display Test
      sendMessage("Display Test");
      Serial.println("Select the display test mode:");
      Serial.println("0 - Display test mode");
      Serial.println("1 - Normal operation");

      while(!Serial.available())
        ;

      //Code block to create a local scope and avoid variable name conflicts
      {
        char selectedData = Serial.read();

        if (selectedData == '0'){
          Serial.println("Display test mode");
          transferData(addr, 0x00);
        }
        else if (selectedData == '1'){
          Serial.println("Normal operation");
          transferData(addr, 0x01);
        }
        else{
          Serial.println("Invalid option");
        }

      }

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