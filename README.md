# Pipeline Alarm System 🚨

An **ultrasonic distance-based alarm system** built on Arduino, designed as a **small-scale prototype for rural and poverty-affected pipeline safety monitoring**. The device integrates an **ultrasonic sensor, LED indicators, buzzer, and LCD display**, providing real-time feedback on distance thresholds. This prototype can also be adapted for applications such as **obstacle detection** or **proximity-based alerts**.  

---

## ✨ Features
- **Real-time distance sensing** using an ultrasonic sensor (in centimeters).  
- **Dynamic alerts**:
  - LCD displays measured distance and warning messages.  
  - Buzzer and LED alarms escalate as objects approach closer thresholds.  
  - RGB LCD background color changes based on proximity (“Very Far”, “Far”, “Close”, “Very Close”).  
- **Touch sensor** for device activation/deactivation.  
- Implemented in **C++ with Arduino libraries**, ensuring reliable hardware–software integration.  

---

## 🛠️ Tech Stack
- **Hardware**: Arduino Uno, Ultrasonic Sensor (HC-SR04), Buzzer, RGB LCD, Grove LED Bar, Touch Sensor  
- **Languages**: C++ (Arduino IDE)  
- **Libraries**: `Ultrasonic.h`, `Grove_LED_Bar.h`, `Wire.h`, `rgb_lcd.h`  

---

## 🚀 Setup & Usage
1. **Hardware Assembly**  
   - Connect the ultrasonic sensor to digital pin D7.  
   - Connect the LED to D4, buzzer to D3, touch sensor to D2, and LED bar to D8.  
   - Attach RGB LCD via I²C pins.  

2. **Software Installation**  
   - Install the Arduino IDE.  
   - Add the required libraries (`Ultrasonic`, `Grove_LED_Bar`, `rgb_lcd`).  
   - Clone this repository:  
     ```bash
     git clone https://github.com/yourusername/Arduino-Distance-Based-Alarm-System.git
     ```
   - Upload the code to your Arduino Uno.  

3. **Operation**  
   - Power on the device.  
   - Press the touch sensor to activate monitoring.  
   - Place an object in front of the sensor to observe alarms at varying distances.  
   - Press the touch sensor again to deactivate.  

---

## 📊 Distance Thresholds
| Distance (cm) | LCD Display   | LED/Buzzer | LCD Color  |
|---------------|--------------|------------|------------|
| > 100         | “Very Far”   | OFF        | Blue       |
| 50–100        | “Far”        | LED ON     | Green      |
| 20–50         | “Close”      | Beeps      | Yellow     |
| ≤ 20          | “Very Close” | Alarm ON   | Red        |

---

---

## 🔍 Applications
- **Rural and poverty pipeline safety monitoring (primary purpose)**  
- Obstacle detection in robotics  
- Proximity alarms for safety zones  
- Assistive devices for visually impaired navigation  

---
