
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int timeon = 30;
int timeoff = 30;
int relayctrlpins[] = {2,3,4,5};
int relaytogglepins[] = {9,8,7,6};
int numrelay = 4;
unsigned long counter[4];
int numspaces = 0;


void displayupdate() {

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("R1: "); display.println(counter[0],DEC);
  display.print("R2: "); display.println(counter[1],DEC);
  display.print("R3: "); display.println(counter[2],DEC);
  display.print("R4: "); display.println(counter[3],DEC);
  display.setCursor(92, 0);display.print("time");
  display.setCursor(96, 10);display.print("on:");display.print(timeon, DEC);
  display.setCursor(90, 20);display.print("off:");display.print(timeoff, DEC);
  display.display();
  
}

void setup() {
  for (int thisPin = 0; thisPin < numrelay; thisPin++) {
    pinMode(relayctrlpins[thisPin], OUTPUT);
    digitalWrite(relayctrlpins[thisPin], LOW);
    pinMode(relaytogglepins[thisPin], INPUT);
    digitalWrite(relaytogglepins[thisPin], HIGH);
    counter[thisPin]=0;
  }

  //map 1-60s to 0-1023 ADC bits... time = (-59/1023)*analog + 60
  timeon = -(analogRead(A0)*59.0/1023)+60;
  timeoff = -(analogRead(A1)*59.0/1023)+60;
  
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("hi Justin");
  display.display();
  delay(500);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("relay");
  display.println("cycler");
  display.display();
  delay(2000);

  displayupdate();

}

void loop() {

  for (int thisPin = 0; thisPin < numrelay; thisPin++) {
    if (digitalRead(relaytogglepins[thisPin])>0){
      digitalWrite(relayctrlpins[thisPin], HIGH);
      delay(timeon*1000);
      digitalWrite(relayctrlpins[thisPin], LOW);
      delay(timeoff*1000);
      counter[thisPin]++;
    }
    timeon = -(analogRead(A0)*59.0/1023)+60;
    timeoff = -(analogRead(A1)*59.0/1023)+60;
    displayupdate();
  }

}
