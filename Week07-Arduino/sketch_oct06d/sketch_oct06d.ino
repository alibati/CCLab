
int ledPin = 13;
int ledPin2 = 12;
int buttonPin = 2;
int buttonState = 0;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH){
    digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW);
  }
 
   buttonState = digitalRead(buttonPin);

  if(buttonState == LOW){
    digitalWrite(ledPin2, HIGH);
  } else {
   digitalWrite(ledPin2, LOW);
  }
 }


