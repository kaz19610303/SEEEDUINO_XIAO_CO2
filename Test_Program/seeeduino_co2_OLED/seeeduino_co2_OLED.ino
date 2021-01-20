/*
  Library for the Sensirion SGP30 Indoor Air Quality Sensor
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 28th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  SGP30 Datasheet: 
  https://cdn.sparkfun.com/assets/c/0/a/2/e/Sensirion_Gas_Sensors_SGP30_Datasheet.pdf

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14813

  This example reads the sensors calculated CO2 and TVOC values
*/

#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: https://github.com/sparkfun/SparkFun_SGP30_Arduino_Library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SGP30 mySensor; //create an object of the SGP30 class

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(2);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(15,30);             // Start at top-left corner
  display.println(F("Next Step"));
  display.display();
}

void co2_data_display(uint16_t co2,uint16_t tvoc) {
  char disp_co2[10];
  char disp_tvoc[10];

  sprintf(disp_co2,"%4d",co2);
  sprintf(disp_tvoc,"%4d",tvoc);

  display.clearDisplay();
  display.setCursor(35,0);             // Start at top-left corner
  display.setTextSize(1);                      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.println(F("CO2 Monitor"));

  display.setCursor(0,28);             // Start at top-left corner
  display.setTextSize(1);             // Draw 2X-scale text
  display.println(F("CO2")); 
  display.setTextSize(3);             // Draw 2X-scale text
  display.setCursor(35,15);
  display.print(disp_co2);
  display.setTextSize(1);             // Draw 2X-scale text
  display.setCursor(110,28);
  display.print("ppm");
  display.setCursor(0,53);             // Start at top-left corner
  display.println(F("TVOC"));
  display.setTextSize(3);             // Draw 2X-scale text
  display.setCursor(35,40);
  display.print(disp_tvoc);
  display.setTextSize(1);             // Draw 2X-scale text
  display.setCursor(110,53);
  display.print("ppb");
  display.display();
}  


void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin();

  if (mySensor.begin() == false) {
    for(int i=0; i<10 ; i++){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(200);                        // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(200);
    }
    while (1);
  }
  delay(2000);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.println("SSD1306 allocation.");

  for(int i=0; i<3 ; i++){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                        // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200);
  }
  //Initializes sensor for air quality readings
  //measureAirQuality should be called in one second increments after a call to initAirQuality
  mySensor.initAirQuality();
  display.clearDisplay();
  testdrawstyles();    // Draw 'stylized' characters
}

void loop() {
  uint16_t co2_data;
  uint16_t tvoc_data;

  //First fifteen readings will be
  //CO2: 400 ppm  TVOC: 0 ppb
  delay(800); //Wait 2 second
  //measure CO2 and TVOC levels
  mySensor.measureAirQuality();
  co2_data  = mySensor.CO2;
  tvoc_data = mySensor.TVOC;

  co2_data_display(co2_data,tvoc_data);

  Serial.print("CO2: ");
  Serial.println(mySensor.CO2);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                        // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}
