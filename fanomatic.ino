/*
Name: Rana Balabel
Program Description: Creating a program and circuit to measure the temperature of the environment using a temperature sensor. When the switch is turned ON, 
the LED turns on, the temperature sensor measures the temperature and prints it, the servo motor goes to a position according to the temperature, and the motor speed (fan strength) changes depending on the temperature.
When the switch is turned off, the sensor no longer works, the servo goes back to 0 degrees, the LED turns off, and the fan turns off. 

Latest date of modification: September 2022
*/
#include <Servo.h>                            //Import the servo.h library for servo use
Servo myservo;                                //Create an object, of the type "Servo", to control our Servo motor
int temperaturePin = 0;                       //Declaring a variable for the temperature sensor using pin A0
float temperatureCel, temperatureFehr;        //Declaring two float variables for the temperature in degrees Celsius and the temperature in degrees Fehrenheit 
int switchPin = 2;                            //Declaring a variable for the switch in Pin 2
int ledPin = 3;                               //Declaring a variable for the LED in Pin 3
int motorPin = 6;                             //Declaring a variable for motor in Pin 6 
int motorSpeed = 0;                           //Declaring a variable to hold the value of the speed of the motor 
int val;                                      //Declaring a variable for the value of the angle of position to be used with the servo motor

void setup() {
 Serial.begin(9600);                          //Initializing the serial connection at 9600 bits per second 
 myservo.attach(7);                           //Initializes and attaches the servo on pin 7 to the servo object
 pinMode(switchPin, INPUT);                   //Configuring the switch's 2nd digital pin to INPUT
 pinMode(ledPin, OUTPUT);                     //Configuring the LED's 3rd digital pin to OUTPUT
 pinMode(motorPin, OUTPUT);                   //Configuring the motor's 6th digital pin to OUTPUT
}

void loop() {
  if (digitalRead(switchPin) == HIGH)                 //If the switch at pin 2 is pressed (reads HIGH)
  {
  digitalWrite(ledPin, 1);                            //Turn ON the LED at Pin 3
  float temperatureCel = getVoltage(temperaturePin);  //Declaring a float variable to hold the value of the temperature through the getVoltage float method. 
  temperatureCel = (temperatureCel - 0.5) *100;       //Deduct the 0.5 degrees offset from the voltage, then multiply it by 100 to get the temperature value 
  float temperatureFehr = (temperatureCel*1.8) + 32;  //Convert the temperature value in degrees Celsius to degrees Fehrenheit 
  Serial.print("Celsius: ");                          //Prompt to print the temperature in Celsius
  Serial.println(temperatureCel);                     //Prints the value of the variable temperatureCel
  Serial.print("Fehrenheit: ");                       //Prompt to print the temperature in Fehrenheit
  Serial.println(temperatureFehr);                    //Prints the value of the variable temperatureFehr
   if (temperatureCel < 19)                           //If the temperature is less than or equal to 18 degrees 
    {
     val=0;                                           //Set the value of the servo motor's angle to 0 degrees (all the way to the left)
     motorSpeed=0;                                    //Set the value of the motor speed to be 0 
    }
    else if (temperatureCel >=18 && temperatureCel <=24.6)  //If the above condition is false, check to see if the temperature value is between 18 and 25 degrees 
    {
      val = map(temperatureCel, 18,25,0,180);               //If it is, set the value of the servo position to be mapped from 18 to 25 degrees celsius to 0 to 180 degrees 
      motorSpeed = map(temperatureCel, 18,25,0,255);        //Set the value of the motor speed to be mapped from 18 to 25 degrees celsius to 0 to 255 analogue signals, used to control the motor's speed
    }
     else                                                   //If all the above conditions are false, and the temperature value exceeds 25 degrees 
    {
     val = 180;                                             //Set the value of the servo motor's angle to be 180 degrees (all the way to the right)
     motorSpeed = 255;                                      //Set the value of the motor speed to be 100%
    }
  }
  else if (digitalRead(switchPin) == LOW)                   //If the switch at pin 2 is NOT pressed (reads LOW)
  {
    val =0;                                                 //Set the value of the servo motor's angle to 0 degrees (all the way to the left)
    motorSpeed = 0;                                         //Set the value of the motor speed to be 0
    digitalWrite(ledPin, 0);                                //Turn OFF the LED at Pin 3
  }
  myservo.write(val);                                       //After going through all the if statements and setting the value of the angle position accordingly, write it to the servo motor 
  analogWrite(motorPin, motorSpeed);                        //After determining what speed the motor should be at through the if statements, write it to the motor 
  delay(1000);                                              //Delay for 1 second 
}

float getVoltage(int pin) {                       //Creating a float method called getVoltage. It receives the value of the temperature pin from line 16 and uses it in this method 
  return(analogRead(pin) * .004882814);           /*Reads the value of the temperature from the temperature sensor. The value received gets multiplied by 5 volts / 1023 (analog reading). 
  This determines the voltage increase per temperature step. This value is returned to the main function, where it is then decreased by 0.5 and multiplied by 100 to acquire a degrees value.*/
}
