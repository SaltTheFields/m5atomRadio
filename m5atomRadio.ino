#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include <Adafruit_NeoPixel.h>
#include "secrets.h"

// --- 1. WIFI SETTINGS ---
const char* ssid = SECRET_SSID;       
const char* password = SECRET_PASS; 

// --- 2. RADIO STATIONS (Interesting & Reliable) ---
struct Station {
    const char* name;
    const char* url;
    uint32_t color; 
};

Station stations[] = {
    {"KUT 90.5 Austin",      "http://streams.kut.org/4426_128.mp3", 0x0000FF},      // Blue
    {"KUTX 98.9 Austin",     "http://streams.kut.org/4427_128.mp3", 0xFF0000},      // Red
    {"KEXP Seattle",         "http://kexp-mp3-128.streamguys1.com/kexp128.mp3", 0x00FF00}, // Green
    {"SomaFM GrooveSalad",   "http://ice1.somafm.com/groovesalad-128-mp3", 0xFFFF00},  // Yellow
    {"WNYC New York",        "http://fm939.wnyc.org/wnycfm", 0x00FFFF},             // Cyan
    {"Radio Paradise",       "http://stream.radioparadise.com/mp3-128", 0xFFFFFF}    // White
};

int currentStation = 0;
const int numStations = sizeof(stations) / sizeof(stations[0]);

// --- 3. HARDWARE PINOUT (Atom Echo) ---
#define I2S_DSIN      22 
#define I2S_BCLK      19
#define I2S_LRCK      33
#define BUTTON_PIN    39  
#define LED_PIN       27  
#define NUM_LEDS      1

Audio audio;
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastButtonPress = 0;
bool isPlaying = false;

void playStation(int index) {
    audio.stopSong(); 
    Serial.printf("\n[RADIO] Connecting to: %s\n", stations[index].name);
    audio.connecttohost(stations[index].url);
    
    pixels.setPixelColor(0, stations[index].color);
    pixels.show();
    isPlaying = false; 
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    pixels.begin();
    pixels.setBrightness(40); 
    pixels.setPixelColor(0, 0xFFFFFF); 
    pixels.show();

    Serial.println("\n\n--- M5Stack Atom Echo: Interesting Radio ---");

    WiFi.begin(ssid, password);
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 40) {
        delay(500);
        Serial.print(".");
        retries++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n[WIFI] Connected! IP: " + WiFi.localIP().toString());
    } else {
        Serial.println("\n[WIFI] FAILED!");
        pixels.setPixelColor(0, 0xFF0000);
        pixels.show();
    }

    audio.setPinout(I2S_BCLK, I2S_LRCK, I2S_DSIN);
    audio.setVolume(21); 
    audio.setBufsize(16000, 16000); 

    delay(1000);
    playStation(currentStation);
}

void loop() {
    audio.loop();

    if (digitalRead(BUTTON_PIN) == LOW) {
        unsigned long now = millis();
        if (now - lastButtonPress > 1000) {
            lastButtonPress = now;
            currentStation = (currentStation + 1) % numStations;
            playStation(currentStation);
        }
    }

    if (isPlaying) {
        float pulse = (sin(millis() / 300.0) * 0.4 + 0.6); 
        uint32_t baseColor = stations[currentStation].color;
        byte r = (uint8_t)((baseColor >> 16) & 0xFF) * pulse;
        byte g = (uint8_t)((baseColor >> 8) & 0xFF) * pulse;
        byte b = (uint8_t)(baseColor & 0xFF) * pulse;
        pixels.setPixelColor(0, pixels.Color(r, g, b));
        pixels.show();
    }
}

void audio_info(const char *info){
    Serial.printf("[INFO] %s\n", info);
    if (strstr(info, "stream ready")) isPlaying = true;
}

void audio_eof_mp3(const char *info){
    Serial.println("[RADIO] Stream ended, reconnecting...");
    audio.connecttohost(stations[currentStation].url);
}
