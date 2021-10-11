#include "MyBluetooth.h"


class EtatServeur : public BLEServerCallbacks 
{


	void onConnect(BLEServer* pServer){
		MyBluetooth* myBluetooth = MyBluetooth::getInstance();
		myBluetooth->setConnected();
	}

	void onDisconnect(BLEServer* pServer){
		MyBluetooth* myBluetooth = MyBluetooth::getInstance();
		myBluetooth->setDisconnected();
	}
};


MyBluetooth* MyBluetooth::instance = nullptr;

MyBluetooth* MyBluetooth::getInstance(){
	if(!instance){
		instance = new MyBluetooth;
	}
	return instance;
}


MyBluetooth::MyBluetooth(){
	_isConnected = false;
	_isNotified = false;
	ledManager = LedManager::getInstance();

}

void MyBluetooth::init(){
	Serial.println("Test BLE init");
	BLEDevice::init("Beerover Buzzer");
	//BLEDevice::getAddress(); // Retrieve our own local BD BLEAddress
	_server = BLEDevice::createServer();
	_server->setCallbacks(new EtatServeur());
	
	_service = _server->createService(SERVICE_UUID);
	
	_notifieur = _service->createCharacteristic(CHARACTERISTIC_UUID,
		BLECharacteristic::PROPERTY_READ |
		BLECharacteristic::PROPERTY_WRITE  |
		BLECharacteristic::PROPERTY_NOTIFY |
		BLECharacteristic::PROPERTY_INDICATE);
	_notifieur->addDescriptor(new BLE2902());

	_service->start();
	_server->getAdvertising()->start();
	Serial.println("Test BLE wait connection");
	ledManager->startBlinkerRed();
}

void MyBluetooth::sendNotif(){
	
	_notifieur->setValue("Bonjour"); // la nouvelle valeur du compteur
	_notifieur->notify();
	//delay(1000);
}

bool MyBluetooth::setConnected(){
	ledManager->stopBlinker();
	_isConnected = true;
	return _isConnected;
}
bool MyBluetooth::setDisconnected(){
	ledManager->startBlinkerRed();
	_isConnected = false;
	return _isConnected;
}

bool MyBluetooth::isConnected(){
	return _isConnected;
}