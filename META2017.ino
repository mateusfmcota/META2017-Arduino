#include <Wire.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

unsigned long time;
unsigned long time2 = 0;

const int analogIn = A0;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue = 0;
int ACSoffset = 2500;
double Tensao = 0;
double Corrente = 0;


void setup()
{
	Serial.begin(9600);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop()
{
	time = millis();

	RawValue = analogRead(analogIn);
	Tensao = (RawValue / 1024.0) * 5000;
	Corrente = ((Tensao - ACSoffset) / mVperAmp);

	if ((unsigned long)(time - time2) >= 500) {
		display.clearDisplay();

		display.setTextColor(WHITE);

		display.setTextSize(1);
		display.setCursor(0, 0);
		display.println("Tensao: ");
		display.setCursor(60, 0);
		if(Tensao<1000)
			display.println((String)Tensao + " mV");
		else 
			display.println((String)(Tensao/1000) + " V");

		display.setCursor(0, 10);
		display.print("Corrente: ");
		display.setCursor(60, 10);
		if (Corrente < 1000) {
			display.println((String)Corrente + " mA");
		}
		else if (Corrente >= 1000)
		{
			display.println((String)(Corrente / 1000) + " A");
		}

		long potencia = Tensao * Corrente;

		display.setCursor(0, 20);
		display.print("Watts: ");
		display.setCursor(60, 20);
		if (potencia < 1000)
			display.println((String)potencia + "  mW");
		else if (potencia >= 1000)
			display.println((String)potencia + "  W");

		display.drawLine(0, 8, 128, 8, 1);

		display.drawLine(55, 0, 55, 32, 1);

		display.drawLine(0, 18, 128, 18, 1);

		display.display();
		time2 = millis();
	}

	Serial.println((String)Tensao + "/" + (String)Corrente);

}






