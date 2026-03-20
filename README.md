# sensor-fault-detection
Temperature sensor fault detection using LM35 (Drift, Noise, Saturation)
# LM35 Temperature Sensor Fault Detection System

## 📌 Overview

This project focuses on detecting faults in temperature sensor readings using the LM35 analog temperature sensor. Instead of simply measuring temperature, the system analyzes the behavior of sensor data to classify it into different operating conditions.

The goal is to improve reliability in sensor-based systems by identifying abnormal patterns such as drift, noise, and saturation.

---

## 🎯 Objective

* To monitor temperature using LM35 sensor
* To detect abnormal sensor behavior
* To classify readings into meaningful fault categories
* To simulate and validate the system using Proteus

---

## ⚙️ System Architecture

The system follows a simple data flow:

Sensor (LM35) → Signal Processing → Fault Detection Logic → Output Classification

* LM35 provides analog voltage proportional to temperature
* Microcontroller reads and processes the signal
* Algorithm analyzes variations over time
* Output is classified into different fault conditions

---

## 🔍 Fault Classification Logic

The system identifies four main conditions:

### 1. Normal

* Temperature remains stable within expected variation
* No sudden spikes or long-term deviation

### 2. Noise

* Rapid fluctuations in readings within short time intervals
* Caused by signal interference or unstable readings

### 3. Drift

* Slow and continuous change in temperature over time
* Indicates sensor deviation or calibration issues

### 4. Saturation

* Constant maximum or minimum value for extended duration
* Indicates sensor stuck or hardware limitation

---

## 🧠 Detection Method

The classification is based on:

* **Rate of Change** → Detects sudden spikes (Noise)
* **Time-based Analysis** → Detects gradual deviation (Drift)
* **Stability Check** → Detects constant readings (Saturation)

Basic logic:

* If value is constant for long time → Saturation
* If rapid fluctuations → Noise
* If gradual increase/decrease → Drift
* Else → Normal

---

## 🧰 Tools & Technologies Used

* Arduino (Embedded C)
* Proteus Design Suite
* LM35 Temperature Sensor

---

## 🧪 Simulation

The system was implemented and tested using Proteus simulation.

Different scenarios were created to validate:

* Stable temperature (Normal)
* Rapid fluctuations (Noise)
* Gradual increase (Drift)
* Constant extreme values (Saturation)

---

## 📊 Results

The system successfully classified temperature data into different fault conditions.

### Add your screenshots below:

* Normal case
* Noise case
* Drift case
* Saturation case

---

## 🚀 Future Improvements

* Real hardware implementation
* Integration with IoT platforms
* Data logging and visualization
* Multi-sensor fault detection

---

## ⚠️ Limitations

* Based on simulation only
* Threshold values are manually defined
* Accuracy depends on tuning parameters

---

## 👤 Author

Hakesh S
