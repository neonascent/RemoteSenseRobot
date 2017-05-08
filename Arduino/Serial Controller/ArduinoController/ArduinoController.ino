#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// elements
#define CLAW_SERVO 5
#define HAND_SERVO 4
#define WRIST_SERVO 3
#define ELBOW_SERVO 2
#define SHOULDER_SERVO 1
#define TWIST_SERVO 0

// motor controller arduino pin setup
//Configure these to fit your design...
#define out_STBY 6
#define out_B_PWM 3
#define out_A_PWM 9
#define out_A_IN2 8
#define out_A_IN1 7
#define out_B_IN1 5
#define out_B_IN2 4

// motor control defines
#define motor_A 0
#define motor_B 1
#define motor_AB 2

// commands
#define CLAW_COMMAND 'C'
#define HAND_COMMAND 'H'
#define WRIST_COMMAND 'W'
#define ELBOW_COMMAND 'E'
#define SHOULDER_COMMAND 'S'
#define TWIST_COMMAND 'T'
#define ROBOT_FORWARD 'F'
#define ROBOT_BACKWARD 'B'
#define ROBOT_LEFT 'L'
#define ROBOT_RIGHT 'R'

// our servo # counter
uint8_t servonum = 0;
int servoPosition[6] = {350, 380, 350, 300, 350, 370};
int motorSpeed[2] = {0, 0};
unsigned long motorStart[2] = {0,0};
int motorTime[2] = {0,0};
bool motorsActive = false;

void setup() {
  // set up motor controller pins
  pinMode(out_STBY,OUTPUT);
  pinMode(out_A_PWM,OUTPUT);
  pinMode(out_A_IN1,OUTPUT);
  pinMode(out_A_IN2,OUTPUT);
  pinMode(out_B_PWM,OUTPUT);
  pinMode(out_B_IN1,OUTPUT);
  pinMode(out_B_IN2,OUTPUT);

  Serial.begin(115200);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  resetServos();
  yield();
}

void loop() {
  parseCommands();
}

