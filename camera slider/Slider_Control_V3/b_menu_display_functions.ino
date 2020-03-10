//Following functions controll the actual displaying of the menus




//MAINMENU DISPLAY
void  mainMenu() { 
  subMenu = mainSubMenuID;               
  menuOptionCount = 3;                        //CHANGE ME: when more options are added
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

  if(counter == 3){  //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Global Values");  
  
  display.display();  //displays the configured text

  if(counter > menuOptionCount){ //loop cursor if it is now larger than the number of options
    counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}

//GLOBAL VALUES DISPLAY
void menuGlobalValues(){
  menuOptionCount = 1;
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(1.5);             // Normal 1:1 pixel scale   
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Global Values"));
  display.setTextSize(1.75);


  if(counter == 0){
    subMenu = returnSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);                // Draw white text
    }
  display.println("Return");

  
if(counter == 1){
    subMenu = secondsSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Rail Length");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 1){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(length_Inches);       //if we arn't changing anything display the saved value
  }
  display.display();
  
   if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
   counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}


//TUNE MENU DISPLAY
void menuTune(){
  
  if(counter > menuOptionCount){
    counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
  menuOptionCount = 2;
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(1.5);             // Normal 1:1 pixel scale   
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("TUNE OPTIONS"));
  display.setTextSize(1.75);


  if(counter == 0){
    subMenu = returnSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);                // Draw white text
    }
  display.println("Return");

  
  if(counter == 1){
    subMenu = steppersSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);                // Draw white text
    } 
  display.print("Steppers:"); 
  display.println(stepperState);    


  if(counter == 2){
    subMenu = jogSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);                // Draw white text
    } 
  display.println("Jog to Start");
  
  display.display();
}



//TIMECONTROLL MENU
void  menuTimeControl() {
  if(subMenu = tuneSubMenuID){
    counter = 6;
  }
  menuOptionCount = 7;                   //number of options on the menu
  int16_t i = 9;
  display.clearDisplay();                //clear displau
  display.setTextColor(SSD1306_WHITE);   // Draw white text
  display.setTextSize(1.5);              // Normal 1:1 pixel scale   
  display.setCursor(0,0);                // Start at top-left corner
  display.println(F("Time Control"));
  display.setTextSize(1.75);

  //display all of the options and highlight if they are selected
  if (counter <7){
    if(counter == 0){
      subMenu = returnSubMenuID;
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
      }
    else{
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      }
    display.println("Return");
  }

  //Camera time delay Logic
  if(counter == 1){
    subMenu = secondsSubMenuID;
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
    subMenu = minutesSubMenuID;
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
    subMenu = hoursSubMenuID;
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
    subMenu = angleSubMenuID;
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
  display.println((char)223);
  

  //Camera Direction Logic
  if(counter == 5){
    subMenu = directionSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Direction:");
  display.setTextColor(SSD1306_WHITE);
  display.println(movementDirection);


  //go to tune Menu
  if(counter == 6){
    subMenu = tuneSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("TUNE");
  


  //Start Shot Logic
  if(counter == menuOptionCount){
    subMenu = runSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  
  display.display();  //update screen

  if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
   counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}




//SPEEDCONTROLL MENU DISPLAY
void  menuSpeedControl() {
    if(subMenu = tuneSubMenuID){
    counter = 4;
  }
  menuOptionCount = 5;                   //number of options on the menu
  int16_t i = 9;
  display.clearDisplay();                //clear displau
  display.setTextColor(SSD1306_WHITE);   // Draw white text
  display.setTextSize(1.5);              // Normal 1:1 pixel scale   
  display.setCursor(0,0);                // Start at top-left corner
  display.println(F("Speed Control"));
  display.setTextSize(1.75);

  //display all of the options and highlight if they are selected
  if(counter == 0){
    subMenu = returnSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Return");

  //Camera Speed Logic
  if(counter == 1){
    subMenu = speedSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("speed:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 1){    //if we are activley changing the value display change counter instead of the saved value
    display.print( pow(changeCounter,3) * .0006);
  } 
  else{
    display.print(speedControl_speed);       //if we arn't changing anything display the saved value
  }
  display.println(" in/min");
 
  //Camera Angle Display Logic
  if(counter == 2){
    subMenu = angleSubMenuID;
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
  display.println((char)223);
  

  //Camera Direction Logic
  if(counter == 3){
    subMenu = directionSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("direction:");
  display.setTextColor(SSD1306_WHITE);
  display.println(movementDirection);

  //go to tune Menu
  if(counter == 4){
    subMenu = tuneSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("TUNE");

  //Start Shot Logic
  if(counter == menuOptionCount){
    subMenu = runSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  display.display();  //update screen
  if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
   counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}

//MOTIONCONTROLL MENU
void menuMotionControl() {
  menuOptionCount = 5;
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
    display.print(changeCounter);
  } 
  else{
    display.print(motionControl_dAway);       //if we arn't changing anything display the saved value
  }
  display.println("in");
  
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
    display.print(changeCounter);
  } 
  else{
    display.print(motionControl_dDown);       //if we arn't changing anything display the saved value
  }
  display.println("in");

  if(counter == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Speed:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 3){    //if we are activley changing the value display change counter instead of the saved value
    display.print(changeCounter);
  } 
  else{
    display.print(motionControl_speed);       //if we arn't changing anything display the saved value
  }
  display.println(" in/min");

  //Camera Direction Logic
  if(counter == 4){
    subMenu = directionSubMenuID;
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("direction:");
  display.setTextColor(SSD1306_WHITE);
  display.println(movementDirection);

  if(counter == menuOptionCount){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  
  display.display();

  if(counter > menuOptionCount){
    counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}
