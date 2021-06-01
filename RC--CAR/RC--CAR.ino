#include <IRremote.h>
//Init IR sensor
IRrecv rc(11);
decode_results results;

//Init Motors

const int PWM_M1 = 10;
const int IN1_M1 = 7;
const int IN2_M1 = 3;

const int PWM_M2 = 6;
const int IN1_M2 = 8;
const int IN2_M2 = 9;

int speed = 100;

//Init the lights

const int Back_Light = 4;
const int Front_Light = 13;
const int Left_Light = 2;
const int Right_Light = 12;

void setup(){
  Serial.begin(9600);
  rc.enableIRIn();
  
  //Setting the pinmodes
  pinMode(PWM_M1,OUTPUT);
  pinMode(PWM_M2,OUTPUT);
  
  pinMode(IN1_M1,OUTPUT);
  pinMode(IN2_M1,OUTPUT);
  
  pinMode(IN1_M2,OUTPUT);
  pinMode(IN2_M2,OUTPUT);
  
  //initalizing every pin to zero
  digitalWrite(IN1_M1, LOW);
  digitalWrite(IN2_M1, LOW);
  digitalWrite(IN1_M2, LOW);
  digitalWrite(IN2_M2, LOW);
  digitalWrite(Front_Light,LOW);
  digitalWrite(Back_Light,LOW);
  digitalWrite(Left_Light,LOW);
  digitalWrite(Right_Light,LOW);
}


void loop(){
  if (rc.decode(&results)){   //Reading the receiver value
 
       
      switch(results.value){// calling the appropriate function according to the value read
          case 0xFD807F://vol+
            forward();
          break;
          case 0xFD20DF://|<<
            turnLeft();
          break;
          case 0xFDA05F://>||
            stop();
          break ;  
          case 0xFD609F://>>|
           turnRight();
          break ;               
          case 0xFD10EF://down arrow
            speedDown();
          break ;  
          case 0xFD906F://vol-
            backward();
          break ;  
          case 0xFD50AF://up arrow
            speedUp();
          break ;  
           
          
        }
       rc.resume(); 
  }
}



void forward(){
  Serial.println("forward");
  Serial.println("Head Light ON");
  digitalWrite(Front_Light,HIGH);  //switching on the Head Light
  digitalWrite(Back_Light,LOW);
  
  // Setting the motor on the desired value
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
  
  digitalWrite(IN1_M1, HIGH);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, HIGH);
  digitalWrite(IN2_M2, LOW);
}

void backward(){
  Serial.println("backward");
  digitalWrite(Front_Light,LOW);
  Serial.println("Head Light OFF");
  digitalWrite(Back_Light,HIGH); //Switching on the tail light
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
  
  digitalWrite(IN1_M1, LOW);
  digitalWrite(IN2_M1, HIGH);
  
  digitalWrite(IN1_M2, LOW);
  digitalWrite(IN2_M2, HIGH);
}

void turnLeft(){
  Serial.println("turnLeft");
  digitalWrite(Left_Light,HIGH);
  analogWrite(PWM_M1, 0);
  analogWrite(PWM_M2, speed);
  
  digitalWrite(IN1_M1, LOW);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, HIGH);
  digitalWrite(IN2_M2, LOW);
  digitalWrite(Left_Light,LOW);
}

void turnRight(){
  Serial.println("turnRight");
  digitalWrite(Right_Light,HIGH);
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, 0);
  
  digitalWrite(IN1_M1, HIGH);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, LOW);
  digitalWrite(IN2_M2, LOW);
  digitalWrite(Right_Light,LOW);
}

void stop(){
  Serial.println("stop");
  digitalWrite(Back_Light,HIGH);
  digitalWrite(IN1_M1, LOW);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, LOW);
  digitalWrite(IN2_M2, LOW);
}

void speedUp(){
  Serial.println("speedUp");
  speed+=10;
  if(speed>255) speed =255;
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
}

void speedDown(){
  Serial.println("speedDown");
  digitalWrite(Back_Light,HIGH);
  speed-=10;
  if(speed<0) speed =0;
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
  digitalWrite(Back_Light,LOW);
}
