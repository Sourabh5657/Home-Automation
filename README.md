# Home Automation

## Introduction  
This project is a **NodeMCU-based Home Automation System** that automates household appliances and provides **real-time security features**, including **intruder detection** and a **fire alarm system**. The system is controlled and monitored via the **Blynk mobile application**, ensuring convenience, safety, and energy efficiency.  

## Features  
- **Appliance Automation:** Control lights, fans, and DC motors through the Blynk app.  
- **Intruder Detection:** Alerts for unauthorized access using IR sensors.  
- **Fire Alarm:** Detects fire and smoke using an MQ2 sensor with instant alerts.  
- **Automatic Lighting:** LDR-based day/night detection for automated bulb control.  
- **Remote Access:** Operate and monitor devices remotely via smartphone.  
- **Energy Efficiency:** Smart automation logic for power savings.  

## Hardware Components  
- **Microcontroller:** NodeMCU ESP8266  
- **Sensors:**  
  - IR sensors for intruder detection  
  - LDR for automatic lighting (day/night)  
  - MQ2 sensor for fire/smoke detection  
- **Actuators:** DC motors, LEDs, and buzzers  
- **Driver circuits** for motor and appliance control  
- **IoT Platform:** Blynk app  

## Software Tools  
- **Arduino IDE** for code uploading and development  
- **Blynk mobile app** for real-time control and notifications  
- **C/C++** for programming  

## Setup & Usage  
1. Connect NodeMCU to WiFi.  
2. Upload the `HomeAutomation.ino` file via Arduino IDE.  
3. Configure the Blynk app with your device token and WiFi details.  
4. Build the circuit with IR, LDR, MQ2 sensors, and driver circuits.  
5. Use the Blynk app for monitoring alerts and controlling appliances.

## Circuit connection
<img width="1038" height="636" alt="image" src="https://github.com/user-attachments/assets/327e59bd-c6b3-4d51-a5c7-d26072d2fb6f" />

<img width="862" height="639" alt="image" src="https://github.com/user-attachments/assets/aa982d3c-6c76-4182-87b8-950cb189cc0f" />

## Working Prototype
![Uploading image.png…]()


## Accuracy  
The system achieves **85–90% accuracy** in intruder and fire detection across different environmental conditions.  

## Future Scope  
- **Cost Efficiency:** Energy-efficient components for longer life and reduced bills.  
- **AI Integration:** Adding AI for predictive automation and advanced customization.  
- **Smart Integrations:** Voice control via **Google Home** or **Alexa**.  
- **Real-time Updates:** Live data for weather, traffic, and appliance status.  
