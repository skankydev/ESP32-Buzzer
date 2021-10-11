#include "LedManager.h"

void blinkerRed(LedManager* ledManager){
	ledManager->blinkRed();
}

void blinkerGreen(LedManager* ledManager){
	ledManager->blinkGreen();
}

LedManager* LedManager::instance = nullptr;

LedManager* LedManager::getInstance(){
	if(!instance){
		instance = new LedManager;
	}
	return instance;
}


LedManager::LedManager(){

	_redPin = RED;
	_greenPin = GREEN;

	_redStatus = LOW;
	_greenStatus = LOW;

	blinker = new Ticker;
}



void LedManager::init(){
	pinMode(_redPin, OUTPUT);
	pinMode(_greenPin,OUTPUT);

	digitalWrite(_redPin, LOW);
	digitalWrite(_greenPin, LOW);
}

void LedManager::step(){
	digitalWrite(_redPin, _redStatus);
	digitalWrite(_greenPin, _greenStatus);
}

void LedManager::stopBlinker(){
	blinker->detach();
}

void LedManager::startBlinkerRed(){
	blinker->detach();
	blinker->attach_ms(500, blinkerRed,this);
}

void LedManager::blinkRed() {
	if(_redStatus == LOW){
		_redStatus = HIGH;
	}else{
		_redStatus = LOW;
	}
}

void LedManager::startBlinkerGreen(){
	blinker->detach();
	blinker->attach_ms(500, blinkerGreen,this);
}

void LedManager::blinkGreen() {
	if(_greenStatus == LOW){
		_greenStatus = HIGH;
	}else{
		_greenStatus = LOW;
	}
}

