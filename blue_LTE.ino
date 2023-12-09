// Pin configurations
const int buzzerPin = 8; // Connect the piezo buzzer to pin 8
const int ledPin = 13;   // Connect the LED to pin 13

void setup() {
  // Set up the buzzer and LED pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Play activation sound
  playActivationSound();

  // Blink the LED for 5 seconds
  blinkLED();
}

void loop() {
  // Nothing to do here
}

void playActivationSound() {
  // Play a simple tone for the activation sound
  tone(buzzerPin, 1000, 500); // 1000 Hz for 500 milliseconds
  delay(1000); // Pause for 1 second after the sound
  noTone(buzzerPin); // Stop the tone
}

void blinkLED() {
  // Blink the LED for 5 seconds
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH); // Turn the LED on
    delay(500); // Wait for 500 milliseconds
    digitalWrite(ledPin, LOW); // Turn the LED off
    delay(500); // Wait for 500 milliseconds
  }
}
