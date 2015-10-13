
int ledPin = 13;
int ledPin2 = 12;
int buttonPin = 2;
int buttonPin2 = 4;
int buttonState = 0;
int buttonState2 = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);

  if(buttonState == HIGH){
    digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW);
  }

  if(buttonState2 == HIGH){
    digitalWrite(ledPin2, HIGH);
  } else {
   digitalWrite(ledPin2, LOW);
  }

 }


