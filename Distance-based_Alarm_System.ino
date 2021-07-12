// Author: Ashwin Unnithan
// Device: Distance-based Alarm System V.1.0
// Created Date: Friday April 9, 2021
// Publication Date: Sunday May 9, 2021
// Program: An ultrasonic distance-based alarm system which measures frontal distance(cm) and reacts to different distance thresholds through various alarm mechanisms  


#include "Ultrasonic.h" //Import the Ultrasonic.h library

#include "Grove_LED_Bar.h" //Import the Grove_LED_Bar.h library

#include "Wire.h" //Import the Wire.h library

#include "rgb_lcd.h" //Import the rgb_lcd.h library


rgb_lcd lcd; // Calls the library called rgb_lcd library to create an lcd object


// Defines the connection pins of the primary sensors and components of the device
const int LEDpin = 4; //LED is connected to digital port D4 (constant)

const int buzzerpin = 3; //Buzzer is connected to digital port D3 (constant)
const int Touch_sensor = 2; //Touch Sensor is connected to digital port D2 (constant)
const int bar_light = 8; // LED Bar Light is connected to digital port D8 (constant)

// Note: All pins are defined as constant variables since all connections remain unchanged during operation


long DistInCentimeters = 0; 
// Defines a long varaible called DistInCentimeters to represent distance(cm) detected by ultrasonic sensor


// Defines variables to represent the RGB value of the LCD's background
int colorR; //Defines a variable called colorR(integer) to represent the color value for red
int colorG; //Defines a variable called colorG(integer) to represent the color value for green
int colorB; //Defines a variable called colorB(integer) to represent the color value for blue



Grove_LED_Bar bar(9, bar_light, 0);
// calls the Grove_LED_Bar class to create a led bar object
// Clock pin:9, connection pin: D8, orientation: 0


int light_bar = 0;
// creates an integer variable called light_bar to represent the number of LED bars of the LED bar


char Statement; 
// Defines a variable called Statement to represent the message displayed to LCD Screen during device operation



Ultrasonic ultrasonic(7);
// calls the Ultrasonic class to create an ultrasonic object
// Ultrasonic sensor is connected to digital port: D7 


int Touch_sensor_value = 0;
// creates an integer variable called Touch_sensor_value to represent the state of the touch sensor



void setup() //Creates a void function called setup for one-time executions(located below)

{
    Serial.begin(9600); // sets the baud rate for serial data transmission to 9600 bps
    
    pinMode(Touch_sensor, INPUT);
    // Initializes the touch sensor pin as Input

    pinMode(LEDpin, OUTPUT);
    // Initializes the LED pin as Output
    
    pinMode(buzzerpin, OUTPUT);
    // Initializes the buzzer pin as Output
    
    lcd.begin(16, 2);
    // Initializes the resolution of the LCD screen (16x2 inches)
    
    program_Intro();
    // Calls the program_Intro() function to welcome user to program
    
    delay(2000);
    //program delays for 2000 milliseconds(2 seconds) before transitioning to next instruction
    
    lcd.clear();
    // clears the lcd screen
    
    
}


void loop() //creates a void function called loop to execute instructions continuously
{
    Touch_sensor_value = digitalRead(Touch_sensor);
    // reads the digital state of the touch sensor

  
    if (Touch_sensor_value == 0) // if the touch sensor is not pressed(state == 0)
    {
 
      DistInCentimeters = ultrasonic.MeasureInCentimeters(); 
      // measures the distance from the ultrasonic sensor(in cm) and assigns value to variable: DistInCentimeters
      
      DistanceSense(DistInCentimeters);
      // calls the DistanceSense function and passes DistInCentimeters as a parameter

      Statement = (char(DistInCentimeters) + " cm");
      // creates the distance statement to be displayed onto serial monitor and assigns value to variable: Statement
      
      Serial.println(Statement);
      // prints the Statement to the serial monitor in a new line
    
      lcd.setCursor(0, 0);
      // sets the lcd cursor to 0,0: column:0 and row:0
      
      lcd.print("Distance: ");  
      // Prints a segment of the distance message to the LCD's screen

      lcd.print(DistInCentimeters);  
      // Prints the DistInCentimeters(distance) to the LCD's screen

      lcd.println(" cm   ");
      // prints the last segment of the distance message to the lcd. Thereby, indicating to user that measured distance is in centimeters

      lcd.setRGB(colorR, colorG, colorB);
      // sets the RGB value of the LCD background equivalent to the values of colorR, colorG and colorB
  
    }

    else // Otherwise, if the touch sensor is pressed (state == 1)
    {
      
      End_program();
      // calls the End_program function to deactivate the device and end the program
      
    }


}



