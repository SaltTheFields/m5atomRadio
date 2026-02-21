# M5Atom Radio Project Overview

This project is an ESP32-based internet radio receiver designed for the **M5Stack Atom Echo**. It streams audio from predefined internet radio stations over WiFi and outputs sound via the onboard I2S DAC.

## Main Technologies
- **Hardware:** ESP32 (specifically M5Stack Atom Echo).
- **Language:** C++ (Arduino IDE compatible).
- **Core Libraries:**
  - `WiFi.h`: For wireless connectivity.
  - `Audio.h` ([ESP32-audioI2S](https://github.com/schreibfaul1/ESP32-audioI2S)): Handles stream decoding (MP3) and I2S output.
  - `Adafruit_NeoPixel`: Manages the onboard RGB LED for status and visual feedback.

## Key Features
- **Station Selection:** Cycles through a curated list of reliable non-commercial stations (KEXP, SomaFM, KUT, etc.) using the main button.
- **Visual Feedback:** The NeoPixel LED changes color based on the selected station and pulses during playback.
- **Secrets Management:** Credentials handled via `secrets.h`.

## Building and Running

### Prerequisites
1. **Arduino CLI** or IDE.
2. **ESP32 Core:** v2.0.17 (Stable for I2S).
3. **Libraries:**
    - `ESP32-audioI2S-master` (v2.0.0)
    - `Adafruit_NeoPixel`

### Setup
1. Create `secrets.h` from `secrets.h.example`.
2. Compile and upload using the `m5stack-atom` FQBN.

## Hardware Pinout (M5Stack Atom Echo)
| Function | Pin |
| :--- | :--- |
| I2S Data (DSIN) | 22 |
| I2S BCLK | 19 |
| I2S LRCK | 33 |
| Main Button | 39 |
| NeoPixel LED | 27 |
