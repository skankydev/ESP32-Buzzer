#include "LedManager.h"

void blinkerRed(LedManager* ledManager){
	ledManager->blinkRed();
}

void blinkerGreen(LedManager* ledManager){
	ledManager->blinkGreen();
}

void blinkerBuzzer(LedManager* ledManager){
	ledManager->blinkBuzzer();
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
	_buzzerPin = BUZZER_LED;

	redStatus = LOW;
	greenStatus = LOW;
	buzzerStatus = HIGH;

	blinker = new Ticker;
}



void LedManager::init(){
	Serial.println("LedManager init");
	pinMode(_redPin, OUTPUT);
	pinMode(_greenPin,OUTPUT);
	pinMode(_buzzerPin,OUTPUT);

	digitalWrite(_redPin, redStatus);
	digitalWrite(_greenPin, greenStatus);
	digitalWrite(_buzzerPin, buzzerStatus);
}

void LedManager::step(){
	digitalWrite(_redPin, redStatus);
	digitalWrite(_greenPin, greenStatus);
	digitalWrite(_buzzerPin, buzzerStatus);
}

void LedManager::stopBlinker(){
	blinker->detach();
}

void LedManager::startBlinkerRed(){
	blinker->detach();
	blinker->attach_ms(500, blinkerRed,this);
}

void LedManager::blinkRed() {
	if(redStatus == LOW){
		redStatus = HIGH;
	}else{
		redStatus = LOW;
	}
}

void LedManager::startBlinkerGreen(){
	blinker->detach();
	blinker->attach_ms(500, blinkerGreen,this);
}

void LedManager::blinkGreen() {
	if(greenStatus == LOW){
		greenStatus = HIGH;
	}else{
		greenStatus = LOW;
	}
}

void LedManager::startBlinkerBuzzer(){
	blinker->detach();
	blinker->attach_ms(500, blinkerBuzzer,this);
}

void LedManager::blinkBuzzer(){
	if(buzzerStatus == LOW){
		buzzerStatus = HIGH;
	}else{
		buzzerStatus = LOW;
	}
}