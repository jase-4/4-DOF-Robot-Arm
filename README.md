# 4-DOF Robotic Arm

**Blog Page:** [For more depth, photos, and video demos](https://jasebranch.com/posts/robot_arm/)

A physical 4-DOF robotic arm built using **STM32 firmware**, **custom PCB design**, **Fusion 360 CAD**, and **3D printing**. The system is controlled through a Python host application communicating with the arm over **UART**.
<img width="4032" height="3024" alt="robot" src="https://github.com/user-attachments/assets/b664d6d1-67fd-476d-ba1e-5251e8825f94" />


---

## Features

- **Embedded Control:** STM32 firmware written in C for real-time servo control.
- **Motion Smoothing:** Velocity-limited control loop for smoother and more reliable movement.
- **Custom PCB:** Dedicated servo power distribution board designed in KiCad.
- **Host Interface:** Python application for commanding arm poses and gripper actions.
- **Mechanical Design:** Custom 3D-printed arm structure and rack-and-pinion gripper.

---

## Hardware

- STM32F446RE
- 4x SG90 9g servos
- 3D-printed mechanical structure
- Custom servo power distribution PCB
- External buck converter module
- External DC power supply

---

## Gallery

### Completed Arm

<img width="4032" height="3024" alt="pic5" src="https://github.com/user-attachments/assets/33071936-8e87-433a-824b-ebc846b9a781" />

### PCB

<img width="4032" height="3024" alt="board" src="https://github.com/user-attachments/assets/d8c0b59c-7692-4dbe-91f2-5212b4ad5bde" />


### CAD Design

<img width="1271" height="853" alt="fusion" src="https://github.com/user-attachments/assets/e0dc3880-b13f-4816-9867-6511acaf9c6b" />


---

## Repository Structure

## Repository Structure

```text
.
├── stm32/        # STM32CubeIDE firmware (C)
│   └── Core/Src  # Main application logic (PWM control, UART handling, control loop)
├── python/       # Host control application (UART interface, motion commands)
├── hardware/     # PCB design files and schematics
└── cad/          # Fusion 360 mechanical design files
```

---

## Running the Host Application

Install dependencies:

```bash
pip install -r requirements.txt
```

Run the demo script:

```bash
python demo.py
```

The STM32 board must be connected over USB and configured for UART communication.


