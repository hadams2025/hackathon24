/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/
//init for wifi client
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "ESPap_smort"
#define STAPSK "thereisnospoon"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "192.168.4.1";//"djxmmx.net";
const uint16_t port = 80;
int lastRequestExecution = 0;
WiFiClient client;

//end init for wifi client
//start init for button
const int buttonPin = D3;
const int ledPin = BUILTIN_LED;
int ledState = HIGH;         // the current state of the output pin

int buttonState = 0;
int first = false;
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastPressTime = 0;
unsigned long currentPressTime = 0;
unsigned long lastWifiConnection = 0;
unsigned long currentTime = 0;
//end init for button

void setup() {
  Serial.begin(115200);
  //start setup for wifi client
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //end setup for wifi client
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
  //end setup2 for wifi client
  //start setup for button
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial state, LED off
  digitalWrite(ledPin, buttonState);
  //end setup for button
  
}

void loop() {
  //start loop for wifi client
  static bool wait = false;

  if (!client.connected()) {
    Serial.println("Connection is disconnected");
    client.stop();

    // reconnect to TCP server (Arduino #2)
    if (client.connect("192.168.4.2", 4080))
      Serial.println("Reconnected to TCP server");
    else
      Serial.println("Failed to reconnect to TCP server");
  }
  lastWifiConnection = millis();

  // This will send a string to the server
  /*Serial.println("sending data to server");
  if (client.connected()) { client.println("hello from ESP8266"); }*/
  //start button timing to send requests to server
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        lastPressTime = millis();
        first = true;
        while(millis()-lastPressTime<300){
          int reading = digitalRead(buttonPin);
          if (reading != buttonState) {
            buttonState = reading;
            if(buttonState==HIGH){
                ledState = !ledState;
                currentPressTime = millis();
                first = false;
                Serial.println("double click");
                client.write('2');
                client.flush();
            }
          }
        }
        if(first){
          Serial.println("dingle click");
          client.write('1');
          client.flush();
          first = false;
        }
      }
    }
    /*else if(first&&(millis()-currentPressTime)>=300){
          Serial.println("dingle click");
          first = false;
    }*/
  }
  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
  //end button timing section
  
  // wait for data to be available
  /*unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }*/

/*
  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }
*/
  // Close the connection
  //Serial.println();
  //Serial.println("closing connection");
  //client.stop();
  
  /*if (wait) {
    delay(300000);  // execute once every 5 minutes, don't flood remote service
  }*/
  //wait = true;
  //end loop for wifi client
}