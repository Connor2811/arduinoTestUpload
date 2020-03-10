

//the following functions are attached to interupts and run depending on if the encoder button was pressed or if the encoder changed position


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
      else if (changeValue == true && changeCounter > 0 && negative == false){   //if we are trying to change a value decrease "ChangeCounter" instead
        changeCounter --;
      }
      else if (changeValue == true && negative == true){   //if we are trying to change a value decrease "ChangeCounter" instead
        changeCounter --;
      }
     }   
   } 
   aLastState = aState;                // Updates the previous state of the outputA with the current state
  // Serial.println(changeCounter);
}

void clicked() {                        //if the button on the encoder was clicked this function will run
    delay(1000);   //wait a bit to debounce click

  if (menu == homeMenuID){              //if we detected a click while on homemenu go to selected menu
    if (counter == 0){
      menu = timeControlID;
      EEPROM.get(timeControl_seconds_eeAddress, timeControl_seconds);        //load in EEPROM value for this modes settings
      EEPROM.get(timeControl_minutes_eeAddress, timeControl_minutes);        //load in EEPROM value for this modes settings
      EEPROM.get(timeControl_hours_eeAddress, timeControl_hours);            //load in EEPROM value for this modes settings
      EEPROM.get(timeControl_rDistance_eeAddress, timeControl_rDistance);    //load in EEPROM value for this modes settings
    }
    else if (counter == 1){
       menu = speedControlID;
       EEPROM.get(speedControl_speed_eeAddress, speedControl_speed);           //load in EEPROM value for this modes settings
       EEPROM.get(speedControl_rDistance_eeAddress, speedControl_rDistance);   //load in EEPROM value for this modes settings
       EEPROM.get(speedControl_counter_eeAddress, speedControl_counter);       //load in EEPROM value for this modes settings
    }
    else if (counter == 2){
       menu = motionControlID;
        EEPROM.get(motionControl_dAway_eeAddress, motionControl_dAway);           //load in EEPROM value for this modes settings
        EEPROM.get(motionControl_dDown_eeAddress, motionControl_dDown);           //load in EEPROM value for this modes settings
        EEPROM.get(motionControl_speed_eeAddress, motionControl_speed);           //load in EEPROM value for this modes settings
        EEPROM.get(motionControl_time_eeAddress, motionControl_time);             //load in EEPROM value for this modes settings
    }
    else if (counter == 3){
       menu = globalValuesID;
       EEPROM.get(length_Inches_eeAddress, length_Inches);           //load in EEPROM value for this modes settings
    }
    counter = 0;                   //reset the counter so that the cursor is at the top of the new screen
  }


  //global values adjustment logic
  else if (menu == globalValuesID){
    
    if (subMenu == returnSubMenuID){    //if we click on return send us back to the home menu
      menu = homeMenuID;
    }

    
    else if (subMenu == lengthSubMenuID && changeValue == false){         //put controller in mode to edit speed value
      changeValue = true;
      changeCounter = length_Inches;                        //speed is now loaded speed plus the counted encoder ticks
    }
    else if (subMenu == lengthSubMenuID && changeValue == true){          //exit edit speed mode
       length_Inches = changeCounter;                       //update the speed
       EEPROM.put(length_Inches_eeAddress, length_Inches);  //send value to eeprom
       LENGTH = length_Inches * Steps_Per_inch;             //converts length into steps
       changeCounter = 0;                                   //reset change counter to zero for next time
       changeValue = false;                                 //termiate edit mode
    }
  }



    //TUNE menu adjustment logic
    else if (menu > menuTuneID){
    
      if (subMenu == returnSubMenuID){    //if we click on return send us back to the home menu
        menu = menu - menuTuneID;
      }
      else if (subMenu == steppersSubMenuID){         //put controller in mode to edit speed value
        if (stepperState == " disabled"){
          stepperState = " enabled ";
        }
  
        else if (stepperState == " enabled "){
          stepperState = " disabled";
        }
        enableSteppers();               
      }
  
      else if (subMenu == jogSubMenuID){
        runReset();
      }
  }



  
  //timeControlMenu Logic
  else if (menu == timeControlID){
       
    
    if (subMenu == returnSubMenuID){    //if we click on return, send us back to the home menu
      menu = homeMenuID;
    }

    
    else if (subMenu == secondsSubMenuID && changeValue == false){         //put controller in mode to edit seconds value
      changeValue = true;
      changeCounter = timeControl_seconds;                  //the encoder changeCounter value is now equal to timeControl_seconds and will be increased by the encoder function
    }
    else if (subMenu == secondsSubMenuID && changeValue == true){                       //exit edit seconds mode
       timeControl_seconds = changeCounter;                              //update the seconds with the tracked value
       EEPROM.put(timeControl_seconds_eeAddress, timeControl_seconds);   //send value to eeprom
       changeCounter = 0;                                                //reset change counter to zero for next time
       changeValue = false;                                              //termiate edit mode
    }

    else if (subMenu == minutesSubMenuID && changeValue == false){         //put controller in mode to edi value
      changeValue = true;
      changeCounter = timeControl_minutes;                  //the change counter is now set to the value and is incremented by encoder()
    }
    else if (subMenu == minutesSubMenuID && changeValue == true){                       //exit edit mode
       timeControl_minutes = changeCounter;                              //update the value
       EEPROM.put(timeControl_minutes_eeAddress, timeControl_minutes);   //send value to eeprom
       changeCounter = 0;                                                //reset change counter to zero for next time
       changeValue = false;                                              //termiate edit mode
    }

    else if (subMenu == hoursSubMenuID && changeValue == false){          //put controller in mode to edi value
      changeValue = true;
      changeCounter = timeControl_hours;                     //the change counter is now set to the value and is incremented by encoder()
    }
    else if (subMenu == hoursSubMenuID && changeValue == true){                     //exit edit s mode
       timeControl_hours = changeCounter;                              //update the value
       EEPROM.put(timeControl_hours_eeAddress, timeControl_hours);     //send value to eeprom
       changeCounter = 0;                                              //reset change counter to zero for next time
       changeValue = false;                                            //termiate edit mode
    }

    else if (subMenu == angleSubMenuID && changeValue == false){           //put controller in mode to edit speed value
      changeValue = true;
      negative = true;
      changeCounter = timeControl_rDistance;                  //speed is now loaded speed plus the counted encoder ticks
    }
    else if (subMenu == angleSubMenuID && changeValue == true){                         //exit edit mode
      negative = false;
       timeControl_rDistance = changeCounter;                              //update the value
       EEPROM.put(timeControl_rDistance_eeAddress, timeControl_rDistance); //send value to eeprom
       changeCounter = 0;                                                  //reset change counter to zero for next time
       changeValue = false;                                                //termiate edit mode
    }
    
    else if (subMenu == directionSubMenuID){                      //if clicked on direction -> FLIP
      if (movementDirection == "  right"){
        movementDirection = "  left ";
      }
      else{
        movementDirection = "  right";
      }    
    }

    else if (subMenu == tuneSubMenuID){                     //if clicked on Run then run the configured operation
        menu = menuTuneID + menu;
        counter = 0;
      }
    
    else if (subMenu == runSubMenuID){                     //if clicked on Run then run the configured operation
      timeControl();                            //run the operation
    }
  }


  //speedControlMenu Logic
  else if (menu == speedControlID){
    
    
    if (subMenu == returnSubMenuID){    //if we click on return send us back to the home menu
      menu = homeMenuID;
    }

    
    else if (subMenu == speedSubMenuID && changeValue == false){         //put controller in edit mode
      changeValue = true;
      changeCounter = speedControl_counter;             //speed is now loaded speed plus the counted encoder ticks
    }
    else if (subMenu == speedSubMenuID && changeValue == true){                     //exit edit mode
      speedControl_speed = pow(changeCounter,3) * .0006;                      //update the value
      speedControl_counter = changeCounter;
      EEPROM.put(speedControl_speed_eeAddress, speedControl_speed);    //send value to eeprom
      EEPROM.put(speedControl_counter_eeAddress, speedControl_counter);    //send value to eeprom
      changeCounter = 0;                                               //reset change counter to zero for next time
      changeValue = false;                                             //termiate edit mode
    }

    else if (subMenu == angleSubMenuID && changeValue == false){                    //put controller in edit mode
      negative = true;
      changeValue = true;                                              
      changeCounter = speedControl_rDistance;          //angle is now loaded angle plus the counted encoder ticks
    }    
    else if (subMenu == angleSubMenuID && changeValue == true){                          //exit edit angle mode
      negative = false;
      speedControl_rDistance = changeCounter;                               //update the stored angle
      EEPROM.put(speedControl_rDistance_eeAddress, speedControl_rDistance); //send new angle to eeprom
      changeCounter = 0;                                                    //reset change counter to zero for next time 
      changeValue = false;                                                  //termiate edit mode
    }

    
    else if (subMenu == directionSubMenuID){                      //if clicked on direction -> FLIP
      if (movementDirection == "  right"){
        movementDirection = "  left ";
      }
      else{
        movementDirection = "  right";
      }    
    }

    else if (subMenu == tuneSubMenuID){                     //if clicked on Run then run the configured operation
        menu = menuTuneID + menu;
        counter = 0;
      }    
    
    else if (subMenu == runSubMenuID){                     //if clicked on Run then run the configured operation
      speedControl();                           //run the operation
    }
  }

  //motionControlMenu Logic
  else if (menu == motionControlID){   //if in motion control mode run this     
    
    if (counter == 0){    //if we click on return send us back to the home menu
      menu = homeMenuID;
    }

    
    else if (counter == 1 && changeValue == false){         //put controller in mode to edit value
      changeValue = true;
      changeCounter = motionControl_dAway;                  //changeCounter is set to old value so it can be incremented by encoder()
    }
    else if (counter == 1 && changeValue == true){                       //exit edit mode
       motionControl_dAway = changeCounter;                              //update the value
       EEPROM.put(motionControl_dAway_eeAddress, motionControl_dAway);   //send value to eeprom
       changeCounter = 0;                                                //reset change counter to zero for next time
       changeValue = false;                                              //termiate edit mode
    }

    else if (counter == 2 && changeValue == false){         //put controller in mode to edit value
      changeValue = true;
      changeCounter = motionControl_dDown;                  //value is now loaded value the counted encoder ticks
    }
    else if (counter == 2 && changeValue == true){                       //exit edit mode
       motionControl_dDown = changeCounter;                              //update the value
       EEPROM.put(motionControl_dDown_eeAddress, motionControl_dDown);   //send value to eeprom
       changeCounter = 0;                                                //reset change counter to zero for next time
       changeValue = false;                                              //termiate edit mode
    }

    else if (counter == 3 && changeValue == false){         //put controller in mode to edit value
      changeValue = true;
      changeCounter = motionControl_speed;                  //value is now loaded value plus the counted encoder ticks
    }
    else if (counter == 3 && changeValue == true){                       //exit edit mode
       motionControl_speed = changeCounter;                              //update the value
       EEPROM.put(motionControl_speed_eeAddress, motionControl_speed);   //send value to eeprom
       changeCounter = 0;                                                //reset change counter to zero for next time
       changeValue = false;                                              //termiate edit mode
    }
    
    else if (counter == 4){                      //if clicked on direction -> FLIP
      if (movementDirection == "  right"){
        movementDirection = "  left ";
      }
      else{
        movementDirection = "  right";
      }    
    }

    
    else if (counter == 5){                     //if clicked on Run then run the configured operation
      delay (10000);                            //give it a second to debounce the button
      motionControl();                          //run the operation
      if (movementDirection == "  right"){       //flip the desired direction after operation
        movementDirection = "  left ";
      }
      else{
        movementDirection = "  right";
      } 
    }
  }

  
}
