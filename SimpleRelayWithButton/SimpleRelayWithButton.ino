const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int relayPin = 7;      // the number of the relay pin

int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize the LED pin as an output:
  pinMode(relayPin, OUTPUT);
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED ON:
    digitalWrite(ledPin, HIGH);
    // turn relay ON:
    digitalWrite(relayPin, LOW);
  } 
  else {
    // turn relay OFF:
    digitalWrite(relayPin, HIGH);
    // turn LED OFF:
    digitalWrite(ledPin, LOW); 
  }
}
