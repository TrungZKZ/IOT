#define BLYNK_TEMPLATE_ID "TMPL63pvMhp2D"
#define BLYNK_TEMPLATE_NAME "testledblynk"
#define BLYNK_AUTH_TOKEN "LFOULtG5oJjCMHcUJYIAZ2JfMvyyvc0x"
#include <Ticker.h>

Ticker timer;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Ngoc Yen 2";
char pass[] = "ngocyen2";
 
//#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

String inputString = "";         // a string to hold incoming data
bool stringComplete = false;  // whether the string is complete
int a = 0;
int b = 0;
bool on = false;
bool ledState = false;
// define the GPIO connected with Relays and switches
#define PHOTO_RESISTOR_PIN 34
#define LED_PIN 2
#define BUTTON_PIN 3
#define buton0 15
#define buton1 5
#define led0 0
#define led1 4
#define led2 16
#define led3 17
int potValue = 0;

int ledPins[] = {led0, led1, led2, led3}; // an array of pin numbers to which LEDs are attached
int pinCount = 4; // the number of pins (i.e. the length of the array)

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(buton0, INPUT_PULLUP);
    pinMode(buton1, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);  
    pinMode(led0, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
  Serial.begin(115200);
  //Blynk.begin(auth, ssid, pass);
  timer.attach(10, handleInterrupt);
  inputString.reserve(200);
  WiFi.begin(ssid, pass);
   for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(buton0), handleButtonPress, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buton1), handleButtonPress, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, CHANGE);
  delay(1000);
}
void loop()
{
  potValue = analogRead(PHOTO_RESISTOR_PIN);
  if (potValue < 2045) {
    ledState = false; // toggle ledState when the button is pressed
  }else{
    ledState = true;
  }
  Serial.println(bool(ledState));
  if (ledState == true) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
    int buttonState = digitalRead(BUTTON_PIN);
    if (stringComplete) {
      if(inputString.startsWith("a=")) {
        a = inputString.substring(2).toInt();
        Serial.print("a = ");
        Serial.println(a);
      } else if(inputString.startsWith("b=")) {
        b = inputString.substring(2).toInt();
        Serial.print("b = ");
        Serial.println(b);
      }
      // clear the string:
      inputString = "";
      stringComplete = false;
    }


    if (on == true) {
    for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
      digitalWrite(ledPins[thisPin], HIGH);
    }
    for (int thisPin = 0; thisPin < pinCount; thisPin++) {
      digitalWrite(ledPins[thisPin], LOW);
      delay(500);
      digitalWrite(ledPins[thisPin], HIGH);
    }
    for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
      digitalWrite(ledPins[thisPin], LOW);
      delay(500);
digitalWrite(ledPins[thisPin], HIGH);
    }
  }
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
void handleInterrupt() {
  Serial.println("-----------------------------------");
  Serial.println("Hello world!!!");
  for(int i=0;i<8;i++){
    Serial.print( i);
  }
  Serial.println("");
  Serial.print("a= ");
  Serial.print( a);
  Serial.print("; b= ");
  Serial.println( b);
    if (a > b) {
      Serial.println("a lon nhat");
    } else if (b > a) {
      Serial.println("b lon nhat");
    } else {
      Serial.println("a va b bang nhau");
    }
    Serial.println("giai pt ax+b=0");
    if (a != 0) {
      float x = -b / a;
      Serial.print("co nghiem x = ");
      Serial.println(x);
    } else {
      Serial.println("vo nghiem (a = 0)");
    }
}
void handleButtonPress() {
  int buttonState = digitalRead(BUTTON_PIN);
  int triggerOn = digitalRead(buton0);
  int triggerOff = digitalRead(buton1);
  if (!triggerOn) {
    digitalWrite(led0, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
  if (!triggerOff) {
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  if (buttonState == LOW) {
    if(on == false){
      on = true;
    }else{
      on= false;
    }
  }
}
