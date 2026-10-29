# Semi-Automatic String Hopper Making Machine

A robotics project developed to assist in the string hopper production process using an Arduino-based control system. The machine uses an ultrasonic sensor, push-button input, and relay-controlled mechanisms to manage movement during operation.

The project demonstrates the integration of embedded programming, electronic components, and mechanical automation to improve convenience in a traditional food preparation process.

## Project Objectives

- Develop a semi-automatic mechanism to assist with string hopper production.
- Implement sensor-based control using an ultrasonic distance sensor.
- Control machine movement through an Arduino-based system.
- Combine hardware components and programming to create a practical automation prototype.

## Features

- **Ultrasonic Distance Detection** – Uses the HC-SR04 sensor to measure distance and determine the machine's operating state.
- **Push-Button Control** – Allows the operator to initiate and control the machine's movement.
- **Motor Movement Control** – Uses relay-based control for upward and downward movement.
- **Automated Tray Control** – Integrates relay control for the tray mechanism.
- **Threshold-Based Logic** – Uses a predefined distance threshold of 20 cm to determine the appropriate control response.
- **Semi-Automatic Operation** – Combines operator input with sensor-based decision-making.

## Hardware Components

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller |
| HC-SR04 Ultrasonic Sensor | Distance measurement |
| Push Button | Operator input |
| Relay Modules | Switching and mechanism control |
| Motorized Mechanism | Upward and downward movement |
| Tray Mechanism | Supports the intended production process |
| Power Supply | Supplies power to the electronic and mechanical components |

## Technologies Used

- **Programming:** Arduino C/C++
- **Microcontroller:** Arduino Uno
- **Sensors:** HC-SR04 ultrasonic sensor
- **Control Electronics:** Relays and push-button input
- **Embedded Systems:** Sensor-based control logic and hardware integration

## System Operation

1. The ultrasonic sensor measures the distance to the detected object.
2. The operator activates the machine using the push button.
3. The Arduino evaluates the sensor reading against the predefined 20 cm threshold.
4. Based on the threshold and button state, the controller activates the relevant relay outputs.
5. The mechanism performs the corresponding movement while the operating conditions are satisfied.
6. Releasing the button stops the button-controlled movement, according to the implemented control logic.

## Pin Configuration

| Component | Arduino Pin |
|---|---|
| HC-SR04 Trigger | Digital Pin 4 |
| HC-SR04 Echo | Digital Pin 5 |
| Push Button | Digital Pin 12 |
| Upward Movement Relay | Digital Pin 8 |
| Downward Movement Relay | Digital Pin 9 |
| Tray Control Relay | Digital Pin 10 |



## Project Objectives and Learning Outcomes

Through this project, the team explored:

- Embedded systems programming.
- Ultrasonic sensor integration.
- Digital input and output control.
- Relay-based switching.
- Hardware and software integration.
- Practical automation and prototype development.
- Collaborative engineering and problem-solving.

## Future Improvements

- Introduce adjustable distance thresholds.
- Add emergency-stop functionality and additional safety interlocks.
- Improve mechanical stability and production consistency.
- Integrate a more advanced control interface.
- Conduct further testing to evaluate reliability and performance.

## Project Type

**Academic Robotics Project**

Developed as part of the Robotics programme at the National Institute of Business Management (NIBM), Sri Lanka.

**Focus Areas:** Arduino · Embedded Systems · Robotics · Sensor Integration · Automation

---

*This project is an educational prototype. Its capabilities depend on the final assembled hardware, implemented control logic, and testing results.*
