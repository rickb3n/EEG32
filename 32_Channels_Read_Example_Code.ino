#include <Arduino.h>
#include <SPI.h>
#include "ADS1118.h"

// Define the chip select pins for the ADCs on HSPI
const uint8_t HSPI_CS_PINS[4] = {15, 25, 26, 27};

// Define the chip select pins for the ADCs on VSPI
const uint8_t VSPI_CS_PINS[4] = {4, 5, 21, 22};

// Create SPIClass instance for HSPI
SPIClass hspi(HSPI);

// Create SPIClass instance for VSPI
SPIClass vspi(VSPI);

// Initialize the ADS1118 objects for HSPI
ADS1118 adsHSPI[4] = {
  ADS1118(HSPI_CS_PINS[0], &hspi),
  ADS1118(HSPI_CS_PINS[1], &hspi),
  ADS1118(HSPI_CS_PINS[2], &hspi),
  ADS1118(HSPI_CS_PINS[3], &hspi)
};

// Initialize the ADS1118 objects for VSPI
ADS1118 adsVSPI[4] = {
  ADS1118(VSPI_CS_PINS[0], &vspi),
  ADS1118(VSPI_CS_PINS[1], &vspi),
  ADS1118(VSPI_CS_PINS[2], &vspi),
  ADS1118(VSPI_CS_PINS[3], &vspi)
};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);

  Serial.begin(115200);

  // Initialize HSPI interface
  hspi.begin(14, 12, 13, -1); // SCLK, MISO, MOSI, SS (-1 means no default SS pin)
  for (int i = 0; i < 4; i++) {
    adsHSPI[i].begin();
    adsHSPI[i].setSamplingRate(adsHSPI[i].RATE_860SPS); //8SPS
    adsHSPI[i].setContinuousMode(); //optional
    //adsHSPI[i].setFullScaleRange(adsHSPI[i].FSR_0256);
  }

    // Initialize VSPI interface
  vspi.begin(18, 19, 23, -1); // SCLK, MISO, MOSI, SS (-1 means no default SS pin)
  for (int i = 0; i < 4; i++) {
    adsVSPI[i].begin();
    adsVSPI[i].setSamplingRate(adsVSPI[i].RATE_860SPS); //8SPS
    adsVSPI[i].setContinuousMode(); //optional
    //adsVSPI[i].setFullScaleRange(adsVSPI[i].FSR_0256);
  }
}

void loop() {
  // Read and print values from HSPI ADCs
  for (int i = 0; i < 4; i++) {
    //uint16_t adcValue = adsHSPI[i].getADCValue(adsHSPI[i].AIN_0); // Example reading from AIN_0
    double millivolts = adsHSPI[i].getMilliVolts(adsHSPI[i].AIN_0);
    Serial.print(millivolts); Serial.print(",");
    millivolts = adsHSPI[i].getMilliVolts(adsHSPI[i].AIN_1);
    Serial.print(millivolts); Serial.print(",");
    millivolts = adsHSPI[i].getMilliVolts(adsHSPI[i].AIN_2);
    Serial.print(millivolts); Serial.print(",");
    millivolts = adsHSPI[i].getMilliVolts(adsHSPI[i].AIN_3);
    Serial.print(millivolts); /*if (i!=3) */ Serial.print(",");
  }

    // Read and print values from VSPI ADCs
  for (int i = 0; i < 4; i++) {
    double millivolts = adsVSPI[i].getMilliVolts(adsVSPI[i].AIN_0);
    Serial.print(millivolts); Serial.print(",");
    millivolts = adsVSPI[i].getMilliVolts(adsVSPI[i].AIN_1);
    Serial.print(millivolts); Serial.print(",");
    millivolts = adsVSPI[i].getMilliVolts(adsVSPI[i].AIN_2);
    Serial.print(millivolts); Serial.print(",");
    millivolts = adsVSPI[i].getMilliVolts(adsVSPI[i].AIN_3);
    Serial.print(millivolts); if (i!=3) Serial.print(",");
  }

  Serial.println();
  //digitalWrite(2, !digitalRead(2)); //led io2 toggle
  //delay(100); // Delay for readability
}