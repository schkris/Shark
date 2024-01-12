#ifndef Status_h
#define Status_h

// Define DHT sensor pin and type
#define DHTPIN 18 // X_STOP_PIN
#define STEP 3 // Z_STEP_PIN
#define DIR 2 // Z_DIR_PIN
#define ENABLE 26 // Z_ENABLE_PIN
#define STOP 20 // Z_STOP_PIN
#define DHTTYPE DHT11

extern float humidity;
extern float temperature;
extern int stepperSpeed;

void initializeDHTSensor();
void initializeStepper();
void readDHTSensor();
void controlStepperMotor(int speed);

#endif