/***********************************************************
*
* File Name:   Internet_of_Things_Project       
*                      
* Description: Using a buzzer and a DHT22 sensor along with the grove LCD
*              we created a temperature and humidity alarm system.
*
* Programmers: Adam and Sadiq   
*
* Date:        06/03/2019
*
* Version:     1.0
*
***********************************************************/
#include <Wire.h>
#include <rgb_lcd.h>
#include <DHT.h>
int speakerPin = 8;

rgb_lcd lcd;
 DHT dht(A0, DHT22);

byte DEGREE_SYMBOL = 0;
 byte degree[8] = {
 0b00000,
 0b00010,
 0b00101,
 0b00010,
 0b00000,
 0b00000,
 0b00000,
 0b00000
 };

void setup(){
 Serial.begin(9600); // Initialise serial port
 lcd.begin(16, 2); // Initialise display – two lines with 16 characters respectively
 lcd.createChar(DEGREE_SYMBOL, degree); // Register the new "°" character on the display
 dht.begin(); // Initialise sensor
 }

void loop() {
 pinMode(speakerPin, OUTPUT);
 float humidity = dht.readHumidity();
 float temperature = dht.readTemperature();


if (temperature <= 15){           // Buzzes if temp. decreses below 15.
  digitalWrite(speakerPin, HIGH);
  delay(1000);
  digitalWrite(speakerPin, LOW);
}

else if (temperature >= 32){      // Buzzes if temp. increses above 32.
  digitalWrite(speakerPin, HIGH);
  delay(1000);
  digitalWrite(speakerPin, LOW);
}


if (humidity >= 65){              // Buzzes if humidity increses above 65.
  digitalWrite(speakerPin, HIGH);
  delay(1000);
  digitalWrite(speakerPin, LOW);
}


if (isnan(temperature) || isnan(humidity)) {    //If no reading is being taken displays error.
 Serial.println("Error when reading sensor");
 } else {
 const float coldest = 18;
 const float hottest = 30;
 int red = limit(255 * (temperature - coldest) / (hottest - coldest));
 // Colours from blue to violet to red
 int green = 0;
 // Red and blue the closer it gets to the ends, white in the centre
 // int green = limit(255 * sqrt(max(0, (hottest - temperature)*(temperature -
 coldest / (hottest - coldest);
 int blue = limit(255 * (hottest - temperature) / (hottest - coldest));
 lcd.setRGB(red, green, blue);

lcd.setCursor(0, 0);
 lcd.print("T:");
 lcd.print(temperature,1);
 lcd.write(DEGREE_SYMBOL);
 lcd.print("C");

 

lcd.setCursor(0, 1);
 lcd.print("H:");
 lcd.print(humidity,1);
 lcd.print("%");
 }
 delay(100);
 
if (humidity <=65){           // Prints on LCD screen to display how controlled the temp/humidity is
lcd.setCursor(9, 1);
 lcd.print("OKAY     ");
}

else if (humidity >=65){
lcd.setCursor(9, 1);
 lcd.print("WARNING");
}

if (temperature >=32){
lcd.setCursor(9, 0);
 lcd.print("TOOHOT   ");
}

else if (temperature <=15){
lcd.setCursor(9, 0);
 lcd.print("COLD    ");
}

else if ((temperature >=15) && (temperature <=32)){
lcd.setCursor(9, 0);
 lcd.print(" OKAY      ");
}
}



float limit(float color) { // Colour values need to be in the are of 0..255
 if (color < 0) {
 return 0;
 }
 else if (color > 255) {
 return 255;
 }
 else {
 return color;
 }
 }
