# SaarthiAI 🤖
### Vision-Based Autonomous Robot | Hack in Hills '26

SaarthiAI is a vision-based autonomous robot project designed to explore intelligent perception, object detection, obstacle awareness, and navigation using computer vision and embedded hardware.

## 🎯 Project Objectives

- Detect and identify objects using a camera and AI-based computer vision.
- Detect nearby obstacles using distance sensors.
- Support robot movement and directional control.
- Develop decision-making logic for safer navigation.
- Explore real-time AI-assisted robotic navigation.

## 🛠️ Hardware Components

- Arduino UNO R3
- HW-130 L293D Motor Driver Shield
- Two TT DC motors
- HC-SR04 ultrasonic sensors (3)
- VL53L0X Time-of-Flight distance sensor
- Webcam
- Chassis and battery holder

## 💻 Technologies Used

- Python
- OpenCV
- Ultralytics YOLO
- Arduino C/C++
- Serial communication

## ⚙️ Project Status

**Development in progress.**

The project includes motor-control testing and computer-vision experiments. Sensor integration, autonomous navigation, and full-system testing are ongoing.

## 🚀 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/somukumar45/SaarthiAI.git
cd SaarthiAI
```

### 2. Set up Python

Create and activate a virtual environment:

```bash
python -m venv .venv
```

On Windows PowerShell:

```powershell
.\.venv\Scripts\Activate.ps1
```

### 3. Install dependencies

Install the packages required by your actual Python scripts. For example:

```bash
pip install opencv-python ultralytics pyserial
```

### 4. Connect the hardware

Connect the Arduino and motor driver according to the project's wiring plan. Verify power polarity and sensor connections before powering the robot.

### 5. Run the project

Run the appropriate Python detection or robot-control script from the project folder. The script filename and required configuration depend on the files included in the repository.

## 🔭 Future Improvements

- Integrate camera-based object detection with robot movement.
- Combine distance-sensor readings with obstacle-avoidance logic.
- Improve navigation and decision-making.
- Test the complete system in real-world environments.
- Optimize performance for real-time operation.

## 👨‍💻 Project Information

**Project:** SaarthiAI  
**Event:** Hack in Hills '26  
**Repository:** https://github.com/somukumar45/SaarthiAI

---

*Built as a work in progress toward intelligent, vision-based robotic navigation.*