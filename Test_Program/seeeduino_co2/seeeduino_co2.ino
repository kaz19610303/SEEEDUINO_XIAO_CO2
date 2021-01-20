/*
  Library for the Sensirion SGP30 Indoor Air Quality Sensor
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 28th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  SGP30 Datasheet: https://cdn.sparkfun.com/assets/c/0/a/2/e/Sensirion_Gas_Sensors_SGP30_Datasheet.pdf

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14813

  This example reads the sensors calculated CO2 and TVOC values
*/

#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 6
#define LED6 7
#define LED7 8
#define LED8 9
#define LED9 10

SGP30 mySensor; //create an object of the SGP30 class

void led_all_on(void);
void led_all_off(void);
void display_co2(uint16_t);

void led_all_on(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);
  digitalWrite(LED9, LOW);
}
void led_all_off(){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, HIGH);
  digitalWrite(LED8, HIGH);
  digitalWrite(LED9, HIGH);
}


void display_co2(uint16_t value){
  value=1800;
  led_all_off();
  if(value < 500){
    // nothing
  } else if(value < 600){
    digitalWrite(LED1, LOW);
  } else if(value < 700){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  } else if(value < 800){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } else if(value < 1000){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
  } else if(value < 1150){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
  } else if(value < 1300){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
  } else if(value < 1500){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
  } else if(value < 2000){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, LOW);
  } else {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, LOW);
    digitalWrite(LED9, LOW);
  }
}

void setup() {
  Serial.begin(115200);
//  while (!Serial) { delay(10); } // Wait for serial console to open!
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  led_all_off();
  
  Wire.begin();
  //Initialize sensor

  if (mySensor.begin() == false) {
    for(int i=0; i<10 ; i++){
      led_all_on();
      delay(200);
      led_all_off();
      delay(200);
    }
    while (1);
  }
    for(int i=0; i<3 ; i++){
      led_all_on();
      delay(200);
      led_all_off();
      delay(200);
    }

  //Initializes sensor for air quality readings
  //measureAirQuality should be called in one second increments after a call to initAirQuality
  mySensor.initAirQuality();
}

void loop() {
  //First fifteen readings will be
  //CO2: 400 ppm  TVOC: 0 ppb
  delay(800); //Wait 2 second
  //measure CO2 and TVOC levels
  mySensor.measureAirQuality();
  display_co2(mySensor.CO2);
  Serial.print("CO2: ");
  Serial.println(mySensor.CO2);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                        // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}
