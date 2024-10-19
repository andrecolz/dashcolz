#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <SPI.h>
#include "img/dashboard.h"
#include "img/loading.h"
#include "img/wificon.h"
#include <Wire.h>
#include <Time.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include "epd3c/GxEPD2_750c_Z08.h"
#include "class/Calendar.h"
#include "class/Weather.h"

GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> display(GxEPD2_750c_Z08(/*CS=D8*/ SS, /*DC=D3*/ 21, /*RST=D4*/ 3, /*BUSY=D2*/ 2));
struct tm timeinfo;
Calendar calendar(WiFi, display, timeinfo);
Weather weather(WiFi, display, timeinfo);

const char* ssid = "TIM-62244755_2.4GEXT";                      // const char* ssid = "GalaxyA53";
const char* password = "RDe7AYX3SRf3F4zH4RKfUtc6";              // const char* password = "aaaaaaaa";


void setup() {
  Serial.begin(9600);
  display.init(115200, true, 2, false);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  //esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, 0); 
  //esp_sleep_enable_timer_wakeup(300 * 1000000);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  configTime(3600, 3600, "pool.ntp.org");
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_BLACK);
    calendar.drawCalendar();        //ATTENTO LA DASHBOARD VIENE DISEGNATA NEL CALENDARIO, FAI UNA FUNZIONE A PARTE
    weather.drawInternalInfo();
  } while (display.nextPage());
}

void loop() {

  //delay(10000000); 
  //esp_deep_sleep_start();
}