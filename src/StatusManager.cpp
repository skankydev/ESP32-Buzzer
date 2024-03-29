#include "StatusManager.h"


StatusManager* StatusManager::instance = nullptr;

StatusManager* StatusManager::getInstance(){
	if(!instance){
		instance = new StatusManager;
	}
	return instance;
}


StatusManager::StatusManager(){
	_status = "";
	ledManager = LedManager::getInstance();
}


void StatusManager::init(){
	ledManager->stopBlinker();
	ledManager->greenStatus = LOW;
	ledManager->redStatus = LOW;
	ledManager->buzzerStatus = LOW;

	//Serial.println("StatusManager init");
}

void StatusManager::setStatus(String status){
	Serial.println("StatusManager status : "+status);
	if(_status != status){
		_status = status;

		this->init();

		if(_status == F("disconected")){
			ledManager->startBlinkerRed();

		}else if(_status == F("sleep")){
			ledManager->greenStatus = HIGH;
			ledManager->redStatus = HIGH;
			ledManager->buzzerStatus = LOW;
		}else if(_status == F("wait")){
			ledManager->greenStatus = HIGH;
			ledManager->redStatus = LOW;
			ledManager->buzzerStatus = LOW;
			ledManager->startBlinkerBuzzer();
		}else if(_status == F("choice")){
			ledManager->greenStatus = LOW;
			ledManager->redStatus = LOW;
			ledManager->buzzerStatus = HIGH;
			ledManager->startBlinkerGreen();
		}else if(_status == F("win")){
			ledManager->greenStatus = HIGH;
			ledManager->redStatus = LOW;
			ledManager->buzzerStatus = HIGH;

		}else if(_status == F("lost")){
			ledManager->redStatus = HIGH;
		}else{
			ledManager->startBlinkerBuzzer();
		}
	}
}

String StatusManager::getStatus(){
	return _status;
}