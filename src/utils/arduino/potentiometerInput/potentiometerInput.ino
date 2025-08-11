void setup() {
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(A3);  // Read from A3
     Serial.println(potValue);         // Send the value as text
     delay(50);
   }