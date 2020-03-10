/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/
//OLED DISPLAY
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128
static const unsigned char PROGMEM logo_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xF0, 0xF1, 0x71, 0xE0, 0xC3, 0x83,
0x00, 0x86, 0xC6, 0xE0, 0x74, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xE0, 0x70, 0x39, 0x1F,
0x0F, 0x1F, 0x39, 0x70, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x3F, 0x3F, 0xB0, 0x80, 0x98, 0x98, 0x00, 0x0C, 0x8C,
0x00, 0x06, 0x06, 0x00, 0x82, 0x03, 0x01, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x44, 0x44, 0x47, 0x38, 0x00, 0x70, 0x1C, 0x17, 0x11, 0x17,
0x1C, 0x70, 0x00, 0x23, 0x44, 0x48, 0x30, 0x00, 0x00, 0x7F, 0x44, 0x44, 0x44, 0x00, 0x00, 0x7F,
0x40, 0x40, 0x40, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x7F, 0x01, 0x06, 0x18, 0x60, 0x7F, 0x00, 0x00,
0x7F, 0x44, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x81, 0x81, 0x81, 0x42, 0x3C, 0x00,
0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0x00, 0x46, 0x8B, 0x91, 0x61, 0x00, 0x00, 0xFF, 0x00, 0x00,
0x00, 0x3C, 0x42, 0x81, 0x91, 0x91, 0x72, 0x00, 0x00, 0xFF, 0x03, 0x0C, 0x30, 0xC0, 0xFF, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
  

//ENCODER
 #define outputA 3   //first data input pin for the encoder
 #define outputB 4   //second data input pin for the encoder
 int counter = 0;    //tracks how many clicks the encoder has had
 int aState;         //Value to store the current state of the Encoder
 int aLastState;     //Value to store the last state of the Encoder
 const byte encoderButtonInterruptPin = 2;        //inerupt pin attached to the encoders button  
 const byte encodeRotationrInterruptPin = 3;      //interupt pin attached to the encoders rotation

//STEPPER
#define horizontalDirPin 5        //direction pin for horizontal motor       
#define horizontalStepPin 6       //drive pin for horizontal motor  
#define rotationlDirPin 7         //direction pin for rotation motor
#define rotationStepPin 8         //drive pin for rotation motor
#define disablePin 9              //pin to dissable both stepper drivers

//MENU LOGIC
  int menu = 0;                  //menus are stored as numbers
  #define homeMenuID 0           //numerical ID for all menu options
  #define timeControlID 1
  #define speedControlID 2
  #define motionControlID 3
  #define globalValuesID 4
  int menuOptionCount;           //number of options availible on a given menu
  
  

//EEPROM CONFIGURE
  //Global EEPROM
  long length_Inches = 32;                  //length of the slider rail in inches
  int length_Inches_eeAddress = 0;          //Location of information in eeprom
  
  //speedControl EEPROM
  long speedControl_speed = 50;             //speed of the horizontal slider while in speedControl Mode
  int speedControl_speed_eeAddress = 4;     //Location of information in eeprom
  
  long speedControl_rDistance = 1;          //amount in degrees to rotate camera over one slide operation in speed control mode
  int speedControl_rDistance_eeAddress = 8; //Location of information in eeprom


  //timeControl EEPROM 
  long timeControl_seconds = 30;           //speed of the horizontal slider while in speedControl Mode
  int timeControl_seconds_eeAddress = 28;     //Location of information in eeprom

  long timeControl_minutes = 0;            //speed of the horizontal slider while in speedControl Mode
  int timeControl_minutes_eeAddress = 32;     //Location of information in eeprom

  long timeControl_hours = 0;              //speed of the horizontal slider while in speedControl Mode
  int timeControl_hours_eeAddress = 36;     //Location of information in eeprom
  
  long timeControl_rDistance = 1;          //amount in degrees to rotate camera over one slide operation in speed control mode
  int timeControl_rDistance_eeAddress = 40;//Location of information in eeprom


  //motionControl EEPROM
  double motionControl_dAway = 4;          //Distance of object to be tracked tangent to the rail
  int  motionControl_dAway_eeAddress = 12; //Location of information in eeprom

  double motionControl_dDown= 4;           //distance of the tracked object from the right side and parallel to the rail
  int  motionControl_dDown_eeAddress = 16; //Location of information in eeprom

  long motionControl_speed= 50;            //speed of the shot
  int  motionControl_speed_eeAddress = 20; //Location of information in eeprom

  long motionControl_time= 50;            //time in seconds to traverse
  int  motionControl_time_eeAddress = 24; //Location of information in eeprom

  
