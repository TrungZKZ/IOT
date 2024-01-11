#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Ticker.h>
Ticker timer;
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Tại Sao Lá Cây Màu Xanh??"
#define WIFI_PASSWORD "chlorophyll"

#define USER_EMAIL "lethanhtrung05042002@gmail.com"
#define USER_PASSWORD "666999"

#define API_KEY "AIzaSyDJWcEsdUX8kbqYE2CF8X30Md9FhJH0C2A"
#define DATABASE_URL "https://test-zkz-default-rtdb.europe-west1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
String uid;
const int doam = 34;  // Chân analog kết nối với biến trở
const int LED_PIN = 2;

#define led0 0
#define buton0 5
int Relay = 15;

int lightThreshold;
int value = 0 ;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
bool relay = false;
int lightValue;
int percent = 0 ;
void handleInterrupt() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Do am: ");
  display.print(percent);
  display.println("%");
  display.print("bom nuoc: ");
  display.println(relay);
  display.display();
}
void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Hello, world!");
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  display.setCursor(0, 0);
  Serial.print("Connecting to Wi-Fi");
  display.print("Connecting to Wi-Fi");
  display.display();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    display.print(".");
    display.display();
    delay(300);
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  Serial.println();
  Serial.print("Connected with IP: ");
  display.println("Connected with IP: ");
  display.println(WiFi.localIP());
  Serial.println(WiFi.localIP());
  display.display();
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the callback function for the long running token generation task
  config.token_status_callback = tokenStatusCallback;
  //see addons/TokenHelper.h // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;
  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);
  // Assign the callback function for the long running token generation task
config.token_status_callback = tokenStatusCallback;
//see addons/TokenHelper.h // Assign the maximum retry of token generation
config.max_token_generation_retry = 5;
// Initialize the library with the Firebase authen and config
Firebase.begin(&config, &auth);

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("conect Firebase : ok");
    display.println("conect Firebase : ok");
    display.display();
    signupOK = true;
  } else {
    Serial.printf("Firebase connection failed");
  }
  timer.attach(1, handleInterrupt);
  pinMode(buton0, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(doam, INPUT);  // Khai báo chân cảm biến độ ẩm là INPUT
  pinMode(led0, OUTPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);

 
}

void loop() {
  value = analogRead(doam);     // Ta sẽ đọc giá trị hiệu điện thế của cảm biến
  percent = map(value, 0, 4060, 100, 0);
  if(percent <= 5){
    digitalWrite(Relay, HIGH);
    relay = true;
  }else{
    digitalWrite(Relay, LOW);
    relay = false;
  }
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 250|| sendDataPrevMillis == 0)) 
  {
     sendDataPrevMillis = millis();
  
  if (Firebase.setInt(fbdo, "/DoAn/doam",percent)) {
  } else {
    Serial.println("Failed to write doam");
    Serial.println(fbdo.errorReason());
  }
  if (Firebase.setBool(fbdo, "/DoAn/relay",relay)) {
  } else {
    Serial.println("Failed to write relay");
    Serial.println(fbdo.errorReason());
  }
  delay(250);
}}


