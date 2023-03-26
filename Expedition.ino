// ----- INCLUDES ------ //
#include <Wire.h>

// Air Pressure
#include "Seeed_BMP280.h"

// Ultraviolet
#include <Adafruit_VEML6070.h>

// Temp and Humidity
#include "DHT.h"

// Air Quality
#include <SparkFunCCS811.h>
// --- END INCLUDES ---- //


// ----- ASSIGNS ----- //
// Air Pressure
BMP280 bmp280;

// Ultraviolet
Adafruit_VEML6070 uv = Adafruit_VEML6070();

// Temp and Humidity
#define DHTTYPE DHT11 
#define DHTPIN 3
DHT dht(DHTPIN, DHTTYPE);

// Air Quality
#define CCS811_ADDR 0x5B
CCS811 mySensor(CCS811_ADDR);
// --- END ASSIGNS --- //


// ----- SETUPS ----- //
void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Air Pressure
  bmp280.init();
  
  // Ultraviolet
  uv.begin(VEML6070_1_T);
  
  // Temp and Humidity
  dht.begin();
  
  // Air Quality
  mySensor.begin();
}
// --- END SETUPS --- //


// ----- LOOP ----- //
void loop() {
  // ------ VAR ------ //
  // Air Pressure
  float pressure;
  
  // Temp and Humidity
  float temp_hum_val[2] = {0};
  
  // Light
  int light_val_raw = analogRead(A6);
  int light_val = map(light_val_raw, 0, 752, 0, 10);
  // ---- END VAR ---- //
  

  // ----- PRINT ----- //
  // Light
  Serial.print("Brightness:    ");
  Serial.print(light_val);
  Serial.println(" / 10");
  
  // Air Pressure
  Serial.print("Air Pressure:  ");
  Serial.print(pressure = bmp280.getPressure());
  Serial.println(" Pa");

  Serial.print("Altitude:      ");
  Serial.print(bmp280.calcAltitude(pressure));
  Serial.println("m");
  
  // Ultraviolet
  Serial.print("UV level:      "); Serial.println(uv.readUV());
  
  // Temp and Humidity
  if (!dht.readTempAndHumidity(temp_hum_val)) {
        Serial.print("Humidity:      ");
        Serial.print(temp_hum_val[0]);
        Serial.print(" %\n");
        Serial.print("Temperature:   ");
        Serial.print(temp_hum_val[1]);
        Serial.println(" *C");
    } else {
        Serial.println("Failed to get temprature and humidity value.");
    }
  
  // Air Quality
  if (mySensor.dataAvailable()){
    mySensor.readAlgorithmResults();

    Serial.print("CO2:           ");
    Serial.print(mySensor.getCO2());
    Serial.print("\ntVOC:          ");
    Serial.print(mySensor.getTVOC());
    }

  Serial.print("\n\n--------------------------\n\n");
  // --- END PRINT --- //

  delay(300);
}
// --- END LOOP --- //
