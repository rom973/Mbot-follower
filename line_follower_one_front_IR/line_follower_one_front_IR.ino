
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMCore.h>

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);
void move(int direction, int speed)
{
      int leftSpeed = 0;
      int rightSpeed = 0;
      if(direction == 1){
          leftSpeed = speed;
          rightSpeed = speed;
      }else if(direction == 2){
          leftSpeed = -speed;
          rightSpeed = -speed;
      }else if(direction == 3){
          leftSpeed = -speed;
          rightSpeed = speed;
      }else if(direction == 4){
          leftSpeed = speed;
          rightSpeed = -speed;
      }
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
MeLineFollower linefollower_2(2);

void setup(){
    pinMode(A7,INPUT);
    while(!((0^(analogRead(A7)>10?0:1))))
    {
        _loop();
    }
    _delay(5);
}

void loop(){
    if((((true&&(1?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(1?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1))))) || (((true&&(0?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(0?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1)))))){
        move(1,200);
    }else{
        if((true&&(0?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))){
            while(!(((true&&(1?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(1?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1))))))
            {
                _loop();
                move(4,100);
            }
        }
        if((true&&(0?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1)))){
            while(!(((true&&(1?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(1?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1))))))
            {
                _loop();
                move(3,100);
            }
        }
    }
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
}
