// Pin definitions
const int BUTTON_PIN = 4;
const int LED_PIN = 2;

// Debounce parameters
const unsigned long debounce_delay = 50;  // milliseconds

// Button state variables
volatile bool buttonState = HIGH;             // Current button state
volatile bool lastButtonState = HIGH;         // Previous button state
volatile unsigned long lastDebounceTime = 0;  // Last time button state changed
volatile bool ledState = LOW;                 // LED state

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);  // Initialize LED to OFF
}

void loop() {
  // Non-blocking button debounce routine
  checkButton();
}

void checkButton() {
  // Read the current button state
  bool reading = digitalRead(BUTTON_PIN);

  // If the button state has changed
  if (reading != lastButtonState) {
    // Reset the debounce timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounce_delay) {
    // If the button state has actually changed
    if (reading != buttonState) {
      buttonState = reading;
      doSomething();
    }
  }

  // Save the current reading for the next loop
  lastButtonState = reading;
}

void doSomething(){
  // Only act on Rising edge
  if (buttonState == LOW) {
    Serial.println("Button pressed!");
     // Toggle LED state
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.println(ledState ? "LED ON" : "LED OFF");
  } else {
    Serial.println("Button released!");
    // Put anything here to execute at falling edge
  }
}
