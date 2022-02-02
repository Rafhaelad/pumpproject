// include libraries
#include "DHT.h"

// pin definition for inputs and outputs
#define blinkPin 13 // pin that turns on the LED
#define trigPin 12 // pin for us_trig
#define echoPin 11 // pin for us_echo
#define motorPin 8 // pin that turns on the motor
#define dhtPin 2 // pin for humidity and temp
#define button 4 // pin watering the plant 

// define variables
bool blinkBool = true;
long duration; // for ultrasonic
int distance; // for ultrasonic

// Water level
int limit = 20;
int valve = 0;
int level = 0;

//Humidty level
int low = 3;
int normal = 10;


// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.

#define DHTTYPE DHT11 // DHT 11
DHT dht(dhtPin, DHTTYPE);


void setup()
{
  // Set up inputs and outputs
  pinMode(blinkPin, OUTPUT); // set pin 13 to an output so we can use it to turn on the LED
  pinMode(trigPin, OUTPUT); // set pin 12 to an output so we can use it to read the distance
  pinMode(echoPin, INPUT); // set pin 11 to an Input so we can use it to get the distance
  pinMode(motorPin, OUTPUT); // set pin 8 to an output so we can use it to turn on the transistor
  pinMode(dhtPin, INPUT); // set pin 2 to an input so we can use it to to read the tempratur
  pinMode(button, INPUT); // set pin  4 to an input so it can water the plant

  Serial.begin(9600); // Starts the serial communication
  Serial.println(F("DHTxx test!"));

  dht.begin(); // Starts the tempratur

  Serial.begin(9600);
}

void loop() {
  // update sensor values
  level = checkDistance();
  checkHumidity();

  
   * if (digitalRead(checkhumdity) == HIGH ) {
          Serial.println("The plant needs water");
   }

   
  // If statement is true call function water()
  if (checkhumidity < low) {
      Serial.println("The plant need water");

     
    if (distance > limit) {
      Serial.println("Tank is getting low");
      
    } else {
      
      water();
        delay(600 000); 
    }
  }

  




  // blink every loop
  blinker();
  delay(500);
}

void blinker() {
  digitalWrite(blinkPin, blinkBool);
  blinkBool = !blinkBool;
}

void water() {
  digitalWrite(blinkPin, HIGH); // turn on the LED
  digitalWrite(motorPin, HIGH); // turn on the motor
  delay(500);
  digitalWrite(blinkPin, LOW); // turn off the LED
  digitalWrite(motorPin, LOW); // turn off the motor
}

int checkDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  return distance;
}

void checkHumidity() {
  // Wait a few seconds between measurements.

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);


  Serial.print(F(" Humidity: "));
  Serial.println(h);
 
}
