//===================================================================================================================

//#define DISPLAY_SSD1306Wire
#include <stdlib.h>
#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID        "110a4526-2552-11ec-9621-0242ac130002"
#define CHARACTERISTIC_UUID "243b1e7c-2552-11ec-9621-0242ac130002"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;

#define NOTIFY_CHARACTERISTIC

bool estConnecte = false;
bool etaitConnecte = false;
uint8_t valeur = 0; // le compteur

class EtatServeur : public BLEServerCallbacks 
{
	void onConnect(BLEServer* pServer){
		estConnecte = true;
	}

	void onDisconnect(BLEServer* pServer){
		estConnecte = false;
	}
};



void setup() 
{
	Serial.begin(115200);
	Serial.println("Test BLE init");

	BLEDevice::init("BeeroverBuzzer");
	//BLEDevice::getAddress(); // Retrieve our own local BD BLEAddress
	pServer = BLEDevice::createServer();
	pServer->setCallbacks(new EtatServeur());
	
	BLEService *pService = pServer->createService(SERVICE_UUID);
	
	pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID,
		BLECharacteristic::PROPERTY_READ |
		BLECharacteristic::PROPERTY_WRITE  |
		BLECharacteristic::PROPERTY_NOTIFY |
		BLECharacteristic::PROPERTY_INDICATE);
	pCharacteristic->addDescriptor(new BLE2902());

	pService->start();

	pServer->getAdvertising()->start();
	//BLEAdvertising *pAdvertising = pServer->getAdvertising();
	//pAdvertising->start();
	Serial.println("Test BLE start advertising");

	Serial.println("Test BLE wait connection");

}

void loop() 
{
	if (estConnecte) 
	{ 
		//pCharacteristic->setValue(&valeur, 1); // la nouvelle valeur du compteur
		pCharacteristic->setValue("Bonjour !!"); // la nouvelle valeur du compteur
		pCharacteristic->notify();
		delay(1000); // bluetooth stack will go into congestion, if too many packets are sent

		String datas(valeur);
		//Serial.println("BLE notify");
		Serial.printf("BLE notify : %d\n", valeur);
				
		valeur++; // on compte ...
	}

	if (!estConnecte && etaitConnecte) 
	{
		Serial.println("BLE deconnection");
		delay(500); // give the bluetooth stack the chance to get things ready
		
		pServer->startAdvertising(); // restart advertising
		Serial.println("BLE restart advertising");

		Serial.println("Test BLE wait connection");
		
		
		etaitConnecte = estConnecte;
	}
	// connectÃ© ?
	if (estConnecte && !etaitConnecte) 
	{
		Serial.println("BLE connection");
		etaitConnecte = estConnecte;
	}
}


