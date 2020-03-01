#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int ventilator = 34;
int ledoranje = 35;
int ledrood = 32;

void setup() {
  pinMode(ventilator, OUTPUT);
  pinMode(ledoranje, OUTPUT);
  pinMode(ledrood, OUTPUT);
  Serial.begin(9600);
                                                                                      // Oled display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

//  bmp_temp->printSensorDetails();
  delay(2000);

  
}

void loop() {

int T =  bmp.readTemperature();


delay(200);

 if(T < 0){
  
  digitalWrite(ledrood,HIGH);
  digitalWrite(ledoranje,LOW);
  digitalWrite(ventilator, LOW);
  delay(500);
  digitalWrite(ledrood,LOW);
  digitalWrite(ledoranje,LOW);
  digitalWrite(ventilator, LOW);
  
 }
if(T > 0 && T < 24){
  digitalWrite(ledoranje, HIGH);
  digitalWrite(ledrood, LOW);
  digitalWrite(ventilator, LOW);
  
}
if(T > 24 && T < 26){
  digitalWrite(ledoranje, LOW);
  digitalWrite(ledrood, LOW);
  digitalWrite(ventilator, LOW);
  
}
if(T > 26){
  digitalWrite(ledrood, LOW);
  digitalWrite(ledoranje, LOW);
  digitalWrite(ventilator, HIGH);
}
  display.clearDisplay();

  

 sensors_event_t temp_event, pressure_event;   // digitale sensor BMP
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
  Serial.print(F("Temperature = "));
  Serial.print(T);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");
  
  Serial.println();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("temperatuur BMP280: ");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  display.println(temp_event.temperature);
  display.display();
  
 if(T < 0){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Datakabel onderbroken");

  
 }
   


}
