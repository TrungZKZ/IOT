#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Ticker.h>
Ticker timer;
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Tại Sao Lá Cây Màu Xanh??"
#define WIFI_PASSWORD "chlorophyll"

#define USER_EMAIL "lethanhtrung05042002@gmail.com"
#define USER_PASSWORD "lethanhtrung14736928"

#define API_KEY "AIzaSyDJWcEsdUX8kbqYE2CF8X30Md9FhJH0C2A"
#define DATABASE_URL "https://test-zkz-default-rtdb.europe-west1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
String uid;
const int LDR_PIN = 34;  // Chân analog kết nối với biến trở
const int LED_PIN = 2;

#define led0 0
#define buton0 5

int lightThreshold;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
bool onled = false;
int lightValue;
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
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

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("conect Firebase : ok");
    signupOK = true;
  } else {
    Serial.printf("Firebase connection failed");
  }
  timer.attach(1, handleInterrupt);
  pinMode(buton0, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);  // Khai báo chân cảm biến ánh sáng là INPUT
  pinMode(led0, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buton0), handleButtonPress, CHANGE);
 
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 250|| sendDataPrevMillis == 0)) 
  {
     sendDataPrevMillis = millis();
  
  if (Firebase.setBool(fbdo, "/test/ledState",onled)) {
  } else {
    Serial.println("Failed to write ledState");
    Serial.println(fbdo.errorReason());
  }

    if (Firebase.getFloat(fbdo, "test/float")) {
      lightThreshold = fbdo.floatData();
      Serial.println(lightThreshold);
    } else {
      Serial.println("Không thể nhận được giá trị float");
    }     
        
    if (Firebase.getBool(fbdo, "/test/ledState")) {
      onled = fbdo.boolData();
      Serial.println(onled);
    } else {
      Serial.println("Không thể nhận được giá trị ledState");
    }
  delay(250);
}}

void handleButtonPress() {
  int triggerOn = digitalRead(buton0);
  if (!triggerOn) {if(onled == true){onled = false;}else{onled = true;}}}

void handleInterrupt() {
    lightValue = analogRead(LDR_PIN);  // Đọc giá trị từ cảm biến ánh sáng
    if (lightValue >= lightThreshold) {
      digitalWrite(LED_PIN, HIGH);  // Bật đèn LED
    } else {
      digitalWrite(LED_PIN, LOW);  // Tắt đèn LED
    }

    if (onled == true) {
      digitalWrite(led0, LOW);  // Bật đèn LED
    } else {
      digitalWrite(led0, HIGH);  // Tắt đèn LED
    }
}
