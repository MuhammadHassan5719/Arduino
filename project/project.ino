






//servo library
#include <ESP32Servo.h>

Servo myservo;
const int servoPin = 26;
int currentAngle;
int targetAngle;
//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "my_device"

#define REMOTEXY_ACCESS_PASSWORD "0000"


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 56 bytes
  { 255,3,0,0,0,49,0,19,0,0,0,109,121,95,100,101,118,105,99,101,
  0,176,2,106,200,200,84,1,1,2,0,5,7,26,143,143,115,11,60,60,
  48,2,26,31,4,18,67,7,86,31,24,14,45,0,2,26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_01_x; // from -100 to 100
  int8_t joystick_01_y; // from -100 to 100
  int8_t slider_01; // from 0 to 100

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
//servo library




//define right motor control pins
#define right_motor_A 19
#define right_motor_B 21
#define right_motor_speed 12 //enable pin

//define left motor control pins
#define left_motor_A 22
#define left_motor_B 23
#define left_motor_speed 13 //enable pin

//define two arrays with a list of pins for each motor
uint8_t RightMotor[3] = {right_motor_A, right_motor_B, right_motor_speed};
uint8_t LeftMotor[3] = {left_motor_A, left_motor_B, left_motor_speed};

//speed control of motors
void Wheel (uint8_t * motor, int v) // v = motor speed, motor = pointer to an array of pins 
{
  if (v > 100) v=100;
  if (v < -100) v=-100;
  if (v > 0){

    digitalWrite (motor [0], HIGH);
    digitalWrite (motor [1], LOW);
    analogWrite (motor [2], v * 2.55);
  }
  else if ( v<0 ){

    digitalWrite (motor [0], LOW);
    digitalWrite (motor [1], HIGH);
    analogWrite (motor [2], (-v) * 2.55);
  }
  else{
    digitalWrite (motor [0], LOW);
    digitalWrite (motor [1], LOW);
    analogWrite (motor [2], 0);
  }
}

void setup() 
{
  RemoteXY_Init (); 
  Serial.begin(115200);
  
  // TODO you setup code
  
  myservo.attach(servoPin);  //Servo Attached At pin 26

    //initialization pins
  pinMode (right_motor_A, OUTPUT);
  pinMode (right_motor_B, OUTPUT);
  pinMode (left_motor_A, OUTPUT);
  pinMode (left_motor_B, OUTPUT);
  
  RemoteXY.slider_01 =50;//adjust intial position of servo
}

void loop() { 
  targetAngle = map(RemoteXY.slider_01, 0, 100, 0, 180);
  
  // Move the servo to the target angle
  if (currentAngle != targetAngle) {
    currentAngle = targetAngle;
    myservo.write(currentAngle);
  
  RemoteXY_delay(15); // Small delay to smooth out the movement
  }

  // Manage the right and left motors
  Wheel(RightMotor, RemoteXY.joystick_01_y - RemoteXY.joystick_01_x);
  Wheel(LeftMotor, RemoteXY.joystick_01_y + RemoteXY.joystick_01_x);
}
