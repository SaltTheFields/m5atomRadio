# M5Stack Atom Echo Internet Radio

An ESP32-based internet radio receiver designed for the **M5Stack Atom Echo**. This project streams high-quality MP3 audio from curated non-commercial radio stations over WiFi and outputs sound via the onboard I2S DAC and 0.5W speaker.

## Features
- **Curated Stations:** Includes reliable streams from KEXP, KUT, SomaFM, and more.
- **Visual Feedback:** Built-in RGB LED indicates connection status and pulses rhythmically during playback.
- **Simple Interface:** Single-button operation to cycle through your favorite stations.
- **Safe Credentials:** Uses a `secrets.h` file to keep your WiFi details out of source control.

## Hardware
- **Device:** M5Stack Atom Echo (ESP32-PICO-D4).
- **Audio:** Onboard I2S DAC (NS4168) and 0.5W Speaker.
- **LED:** 1x SK6812 RGB LED.

## Software Setup

### Prerequisites
1. **Arduino IDE** or **Arduino CLI**.
2. **ESP32 Board Support:** Install the `esp32` core (v2.0.17 recommended for stability).
3. **Required Libraries:**
   - `ESP32-audioI2S` (v2.0.0 recommended)
   - `Adafruit_NeoPixel`

### Configuration
1. Rename `secrets.h.example` to `secrets.h`.
2. Enter your WiFi credentials:
   ```cpp
   #define SECRET_SSID "Your_SSID"
   #define SECRET_PASS "Your_Password"
   ```

### Installation
1. Connect your M5Stack Atom Echo via USB.
2. Select **M5Stack-ATOM** as the board.
3. Compile and upload `m5atomRadio.ino`.

## Usage
- **Booting:** LED blinks **White** while connecting to WiFi.
- **Playing:** LED pulses the station's unique color.
- **Button Press:** Cycles to the next station in the list.

### Station Colors
| Color | Station |
| :--- | :--- |
| **Blue** | KUT 90.5 Austin |
| **Red** | KUTX 98.9 Austin |
| **Green** | KEXP Seattle |
| **Yellow** | SomaFM Groove Salad |
| **Cyan** | WNYC New York |
| **White** | Radio Paradise |

## Hardware Pinout
| Function | Pin |
| :--- | :--- |
| I2S Data (DSIN) | 22 |
| I2S BCLK | 19 |
| I2S LRCK | 33 |
| Button | 39 |
| NeoPixel | 27 |

## License
MIT
