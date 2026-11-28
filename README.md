# Automated Bioactive Hedgehog Rehabilitation Enclosure (In Progress)

> A low-cost (~$200), low-stress, smart bioactive enclosure for hedgehog recovery, featuring automated environmental monitoring and non-invasive computer vision tracking.

(./docs/images/final_build.png)

---

## Project Overview
Wild or recovering hedgehogs experience high stress in traditional clinical setups. This project provides an automated, low-intervention bioactive enclosure that tracks activity, weight, and movement patterns while keeping human disruption to an absolute minimum.

---

## Quick Navigation
* [System Architecture](./docs/system_architecture.md)
* [Mechanical Design & Prototype](./docs/mechanical_design.md)
* [Firmware & Software Setup](./docs/software_setup.md)
* [Bill of Materials (BOM) & Wiring](#-bill-of-materials--hardware)

---

## Bill of Materials & Hardware

| Component | Quantity | Purpose | 

| **Raspberry Pi 3 Model B** | 1 | Camera server, Web UI, Data logging |
| **Arduino MCU** | 1 | Sensor data processing & motor control | 
| **Raspberry Pi Camera Module (Wide View)** | 1 | Overhead visual tracking | 
| **IR Break-Beam Sensors** | 1 pair | Entry/exit monitoring | 
| **Hall-Effect Sensor Module** | 1 | Running wheel revolution counting | 
| **SG90 Servo Motor** | 1 | Food/treat dispenser actuation | 
| **Substrate** | Quantity based on enclosure size | Bioactive habitat structure | 

> *<!-- Add notes or specific model part numbers here as parts arrive -->*

---

## System Architecture & Wiring

The system utilizes a split-architecture design:
1. **Low-Level Layer (Arduino):** Handles millisecond-sensitive hardware pulses (break beams, wheel rotation, load cells) and communicates via USB Serial.
2. **High-Level Layer (Raspberry Pi 3B):** Runs the CSI camera module, processes frames via lightweight YOLOv5n TFLite inference, and hosts the local web dashboard.

*<!-- Add electrical box wiring diagram image into ./docs/images/ and reference it below: -->*
<!-- ![Wiring Diagram](./docs/images/wiring_diagram.png) -->

---

## Getting Started & Repository Layout

* **`/firmware/`**: Contains C code for the Arduino microcontroller.
* **`/software/`**: Contains Python scripts for the Raspberry Pi (camera stream, YOLOv5 inference, and serial parsing).
* **`/hardware/`**: Contains mechanical design notes, CAD mockups, and layout schematics.
* **`/docs/`**: Comprehensive documentation guides.

---

## Project Roadmap & Current Status

- [x] Initial conceptual design & Pugh matrix evaluation
- [x] Baseline MCU firmware & Python script drafts
- [x] Cardboard physical layout prototyping
- [x] Final enclosure material assembly & bioactive setup
- [x] Electrical control box wiring & din rail connections setup
- [x] YOLOv5n model export (`.tflite`) and edge deployment on Pi 3B
- [x] 48-hour system testing and data logging baseline run

---

##  Authors & Contributions
* **Project Team:** [Jack Sarina / Jackson Adams, Jawei Zou, Jackie White]
* **Open Source:** Contributions, forks, and suggestions are welcome! Please open an issue if you have questions.