// Stored Values
  long LENGTH = length_Inches * 2032;          //converts length into steps
  String movementDirection = " left";    //sets direction of travel, this is flopped after each operation
  int changeValue = false;                     //determines whether to configure the operation values or scroll down a menu, this is flipped by clicking encoder while over value
  int changeCounter = 0;                       // if change value is true "changeCounter" will be changed instead of the normal "counter" value
  int runningPath = false;                     //tracks wether or not an operation is curretly running

  


void setup() {
  Serial.begin(9600);

//OLED DISPLAY  
  display.clearDisplay();                    //Display Logo
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
                                                   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                                       // Don't proceed, loop forever
  }
    display.display();
    display.cp437(true);
  
//ENCODER

  pinMode (outputA,INPUT);                          //Sets encoder pins as inputs
  pinMode (outputB,INPUT);
  aLastState = digitalRead(outputA);                //saves encoders current position
  pinMode(encoderButtonInterruptPin, INPUT_PULLUP); //defines encoder button intterupt pin
  attachInterrupt(digitalPinToInterrupt(encoderButtonInterruptPin), clicked, RISING);     //if encoderButtonInterruptPin is rising then stop everything and run clicked()
  attachInterrupt(digitalPinToInterrupt(encodeRotationrInterruptPin), encoder, CHANGE);   //if encodeRotationrInterruptPin has changed stop everything and run encoder()

//STEPPER
  pinMode(horizontalStepPin, OUTPUT);  //defines all the stepper controll pis as outputs
  pinMode(horizontalDirPin, OUTPUT);
  pinMode(rotationStepPin, OUTPUT);
  pinMode(rotationlDirPin, OUTPUT);  
  pinMode(disablePin, OUTPUT);

  digitalWrite(disablePin, HIGH);       //disables all steppers
  
//Menu Initioalization
  menu = homeMenuID;   //set the current screen to homescreen (this is defined again because it was sensing phantom presses on startup)
}





void loop() {

//MENU ORGANIZATION 
  if (menu == homeMenuID){
    mainMenu();
  }
  if (menu == timeControlID){
    menuTimeControl();
  }
  if (menu == speedControlID){
    menuSpeedControl();
  }
  if (menu == motionControlID){
    menuMotionControl();
  }
  if (menu == globalValuesID){
    menuGlobalValues();
  }
}





void encoder(){
   aState = digitalRead(outputA);          // Reads the "current" state of the outputA
                                           // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){              // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise                           
     if (digitalRead(outputB) != aState) { //check to see if its spinning clockwise 
       if (changeValue == false){          //if we are not trying to change a value increase "counter"
        counter ++;                   
       }
       else if (changeValue == true){ //if we are tyring to change a value increase "ChangeCounter" instead
        changeCounter ++;
       } 
     } 
     else{                             //if we are spinning anticlockwise run this
      if (changeValue == false){       //if we not are trying to change a value decrease "counter" 
       counter --;
      }
      else if (changeValue == true){   //if we are trying to change a value decrease "ChangeCounter" instead
        changeCounter --;
      }
     }   
   } 
   aLastState = aState;                // Updates the previous state of the outputA with the current state
  // Serial.println(changeCounter);
}

