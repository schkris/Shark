#include "Status.h"
#include <DHT.h>

float humidity = 0.0;
float temperature = 0.0;

// Define constants based on your stepper motor and driver characteristics
const unsigned long MAX_STEP_DELAY = 50000;  // Maximum delay between steps (slowest speed)
const unsigned long MIN_STEP_DELAY = 500;    // Minimum delay between steps (fastest speed)
const unsigned long STEP_PULSE_DURATION = 10; // Duration of step pulse in microseconds

DHT dht(DHTPIN, DHTTYPE);

void initializeDHTSensor() 
{   
    // pinMode(SOURCE, OUTPUT);
    // pinMode(GROUND, OUTPUT);
    dht.begin();
}

void initializeStepper()
{
    pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
    pinMode(ENABLE, OUTPUT);
}

void readDHTSensor() 
{
    // digitalWrite(SOURCE, HIGH);
    // digitalWrite(GROUND, LOW);
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

void controlStepperMotor(int speed) 
{
    digitalWrite(ENABLE, LOW);

    if (speed == 0) return;

    // Determine the direction of rotation
    digitalWrite(DIR, (speed >= 0) ? HIGH : LOW); // Adjust as necessary

    // Calculate the delay between steps for the desired speed
    // This is a simplistic way to control speed. You might need a more
    // sophisticated approach for fine control.
    unsigned long stepDelay = map(abs(speed), 0, 255, MAX_STEP_DELAY, MIN_STEP_DELAY);
    
    // Perform a step
    digitalWrite(STEP, HIGH);
    delayMicroseconds(STEP_PULSE_DURATION); // Duration of the step pulse
    digitalWrite(STEP, LOW);

    // Wait for the next step
    delayMicroseconds(stepDelay);
}

