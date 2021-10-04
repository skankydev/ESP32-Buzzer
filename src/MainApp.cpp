#include "MainApp.h"
#include "BluetoothSerial.h"

/**
 * constructeur
 */
MainApp::MainApp(){
	//Led Bleu de la carte : pin5 GPIO5
	_ledPin = 5;
	//l entrée analoge pour le nv de baterie
	_battery = 35;
	bleuSerial = new BluetoothSerial;

}

void MainApp::init(){

	Serial.begin(38400);
	bleuSerial->begin("beerover buzzer");
	pinMode(_ledPin, OUTPUT);

	Serial.println("Coucou");
	bleuSerial->println("Coucou");
	digitalWrite(_ledPin, HIGH);
}

/**
 * action effectuer a chaque etatpe de loop
 * @return {void} rien
 */
void MainApp::step(){
	
	uint16_t v = analogRead(_battery);
	float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (1100 / 1000.0);
	Serial.println("DEBUG: Value: " + String(v) + " ,Battery Voltage is " + String(battery_voltage) + "V");
	bleuSerial->println("DEBUG: Value: " + String(v) + " ,Battery Voltage is " + String(battery_voltage) + "V");
	delay(1000);
	
	String message = this->readBleu();
	if(message.length() > 0){
		Serial.println("Message : "+message);
		bleuSerial->println("Message : "+message);
	}

}


String MainApp::readBleu(){
	String message = "";
	while (bleuSerial->available()) {
		char input = (char)bleuSerial->read(); 
		message += String(input);
	}
	return message;
}