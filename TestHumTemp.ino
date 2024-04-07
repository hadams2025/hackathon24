#include <WEMOS_SHT3X.h>

SHT3X sht30(0x45);
int HumDL;
int TempDL;
int SuperDL = 0;

void setup() {

  Serial.begin(115200);
  Wire.begin();

}
//int SuperDL, which is the sum of the danger levels decided by each sensor arduino (a range from 0-6, where the higher the number means more danger), calculated by the OLED, distributed back to each sensor arduino, and is then evaluated by code that changes the variable in the delay() in order to manage power consumption
//GET or some other request to retrieve SuperDL

void loop() {
  sht30.get();
    Serial.println();
    Serial.println();
    if(sht30.humidity < 35){
      Serial.print("Humidity: "  );
      Serial.print(sht30.humidity);
      Serial.print(" is less than 35");
      HumDL = 0;
    }
    if(sht30.humidity > 35 && sht30.humidity < 50){
      Serial.print("Humidity: "  );
      Serial.print(sht30.humidity);
      Serial.print(" is between 35 and 50");
      HumDL = 1;
    }
    if(sht30.humidity > 50){
      Serial.print("Humidity: "  );
      Serial.print(sht30.humidity);
      Serial.print(" is greater than 50");
      HumDL = 2;
    }
    Serial.println();
    if(sht30.fTemp < 35){
      Serial.print("Temperature (F): "  );
      Serial.print(sht30.fTemp);
      Serial.print(" is less than 35");
      TempDL = 0;
    }
    if(sht30.fTemp > 35 && sht30.fTemp < 50){
      Serial.print("Temperature (F): "  );
      Serial.print(sht30.fTemp);
      Serial.print(" is between 35 and 50");
      TempDL = 1;
    }
    if(sht30.fTemp > 50){
      Serial.print("Temperature (F): "  );
      Serial.print(sht30.fTemp);
      Serial.print(" is greater than 50");
      TempDL = 2;
    }
    Serial.println();
    Serial.print("Humidity Danger Level is: " );
    Serial.print(HumDL);
    Serial.println();
    Serial.print("Temperature Danger Level is: " );
    Serial.print(TempDL);
    
    //Somehow send the OLED the values of HumDL & TempDL 

    //If(SuperDL<=2){
    //  powerDelay = 10000;
    //}
    //If(SuperDL > 2 && SuperDL < 4){
    //  powerDelay = 15000;
    //}
    //If(SuperDL >= 5){
    //  powerDelay = 20000;
    //}
    
    //delay(powerDelay);

    delay(10000);
  }