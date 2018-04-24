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
void etatLigne();
double surLaLigne;
MeLineFollower linefollower_1(1);
MeLineFollower linefollower_2(2);
void capteurVirageGauche();
double virageGauche;
void capteurVirageDroite();
double virageDroite;
void capteurRecuperationDroite();
double recuperationDroite;
void capteurRecuperationGauche();
double recuperationGauche;
void legerDroite();
void legerGauche();

// je regarde si les deux capteurs sont noir noir : noir, noir, noir, noir, ça veux dire que je suis sur la ligne donc valeur de la variable surLaLigne = 1
void etatLigne()
{
    if((((true&&(0?(linefollower_1.readSensors()&2):!(linefollower_1.readSensors()&2)))) && ((true&&(0?(linefollower_1.readSensors()&1):!(linefollower_1.readSensors()&1))))) && (((true&&(0?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(0?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1)))))){
        surLaLigne = 1;
    }else{
        surLaLigne = 0;
    }
    
}
// là on a la configuration noir, blanc, noir, noir 
void capteurVirageGauche()
{
    if((((true&&(0?(linefollower_1.readSensors()&2):!(linefollower_1.readSensors()&2)))) && ((true&&(1?(linefollower_1.readSensors()&1):!(linefollower_1.readSensors()&1))))) && (((true&&(0?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(0?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1)))))){
        virageGauche = 1;
    }else{
        virageGauche = 0;
    }
    
}
// là on a noir,noir,blanc,noir
void capteurVirageDroite()
{
    if((((true&&(0?(linefollower_1.readSensors()&2):!(linefollower_1.readSensors()&2)))) && ((true&&(0?(linefollower_1.readSensors()&1):!(linefollower_1.readSensors()&1))))) && (((true&&(1?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(0?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1)))))){
        virageDroite = 1;
    }else{
        virageDroite = 0;
    }
    
}
// là on a merdé, noir,noir,noir,blanc : le robot a été trop à droite
void capteurRecuperationDroite()
{
    if((true&&(1?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1)))){
        recuperationDroite = 1;
    }else{
        recuperationDroite = 0;
    }
    
}
// meme chose que juste avant : le robot a été trop à gauche : blanc,noir,noir,noir
void capteurRecuperationGauche()
{
    if((true&&(1?(linefollower_1.readSensors()&2):!(linefollower_1.readSensors()&2)))){
        recuperationGauche = 1;
    }else{
        recuperationGauche = 0;
    }
    
}
// mouvement pour corriger un peu vers la droite
void legerDroite()
{
    motor_9.run((9)==M1?-(200):(200));
    
    motor_10.run((10)==M1?-(150):(150));
    
}
// mouvement pour corriger un peu vers la gauche
void legerGauche()
{
    motor_9.run((9)==M1?-(150):(150));
    
    motor_10.run((10)==M1?-(200):(200));
    
}

// là je lance le programme avec le bouton et un delais de 5 sec, mais rien n ese passe ...
void setup(){
    pinMode(A7,INPUT);
    while(!((0^(analogRead(A7)>10?0:1))))
    {
        _loop();
    }
    _delay(5);
    
}

void loop(){
    
    etatLigne();
    capteurVirageGauche();
    capteurVirageDroite();
    capteurRecuperationDroite();
    capteurRecuperationGauche();
    while(!(((surLaLigne)==(1))))
    {
        _loop();
        move(1,200);
        if(((virageDroite)==(1))){
            while(!(!(((virageDroite)==(1)))))
            {
                _loop();
                legerDroite();
            }
        }
        if(((virageGauche)==(1))){
            while(!(!(((virageGauche)==(1)))))
            {
                _loop();
                legerGauche();
            }
        }
        if(((recuperationDroite)==(1))){
            while(!(((surLaLigne)==(1))))
            {
                _loop();
                move(3,100);
            }
        }
        if(((recuperationGauche)==(1))){
            while(!(((surLaLigne)==(1))))
            {
                _loop();
                move(4,100);
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