int DistanceSense(long dist) 
// defines an integer function called DistanceSense which accepts distance(dist) as a parameter
// Note: dist is defined as a long type variable

{
    LED_bar_light(dist);
    // calls the LED_bar_light function and passes dist as parameter
    
    
    if (dist > 50 and dist < 100) // if distance is greater than 50cm and less than 100 cm
    
    { 
      digitalWrite(LEDpin, HIGH); // digitally writes HIGH to the LEDpin

      color_change(0, 204, 0); // calls the color_change function to change LCD background color to green
      
      lcd.setCursor(0, 1); // moves the LCD cursor to the next row: column:0 and row:1
      
      lcd.print("Far          ");
      // prints a category message(based on distance of object) to LCD screen
      // During this instance, program tells user the object is far
   
    }

    else if(dist <= 20)  // if distance is less than or equal to 20cm
    {
      tone(buzzerpin, 1000, 500); //calls the tone function to play a tone(frequency: 1000hz and duration: 500 milliseconds) on the buzzer
      
      color_change(255, 0, 0); // calls the color_change function to change LCD background color to red
      
      lcd.setCursor(0, 1); // moves the LCD cursor to the next row: column:0 and row:1
      
      lcd.print("Very Close        ");
      // prints a category message(based on distance of object) to LCD screen
      // During this instance, program tells user the object is very close

    }


    else if (dist > 20 and dist < 50) // if distance is greater than 20cm and less than 50cm
    {
      color_change(255, 255, 0); // calls the color_change function to change LCD background color to yellow
      
      tone(buzzerpin, 100, 100); //calls the tone function to play a tone(frequency: 100hz and duration: 100 milliseconds) on the buzzer
      
      lcd.setCursor(0, 1); // moves the LCD cursor to the next row: column:0 and row:1
      
      lcd.print("Close      ");
      // prints a category message(based on distance of object) to LCD screen
      // During this instance, program tells user the object is close
      
    }

    
    else //Otherwise, if distance is greater than 100cm
    {
      digitalWrite(LEDpin, LOW); // digitally writes LOW to the LEDpin
      
      color_change(0, 128, 255); // calls the color_change function to change LCD background color to blue
      
      lcd.setCursor(0, 1); // moves the LCD cursor to the next row: column:0 and row:1
      
      lcd.print("Very Far      ");
      // prints a category message(based on distance of object) to LCD screen
      // During this instance, program tells user the object is very far
      
    }
    
    delay(50); //program waits 50 milliseconds before transitioning to next instruction
   
    
}



float LED_bar_light(long distance) // defines a float function called LED_bar_light which accepts distance as a parameter(long variable)
{
  // Essientially, this function is used to display the changes in distance to LED bar
  
  light_bar = DistInCentimeters/5; // defines a variable called light_bar to store how many bars will activate based on distance 
  
  bar.setLevel(light_bar); // sets the level of the bar light equal to light_bar(dependant on distance)
}



int color_change(int red, int green, int blue) //defines an integer function which accepts integer parameters such as red, green and blue
{
  // Essientially, this function is used to change the color of the LCD background 
  
  colorR = red; // assigns the red paramter to variable: colorR
  
  colorG = green; // assigns the red paramter to variable: colorG
  
  colorB = blue; // assigns the red paramter to variable: colorB
  
}


void program_Intro() //Defines a void function called program_Intro to introduce user to the device
{
  lcd.clear(); // clears the LCD screen

  lcd.print("RAM Industries");
  // prints company name to LCD screen

  lcd.setCursor(0,1);
  // moves the LCD cursor to the next row: column:0 and row:1

  lcd.print("DAS");
  // prints the name of the device(Distance-based Alarm System) to LCD screen
  
}


void End_program() // Defines a void function called End_program() to deactivate the device and end program 
{
  lcd.clear(); // clears the LCD screen
  
  lcd.print("DAS"); 
  // prints the name of the device(Distance-based Alarm System) to LCD screen
  
  lcd.setCursor(0,1); 
  //repositions cursor at column: 0 and row: 1
  
  lcd.print("Deactivated"); 
  // prints "Deactivated" to the LCD screen

  delay(1200); 
  //program waits 1200 milliseconds before transitioning to next instruction

  lcd.clear(); // clears the LCD screen

  lcd.print("RAM Industries");
  // prints company name to LCD screen 
  
  exit(0);
  // calls exit(0) function to end the program

} 
