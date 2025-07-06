#define BLINKER_WIFI
//#define BLINKER_ESP_SMARTCONFIG

#include <Blinker.h>
#include "ESP32_CAM_SERVER.h"

char auth[] = "8751d66549ec";
char ssid[]="GeekHome";//WiFi名称
char pswd[]="你  ";//wifi密码
bool setup_camera = false;

void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();
    
    uint32_t BlinkerTime = millis();
    
    Blinker.print("millis", BlinkerTime);
}

void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    
    Blinker.begin(auth,ssid,pswd);
    Blinker.attachData(dataRead);
}

void loop()
{
    Blinker.run();

    if (Blinker.connected() && !setup_camera)
    {
        setupCamera();
        setup_camera = true;

        Blinker.printObject("video", "{\"str\":\"mjpg\",\"url\":\"http://"+ WiFi.localIP().toString() + "\"}");
    }
}
