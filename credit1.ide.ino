const int motionSensorPin = 2;
const int trigPin = 13;  // Connect to the trigger pin of the ultrasonic sensor
const int echoPin = 12;  // Connect to the echo pin of the ultrasonic sensor
const int ledPin = 13;
volatile int motionValue = LOW;
int distance = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motionSensorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check motion sensor in every loop iteration
  motionValue = digitalRead(motionSensorPin);

  // Read distance from ultrasonic sensor in every loop iteration
  distance = getUltrasonicDistance();

  // Update LED based on both motion and distance values
  digitalWrite(ledPin, (motionValue == HIGH || distance < 20) ? HIGH : LOW);

  // Print sensor values to Serial Monitor
  Serial.print("Motion Sensor: ");
  Serial.println(motionValue == HIGH ? "Motion Detected" : "No Motion");

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Add a delay to avoid flooding the Serial Monitor with messages
  delay(500);
}

int getUltrasonicDistance() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo duration
  unsigned long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  int distance = duration / 58;

  return distance;
}
