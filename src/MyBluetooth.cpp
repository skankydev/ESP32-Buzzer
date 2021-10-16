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

class StatusUpdate: public BLECharacteristicCallbacks{
	void onWrite(BLECharacteristic *status) {
		//MyBluetooth* myBluetooth = MyBluetooth::getInstance();
		std::string tmp = status->getValue();
		String value = "";
		for (int i = 0; i < tmp.length(); i++) {
			value += String(tmp[i]);
		}

		Serial.println("BLE Callbacks :");
		Serial.println(value);

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
	
	_notifieur = _service->createCharacteristic(NOTIFIEUR_UUID,
		BLECharacteristic::PROPERTY_READ |
		BLECharacteristic::PROPERTY_WRITE  |
		BLECharacteristic::PROPERTY_NOTIFY |
		BLECharacteristic::PROPERTY_INDICATE);
	_notifieur->addDescriptor(new BLE2902());

	_battery = _service->createCharacteristic(BATTERY_UUID,
		BLECharacteristic::PROPERTY_READ );
	_battery->addDescriptor(new BLE2902());

	_status = _service->createCharacteristic(STATUS_UUID,
		BLECharacteristic::PROPERTY_READ |
		BLECharacteristic::PROPERTY_WRITE);
	_status->addDescriptor(new BLE2902());
	_status->setCallbacks(new StatusUpdate());
	
	

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
	ledManager->_redStatus = LOW;
	_isConnected = true;
	return _isConnected;
}
bool MyBluetooth::setDisconnected(){
	ledManager->startBlinkerRed();
	_isConnected = false;
	_server->getAdvertising()->start();
	return _isConnected;
}

bool MyBluetooth::isConnected(){
	return _isConnected;
}

void MyBluetooth::setBatteryLvl(float lvl){
	
	char txString[8]; 
	dtostrf(lvl, 2, 2, txString);
	_battery->setValue(txString);
}