void clicked() {                        //if the button on the encoder was clicked this function will run

  if (menu == homeMenuID){              //if we detected a click while on homemenu go to selected menu
    if (counter == 0){
      menu = timeControlID;
    }
    else if (counter == 1){
       menu = speedControlID;
    }
    else if (counter == 2){
       menu = motionControlID;
    }
    counter = 0;                   //reset the counter so that the cursor is at the top of the new screen
  }

  //global values adjustment logic
  else if (menu == globalValuesID){
    EEPROM.get(length_Inches_eeAddress, length_Inches);           //load in EEPROM value for this modes settings
    
    if (counter == 0){    //if we click on return send us back to the home menu
      menu = homeMenuID;
    }

    
    else if (counter == 1 && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = length_Inches;   //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 1 && changeValue == true){                     //exit edit speed mode
       length_Inches = changeCounter;                              //update the speed
       EEPROM.put(length_Inches_eeAddress, length_Inches);    //send value to eeprom
       changeCounter = 0;                                               //reset change counter to zero for next time
       changeValue = false;                                             //termiate edit mode
    }
  }



  
  //timeControlMenu Logic
  else if (menu == timeControlID){
    EEPROM.get(timeControl_seconds_eeAddress, timeControl_seconds);           //load in EEPROM value for this modes settings
    EEPROM.get(timeControl_minutes_eeAddress, timeControl_minutes);
    EEPROM.get(timeControl_hours_eeAddress, timeControl_hours);           //load in EEPROM value for this modes settings
    EEPROM.get(timeControl_rDistance_eeAddress, timeControl_rDistance);
       
    
    if (counter == 0){    //if we click on return send us back to the home menu
      menu = homeMenuID;
    }

    
    else if (counter == 1 && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = timeControl_seconds;   //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 1 && changeValue == true){                     //exit edit speed mode
       timeControl_seconds = changeCounter;                              //update the speed
       EEPROM.put(timeControl_seconds_eeAddress, timeControl_seconds);    //send value to eeprom
       changeCounter = 0;                                               //reset change counter to zero for next time
       changeValue = false;                                             //termiate edit mode
    }

    else if (counter == 2 && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = timeControl_seconds;   //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 2 && changeValue == true){                     //exit edit speed mode
       timeControl_minutes = changeCounter;                              //update the speed
       EEPROM.put(timeControl_minutes_eeAddress, timeControl_minutes);    //send value to eeprom
       changeCounter = 0;                                               //reset change counter to zero for next time
       changeValue = false;                                             //termiate edit mode
    }

    else if (counter == 3 && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = timeControl_hours;   //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 3 && changeValue == true){                     //exit edit speed mode
       timeControl_hours = changeCounter;                              //update the speed
       EEPROM.put(timeControl_hours_eeAddress, timeControl_hours);    //send value to eeprom
       changeCounter = 0;                                               //reset change counter to zero for next time
       changeValue = false;                                             //termiate edit mode
    }

    else if (counter == 4 && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = timeControl_rDistance;   //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 4 && changeValue == true){                     //exit edit speed mode
       timeControl_rDistance = changeCounter;                              //update the speed
       EEPROM.put(timeControl_rDistance_eeAddress, timeControl_rDistance);    //send value to eeprom
       changeCounter = 0;                                               //reset change counter to zero for next time
       changeValue = false;                                             //termiate edit mode
    }
    
    else if (counter == 5){                      //if clicked on direction -> FLIP
      if (movementDirection == " right"){
        movementDirection = " left";
      }
      else{
        movementDirection = " right";
      }    
    }

    
    else if (counter == 6){                     //if clicked on Run then run the configured operation
      delay (10000);                            //give it a second to debounce the button
      timeControl();                           //run the operation
      if (movementDirection == " right"){  //flip the desired direction after operation
        movementDirection = " left";
      }
      else{
        movementDirection = " right";
      } 
    }
  }


  //speedControlMenu Logic
  else if (menu == speedControlID){
    EEPROM.get(speedControl_speed_eeAddress, speedControl_speed);           //load in EEPROM value for this modes settings
    EEPROM.get(speedControl_rDistance_eeAddress, speedControl_rDistance);   
    
    if (counter == 0){    //if we click on return send us back to the home menu
      menu = homeMenuID;
    }

    
    else if (counter == 1 && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = speedControl_speed;   //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 1 && changeValue == true){                     //exit edit speed mode
      speedControl_speed = changeCounter;                              //update the speed
      EEPROM.put(speedControl_speed_eeAddress, speedControl_speed);    //send value to eeprom
      changeCounter = 0;                                               //reset change counter to zero for next time
      changeValue = false;                                             //termiate edit mode
    }

    else if (counter == 2 && changeValue == false){                    //put controller inedit mode
      changeValue = true;                                              
      changeCounter = speedControl_rDistance + changeCounter;          //angle is now loaded angle plus the counted encoder ticks
    }    
    else if (counter == 2 && changeValue == true){                          //exit edit angle mode
      speedControl_rDistance = changeCounter;                               //update the stored angle
      EEPROM.put(speedControl_rDistance_eeAddress, speedControl_rDistance); //send new angle to eeprom
      changeCounter = 0;                                                    //reset change counter to zero for next time 
      changeValue = false;                                                  //termiate edit mode
    }

    
    else if (counter == 3){                      //if clicked on direction -> FLIP
      if (movementDirection == " right"){
        movementDirection = " left";
      }
      else{
        movementDirection = " right";
      }    
    }

    
    else if (counter == 4){                     //if clicked on Run then run the configured operation
      delay (10000);                            //give it a second to debounce the button
      speedControl();                           //run the operation
      if (movementDirection == " right"){  //flip the desired direction after operation
        movementDirection = " left";
      }
      else{
        movementDirection = " right";
      } 
    }
  }

  //motionControlMenu Logic
  else if (menu == motionControlID){   //if in motion control mode run this
    EEPROM.get(motionControl_dAway_eeAddress, motionControl_dAway);           //load in EEPROM value for this modes settings
    EEPROM.get(motionControl_dDown_eeAddress, motionControl_dDown);
    EEPROM.get(motionControl_speed_eeAddress, motionControl_speed);           //load in EEPROM value for this modes settings
    EEPROM.get(motionControl_time_eeAddress, motionControl_time);
       
    
    if (counter == 0){    //if we click on return send us back to the home menu
      menu = homeMenuID;
    }

    
    else if (counter == 1 && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = motionControl_dAway;   //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 1 && changeValue == true){                     //exit edit speed mode
       motionControl_dAway = changeCounter;                              //update the speed
       EEPROM.put(motionControl_dAway_eeAddress, motionControl_dAway);    //send value to eeprom
       changeCounter = 0;                                               //reset change counter to zero for next time
       changeValue = false;                                             //termiate edit mode
    }

    else if (counter == 2 && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = motionControl_dDown;   //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 2 && changeValue == true){                     //exit edit speed mode
       motionControl_dDown = changeCounter;                              //update the speed
       EEPROM.put(motionControl_dDown_eeAddress, motionControl_dDown);    //send value to eeprom
       changeCounter = 0;                                               //reset change counter to zero for next time
       changeValue = false;                                             //termiate edit mode
    }

    else if (counter == 3 && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = motionControl_speed;   //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 3 && changeValue == true){                     //exit edit speed mode
       motionControl_speed = changeCounter;                              //update the speed
       EEPROM.put(motionControl_speed_eeAddress, motionControl_speed);    //send value to eeprom
       changeCounter = 0;                                               //reset change counter to zero for next time
       changeValue = false;                                             //termiate edit mode
    }
    
    else if (counter == 4){                      //if clicked on direction -> FLIP
      if (movementDirection == " right"){
        movementDirection = " left";
      }
      else{
        movementDirection = " right";
      }    
    }

    
    else if (counter == 5){                     //if clicked on Run then run the configured operation
      delay (10000);                            //give it a second to debounce the button
      motionControl();                           //run the operation
      if (movementDirection == " right"){  //flip the desired direction after operation
        movementDirection = " left";
      }
      else{
        movementDirection = " right";
      } 
    }
  }

  
  delay(200);   //wait a bit to debounce click
}







