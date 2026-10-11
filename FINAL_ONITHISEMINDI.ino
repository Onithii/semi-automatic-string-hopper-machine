const int trigPin = 4;
const int echoPin = 5;

// Relay pin definitions
const int relayPin8 = 8;
const int relayPin9 = 9;
const int relayPin10 = 10; 

// Switch pin definition
const int switchPin = 12;

// Track state initialization
bool isInitialized = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(relayPin8, OUTPUT);
  pinMode(relayPin9, OUTPUT);
  pinMode(relayPin10, OUTPUT); // Configure Relay 10 as output

  // Configure switch pin with internal pull-up resistor
  pinMode(switchPin, INPUT_PULLUP);

  // Default initial state
  digitalWrite(relayPin8, HIGH);
  digitalWrite(relayPin9, HIGH);
  digitalWrite(relayPin10, LOW); // OFF when Relays 8 & 9 are HIGH
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10µs HIGH pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin (timeout set to 30000µs)
  long duration = pulseIn(echoPin, HIGH, 30000);

  // Calculate distance in centimeters
  float distanceCm = duration * 0.034 / 2;

  // Read switch state (LOW when pressed due to INPUT_PULLUP)
  bool switchPressed = (digitalRead(switchPin) == LOW);

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.print(" cm | Switch: ");
  Serial.print(switchPressed ? "PRESSED" : "RELEASED");
  Serial.print(" -> ");

  // 1. Timeout / Invalid reading -> Keep previous state
  if (distanceCm == 0) {
    Serial.println("Sensor error -> Holding previous state");
  }
  // 2. Sensor OVERRIDE Condition (>= 15cm)
  else if (distanceCm >= 19.0) {
    digitalWrite(relayPin8, LOW);   // Turn ON Relay 8
    digitalWrite(relayPin9, HIGH);  // Turn OFF Relay 9
    digitalWrite(relayPin10, HIGH); // Relay 8 is ON -> Keep Relay 10 ON
    isInitialized = true;
    Serial.println("OVERRIDE ACTIVE: Relay 8 ON (LOW), Relay 9 OFF (HIGH), Relay 10 ON (HIGH)");
  } 
  // 3. Sensor STOP Condition (<= 5cm) -> Relay 8 stops, Switch controls Relays 9 & 10
  else if (distanceCm <= 5.0) {
    digitalWrite(relayPin8, HIGH); // Turn OFF Relay 8 (Motor up stopped)
    
    if (switchPressed) {
      digitalWrite(relayPin9, LOW);   // Turn ON Relay 9
      digitalWrite(relayPin10, LOW);  // Relay 9 is ON -> Maintain current active state
      Serial.println("STOP ZONE: Relay 8 OFF, Relay 9 ON, Relay 10 LOW (Switch Pressed)");
    } else {
      digitalWrite(relayPin9, HIGH);  // Turn OFF Relay 9
      digitalWrite(relayPin10, LOW);  // BOTH 8 & 9 OFF -> Turn Relay 10 OFF (LOW)
      Serial.println("STOP ZONE: Relays 8 & 9 OFF -> Relay 10 OFF (LOW)");
    }
    isInitialized = true;
  }
  // 4. In-between Zone (6cm - 14cm)
  else {
    if (!isInitialized) {
      // First run on startup in 6-14cm range: Default Relay 8 ON
      digitalWrite(relayPin8, LOW);   // Turn ON Relay 8
      digitalWrite(relayPin9, HIGH);  // Turn OFF Relay 9
      digitalWrite(relayPin10, HIGH); // Relay 8 is ON -> Relay 10 ON
      isInitialized = true;
      Serial.println("Initial Boot (6-14cm): Relay 8 ON, Relay 9 OFF, Relay 10 ON");
    } 
    else {
      // Check if Relay 8 was turned ON by sensor override logic
      bool sensorRunning = (digitalRead(relayPin8) == LOW);

      if (sensorRunning) {
        // Continue override mode until distance hits <= 5cm
        digitalWrite(relayPin9, HIGH);  // Relay 9 stays OFF
        digitalWrite(relayPin10, HIGH); // Relay 8 is ON -> Relay 10 stays ON
        Serial.println("Sensor sequence running: Relay 8 ON, Relay 9 OFF, Relay 10 ON");
      } 
      else {
        // Switch control for Relays 9 & 10
        if (switchPressed) {
          digitalWrite(relayPin9, LOW);   // Turn ON Relay 9
          digitalWrite(relayPin10, HIGH);  // Relay 9 is ON -> Relay 10 active
          Serial.println("Switch control: Relay 9 ON, Relay 10 HIGH");
        } else {
          digitalWrite(relayPin9, HIGH);  // Turn OFF Relay 9
          digitalWrite(relayPin10, LOW);  // BOTH 8 & 9 OFF -> Turn Relay 10 OFF (LOW)
          Serial.println("Switch control: Relays 8 & 9 OFF -> Relay 10 OFF (LOW)");
        }
      }
    }
  }

  delay(100); // Fast response time for switch reaction
}