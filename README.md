# 🤖 Smart Surveillance Robot

A multifunctional autonomous robot designed for indoor surveillance, obstacle avoidance, and hazard detection. This project integrates real-time environment monitoring and intelligent decision-making using ultrasonic sensors, gas/flame detection, and temperature sensing — all wrapped into a compact embedded system.

---

## 🚀 Features

- **Obstacle Avoidance**  
  Uses three ultrasonic sensors to detect nearby objects and autonomously choose a clear path (forward, left, right).

- **Multi-Hazard Detection**  
  Equipped with temperature, gas (MQ2), flame, and light sensors to detect:
  - Fire emergencies
  - Gas leaks
  - High temperature zones
  - Lighting conditions

- **Alert System**  
  - On-board buzzer and LED indicators for visual/audible alerts  
  - Priority handling for critical threats (e.g., stops movement on fire detection)

- **Live Sensor Display**  
  LCD screen shows real-time data: temperature, gas, flame, light, and distances from 3 directions.

- **Efficient Sensor Multiplexing**  
  Smart time-switching (multiplexing) of ultrasonic sensors using a shared Input Capture Unit (ICU) to reduce hardware load.

---

## 🛠 Technologies Used

| Module        | Component/Interface           |
|---------------|-------------------------------|
| Microcontroller | ATmega32 (AVR)             |
| IDE/Compiler  | AVR-GCC, Atmel Studio / Eclipse AVR |
| Simulation    | Proteus 8+                    |
| Display       | 16x2 Character LCD            |
| Sensing       | LM35, MQ2, Flame sensor, LDR  |
| Distance      | HC-SR04 Ultrasonic Sensors (x3) |
| Actuators     | 2 DC Motors with L298N        |

---

## 🔧 System Architecture

1. **Initialization Phase**  
   Initializes all peripherals (LCD, sensors, motors, ICU, ADC, etc.)

2. **Main Control Loop**  
   - Continuously reads sensor values
   - Decides movement based on obstacle data
   - Scans environment for hazards
   - Handles emergency alerts
   - Displays current status on LCD

3. **Interrupt-Based Ultrasonic Timing**  
   Edge-detection interrupts manage distance measurements using a shared ICU.

---
## 👥 Authors

- [Amr](https://github.com/amryaser338)
- [Zeyad](https://github.com/zeyad-hisham-cyper)
