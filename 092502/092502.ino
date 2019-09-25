int ledPin = 5; //D1
int button = 4; //D2

int buttonState = 0;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(button, INPUT);
}

void loop(){
  buttonState = digitalRead(button);

  if(buttonState == 1){
    digitalWrite(ledPin, HIGH);
    delay(200);
  }

  if(buttonState == 0){
    digitalWrite(ledPin, LOW);
    delay(10);
  }
}
