// Jeff Heppert

// Note frequency list: http://www.phy.mtu.edu/~suits/notefreqs.html

int sensorValue;
int knobValue;
int sensorLow = 1023;
int sensorHigh = 0;
int pitch = 0;
int delayValue = 0;
int buttonState = 0;
int audioMode = 0;

int notes[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25, 587.33, 659.25, 698.46, 783.99, 880.00, 987.77, 1046.50};
char* noteLetters[] = {"C", "D", "E", "F", "G", "A", "B"};

const int ledPin = 13;
const int buttonPin = 4;
const int speakerPin = 2;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Turn on LED and calibrate light sensor:
  digitalWrite(ledPin, HIGH);
  while(millis() < 5000) {
    sensorValue = analogRead(A0);
    if(sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
  digitalWrite(ledPin, LOW);

}

void loop() {
  sensorValue = analogRead(A0);
  knobValue = analogRead(A1);
  buttonState = digitalRead(buttonPin);
  

  // Make sure you can't go past the high or low calibration:
  if (sensorValue < sensorLow) {
    sensorValue = sensorLow;
  } else if (sensorValue > sensorHigh) {
    sensorValue = sensorHigh;
  }


  // detect button press to change audio mode
  if (buttonState == HIGH) {
    if(audioMode == 2) {
      audioMode = 0;
    } else {
      audioMode++;
    }
    Serial.println("BUTTON PRESSED");
    delay(500);
  }

  
  if (audioMode == 0) {
    // Standard analog theremin
    
    int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
    tone(2, pitch, 20);
    delay(10);
    
  } else if(audioMode == 1) {
    // pitch is controlled by light sensor
    
    pitch = map(sensorValue, sensorLow, sensorHigh, 0, 14);  
    delayValue = map(knobValue, 0, 1023, 0, 500);

    // Print to the console:
    Serial.print("Sensor value: ");
    Serial.print(sensorValue);
    Serial.print("\tKnob value: ");
    Serial.print(knobValue);
    Serial.print("\tDelay: ");
    Serial.print(delayValue);
    Serial.print("ms");
    Serial.print("\tNote: ");
    Serial.println(noteLetters[pitch%7]);

     // Output the tone:
    tone(speakerPin, notes[pitch], 50);
    delay(delayValue);
    
  } else {
    // pitch is controlled by potentiometer
    
    pitch = map(knobValue, 0, 1023, 0, 14);  
    delayValue = map(sensorValue, sensorLow, sensorHigh, 0, 200);

    // Print to the console:
    Serial.print("Sensor value: ");
    Serial.print(sensorValue);
    Serial.print("\tKnob value: ");
    Serial.print(knobValue);
    Serial.print("\tDelay: ");
    Serial.print(delayValue);
    Serial.print("ms");
    Serial.print("\tNote: ");
    Serial.println(noteLetters[pitch%7]);

     // Output the tone:
    tone(speakerPin, notes[pitch], 50);
    delay(delayValue);
    
  }
  

  

 
  

}
