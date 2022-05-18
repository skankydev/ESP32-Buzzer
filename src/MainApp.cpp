#include "MainApp.h"

/**
 * constructeur
 */
MainApp::MainApp(){

	//l entrée analoge pour le nv de baterie
	_battery = BATTERY;

	_btnIn = BUTTON_IN;

	myBluetooth   = MyBluetooth::getInstance();
	ledManager    = LedManager::getInstance();
	statusManager = StatusManager::getInstance();
}

void MainApp::init(){
	Serial.begin(115200);
	Serial.println("Beerover Buzzer");

	//
	pinMode(_btnIn, INPUT);

	ledManager->init();
	statusManager->init();
	myBluetooth->init();
}

/**
 * action effectuer a chaque etatpe de loop
 * @return {void} rien
 */
void MainApp::step(){
	ledManager->step();
	
	uint16_t v = analogRead(_battery);
	float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (1100 / 1000.0);
	myBluetooth->setBatteryLvl(battery_voltage);
	

	if(statusManager->getStatus() == "wait"){
		this->stepReady();
	}
}

void MainApp::stepReady(){

	int btnStatus = digitalRead(_btnIn);
	if (btnStatus == HIGH) {
		myBluetooth->sendNotif();
		ledManager->greenStatus = HIGH;
	}else if (btnStatus == LOW) {
		ledManager->greenStatus = LOW;
	};

}

