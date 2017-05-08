//read in string char by char "$S100." better to add a period at the end
void parseCommands() {
  waitForCommand();
  char type = getType();

  String command = getControllerCommand();
  if (command.length() > 0) { // command
    int value = command.toInt();

    // arm controls 
    
    if (type == CLAW_COMMAND) {            // claw control
      setArmServo(CLAW_SERVO, value);
    } else 
    if (type == HAND_COMMAND) {            // hand control
      setArmServo(HAND_SERVO, value);
    } else 
    if (type == WRIST_COMMAND) {            // wrist control
      setArmServo(WRIST_SERVO, value);
    } else 
    if (type == ELBOW_COMMAND) {            // elbow control
      setArmServo(ELBOW_SERVO, value);
    } else 
    if (type == SHOULDER_COMMAND) {            // shoulder control
      setArmServo(SHOULDER_SERVO, value);
    } else 
    if (type == TWIST_COMMAND) {            // twist control
      setArmServo(TWIST_SERVO, value);
    }  else 


    // motor controls
    
    if (type == ROBOT_FORWARD) {            //  ROBOT_FORWARD
      forward();
    }  else 
    if (type == ROBOT_BACKWARD) {            // ROBOT_BACKWARD
      backwards();
    } else 
    if (type == ROBOT_LEFT) {            // ROBOT_LEFT
      left();
    } else 
    if (type == ROBOT_RIGHT) {            // ROBOT_RIGHT
      right();
    }
  }

}

String getControllerCommand() {
  String command = "";
  while (1) {
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      // check if is end or split character
      if (c == '.') { // end of command 
        return command;
      } 
      else {
        command += c; //makes the string readString
      }
    }
    doMotorAction();
  }
}


void waitForCommand() {
  while (1) {
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      // check if is end or split character
      if (c == '$') {
        return;
      }
    }
    doMotorAction();
  }
}

char getType() {
  while (1) {
    if (Serial.available() > 0) {
      return Serial.read();  //gets one byte from serial buffer;
    }
    doMotorAction();
  }
}


