#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
  SERVO_LEFT = 1,
  SERVO_CENTRAL = 2,
  SERVO_RIGHT = 3
} servo_pos_t;

#define SERVO_LOW  1400
#define SERVO_HIGH 1600
#define SERVO_MAX  2200

#define LED_ON HIGH
#define LED_OFF LOW

#define TURN_PERIODE 25000

// PPM read from receiver
#define speedPPM D8 //PPM input for INT3, Froward/Backward channel
#define steerPPM D9 //PPM input for INT0, Steering channel
#define Light_btnPPM D10 //PPM input for INT1, HeadLight door open channel 

// Numbers of pins on Arduino Micro for LEDs control
#define HeadLight D0  // pin 8 - 5mm white HeadLight LEDs
#define ReverseLight D1 // pin A3 - Reverse - 3mm white LEDs on tail panel
#define TurnLeft D2 // pin 4 - Left turn signals
#define TurnRight D3 // pin 6 - Right turn signals
#define TailLeft D4 // pin 10 - Tail lamp Left
#define TailRight D5 // pin 9 - Tail lamp Right
#define BreakLight D6 // pin 9 - Tail lamp Right

volatile servo_pos_t speed_servo;
volatile servo_pos_t steer_servo;
volatile servo_pos_t Light_btn_servo;

int Tail_Light_min=0; //variable indicating the operating modes of the rear lamps.
// Variables for reading signals from receiver
volatile unsigned long lt1, ct1, ms_spd, tmp1;
volatile unsigned long lt2, ct2, ms_steer,tmp2;
volatile unsigned long lt3, ct3, ms_Light_btn, tmp3;

// Variables for light, turn signals, reverse
volatile bool light_on;
volatile bool reverse_on;
volatile bool turn_left;
volatile bool turn_right;

volatile unsigned long turn_left_time;
volatile unsigned long turn_right_time;

servo_pos_t eval_servo( unsigned long servo_value )
{
  servo_pos_t ret_value;

  ret_value = SERVO_CENTRAL;

  if( servo_value < SERVO_LOW )
  {
    ret_value = SERVO_LEFT;
  }
  if( servo_value > SERVO_HIGH )
  {
    ret_value = SERVO_RIGHT;
  }

  return( ret_value );
}

void setup(){

  //Set pin modes for servo connection
  pinMode(steerPPM, INPUT_PULLUP);
  pinMode(speedPPM, INPUT_PULLUP);
  pinMode(Light_btnPPM, INPUT_PULLUP);

  //Set pin modes for LEDs
  pinMode (HeadLight, OUTPUT);
  pinMode (ReverseLight, OUTPUT);
  pinMode (TurnLeft, OUTPUT);
  pinMode (TurnRight, OUTPUT);
  pinMode (TailLeft, OUTPUT);
  pinMode (TailRight, OUTPUT);
  pinMode (BreakLight, OUTPUT);

  //Set pins state on the beginning
  digitalWrite (HeadLight, LOW);
  digitalWrite (ReverseLight, LOW);
  digitalWrite (TurnLeft, LOW);
  digitalWrite (TurnRight, LOW);
  digitalWrite (TailLeft, LOW);
  digitalWrite (TailRight, LOW);
  digitalWrite (BreakLight, LOW);

  digitalWrite (steerPPM, HIGH);
  digitalWrite (speedPPM, HIGH);
  digitalWrite (Light_btnPPM, HIGH);

  //attach PPM interrupt service routines
  attachInterrupt( digitalPinToInterrupt(steerPPM), steerPPM_int, CHANGE);
  attachInterrupt( digitalPinToInterrupt(speedPPM), speedPPM_int, CHANGE);
  attachInterrupt( digitalPinToInterrupt(Light_btnPPM), Light_btnPPM_int, CHANGE);

  speed_servo = SERVO_CENTRAL;
  steer_servo = SERVO_CENTRAL;
  Light_btn_servo = SERVO_CENTRAL;
}

