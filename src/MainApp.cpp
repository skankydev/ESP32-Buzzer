#include "MainApp.h"

/**
 * constructeur
 */
MainApp::MainApp(){

	//l entrée analoge pour le nv de baterie
	//_battery = BATTERY;

	_btnIn = BUTTON_IN;
	_btnA = BUTTON_A;
	_btnB = BUTTON_B;
	_btnC = BUTTON_C;
	_btnD = BUTTON_D;

	myBluetooth   = MyBluetooth::getInstance();
	ledManager    = LedManager::getInstance();
	statusManager = StatusManager::getInstance();
}

void MainApp::init(){
	Serial.begin(115200);
	Serial.println("Beerover Buzzer");

	//
	pinMode(_btnIn, INPUT);
	pinMode(_btnA, INPUT);
	pinMode(_btnB, INPUT);
	pinMode(_btnC, INPUT);
	pinMode(_btnD, INPUT);

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
	
	// uint16_t v = analogRead(_battery);
	// float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (1100 / 1000.0);
	// myBluetooth->setBatteryLvl(battery_voltage);
	

	if(statusManager->getStatus() == "wait"){
		this->stepReady();
	}else if(statusManager->getStatus() == "choice"){
		this->stepChoice();
	}
}

void MainApp::stepReady(){

	int btnStatus = digitalRead(_btnIn);
	if (btnStatus == HIGH) {
		myBluetooth->sendNotif("main");
		//ledManager->greenStatus = HIGH;
	};
}

void MainApp::stepChoice(){
	int btnStatus = digitalRead(_btnA);
	if (btnStatus == HIGH) {
		myBluetooth->sendNotif("btnA");
		//ledManager->greenStatus = HIGH; 
	}
	btnStatus = digitalRead(_btnB);
	if (btnStatus == HIGH) {
		myBluetooth->sendNotif("btnB");
		//ledManager->greenStatus = HIGH;
	}
	btnStatus = digitalRead(_btnC);
	if (btnStatus == HIGH) {
		myBluetooth->sendNotif("btnC");
		//ledManager->greenStatus = HIGH;
	}
	btnStatus = digitalRead(_btnD);
	if (btnStatus == HIGH) {
		myBluetooth->sendNotif("btnD");
		//ledManager->greenStatus = HIGH;
	}
}
