const int soundSensorPin = A0; // Analog pin connected to the sound sensor
const int redLEDPin = 8;       // Digital pin connected to the red LED
const int greenLEDPin = 7;     // Digital pin connected to the green LED
const int threshold = 512;     // Threshold to detect a zero-crossing (can be adjusted based on your sensor)

unsigned long sampleTime = 1000; // Sample time in milliseconds
unsigned int zeroCrossings = 0;
unsigned long startTime;

void setup() {
  pinMode(redLEDPin, OUTPUT);   // Set red LED pin as output
  pinMode(greenLEDPin, OUTPUT); // Set green LED pin as output
  Serial.begin(9600);           // Start the Serial communication

  digitalWrite(greenLEDPin, HIGH); // Initially turn on the green LED
  startTime = millis();         // Initialize the start time
}

void loop() {
  int sensorValue = analogRead(soundSensorPin); // Read the analog value from the sound sensor

  // Check if we have crossed the threshold (indicating a zero-crossing)
  static int lastValue = 0;
  if ((sensorValue > threshold && lastValue <= threshold) || 
      (sensorValue < threshold && lastValue >= threshold)) {
    zeroCrossings++;
  }

  lastValue = sensorValue;

  // If the sample time has elapsed
  if (millis() - startTime >= sampleTime) {
    // Calculate frequency: (zeroCrossings / 2) because each cycle crosses the threshold twice
    float frequency = (zeroCrossings / 2.0) / (sampleTime / 1000.0);

    // Print the frequency to the Serial Monitor
    Serial.print("Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");

    // Check if the frequency is within the range
    if (frequency >= 1000 && frequency <= 2000) {
      digitalWrite(redLEDPin, HIGH);  // Turn on red LED
      digitalWrite(greenLEDPin, LOW); // Turn off green LED
    } else {
      digitalWrite(redLEDPin, LOW);   // Turn off red LED
      digitalWrite(greenLEDPin, HIGH);// Turn on green LED
    }

    // Reset counters and start time for the next sample period
    zeroCrossings = 0;
    startTime = millis();
  }
}
