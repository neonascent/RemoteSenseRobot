
// Smoothstep from Dan Thompson 2009
// For the full tutorial visit http://danthompsonsblog.blogspot.com/

#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x))) //SMOOTHSTEP expression.

//Configure these to fit your design...
// 0 serial
// 1 serial

// 2 
#define out_B_PWM 3
#define out_A_PWM 3 // tied
#define out_B_IN2 4
#define out_B_IN1 5
#define out_STBY  6
#define out_A_IN1 7
#define out_A_IN2 8
// 9
// 10
// 11
// 12
// 13






#define motor_A 0
#define motor_B 1
#define motor_AB 2

// operational values
int motorSpeed = 100;
int motorDuration = 150; // 300 reduced for big battery
int motorTurnDuration = 155;  // 235 reduced for big battery

void setup()
{
  pinMode(out_STBY,OUTPUT);
  pinMode(out_A_PWM,OUTPUT);
  pinMode(out_A_IN1,OUTPUT);
  pinMode(out_A_IN2,OUTPUT);
  pinMode(out_B_PWM,OUTPUT);
  pinMode(out_B_IN1,OUTPUT);
  pinMode(out_B_IN2,OUTPUT);

  Serial.begin(9600);

  randomSeed(analogRead(4));  // floating unconnected pin
}

void loop()
{ 
  
  forward();
  delay(1000);
  backwards();
  delay(1000);  
  left();
  delay(1000);  
  right();
  delay(3000);

 
}



void forward() {
  driveMotors(motorSpeed, motorDuration, -1,-1);
}

void backwards() {
  driveMotors(motorSpeed, motorDuration, 1,1);
}

void right() {
  driveMotors(motorSpeed, motorTurnDuration, -1,1);
}

void left() {
  driveMotors(motorSpeed, motorTurnDuration, 1,-1);
}

// smoothed motion
void driveMotors(int motorSpeed, int motorDuration, int motor_A_direction, int motor_B_direction) {

  // smoothstep variables
  float A = 0.0;         //Input Min Value
  float B = motorSpeed;       //Input Max Value
  float N = 10.0;       //Input number of steps for transition
  float X;               //final smoothstepped value
  float v;               //smoothstep expression variable
  float rampTime = motorDuration / 3; // take 500 ms to accelerate

  // start motors
  motor_standby(false);

  // accelerate
  for (int j = 0; j < N; j++) {
    v = j / N;                    // Iteration divided by the number of steps.
    v = SMOOTHSTEP(v);            // Run the smoothstep expression on v.
    X = (B * v) + (A * (1 - v));  // Run the linear interpolation expression using the current 
    //smoothstep result.

    motor_speed2(motor_A, X * motor_A_direction);
    motor_speed2(motor_B, X * motor_B_direction);
    delay(rampTime/N);
  }

  // full speed
  motor_speed2(motor_A, motorSpeed * motor_A_direction);
  motor_speed2(motor_B, motorSpeed * motor_B_direction);
  delay(rampTime);

  // deccelerate
  for (int j = 0; j < N; j++) {
    v = j / N;                    // Iteration divided by the number of steps.
    v = SMOOTHSTEP(v);            // Run the smoothstep expression on v.
    X = (B * v) + (A * (1 - v));  // Run the linear interpolation expression using the current 
    //smoothstep result.

    motor_speed2(motor_A, (motorSpeed - X) * motor_A_direction);
    motor_speed2(motor_B, (motorSpeed - X) *  motor_B_direction);
    delay(rampTime/N);
  }

  motor_standby(true);

}






/*
/ sparkfun motor driver code
 */

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
    } 
    else {
      digitalWrite(out_A_IN1,LOW);
      digitalWrite(out_A_IN2,HIGH);
    }
    analogWrite(out_A_PWM,speed);
  } 
  else {
    if (direction == 0) {
      digitalWrite(out_B_IN1,HIGH);
      digitalWrite(out_B_IN2,LOW);
    } 
    else {
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
  } 
  else {
    digitalWrite(out_B_IN1,HIGH);
    digitalWrite(out_B_IN2,HIGH);
  }
}

void motor_coast(boolean motor) {
  if (motor == motor_A) {
    digitalWrite(out_A_IN1,LOW);
    digitalWrite(out_A_IN2,LOW);
    digitalWrite(out_A_PWM,HIGH);
  } 
  else {
    digitalWrite(out_B_IN1,LOW);
    digitalWrite(out_B_IN2,LOW);
    digitalWrite(out_B_PWM,HIGH);
  }
} 
















