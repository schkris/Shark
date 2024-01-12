#include "Status.h"
#include <DHT.h>

float humidity = 0.0;
float temperature = 0.0;

DHT dht(DHTPIN, DHTTYPE);

void initializeDHTSensor() 
{   
    pinMode(SOURCE, OUTPUT);
    pinMode(GROUND, OUTPUT);
    dht.begin();
}

void readDHTSensor() 
{
    digitalWrite(SOURCE, HIGH);
    digitalWrite(GROUND, LOW);
    // Read humidity and temperature values
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature)) 
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
}

