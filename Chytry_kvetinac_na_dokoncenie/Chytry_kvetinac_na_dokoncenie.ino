 #include <WEMOS_SHT3X.h>

#include <OLEDDisplay.h>
#include <OLEDDisplayFonts.h>
#include <OLEDDisplayUi.h>
#include <SH1106.h>
//#include <SH1106Brzo.h>
#include <SH1106Spi.h>
#include <SH1106Wire.h>
#include <SSD1306.h>
//#include <SSD1306Brzo.h>
#include <SSD1306I2C.h>
#include <SSD1306Spi.h>
#include <SSD1306Wire.h>

SHT3X sht30(0x45);
//OLED display init using i2c
SSD1306Wire display(0x3c, SDA, SCL);

char buff[30];
char buffpudy[30];
int analogValue = 0;
int analogVolts = 0;
float floatVolts = 0.0;


void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  Serial.begin(115200);
  Wire.begin();
  display.init();
  display.setContrast(255);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.display();
}

void loop() {

  analogVolts = analogReadMilliVolts(39);
    floatVolts = analogVolts/1000.0;

    if(floatVolts > 2.6     ) {
      snprintf(buffpudy, 20, "Kvetina: sucha");
    }
    else if (floatVolts <   2.0  )
    {
      snprintf(buffpudy, 20, "Kvetina: prelita");
    }
    else
    {
      snprintf(buffpudy, 20, "Kvetina: zalita");
    }

  if(sht30.get()==0) {
      display.clear();
      
      snprintf(buff, 20, "Teplota: %.1f °C", sht30.cTemp);
      display.drawString(0, 0, buff);

      snprintf(buff, 20, "Vlhkost: %.1f %%", sht30.humidity);
      display.drawString(0, 16, buff);

      display.drawString(0, 32, buffpudy);

      display.display();
  }
  else
  {
    sprintf(buff, "Error!");
    display.drawString(32, 0, buff);
    display.display();
    
    delay(2000);
  }

  // print out the values you read:
  Serial.printf("ADC volts value = %f\n", floatVolts);

  
  delay(100);  // delay in between reads for clear read from serial

}
