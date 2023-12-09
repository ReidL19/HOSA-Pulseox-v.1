const int ledPin = 13;  // Connect an LED to pin 13

void setup() {
  pinMode(ledPin, OUTPUT);  // Initialize the LED pin as an output
}

void loop() {
  digitalWrite(ledPin, HIGH); // Turn on the LED
  delay(500);                // Wait for 1 second (1000 milliseconds)
  digitalWrite(ledPin, LOW);  // Turn off the LED
  delay(500);                // Wait for 1 second

}