// Main cycle
void loop()
{
  //convert servo puls values to servo status
  speed_servo = eval_servo( ms_spd );
  steer_servo = eval_servo( ms_steer );
  Light_btn_servo = eval_servo( ms_Light_btn );

  //evaluate the servo status
  if( Light_btn_servo == SERVO_RIGHT )
  {
    light_on = true;
  }
  else
  {
    light_on = false;
  }

  if( speed_servo == SERVO_LOW )
  {
    reverse_on = true;
  }
  else
  {
    reverse_on = false;
  }

  if( steer_servo == SERVO_RIGHT )
  {
    turn_left = true;
  }
  else
  {
    turn_left = false;
  }

  if( steer_servo == SERVO_LEFT )
  {
    turn_right = true;
  }
  else
  {
    turn_right = false;
  }

  //switch on head light
  if( light_on == true )
  {
    digitalWrite( HeadLight, HIGH );
    if( turn_left == false )
    {
      digitalWrite( TailLeft, HIGH );
    }
    if( turn_right == false )
    {
      digitalWrite( TailRight, HIGH );
    }
  }
  else
  {
    digitalWrite( HeadLight, LOW );
    if( turn_left == false )
    {
      digitalWrite( TailLeft, LOW );
    }
    if( turn_right == false )
    {
      digitalWrite( TailRight, LOW );
    }
  }

  //switch on reverse light
  if( reverse_on == true )
  {
    digitalWrite( ReverseLight, HIGH );
  }
  else
  {
    digitalWrite( ReverseLight, LOW );
  }
  
  //Handle blink timing
  if( turn_left == true )
  {
    turn_left_time++;
    if( turn_left_time > TURN_PERIODE)
    {
      turn_left_time = 0;
    }
  }
  else
  {
    turn_left_time = 0;
  }

  if( turn_right == true )
  {
    turn_right_time++;
    if( turn_right_time > TURN_PERIODE)
    {
      turn_right_time = 0;
    }
  }
  else
  {
    turn_right_time = 0;
  }

  //switch on Turn Left
  if( turn_left == true )
  {
    if( turn_left_time < TURN_PERIODE/2 )
    {
      digitalWrite( TurnLeft, HIGH );
      digitalWrite( TailLeft, HIGH );
    }
    else
    {
      digitalWrite( TurnLeft, LOW );
      digitalWrite( TailLeft, LOW );
    }
  }
  else
  {
    digitalWrite( TurnLeft, LOW );
    if( light_on == true )
    {
      digitalWrite( TailLeft, HIGH );
    }
    else
    {
      digitalWrite( TailLeft, LOW );
    }
  }

  //switch on Turn Right
  if( turn_right == true )
  {
        if( turn_right_time < TURN_PERIODE/2 )
    {
      digitalWrite( TurnRight, HIGH );
      digitalWrite( TailRight, HIGH );
    }
    else
    {
      digitalWrite( TurnRight, LOW );
      digitalWrite( TailRight, LOW );
    }
  }
  else
  {
    digitalWrite( TurnRight, LOW );
    if( light_on == true )
    {
      digitalWrite( TailRight, HIGH );
    }
    else
    {
      digitalWrite( TailRight, LOW );
    }
  }  
}

// Reading signals from 3 channels
void speedPPM_int() 
{    // PPM read interrupt
 ct1 = micros(); // read current time
 ms_spd=ct1-lt1; // ms = current time - last time
 lt1=ct1; // last time
 if(ms_spd>SERVO_MAX)  // fix time bug 
   ms_spd=tmp1;        // fix time bug
   tmp1=ms_spd;        // fix time bug
}    
void steerPPM_int() 
{
 ct2 = micros();
 ms_steer=ct2-lt2;
 lt2=ct2;
 if(ms_steer>SERVO_MAX)
   ms_steer=tmp2;
   tmp2=ms_steer;
}
void Light_btnPPM_int() 
{
 ct3 = micros();
 ms_Light_btn=ct3-lt3;
 lt3=ct3; // last time
 if(ms_Light_btn>SERVO_MAX)
   ms_Light_btn=tmp3;
   tmp3=ms_Light_btn;
}
