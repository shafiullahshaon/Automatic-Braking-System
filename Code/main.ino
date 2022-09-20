#include <Servo.h>
int state = 0; // variable
Servo myservo1; 
Servo myservo2;
int n4=7,n3=8,e2=9,n2=11,e1=10,n1=12,servo1=5,servo2=6,buz=4,sonar1_tx=A1,sonar1_rx=A2,sonar2_tx=A3,sonar2_rx=A4,SWITCH=A0,Lr=2,Lg=3;    //ardionuo connection
#define TUNE_HI digitalWrite(buz,HIGH)
#define TUNE_LOW digitalWrite(buz,LOW)
#define light_red_HI digitalWrite(Lr,HIGH)
#define light_red_LOW digitalWrite(Lr,LOW)
#define light_green_HI digitalWrite(Lg,HIGH)
#define light_green_LOW digitalWrite(Lg,LOW)
void setup() {
  Serial.begin(9600);
  pinMode(n1,OUTPUT);
  pinMode(n2,OUTPUT);
  pinMode(n3,OUTPUT);
  pinMode(n4,OUTPUT);
  pinMode(e1,OUTPUT);
  pinMode(e2,OUTPUT);
  pinMode(buz,OUTPUT);
  pinMode(sonar1_tx,OUTPUT);
  pinMode(sonar1_rx,INPUT);
  pinMode(sonar2_tx,OUTPUT);
  pinMode(sonar2_rx,INPUT);
  pinMode(SWITCH,INPUT);
  pinMode(Lr,OUTPUT);
  pinMode(Lg,OUTPUT);
  myservo1.attach(servo1);
  myservo2.attach(servo2);
  myservo1.write(0); //BREAK OUT BY RIGHT MOTOR
  myservo2.write(0); //BREAK OUT BY LEFT MOTOR

}

void loop() 
{
  if(digitalRead(SWITCH)==HIGH)
  {
    mobile_control();
  }
  else
  {
   oto_break(); 
  }
}
/////////////////////////////////////////
void mobile_control()
{
  
  if(Serial.available()>0)
    {
    state = Serial.read();
    }
  
 
  if(state == '1')
  {
    float diss1=sonar_read1();
    float diss2=sonar_read2();
    if(diss1<20.00 || diss2<20.00)
    {
       light_red_HI;
       bot(0,0);
       TUNE_HI;
       break_in();
       light_green_LOW;
    }
    else{
      bot(255,255);// straight forward
      light_green_HI;
      light_red_LOW;
    }
  }
  else if(state == '2') 
  {
    myservo1.write(0); //BREAK OUT BY RIGHT MOTOR
    myservo2.write(0); //BREAK OUT BY LEFT MOTOR
    bot(-255,-255);// straight backward
    TUNE_HI;
    light_green_LOW;
    light_red_HI;
  } 
  else if(state == '3')
  {
    bot(-255,255);// left turn;
    TUNE_HI;
    light_green_HI;
    light_red_HI;
  }
  else if(state == '4') 
  {
    bot(255,-255);// right turn 
    TUNE_HI;
    light_green_HI;
    light_red_HI;
  }
  else if(state == '5')
  {
    TUNE_HI;
  }
  else if(state == '0')
  {
    bot(0,0);
    TUNE_LOW;
    light_green_LOW;
    light_red_LOW;
  } 
  
   
}

///////////////////////////////////////////
void oto_break()
{
float diss1=sonar_read1();
float diss2=sonar_read2();
if(diss1<20.00 || diss2<20.00)
{
   bot(0,0);
   TUNE_HI;
   break_in();
   light_green_LOW;
   light_red_HI;
}
else
{
   bot(255,255);
   break_out();
   TUNE_LOW;
   light_green_HI;
   light_red_LOW;
}
  
}
void break_in()
{
 myservo1.write(170); //BREAK IN BY RIGHT MOTOR
 myservo2.write(170); //BREAK IN BY LEFT MOTOR 
  
}
////////////////////////////////////////////
void break_out()
{
 myservo1.write(0); //BREAK OUT BY RIGHT MOTOR
 myservo2.write(0); //BREAK OUT BY LEFT MOTOR
  
}
///////////////////////////////////////////////
void bot(int left, int right)// left motor value// right motor value
{
  if(left==0)
  {
    left_motor(0,left);
  }
  else if(left>0)
  {
    left_motor(1,left);
  }
  else
  {
    left_motor(2,-left);
  }
  /////////////////////////////////////
  if(right==0)
  {
    right_motor(0,right);
  }
  else if(right>0)
  {
    right_motor(1,right);
  }
  else
  {
    right_motor(2,-right);
  }
  
}
//////////////////////////////////////////////////////////////////
void left_motor(int dir, int spd)// sub function for left motor operation
{
  if(dir==1)// for forward
  {
    digitalWrite(n1,HIGH);
    digitalWrite(n2,LOW);
  }
  else if(dir==2)// for reverse
  {
    digitalWrite(n2,HIGH);
    digitalWrite(n1,LOW);
  }
  else// FOR STOP
  {
    digitalWrite(n2,LOW);
    digitalWrite(n1,LOW);
  }
  analogWrite(e1,spd);
}

void right_motor(int dir, int spd)// function for right motor operation
{
  if(dir==1)//for forward
  {
    digitalWrite(n3,HIGH);
    digitalWrite(n4,LOW);
  }
  else if(dir==2)// for reverse
  {
    digitalWrite(n4,HIGH);
    digitalWrite(n3,LOW);
  }
  else
  {
    digitalWrite(n3,LOW);
    digitalWrite(n4,LOW);
  }
  analogWrite(e2,spd);
}
////////////////////////////////////
float sonar_read1()
{
  digitalWrite(sonar1_tx, LOW);
  delayMicroseconds(5 );
  digitalWrite(sonar1_tx, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonar1_tx, LOW);
  float duration = pulseIn(sonar1_rx, HIGH);
  float Dis = (duration/2) / 29.1;
  return Dis;
}
////////////////////////////////////
float sonar_read2()
{
  digitalWrite(sonar2_tx, LOW);
  delayMicroseconds(5 );
  digitalWrite(sonar2_tx, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonar2_tx, LOW);
  float duration = pulseIn(sonar2_rx, HIGH);
  float Dis = (duration/2) / 29.1;
  return Dis;
}
