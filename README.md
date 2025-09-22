# Implementation of an Automatic Roller Door for Mine Ventilation Control
 
![Project Status](https://img.shields.io/badge/status-complete-success)

This repository documents the implementation of an automated roller door system designed to improve ventilation control, safety, and operational efficiency at the 275 fm level of the Bogala Graphite Lanka PLC mining facility. The project was developed to address the challenges of manually operating heavy ventilation doors in a high-pressure underground environment.

The full, detailed project report can be found in the `/report` directory.

## Table of Contents
- [Problem Statement](#problem-statement)
- [Project Objectives](#project-objectives)
- [System Design](#system-design)
- [Hardware Components](#hardware-components)
- [Software & Code](#software--code)
- [Safety Considerations](#safety-considerations)
- [Expected Benefits](#expected-benefits)

## Problem Statement
Underground workers at the 275 fm level faced significant physical strain and safety risks while manually operating the existing steel ventilation doors. The high air pressure made the doors difficult to manage, especially during trolley transport, leading to operational inefficiencies and ergonomic hazards. This project automates the door operation process using a motorized roller door integrated with motion and obstacle sensors.

## Project Objectives
- **Automated Detection:** Accurately detect the presence of personnel and trolleys using motion sensors to trigger door operation.
- **Obstacle Prevention:** Implement obstacle detection sensors to prevent the door from closing on obstructions, enhancing safety.
- **Reliability:** Ensure the system functions reliably in challenging underground conditions (variable temperature and humidity).
- **Safety Alarms:** Incorporate visual (red/green lights) and audible (buzzer) alerts for door status and hazard warnings.
- **Fail-Safe Mechanisms:** Integrate a UPS for uninterrupted power and a mechanical breaker system to halt trolleys in case of system failure.

## System Design
The system is controlled by an Arduino Uno R3 board, which processes inputs from a series of PIR motion sensors and IR proximity sensors. Based on these inputs, it controls two relays connected to the roller door motor and auxiliary components like the indicator lights and buzzer.

A detailed circuit diagram illustrating the connections between the Arduino, sensors, relays, and other components is available on **page 12** of the full project report.

The sensor installation plan, detailing the strategic placement of all sensors for optimal coverage, can be found on **page 15** of the report.

## Hardware Components

| Component                       | Quantity | Purpose                                        |
| ------------------------------- | :------: | ---------------------------------------------- |
| Motorized Roller Door           |    1     | Main door mechanism                            |
| Arduino UNO R3                  |    1     | Central control unit                           |
| PIR Sensor (HC-SR501)           |    5     | Motion detection (personnel, trolleys)         |
| Proximity IR Sensor (E18-D80NK) |    2     | Obstacle detection beneath the door            |
| 2-Channel Relay Module          |    1     | Switches the door motor and indicator lights   |
| Indicator Bulbs (Red & Green)   |    2     | Visual status indication (Open/Closed)         |
| Buzzer                          |    3     | Audible alert for obstacles or warnings        |
| Uninterruptible Power Supply (UPS)|   1    | Provides backup power                          |

## Software & Code
The control logic is implemented in C++ on the Arduino platform. The code continuously reads data from the sensors to make decisions. The full, commented source code is available in the `code/` directory.

**Core Logic:**
1.  **Initialization:** Sets up all sensor and output pins. The door starts in a closed state with the red light on.
2.  **Loop:**
    - Reads values from all 5 PIR motion sensors and 2 IR obstacle sensors.
    - **Obstacle Detected:** If either IR sensor detects an object, the door is forced open, and a buzzer sounds an alarm.
    - **Motion Detected:** If the combined reading of the PIR sensors exceeds a threshold, the door opens. After a 15-second delay (to allow full opening), the green light turns on.
    - **No Motion/Obstacles:** If no motion is detected, the door closes, and the red light turns on.

```cpp
// A snippet of the Arduino code for demonstration.
// The full code is available in 'code/ventilation_door_control.ino'

void loop(){
  // Read sensor values
  val = analogRead(sensor);
  val2 = analogRead(sensor2);
  // ... reading other sensors ...
  val6 = digitalRead(ir1);
  val7 = digitalRead(ir2);

  float sum = (voltage + voltage2 + voltage3 + voltage4 + voltage5);

  if (ir1 == LOW || ir2 == LOW){
    // If any obstacles are found under the door,
    // door will open and buzzer will be alarmed
    digitalWrite(relay1, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
  }
  else if (sum > 1){
    // If any pir of the sensor detects motion
    // Door will open
    digitalWrite(relay1, HIGH);
    delay(15000); // Time period for fully open the door
    digitalWrite(relay2, HIGH); // Green Bulb Signal will turn on
    delay(500);
  }
  else {
    // Otherwise, the door will close
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW); // Red Bulb signal will turn on
    digitalWrite(buzzer, LOW);
    delay(500);
  }
}
```

## Safety Considerations
Safety is the highest priority. The system includes:
- **Enclosure Boxes:** Protects all electronics from the harsh mining environment.
- **Calibrated Timing:** 15-second open/close time to prevent abrupt movements.
- **UPS Backup:** Ensures the system remains operational during power outages.
- **Visual & Audible Alerts:** Clearly communicates door status to all personnel.
- **Mechanical Breaker:** A physical barrier to stop trolleys if the electronic system fails.
- **Manual Override:** A lever allows for manual operation in case of an emergency.

## Expected Benefits
- **Enhanced Safety:** Reduced risk of accidents and collisions.
- **Improved Efficiency:** Streamlined workflow and reduced downtime from manual door handling.
- **Reduced Physical Strain:** Alleviated ergonomic stress on workers.
- **Optimized Ventilation Control:** Consistent and reliable airflow management.


