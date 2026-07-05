//sender
#include <WiFi.h>
#include <esp_now.h>
#include <Stepper.h>

#define IN1 13  
#define IN2 12  

#define IN3 14  
#define IN4 27  
#define TRIGGER_PIN 33 
#define ECHO_PIN    32 
#define LED_PIN     2  

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

uint8_t broadcastAddress[] = {0xdc, 0xb4, 0xd9, 0x05, 0x2c, 0xb4}; //dc:b4:d9:05:2c:b4

typedef struct struct_message {
  char message[100];
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

long duration;
int distance;
bool lastStatus = false; 

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent Success" : "Sent Fail");
}

void setup() {
  Serial.begin(115200);
  myStepper.setSpeed(15);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) return;

  esp_now_register_send_cb(OnDataSent); 
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  bool currentStatus = (distance > 10); 

  if (currentStatus != lastStatus) {
    if (currentStatus) {
      strcpy(myData.message, "START_TIMER"); // Command for Receiver
      digitalWrite(LED_PIN, HIGH);
      esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      myStepper.step(512); // Motor spins
    } else {
      strcpy(myData.message, "STOP_TIMER");  // Command for Receiver
      digitalWrite(LED_PIN, LOW);
      esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      myStepper.step(-512);
    }
    lastStatus = currentStatus;
  }
  delay(500); 
}