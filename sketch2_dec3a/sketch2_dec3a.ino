//Depends on Adafruit DHT Arduino library
//https://github.com/adafruit/DHT-sensor-library

//Depends on Adafruit NeoPixel library
//https://github.com/adafruit/Adafruit_NeoPixel

//Depends on Adafruit Adafruit Unified Sensor library
//https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"    // for DHT shield (humidity/temperature sensors)
#include <Adafruit_NeoPixel.h>    // for LED shield

#define DHTPIN 2     // what pin we're connected to DHT shield
#define LED_PIN   4   // what pin we're connected to LED shield

#define DHTTYPE DHT11   // DHT 11
#define LED_NUM 1   // LED numbers

DHT dht(DHTPIN, DHTTYPE);
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

void start (float humidity, float temperature) {    // start the work with the DHT results

  for (int j = 0; j <= 10; j++) {
    led_set(j, 0, 0);   // red LED brightens up (in half second)
    delay(50);
  }
  for (int j = 0; j <= 10; j++) {
    led_set(0, j, 0);   // green LED brightens up (in half second)
    delay(50);
  }
  for (int j = 0; j <= 10; j++) {
    led_set(0, 0, j);   // blue LED brightens up (in half second)
    delay(50);
  }
  for (int j = 0; j <= 10; j++) {
    led_set(j, j, 0);   // red + green = yellow LED brightens up (in half second)
    delay(50);
  }
  for (int j = 0; j <= 10; j++) {
    led_set(j, 0, j);   // red + blue = purple LED brightens up (in half second)
    delay(50);
  }
  for (int j = 0; j <= 10; j++) {
    led_set(0, j, j);   // green + blue = aqua LED brightens up (in half second)
    delay(50);
  }
  for (int j = 0; j <= 10; j++) {
    led_set(j, j, j);   // red + green + blue = white LED brightens up (in half second)
    delay(50);
  }

  led_set(0, 0, 0);   // all LED turns off (wait half second)
  delay(500);

  if (temperature < 0) {
    String message = "it is snowy weather with a temperature of " + String(temperature, 2) + " degrees celsius, and " + String(humidity, 2) + " percentage humidity.";
    morsecode(10, 10, 10, message);   // white RGB LED setting and the message sent
  }
  else {
    if (humidity > 70) {
      String message = "it is humid weather with a temperature of " + String(temperature, 2)  + " degrees celsius, and " + String(humidity, 2) + " percentage humidity.";
      morsecode(0, 10, 10, message);
    }  
    else {
      if (temperature < 20) {
        String message = "it is cold weather with a temperature of " + String(temperature, 2)  + " degrees celsius, and " + String(humidity, 2) + " percentage humidity.";
        morsecode(0, 10, 0, message);
      }
      else if (temperature > 30) {
        String message = "it is hot weather with a temperature of " + String(temperature, 2)  + " degrees celsius, and " + String(humidity, 2) + " percentage humidity.";
        morsecode(10, 0, 0, message);
      }
      else {
        String message = "it is warm weather with a temperature of " + String(temperature, 2)  + " degrees celsius, and " + String(humidity, 2) + " percentage humidity.";
        morsecode(10, 10, 0, message);
      }
    }  
  }
}

void led_set(uint8 R, uint8 G, uint8 B) {   // the LED operate funkcion
  for (int i = 0; i < LED_NUM; i++) {
    leds.setPixelColor(i, leds.Color(R, G, B));
    leds.show();
  }
}

void morseunit (uint8 R, uint8 G, uint8 B, uint8 mark, int speed) {   // morse code units setting
  if (mark == 0) {
    led_set(0, 0, 0);   //short gap
    delay(speed);
  }
  else if (mark == 1) {
    led_set(R, G, B);   //short mark
    delay(speed);
  }
  else if (mark == 3) {
    led_set(R, G, B);   //long mark
    delay(speed);
    delay(speed);
    delay(speed);
  }
  else if (mark == 4) {
    led_set(0, 0, 0);   //medium gap (between their letters)
    delay(speed);
    delay(speed);
    delay(speed);
  }
  else if (mark == 7) {
    led_set(0, 0, 0);   //long gap (space or sentence space)
    delay(speed);   //1
    delay(speed);   //2
    delay(speed);   //3
    delay(speed);   //4
    delay(speed);   //5
    delay(speed);   //6
    delay(speed);   //7
  }
}

