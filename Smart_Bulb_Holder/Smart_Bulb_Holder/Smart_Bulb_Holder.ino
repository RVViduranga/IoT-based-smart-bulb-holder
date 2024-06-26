

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPL6oYNGcP6f"
#define BLYNK_TEMPLATE_NAME "Smart Bulb"
#define BLYNK_AUTH_TOKEN "nebnTYeydNF-Z6RsLYC8vbrdfH2QguzT"

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Xiaomi 11 Lite 5G NE";
char pass[] = "Arhinius 123";

bool fetch_blynk_state = false;

#include <ESP8266WiFi.h>        
#include <BlynkSimpleEsp8266.h>

// define the GPIO connected with Relays and switches
#define RelayPin1 2  //GPIO-0

//Change the virtual pins according the rooms
#define VPIN_BUTTON_1    V1

// Relay State
bool toggleState_1 = LOW; //remember the toggle state for relay

char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

BLYNK_CONNECTED() {
  // Request the latest state from the server
  if (fetch_blynk_state){
    Blynk.syncVirtual(VPIN_BUTTON_1);
  }
  else{
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  }
}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, !toggleState_1);
}



void setup()
{
  Serial.begin(9600);

  

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, !toggleState_1);

  WiFi.begin(ssid, pass);
  Blynk.config(auth);
  delay(1000);
  
  if (!fetch_blynk_state){
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  }
  delay(5000);
  pinMode(RelayPin1, OUTPUT);
}

void loop()
{  
  Blynk.run();
  timer.run();
  
  if (!Blynk.connected()) {
    toggleState_1 = LOW;
    digitalWrite(RelayPin1, !toggleState_1);
  }
}
