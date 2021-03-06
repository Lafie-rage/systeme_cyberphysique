#include "MeMegaPi.h"
#include "Subsystem.h"
#include <Wire.h>
#include <TimerFive.h>

#define BELT_PITCH 2.032 // distance between teeth
#define NTEETH 90.0 // number of teeth 

#define RPM_2_MMS BELT_PITCH*NTEETH/60.0 // conversion of the speed from rpm to mm/s
#define VOLTS_2_PWM 255.0/12.0 // conversion voltage to pwm [-255 255]
#define MAX_VOLTAGE 9 // max allowed voltage

#define DISTANCE_1_WHEEL BELT_PITCH * NTEETH / 360 // Distance equivalent to an entire wheel turn.


volatile float angle = 0;  //actual heading in deg
volatile float speed1 = 0; //actual speed in mm/s
volatile float speed2 = 0;
volatile float pos1 = 0;
volatile float pos2 = 0;
volatile float ref1 = 0; //actual references from serial
volatile float ref2 = 0;
float u1 = 0; // control signals
float u2 = 0;
float temp_u1 = 0;
float temp_u2 = 0;
volatile long compTime = 0; // actual computation time of the critical loop
volatile short overrun = 0;

MeGyro gyro; // gyroscope object instanciation
MeEncoderOnBoard Encoder_1(SLOT1); // motor with encoder object instanciation
MeEncoderOnBoard Encoder_2(SLOT2);

/*
 * routine that is called every 5ms by the ISR routine
 */

void Update5ms()
{
  UpdateSensors();
  UpdateControl();
  UpdateActuators();
}

void UpdateSensors(){
  gyro.update(); // update the gyroscope state
  angle = gyro.getAngleZ(); // get the estimated heading in deg
  
  Encoder_1.loop(); // update the encoders state
  Encoder_2.loop();

  pos1 = Encoder_1.getCurPos() * DISTANCE_1_WHEEL;
  pos2 = Encoder_2.getCurPos() * DISTANCE_1_WHEEL;
  
  speed1 = Encoder_1.getCurrentSpeed()*RPM_2_MMS; // compute the speed in mm/s
  speed2 = Encoder_2.getCurrentSpeed()*RPM_2_MMS; 
}



void UpdateControl()
{
  // Update FSM
  // Calculate voltage for motor 1
  Subsystem_U.position = pos1;
  Subsystem_U.vitesse_souhaitee = 150;
  Subsystem_step();

  temp_u1 = Subsystem_Y.tension_commandee;
  
  // Calculate voltage for motor 2
  Subsystem_U.position = pos2;
  Subsystem_U.vitesse_souhaitee = 150;
  Subsystem_step();
  temp_u2 = -Subsystem_Y.tension_commandee;

  u1 = temp_u1;
  u2 = temp_u2;
}

void UpdateActuators(){
  setMotorsVoltage(u1,u2); // set the voltages
}
/*=================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
* routine that is called every 5ms by the timer 5
*/
void Timer5ISR(){
  static char executing = 0; // set to 1 when the update function is running
  if(executing) {
    overrun = 1;
    return;
  }
  else executing = 1; // if already running => overrunned

  interrupts(); // enable the interrupts during the execution of this loop
  long startTime = micros();
  
  Update5ms();
  
  compTime = micros()-startTime;
  executing = 0;
}

/*
 * interruption routine for encoder pulse counting (quadrature)
 */

void isr_process_encoder1(void)
{
  if(digitalRead(Encoder_1.getPortB()) == 0)
  {
    Encoder_1.pulsePosMinus();
  }
  else
  {
    Encoder_1.pulsePosPlus();;
  }
}

void isr_process_encoder2(void)
{
  if(digitalRead(Encoder_2.getPortB()) == 0)
  {
    Encoder_2.pulsePosMinus();
  }
  else
  {
    Encoder_2.pulsePosPlus();
  }
}

/*
 * Setup the motors with the reduction ratio and number of pulses per turn
 */

void setupMotors(){
  Encoder_1.setPulse(8);
  Encoder_1.setRatio(46);
  Encoder_2.setPulse(8);
  Encoder_2.setRatio(46);
  
  attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);
  //Set PWM 8KHz
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
}


/*
 * Sets the voltage to the motor. Limited by MAX_VOLTAGE
 */
void setMotorsVoltage(float voltage1,float voltage2){
  Encoder_1.setMotorPwm(constrain(voltage1,-MAX_VOLTAGE,MAX_VOLTAGE)*VOLTS_2_PWM);
  Encoder_2.setMotorPwm(constrain(voltage2,-MAX_VOLTAGE,MAX_VOLTAGE)*VOLTS_2_PWM);
}



void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(1);
  gyro.begin();
  Wire.setClock(400000);
  setupMotors();
  Timer5.initialize(5000);
  Timer5.attachInterrupt(Timer5ISR);  

  // Setup for observer part
  Subsystem_initialize();
}


void loop()
{
  static float lastRef1 = 0;
  static float lastRef2 = 0;
  
  noInterrupts();
  ref1 = lastRef1;
  ref2 = lastRef2;
  float angleCopy = angle;
  float speed1Copy = speed1;
  float speed2Copy = speed2;
  long compTimeCopy = compTime;
  interrupts();
  
  //Serial.read();
//  Serial.print(" compTime: ");
//  Serial.print(compTimeCopy);
//
//  Serial.print(" overrun: ");
//  Serial.print(overrun);
//  
//  Serial.print(" speed1: ");
//  Serial.print(speed1Copy);
//  
//  Serial.print(" speed2: ");
//  Serial.print(speed2Copy);
//
//  Serial.print(" pos1: ");
//  Serial.print(pos1);
//
//  Serial.print(" pos2: ");
//  Serial.print(pos2);

 Serial.print(" temp_u1: ");
 Serial.print(temp_u1);

  Serial.print(" temp_u2: ");
  Serial.print(temp_u2);

//  
//  Serial.print(" angle: ");
//  Serial.print(angleCopy);
//
//  Serial.print(" ref1: ");
//  Serial.print(ref1);
//
//  Serial.print(" ref2: ");
//  Serial.print(ref2);
  
  
 Serial.println();

  if(Serial.available()){
    lastRef1 = Serial.parseFloat();
    lastRef2 = Serial.parseFloat();
  }
  delay(10);
}
