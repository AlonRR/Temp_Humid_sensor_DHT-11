#include <Arduino.h>
#include "one_wire_read.hpp"

#define HUMID_TEMP_PIN 27

one_wire_read dht11(HUMID_TEMP_PIN);

void setup()
{
    Serial.begin(115200);
    pinMode(HUMID_TEMP_PIN, OUTPUT);
}

void loop()
{
    dht11.start_read();
    Serial.print("Humdity = ");
    Serial.print(dht11[0], DEC); // Displays the integer bits of humidity;
    Serial.print('.');
    Serial.print(dht11[1], DEC); // Displays the decimal places of the humidity;
    Serial.print('%');
    Serial.print("\t Temperature = ");
    Serial.print(dht11[2], DEC); // Displays the integer bits of temperature;
    Serial.print('.');
    Serial.print(dht11[3], DEC); // Displays the decimal places of the temperature;
    Serial.print('C');

    if (dht11.checksum() == false)
        Serial.println("\t -- Checksum Error!");
    else
        Serial.println("\t -- OK");

    delay(1000);
}