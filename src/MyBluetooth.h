#ifndef DEF_MYBLUETOOTH
#define DEF_MYBLUETOOTH

#include "setting.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "LedManager.h"


class MyBluetooth{

	private:
		static MyBluetooth* instance;
		MyBluetooth();
		bool _isConnected;
		bool _isNotified;

		BLEServer *_server;
		BLEService *_service;
		BLECharacteristic* _notifieur;

		LedManager* ledManager;


	public:
		static MyBluetooth* getInstance();
		void init();
		void sendNotif();
		bool setConnected();
		bool setDisconnected();
		bool isConnected();
};


#endif