void morsecode(uint8 R, uint8 G, uint8 B, String message) {   // morse ABC and the message disassambly of their letters
  int speed = 250;    // for Ham license needed 2 mark per second and maximum 10 mark per sec is used in radio (easy to understand)
  Serial.print(message);
  Serial.println(message.length ());
  for (int m = 0; m <= message.length () - 1; m++) {   
    if (message[m] == 'a') {
      Serial.print("a");    // tester text
      morseunit(R, G, B, 1, speed);   // short mark
      morseunit(R, G, B, 0, speed);   // gap after the mark 
      morseunit(R, G, B, 3, speed);   // long mark
    }
    else if (message[m] == 'b') {
      Serial.print("b");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'c') {
      Serial.print("c");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'd') {
      Serial.print("d");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'e') {
      Serial.print("e");
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'f') {
      Serial.print("f");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'g') {
      Serial.print("g");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'h') {
      Serial.print("h");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'i') {
      Serial.print("i");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'j') {
      Serial.print("j");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }    
    else if (message[m] == 'k') {
      Serial.print("k");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }    
    else if (message[m] == 'l') {
      Serial.print("l");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }    
    else if (message[m] == 'm') {
      Serial.print("m");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }    
    else if (message[m] == 'n') {
      Serial.print("n");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'o') {
      Serial.print("o");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == 'p') {
      Serial.print("p");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 'q') {
      Serial.print("q");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == 'r') {
      Serial.print("r");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 's') {
      Serial.print("s");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == 't') {
      Serial.print("t");
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == 'u') {
      Serial.print("u");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == 'v') {
      Serial.print("v");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == 'w') {
      Serial.print("w");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == 'x') {
      Serial.print("x");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == 'y') {
      Serial.print("y");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == 'z') {
      Serial.print("z");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == '0') {
      Serial.print("0");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == '1') {
      Serial.print("1");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == '2') {
      Serial.print("2");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == '3') {
      Serial.print("3");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == '4') {
      Serial.print("4");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == '5') {
      Serial.print("5");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == '6') {
      Serial.print("6");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == '7') {
      Serial.print("7");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == '8') {
      Serial.print("8");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == '9') {
      Serial.print("9");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
    }
    else if (message[m] == '.') {
      Serial.print(".");
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    else if (message[m] == ',') {
      Serial.print(",");
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 1, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
      morseunit(R, G, B, 0, speed);
      morseunit(R, G, B, 3, speed);
    }
    if (message[m] == ' ') {    // using a new if for space
      Serial.print(" ");
      morseunit(R, G, B, 7, speed);
    }
    else {    // if not space then needed the end character mark
      morseunit(R, G, B, 4, speed); 
    }
  }
  morseunit(R, G, B, 0, speed);   // end of text needed 4 more gap = 7 gap
  morseunit(R, G, B, 4, speed);

  morseunit(R, G, B, 1, speed);   // AR, end of broadcast
  morseunit(R, G, B, 0, speed);
  morseunit(R, G, B, 3, speed);
  morseunit(R, G, B, 4, speed);
  morseunit(R, G, B, 1, speed);
  morseunit(R, G, B, 0, speed);
  morseunit(R, G, B, 3, speed);
  morseunit(R, G, B, 1, speed);
  morseunit(R, G, B, 0, speed);
  morseunit(R, G, B, 1, speed);
  morseunit(R, G, B, 4, speed);
}

void setup() {
  Serial.begin(9600);   // For serial
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  dht.begin();    // This initializes the DHT library.
  leds.begin(); // This initializes the NeoPixel library.
}

void loop() {
  // Wait a 120 seconds between measurements.
  delay(120000); // 1000 = 1 sec

for (int i = 0; i < 10; i++){
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
    delay(500);                      // Wait half a second
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    delay(500);                      // Wait for half seconds
  }

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  // float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.print(humidity);
    Serial.print(temperature);
    Serial.println(" Failed to read from DHT sensor!");
    return;
  }

  start(humidity, temperature);   // starting the starting funcion 
  Serial.println("OK");
}
