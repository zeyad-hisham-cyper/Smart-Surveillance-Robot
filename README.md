# Smart Surveillance Robot

## Abstract
The Smart Surveillance Robot is an embedded autonomous system designed for real-time indoor monitoring, hazard detection, and obstacle avoidance. Powered by an ATmega32 microcontroller, the robot uses a range of sensors to navigate, detect gas leaks, fire, and abnormal temperature levels. Alerts are communicated via Bluetooth to a remote slave unit for user awareness.

## System Design and Architecture
The system is based on a master-slave architecture:
- **Master Unit (Robot):** Performs all sensing, decision-making, navigation, and hazard alerting.
- **Slave Unit (Human-Carried):** Receives real-time data from the robot and displays it on an LCD, with buzzer alerts for critical events.

Key design features include:
- Autonomous navigation using ultrasonic distance sensors.
- Hazard detection (gas, flame, high temperature).
- Real-time alerts displayed via LCD and buzzer.
- Bluetooth communication between microcontrollers.
- Efficient sensor multiplexing using the Input Capture Unit (ICU).

## Peripherals Used
- **Microcontroller:** ATmega32 (8-bit AVR)
- **Sensors:**
  - 3× HC-SR04 Ultrasonic Sensors
  - MQ2 Gas Sensor
  - Flame Sensor
  - LM35 Temperature Sensor
  - LDR (Light Detection)
- **Actuators:**
  - 2× DC Motors (controlled via L298N motor driver)
  - Buzzer
  - LEDs
  - 16×2 Character LCD
- **Others:**
  - Bluetooth Modules (HC-05/06)

## Protocol Used
- **Bluetooth Serial Communication** with MAC-based identification for secure, one-to-one communication between the robot (master) and the human-carried unit (slave).

## Conclusion
This project demonstrates a robust, low-cost solution for autonomous surveillance and hazard detection using embedded systems. With efficient sensor handling, wireless communication, and real-time alerts, it is well-suited for smart home and safety applications.
