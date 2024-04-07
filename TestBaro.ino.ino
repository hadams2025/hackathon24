#include <LOLIN_HP303B.h>
LOLIN_HP303B HP303BPressureSensor = LOLIN_HP303B();
int PresDL;
int SuperDL = 0;
void setup()
{
  Serial.begin(115200);
  while (!Serial);
HP303BPressureSensor.begin();
int16_t prs_mr = 2;
int16_t prs_osr = 2;
int16_t ret = HP303BPressureSensor.startMeasurePressureCont(prs_mr, prs_osr);
}

//int SuperDL, which is the sum of the danger levels decided by each sensor arduino (a range from 0-6, where the higher the number means more danger), calculated by the OLED, distributed back to each sensor arduino, and is then evaluated by code that changes the variable in the delay() in order to manage power consumption
//GET or some other request to retrieve SuperDL

void loop()
{

  unsigned char pressureCount = 32;
  int32_t pressure[pressureCount];

  unsigned char temperatureCount = 0; //Temp is already covered by the SHT30 Shield
  int32_t temperature[temperatureCount];
  int16_t ret = HP303BPressureSensor.getContResults(temperature, temperatureCount, pressure, pressureCount);

//To implement adaptation case: take the avg of the pressure measurements, pressureCount dictates the number of data points, pressureCount can be between 1-32 given the 32 buffer limit
//Depending on where the pressureAvg falls in set ranges, it would set a BaroDL (Barometric Danger Level) that is sent to the OLED to be calculated into the SuperDL
//The SuperDL would dictate what pressureCount is set to; i.e. a SuperDL <= 2 representing a lower danger level would set the pressureCount to 32 (not conserving power) while a SuperDL > 4 would indicate a more dangerous situation where the pressureCount would set lower


 for (int16_t i = 0; i < pressureCount; i++)
    {
      Serial.println();
      Serial.print("Pressure in Pascals: ");
      Serial.print(pressure[i]);
    }
//Send int PresDL to the OLED to be calculated into SuperDL
    Serial.println();
delay(10000);
}