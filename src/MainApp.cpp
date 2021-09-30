#include "MainApp.h"

/**
 * constructeur
 */
MainApp::MainApp(){
	//Led Bleu de la carte : pin5 GPIO5
	_ledPin = 5;
	//l entrée analoge pour le nv de baterie
	_battery = 35;

}

void MainApp::init(){

	Serial.begin(38400);
	pinMode(_ledPin, OUTPUT);

}

/**
 * action effectuer a chaque etatpe de loop
 * @return {void} rien
 */
void MainApp::step(){
	Serial.println("Coucou");
	delay(1000);

	digitalWrite(_ledPin, HIGH);
	Serial.println("On");
	delay(1000);

	digitalWrite(_ledPin, LOW);
	Serial.println("Off");
	delay(1000);

	uint16_t v = analogRead(_battery);
	float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (1100 / 1000.0);
	Serial.println("DEBUG: Value: " + String(v) + " ,Battery Voltage is " + String(battery_voltage) + "V");

}
