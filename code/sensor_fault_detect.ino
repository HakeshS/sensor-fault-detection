/*************************************************
 * LM35 SENSOR FAULT DETECTION SYSTEM
 * Faults detected:
 * 1. Noise
 * 2. Drift
 * 3. Saturation
 *
 * Hardware:
 * - Arduino UNO
 * - LM35 on A0
 * - Green LED  -> D8  (NORMAL)
 * - Yellow LED -> D9  (DRIFT)
 * - Red LED    -> D10 (NOISE / SATURATION)
 *************************************************/

// ---------- PIN DEFINITIONS ----------
#define LM35_PIN A0

#define LED_GREEN  8
#define LED_YELLOW 9
#define LED_RED    10

// ---------- THRESHOLDS & PARAMETERS ----------
#define SAMPLE_COUNT 20

#define NOISE_THRESHOLD       2.0    // °C sudden jump
#define DRIFT_THRESHOLD       0.03   // °C per second
#define SATURATION_THRESHOLD  0.2    // °C variation
#define SATURATION_TIME       8000   // ms

// ---------- GLOBAL VARIABLES ----------
float prevTemp = 0;
float prevAvgTemp = 0;

unsigned long lastTime = 0;
unsigned long stableStartTime = 0;

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  Serial.println("====================================");
  Serial.println(" LM35 SENSOR FAULT DETECTION SYSTEM ");
  Serial.println("====================================");

  prevTemp = readTemperature();
  prevAvgTemp = prevTemp;
  lastTime = millis();
  stableStartTime = millis();
}

// ---------- MAIN LOOP ----------
void loop() {

  float currentTemp = readTemperature();
  float avgTemp = getAverageTemp();

  unsigned long currentTime = millis();
  float timeDiff = (currentTime - lastTime) / 1000.0;
  if (timeDiff <= 0) timeDiff = 0.001;

  // -------- FAULT DETECTION --------
  bool noiseFault = abs(currentTemp - prevTemp) > NOISE_THRESHOLD;
  bool driftFault = abs(avgTemp - prevAvgTemp) / timeDiff > DRIFT_THRESHOLD;
  bool saturationFault = false;

  if (abs(currentTemp - prevTemp) < SATURATION_THRESHOLD) {
    if (currentTime - stableStartTime > SATURATION_TIME) {
      saturationFault = true;
    }
  } else {
    stableStartTime = currentTime;
  }

  // -------- STATUS & LED CONTROL --------
  if (noiseFault || saturationFault) {
    setLED(false, false, true);
    Serial.print("TEMP: ");
    Serial.print(currentTemp);
    Serial.println(" °C | STATUS: NOISE / SATURATION");
  }
  else if (driftFault) {
    setLED(false, true, false);
    Serial.print("TEMP: ");
    Serial.print(currentTemp);
    Serial.println(" °C | STATUS: DRIFT");
  }
  else {
    setLED(true, false, false);
    Serial.print("TEMP: ");
    Serial.print(currentTemp);
    Serial.println(" °C | STATUS: NORMAL");
  }

  prevTemp = currentTemp;
  prevAvgTemp = avgTemp;
  lastTime = currentTime;

  delay(1000);
}

// ---------- READ LM35 TEMPERATURE ----------
float readTemperature() {
  int adcValue = analogRead(LM35_PIN);
  float voltage = adcValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0; // LM35 = 10mV/°C
  return temperature;
}

// ---------- MOVING AVERAGE ----------
float getAverageTemp() {
  float sum = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    sum += readTemperature();
    delay(5);
  }
  return sum / SAMPLE_COUNT;
}

// ---------- LED CONTROL ----------
void setLED(bool green, bool yellow, bool red) {
  digitalWrite(LED_GREEN, green);
  digitalWrite(LED_YELLOW, yellow);
  digitalWrite(LED_RED, red);
}
