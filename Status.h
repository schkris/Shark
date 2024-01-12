#ifndef Status_h
#define Status_h

// Define DHT sensor pin and type
#define DHTPIN 20 // Z_STOP_PIN
#define SOURCE 19 // Y_STOP_PIN
#define GROUND 3 // Z_STEP_PIN
#define DHTTYPE DHT11

extern float humidity;
extern float temperature;

void initializeDHTSensor();
void readDHTSensor();

#endif