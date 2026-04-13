# Ultrasonic Radar System
**Arduino Nano · HC-SR04 · SG90 Servo · Web Serial API**

A real-time radar system built with an Arduino Nano. An ultrasonic sensor mounted on a servo sweeps 30°–180°, streaming live distance data over serial to a Chrome browser, which renders a radar-style visualization with object detection, angle readout, and alert status. An I2C LCD displays live readings on the hardware side simultaneously.

This project is an iteration of [Project 1 — Ultrasonic Distance Alert](#), expanding it with servo-driven scanning and a custom browser-based display interface.

---

## Demo

*(Insert GIF or video here)*

---

## Features

- Servo sweeps 150° arc (30°–180°) with live angle tracking
- HC-SR04 ultrasonic sensor streams `angle,distance` pairs over serial
- Browser UI via Web Serial API renders real-time radar with fading object dots
- HUD overlay shows current angle, distance, and alert status
- I2C LCD updates live during sweep — no PC required for basic operation

---

## Hardware

| Component | Role |
|---|---|
| Arduino Nano | Microcontroller |
| HC-SR04 | Ultrasonic distance sensor |
| SG90 Servo | Rotates sensor through sweep arc |
| 16x2 I2C LCD | On-device distance/angle display |
| Yellow LED | Visual proximity alert |

### Wiring

| Component | Pin |
|---|---|
| HC-SR04 Trig | D9 |
| HC-SR04 Echo | D10 |
| SG90 Signal | D6 |
| LCD SDA | A4 |
| LCD SCL | A5 |

*(Circuit schematic coming soon — KiCad in progress)*

---

## Software

**Arduino (`radar.ino`)**
Drives the servo sweep loop and reads distance via the HC-SR04. Outputs `angle,distance` over serial at 9600 baud and updates the LCD on each sweep step.

**Browser UI (`index.html`)**
Connects to the Nano via the Web Serial API (Chrome only). Parses the serial stream and renders a canvas-based radar display with a rotating sweep line, fading object history, and a live HUD.

### Requirements
- Arduino IDE (or compatible)
- Chrome browser (Web Serial API support required)
- Libraries: `Servo.h`, `Wire.h`, `LiquidCrystal_I2C.h`

---

## Photos

*(Insert hardware photos here)*

---

## What I'd Improve

- Add a buzzer for audio alerting at close range
- Smooth servo movement with smaller step increments
- Log object detections with timestamps to a file via serial
- Replace breadboard wiring with a custom PCB (KiCad schematic in progress)

---

## About

Built as part of an EE portfolio during my first year at Moorpark College. Focused on hardware-software integration — bridging embedded systems with browser-based interfaces.
