#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int fanPin = 9;      // Connect the PWM fan to pin 9
const int fanRunTime = 10000; // Run the fan for 10 seconds

int TIP120pin = 9; // PWM signal out to transistor on pin 9

void setup() {
  Wire.setClock(400000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);

  particleSensor.begin(Wire, I2C_SPEED_FAST);
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);

  pinMode(fanPin, OUTPUT); // Set the fan pin as an output

  pinMode(TIP120pin, OUTPUT); // Set the TIP120 transistor pin as an output

  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0, 20);
  display.print("BPM:");
  display.print(0);
  display.display();
}

void loop() {
  long irValue = particleSensor.getIR();

  if (irValue > 50000) {

    if (checkForBeat(irValue) == true) {
      long delta = millis() - lastBeat;
      lastBeat = millis();
      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20) {
        rates[rateSpot++] = (byte)beatsPerMinute;
        rateSpot %= RATE_SIZE;

        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;

        display.clearDisplay();
        display.setTextSize(3);
        display.setCursor(0, 20);
        display.print("BPM:");
        display.print(beatAvg);
        display.display();

        // Run the fan using TIP120 transistor
        analogWrite(TIP120pin, 255); // Run full speed (255) 
        delay(3000);                  // for 3 seconds
        analogWrite(TIP120pin, 100); // Run at approximately 40% speed
        delay(6000);                  // for 6 seconds
        analogWrite(TIP120pin, 0);   // Turn off the fan
      }
    }
  } else {
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(0, 20);
    display.print("BPM:");
    display.print(0);
    display.setCursor(0, 45);
    display.setTextSize(1);
    display.print("Place your finger in sensor and wait..");
    display.display();
  }

}                                                                                                 