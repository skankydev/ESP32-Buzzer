#include "MainApp.h"

/**
 * constructeur
 */
MainApp::MainApp(){
	//Led Bleu de la carte : pin5 GPIO5
	



	//l entrée analoge pour le nv de baterie
	_battery = BATTERY;

	_btnIn = BUTTON_IN;
	_btnOldStatus = LOW;

	myBluetooth = MyBluetooth::getInstance();
	_oldBlueToothStatus = false;

	ledManager = LedManager::getInstance();

}

void MainApp::init(){
	Serial.begin(115200);
	Serial.println("beerover buzzer");

	//pinMode(_btnIn, INPUT);

	myBluetooth->init();
	ledManager->init();
}

/**
 * action effectuer a chaque etatpe de loop
 * @return {void} rien
 */
void MainApp::step(){
	ledManager->step();
	
	uint16_t v = analogRead(_battery);
	float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (1100 / 1000.0);
	Serial.println("DEBUG: Value: " + String(v) + " ,Battery Voltage is " + String(battery_voltage) + "V");

	
	if(myBluetooth->isConnected()){
		this->stepReady();
	}
}

void MainApp::stepReady(){

	int btnStatus = digitalRead(_btnIn);
	if (btnStatus == HIGH && _btnOldStatus != btnStatus) {
		myBluetooth->sendNotif();
		ledManager->_greenStatus = HIGH;
	}

	if (btnStatus == LOW && _btnOldStatus != btnStatus) {
		ledManager->_greenStatus = LOW;
	}
	_btnOldStatus = btnStatus;

}


void MainApp::stepDisconected(){

}
