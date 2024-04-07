/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <Wire.h>
//OLED setup
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 64
#define LOGO16_GLCD_WIDTH  48
#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
//end OLED beginning


#ifndef APSSID
#define APSSID "ESPap_smort"
//#define APSSID "HackBeta"

#define APPSK "thereisnospoon"
//#define APPSK "OleMiss2024!!"

#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

//ESP8266WebServer server(80);
WiFiServer TCPserver(4080);
//WiFiClient client;
int status = WL_IDLE_STATUS;
/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  /*WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  display.println(myIP);
  server.begin();
  Serial.println("HTTP server started");*/
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    /*Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, password);*/

    // wait 10 seconds for connection:
    //delay(10000);*/
    delay(500);
    Serial.print(".");
  }

  //Serial.begin(115200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
  //end OLED part
  TCPserver.begin();
}

void loop() {
  //server.handleClient();
  WiFiClient client = TCPserver.available();
  //Serial.print(client);
  if(client){
    char command = client.read(); //single click on button sends '1', double click sends '2'
    Serial.print(command);
  }
  /*If command == 1
   * if(displaystate == 0) displaystate = 1; (turns on the display)
   * else if (displaystate ==1) displaystate = 2; (turns on menu)
   * if(displaystate == 2) advance through menu
   */
   /* if (command ==2)
    *  if(displaystate >=2) select current menu choice, displaystate++;
    */
    /*menu would have different options for power and encryption
     * single clicking would advance through the menu
     * double clicking would select current choice
     * within encryption, could toggle on and off encryption
     * within security, can select lo medium and hi power consumption to increase/decrease polling rate of sensors
     */
  //display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.clearDisplay();
  display.setCursor(0, 0);     // Start at top-left corner
  //display.cp437(true);         // Use full 256 char 'Code Page 437' font
  //display.println("live to serve:");
  display.println(WiFi.localIP());
  //Serial.println("running");
  display.display();
  //delay(1);
}