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

// commands
#define CLAW_COMMAND 'C'
#define HAND_COMMAND 'H'
#define WRIST_COMMAND 'W'
#define ELBOW_COMMAND 'E'
#define SHOULDER_COMMAND 'S'
#define TWIST_COMMAND 'T'

// our servo # counter
uint8_t servonum = 0;
int servoReset[6] = {350, 380, 350, 300, 350, 370};


void setup() {
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

