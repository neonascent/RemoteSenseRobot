
void resetServos() {
  //set all servos
  for (int i = 0; i < 6; i++) {
      // Drive each servo one at a time
    Serial.print(i); Serial.print(" - "); Serial.println(servoPosition[i]);
    pwm.setPWM(i, 0, servoPosition[i]);
  }
}

// set arm servo
void setArmServo(int n, int pulse) {
  pwm.setPWM(n, 0, pulse);
}


// robot direction functions

void forward() {
  setMotorAction(motor_A, -100, 200);
  setMotorAction(motor_B, -100, 200);
}



void backwards() {
  setMotorAction(motor_A, 100, 200);
  setMotorAction(motor_B, 100, 200);
}


void right() {
  setMotorAction(motor_A, -100, 100);
  setMotorAction(motor_B, 100, 100);
}

void left() {
  setMotorAction(motor_A, 100, 100);
  setMotorAction(motor_B, -100, 100);
}

void setMotorAction(int m, int s, int duration) {
  motor_standby(false);
  motorsActive = true;
  motorSpeed[m] = s;
  motorStart[m] = millis();
  motorTime[m] = duration;
  motor_speed2(m,s);
}

void doMotorAction() {  
    if (((motorStart[motor_A] + motorTime[motor_A]) < millis())  && ((motorStart[motor_B] + motorTime[motor_B]) < millis()) && motorsActive) {
      motor_standby(true);
      motorsActive = false;
    } 
}

// motor functions
void motor_speed2(boolean motor, char speed) { //speed from -100 to 100
  byte PWMvalue=0;
  PWMvalue = map(abs(speed),0,100,50,255); //anything below 50 is very weak
  if (speed > 0)
    motor_speed(motor,0,PWMvalue);
  else if (speed < 0)
    motor_speed(motor,1,PWMvalue);
  else {
    motor_coast(motor);
  }
}
void motor_speed(boolean motor, boolean direction, byte speed) { //speed from 0 to 255
  if (motor == motor_A) {
    if (direction == 0) {
      digitalWrite(out_A_IN1,HIGH);
      digitalWrite(out_A_IN2,LOW);
    } else {
      digitalWrite(out_A_IN1,LOW);
      digitalWrite(out_A_IN2,HIGH);
    }
    analogWrite(out_A_PWM,speed);
  } else {
    if (direction == 0) {
      digitalWrite(out_B_IN1,HIGH);
      digitalWrite(out_B_IN2,LOW);
    } else {
      digitalWrite(out_B_IN1,LOW);
      digitalWrite(out_B_IN2,HIGH);
    }
    analogWrite(out_B_PWM,speed);
  }
}
void motor_standby(boolean state) { //low power mode
  if (state == true)
    digitalWrite(out_STBY,LOW);
  else
    digitalWrite(out_STBY,HIGH);
}

void motor_brake(boolean motor) {
  if (motor == motor_A) {
    digitalWrite(out_A_IN1,HIGH);
    digitalWrite(out_A_IN2,HIGH);
  } else {
    digitalWrite(out_B_IN1,HIGH);
    digitalWrite(out_B_IN2,HIGH);
  }
}

void motor_coast(boolean motor) {
  if (motor == motor_A) {
    digitalWrite(out_A_IN1,LOW);
    digitalWrite(out_A_IN2,LOW);
    digitalWrite(out_A_PWM,HIGH);
  } else {
    digitalWrite(out_B_IN1,LOW);
    digitalWrite(out_B_IN2,LOW);
    digitalWrite(out_B_PWM,HIGH);
  }
}
