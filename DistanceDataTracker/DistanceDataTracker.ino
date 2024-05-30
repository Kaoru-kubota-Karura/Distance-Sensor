// Constants won't change. They're used here to set pin numbers:
const int trigPin = 6;    // The number of the ultrasonic sensor's trigger pin
const int echoPin = 7;    // The number of the ultrasonic sensor's echo pin
const int buttonPin = 4;  // The number of the pushbutton pin
const int ledPin = 5;     // The number of the LED pin

// Variables will change:
int buttonState = HIGH;           // Variable for reading the pushbutton status
int lastButtonState = HIGH;       // Variable to store the previous button state
int measuringState = LOW;         // Variable to store the current measuring state
unsigned long lastDebounceTime = 0; // Last time the button state was toggled
unsigned long debounceDelay = 50;   // Debounce time in milliseconds

void setup() {
  // Initialize the pins:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Using INPUT_PULLUP to enable internal pull-up resistor

  // Initialize the LED state:
  digitalWrite(ledPin, measuringState);

  // Initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // Read the state of the pushbutton value:
  int reading = digitalRead(buttonPin);

  // If the button state has changed, reset the debounce timer:
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed after the debounce delay:
    if (reading != buttonState) {
      buttonState = reading;

      // Only toggle the measuring state if the button state is LOW (button pressed):
      if (buttonState == LOW) {
        measuringState = !measuringState;
        // Update LED:
        digitalWrite(ledPin, measuringState ? HIGH : LOW);
      }
    }
  }

  // Update the previous button state:
  lastButtonState = reading;

  if (measuringState == HIGH) {
    // Trigger the ultrasonic sensor:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure distance:
    long duration = pulseIn(echoPin, HIGH);
    float distance = (duration * 0.0343) / 2;

    // Print distance to serial monitor:
    Serial.println(distance);

    // Add your desired actions with the distance here.
  }

  delay(100); // Delay for stability
}
