#include <IRremote.h> // Include IR Remote Library by Ken Shirriff
#include <Servo.h> // Include Arduino Servo Library
#include <Stepper.h> // Include Arduino Stepper Library
#define STEPS 400  //check stepper datasheet, how many steps in 1 revolution
const int RECV_PIN = 4; // Define Sensor Pin
const int SERVO_PIN = 6; // Define Servo Pin
int numstep = 10; //0.9 degree per step roughy 400 step = 1 cycle rotation
int pos = 90;// Start at 90 Degrees (Center position) for servo 
unsigned long lastCode; // Define variable to store last code received

IRrecv irrecv(RECV_PIN); // Define IR Receiver and Results Objects
decode_results results;
Servo myservo; // Create servo object         
Stepper myStepper(STEPS, 8, 9, 10, 11);

void setup()
{
  irrecv.enableIRIn();// Start the receiver
  myStepper.setSpeed(60); // set the speed at 60 rpm:
  myservo.attach(SERVO_PIN); // Attach the servo
  myservo.write(pos); // Start with Servo in Center 
}

void loop() {
if(irrecv.decode(&results)) //this checks to see if a code has been received
{
    if(results.value == 0xFFFFFFFF)   
    {
       results.value = lastCode; // If Repeat then use last code received       
    }
    
    if(results.value == 0xFF18E7)// UP button pressed (Stepper)
    {
     // step one revolution in one direction: (CW)
     lastCode = results.value; 
    // numstep += 10; // Move left 2 degrees
    //if( numstep > 60){ numstep = 60;}
     myStepper.step(numstep);
    }
    
    if(results.value == 0xFF4AB5) // DOWN button pressed (Stepper)
    {
     // step one revolution in the other direction:(CCW)
     lastCode = results.value; 
    // numstep=-numstep; //negative means CCW
    // numstep -= 10; // Move left 2 degrees
    //if( numstep < -60){ numstep = -60;}
     myStepper.step(-numstep);
    }
    
    if(results.value == 0xFF10EF)    
    {
        lastCode = results.value;  // Left Button Pressed (Servo)
        pos += 10; // Move left 2 degrees 
        if(pos > 120){pos = 120;}  // Prevent position above 180                    
        myservo.write(pos);      
    }
      
    if(results.value ==  0xFF5AA5)     
    {       
       lastCode = results.value;  // Right Button Pressed (Servo)
       pos -= 10; // Move Right 2 degrees         
       if(pos < 60){pos = 60;}   // Prevent position below 0                
       myservo.write(pos);     
    }

   if(results.value == 0xFF38C7)     
    {
       // Center Button Pressed
       lastCode = results.value;
       // Move to Center  
      // pos = 90;          
       myservo.write(90);     
    }

   if(results.value == 0xFFA25D)   //mode 1
    {
     for (int i = 0; i <3; i++) 
     
     {
          myservo.write(60);
          delay(1000);
          myservo.write(120);
          delay(1000);
          myservo.write(90);
          delay(1000);
     }

     }
         
       
    
   if(results.value == 0xFF629D)   //mode 2
    {
    for (int i = 0; i <3; i++) 
    {
          myStepper.step(80);
          delay(1000);
          myservo.write(60);
          delay(500);
          myservo.write(120);
          delay(500);
          myservo.write(pos);
          delay(500);
          myStepper.step(-80);
          delay(500);
    }
          
        }
   if(results.value == 0xFFE21D)   //mode 3
    {
    for (int i = 0; i <3; i++) 
    {
          myStepper.step(-80);
          delay(1000);
          myservo.write(60);
          delay(500);
          myservo.write(120);
          delay(500);
          myservo.write(pos);
          delay(500);
          myStepper.step(80);
          delay(500);
    }
          
        }

     if(results.value == 0xFF22DD)   //mode 4
    {
    for (int i = 0; i <3; i++) 
    {
          myStepper.step(-100);
          delay(300);
          myStepper.step(200);
          delay(300);
          myStepper.step(-100);
          delay(300);
    }
          
        }
    // Add delay to prevent false readings
    delay(30); 
    //receive the next value  
    irrecv.resume(); 
}
    
}
