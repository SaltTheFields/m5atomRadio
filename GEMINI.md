# M5Atom Radio Project Overview

This project is an ESP32-based internet radio receiver designed for the **M5Stack Atom Echo**. It streams audio from predefined internet radio stations over WiFi and outputs sound via the onboard I2S DAC.

## Main Technologies
- **Hardware:** ESP32 (specifically M5Stack Atom Echo).
- **Language:** C++ (Arduino IDE compatible).
- **Core Libraries:**
  - `WiFi.h`: For wireless connectivity.
  - `Audio.h` ([ESP32-audioI2S](https://github.com/schreibfaul1/ESP32-audioI2S)): Handles stream decoding (MP3, OGG, AAC) and I2S output.
  - `Adafruit_NeoPixel`: Manages the onboard RGB LED for status and visual feedback.

## Key Features
- **Station Selection:** Cycles through a curated list of stations, including genuine **Fallout game radio streams** (Galaxy News, Diamond City, Radio New Vegas), Austin locals, and post-punk.
- **Visual Feedback:** The NeoPixel LED changes color based on the selected station and pulses during playback.
- **I2S Audio:** Direct digital audio output configured for the Atom Echo's hardware.

## Building and Running

### Prerequisites
1.  **Arduino IDE** or **PlatformIO**.
2.  **ESP32 Board Support:** Install the ESP32 core in your development environment.
3.  **Required Libraries:**
    - `ESP32-audioI2S`
    - `Adafruit_NeoPixel`

### Setup
1.  Open `m5atomRadio.ino`.
2.  Update the `ssid` and `password` variables with your WiFi credentials.
3.  Select the **M5Stack-Atom** or **ESP32 Dev Module** as the target board.
4.  Compile and upload the sketch to your M5Stack Atom Echo.

### Usage
- **Single Press:** Cycles to the next radio station.
- **Volume:** Set to **21 (Maximum)** by default.
- **LED Indicators:**
  - **White (Blinking):** Connecting to WiFi.
  - **Cyan:** Galaxy News Radio (Fallout 3).
  - **Magenta:** Diamond City Radio (Fallout 4).
  - **Amber:** Radio New Vegas.
  - **Yellow:** Fallout (Post-Punk).
  - **Blue/Red/Green:** Austin Locals & KEXP.

## Hardware Pinout (M5Stack Atom Echo)
| Function | Pin |
| :--- | :--- |
| I2S Data (DSIN) | 22 |
| I2S BCLK | 19 |
| I2S LRCK | 33 |
| Main Button | 39 |
| NeoPixel LED | 27 |
