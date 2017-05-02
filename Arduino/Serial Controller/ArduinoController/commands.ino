//read in string char by char "$SP0." better to add a period at the end
void parseCommands() {
  waitForCommand();
  char type = getType();

  String command = getControllerCommand();
  if (command.length() > 0) { // command
    int value = command.toInt();
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
  }
}

char getType() {
  while (1) {
    if (Serial.available() > 0) {
      return Serial.read();  //gets one byte from serial buffer;
    }
  }
}


