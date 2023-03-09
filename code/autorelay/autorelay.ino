
int timeon = 30;
int timeoff = 30;
int relayctrlpins[] = {2,3,4,5};
int relaytogglepins[] = {9,8,7,6};
int numrelay = 4;

void setup() {
  for (int thisPin = 0; thisPin < numrelay; thisPin++) {
    pinMode(relayctrlpins[thisPin], OUTPUT);
    digitalWrite(relayctrlpins[thisPin], LOW);
    pinMode(relaytogglepins[thisPin], INPUT);
    digitalWrite(relaytogglepins[thisPin], HIGH); 
  }

  //map 1-60s to 0-1023 ADC bits... time = (-59/1023)*analog + 60
  timeon = -(analogRead(A0)*59.0/1023)+60;
  timeoff = -(analogRead(A1)*59.0/1023)+60;
  
  Serial.begin(9600);
}

void loop() {

  for (int thisPin = 0; thisPin < numrelay; thisPin++) {
    if (digitalRead(relaytogglepins[thisPin])>0){
      digitalWrite(relayctrlpins[thisPin], HIGH);
      delay(timeon*1000);
      digitalWrite(relayctrlpins[thisPin], LOW);
      delay(timeoff*1000);
    }
    
    timeon = -(analogRead(A0)*59.0/1023)+60;
    timeoff = -(analogRead(A1)*59.0/1023)+60;
  }
  
  Serial.println(timeon);
  Serial.println(timeoff);
}