//Following functions controll the actual displaying of the menus




//MAINMENU DISPLAY
void  mainMenu() {                
  menuOptionCount = 2;                  //CHANGE ME: when more options are added
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(2);                     // Normal 1:1 pixel scale   
  display.setCursor(0,0);                     // Start at top-left corner
  display.println(F("Main Menu"));            //write this text


  //the following are the diffrent menus you can select and the logic to highlight them
  display.setTextSize(1.5);
  if(counter == 0){ //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Time Control");

  if(counter == 1){  //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Speed Control");

    if(counter == 2){  //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Motion Control");
  
  display.display();  //displays the configured text

  if(counter > menuOptionCount){ //loop cursor if it is now larger than the number of options
    counter = 0;
  }
  if (counter < 0){
    counter = menuOptionCount;
  }
}

void menuGlobalValues(){
  menuOptionCount = 1;
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(1.5);             // Normal 1:1 pixel scale   
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Adjust Global Values"));
  display.setTextSize(1.75);


  if(counter == 0){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Return");

  
  if(counter == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Rail Length (INCHES):");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 1){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter + length_Inches);
  } 
  else{
    display.println(length_Inches);       //if we arn't changing anything display the saved value
  }
  
  display.display();

  if(counter > menuOptionCount){
    counter = 0;
  }
  if (counter < 0){
    counter = menuOptionCount;
  }
}

//TIMECONTROLL MENU
void  menuTimeControl() {
  menuOptionCount = 6;                   //number of options on the menu
  int16_t i = 9;
  display.clearDisplay();                //clear displau
  display.setTextColor(SSD1306_WHITE);   // Draw white text
  display.setTextSize(1.5);              // Normal 1:1 pixel scale   
  display.setCursor(0,0);                // Start at top-left corner
  display.println(F("Time Control"));
  display.setTextSize(1.75);

  //display all of the options and highlight if they are selected
  if(counter == 0){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Return");

  //Camera time delay Logic
  if(counter == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Seconds:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 1){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(timeControl_seconds);       //if we arn't changing anything display the saved value
  }


  if(counter == 2){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Minutes:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 2){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(timeControl_minutes);       //if we arn't changing anything display the saved value
  }  


  if(counter == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Hours:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 3){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(timeControl_hours);       //if we arn't changing anything display the saved value
  }

  //Camera Angle Display Logic
  if(counter == 4){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Camera Angle:");
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 4){     //if we are activily changing the angle display change counter
    display.print(changeCounter);
  } 
  else{
    display.print(timeControl_rDistance);     //otherwise change the stored value
  }
  display.println(i);
  

  //Camera Direction Logic
  if(counter == 5){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Direction");
  display.setTextColor(SSD1306_WHITE);
  display.println(movementDirection);

  //Start Shot Logic
  if(counter == menuOptionCount){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  
  display.display();  //update screen

  if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
    counter = 0;
  }
  if (counter < 0){
    counter = menuOptionCount;
  }
}


//SPEEDCONTROLL MENU DISPLAY
void  menuSpeedControl() {
  menuOptionCount = 4;                   //number of options on the menu
  int16_t i = 9;
  display.clearDisplay();                //clear displau
  display.setTextColor(SSD1306_WHITE);   // Draw white text
  display.setTextSize(1.5);              // Normal 1:1 pixel scale   
  display.setCursor(0,0);                // Start at top-left corner
  display.println(F("Speed Control"));
  display.setTextSize(1.75);

  //display all of the options and highlight if they are selected
  if(counter == 0){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Return");

  //Camera Speed Logic
  if(counter == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("speed:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 1){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else if (changeValue == true && counter == 2){
    display.println(changeCounter*100);       //if we arn't changing anything display the saved value
  }
  else{
    display.println(speedControl_speed);       //if we arn't changing anything display the saved value
  }

  //Camera Angle Display Logic
  if(counter == 2){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Camera Angle:");
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 2){     //if we are activily changing the angle display change counter
    display.print(changeCounter);
  } 
  else{
    display.print(speedControl_rDistance);     //otherwise change the stored value
  }
  display.println(i);
  

  //Camera Direction Logic
  if(counter == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Direction");
  display.setTextColor(SSD1306_WHITE);
  display.println(movementDirection);

  //Start Shot Logic
  if(counter == menuOptionCount){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  display.display();  //update screen

  if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
    counter = 0;
  }
  if (counter < 0){
    counter = menuOptionCount;
  }
}

//MOTIONCONTROLL MENU
void menuMotionControl() {
  menuOptionCount = 4;
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(1.5);             // Normal 1:1 pixel scale   
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Motion Control"));
  display.setTextSize(1.75);


  if(counter == 0){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Return");

  
  if(counter == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("D-Away:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 1){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(motionControl_dAway);       //if we arn't changing anything display the saved value
  }

  
  if(counter == 2){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("D-Down:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 2){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(motionControl_dDown);       //if we arn't changing anything display the saved value
  }

  if(counter == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("D-Down:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 3){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(motionControl_speed);       //if we arn't changing anything display the saved value
  }


  if(counter == menuOptionCount){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  
  display.display();

  if(counter > menuOptionCount){
    counter = 0;
  }
  if (counter < 0){
    counter = menuOptionCount;
  }
}








//following functions controll the actual planned operation 



//OPERATION LOGIC FOR TIME CONTROLL
void timeControl(){
  
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  
  if (movementDirection == " right"){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, HIGH);  //move right
    digitalWrite(rotationlDirPin, HIGH);   //move anticlockwise
    if (timeControl_rDistance < 0){       //rotate camera opposite direction if degree value is negative
      digitalWrite(rotationlDirPin, LOW);
    }
  }
    
    if (movementDirection == " left"){
    digitalWrite(horizontalDirPin, LOW);
    digitalWrite(rotationlDirPin, LOW);
    if (timeControl_rDistance < 0){
      digitalWrite(rotationlDirPin, HIGH);
   }
  }
  float angle = timeControl_rDistance * 8.61; //calculate angle from user configured values to 360degree scale
  
  unsigned long pause = timeControl_seconds * 1E6;
  pause = pause + (timeControl_minutes * 6E7);
  pause = pause + (timeControl_hours * 3.6E9);
  pause = (pause / LENGTH)/2;          

  
  int cancel = counter;                        //set cancel equal to the current counter valu
  delay (1000);                                //wait a sec to debounce
  
  for (long i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
    if ( i / (LENGTH/angle) == 0) {            //step the camera angle motor a percentage of the time so it goes a percent of the total distace
      digitalWrite(rotationStepPin, HIGH);
      digitalWrite(horizontalStepPin, LOW);     
    }
    else {
      digitalWrite(horizontalStepPin, LOW);
      digitalWrite(rotationStepPin, LOW);  
    } 
    delayMicroseconds(pause);                //velocity delay controls how fast the camera moves, small value is fast and large value is slow
    digitalWrite(horizontalStepPin,HIGH);
    delayMicroseconds(pause);

    encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
    if (cancel != counter){
    i = LENGTH;
    }    
  }    
  
  digitalWrite(disablePin, HIGH);    //turn everything off and set the running path to false.
  runningPath = false;
}

//OPERATION LOGIC FOR SPEED CONTROLL
void speedControl(){
  
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  
  if (movementDirection == " right"){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, HIGH);  //move right
    digitalWrite(rotationlDirPin, HIGH);   //move anticlockwise
    if (speedControl_rDistance < 0){       //rotate camera opposite direction if degree value is negative
      digitalWrite(rotationlDirPin, LOW);
    }
  }
    
    if (movementDirection == " left"){
    digitalWrite(horizontalDirPin, LOW);
    digitalWrite(rotationlDirPin, LOW);
    if (speedControl_rDistance < 0){
      digitalWrite(rotationlDirPin, HIGH);
   }
  }

  
  float angle = speedControl_rDistance * 8.61; //calculate angle from user configured values to 360degree scale
  float velocity = speedControl_speed * 13;          //scale velocity value by 13X (1 is fastest and 1000 is the slowest
  int cancel = counter;                        //set cancel equal to the current counter value
  delay (1000);                                //wait a sec to debounce
  
  for (long i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
    if ( i / (LENGTH/angle) == 0) {            //step the camera angle motor a percentage of the time so it goes a percent of the total distace
      digitalWrite(rotationStepPin, HIGH);
      digitalWrite(horizontalStepPin, LOW);     
    }
    else {
      digitalWrite(horizontalStepPin, LOW);
      digitalWrite(rotationStepPin, LOW);  
    } 
    delayMicroseconds(velocity);                //velocity delay controls how fast the camera moves, small value is fast and large value is slow
    digitalWrite(horizontalStepPin,HIGH);
    delayMicroseconds(velocity);

    encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
    if (cancel != counter){
    i = LENGTH;
    }    
  }    
  
  digitalWrite(disablePin, HIGH);    //turn everything off and set the running path to false.
  runningPath = false;
}




//OPERATION LOGIC FOR MOTION CONTROLL
void motionControl(){
  
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  
  if (movementDirection == " right"){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, HIGH);  //move right
    digitalWrite(rotationlDirPin, HIGH);   //move anticlockwise
  }
    
    if (movementDirection == " left"){
    digitalWrite(horizontalDirPin, LOW);
    digitalWrite(rotationlDirPin, LOW);
  }

  double startAngle = atan(motionControl_dAway/motionControl_dDown);
  double calculatedAngle;
  double currentAngle = startAngle;
  int angleStepsTaken = 0;
  int flip = true;
  float dTravled = 0;
  float angle = 3200; //calculate angle from user configured values to 360degree scale
  float velocity = motionControl_speed * 13;          //scale velocity value by 13X (1 is fastest and 1000 is the slowest
  int cancel = counter;                        //set cancel equal to the current counter value
  delay (1000);                                //wait a sec to debounce
  
  for (long i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
    if (dTravled < motionControl_dDown){
      if ((currentAngle - calculatedAngle) > .1125){   //if the angle diffrence between the ideal current degree and the actual degree is greator than the size of a single step, than take a step.
        digitalWrite(rotationStepPin, HIGH);
        digitalWrite(horizontalStepPin, LOW);
        angleStepsTaken ++;
        currentAngle = startAngle - (angleStepsTaken * .1125);   
      }
      else {
        digitalWrite(horizontalStepPin, LOW);
        digitalWrite(rotationStepPin, LOW);  
      } 
      delayMicroseconds(velocity);                //velocity delay controls how fast the camera moves, small value is fast and large value is slow
      digitalWrite(horizontalStepPin, HIGH);
      delayMicroseconds(velocity);
  
      dTravled = i/2032;
      calculatedAngle = atan(motionControl_dAway/(motionControl_dDown - dTravled));
  
      encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
      if (cancel != counter){
      i = LENGTH;
      }    
    }  

    else {                      //after the camera has reached 90 degrees to the object the angles are flipped 
      if (flip = true){         //runs once at the beggining of the else statement and then wont run again
        angleStepsTaken = 0;
        flip = false;
      }
      if ((calculatedAngle - currentAngle) > .1125){   //if the angle diffrence between the ideal current degree and the actual degree is greator than the size of a single step, than take a step.
        digitalWrite(rotationStepPin, HIGH);
        digitalWrite(horizontalStepPin, LOW);
        angleStepsTaken ++;
        currentAngle = 90 - (angleStepsTaken * .1125);   
      }
      else {
        digitalWrite(horizontalStepPin, LOW);
        digitalWrite(rotationStepPin, LOW);  
      } 
      delayMicroseconds(velocity);                //velocity delay controls how fast the camera moves, small value is fast and large value is slow
      digitalWrite(horizontalStepPin, HIGH);
      delayMicroseconds(velocity);
  
      dTravled = i/2032;
      calculatedAngle = atan(motionControl_dAway/(dTravled - motionControl_dDown));

      encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
      if (cancel != counter){
      i = LENGTH;
      }    
    }
  }  
  
  digitalWrite(disablePin, HIGH);    //turn everything off and set the running path to false.
  runningPath = false;
}


#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2
