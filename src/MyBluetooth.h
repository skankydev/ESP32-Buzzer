#ifndef DEF_MYBLUETOOTH
#define DEF_MYBLUETOOTH

#include "setting.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "StatusManager.h"


class MyBluetooth{

	private:
		static MyBluetooth* instance;
		MyBluetooth();

		bool _isConnected;
		bool _isNotified;

		//String _batteryLvl;

		BLEServer *_server;
		BLEService *_service;
		BLECharacteristic* _notifieur;
		BLECharacteristic* _battery;
		BLECharacteristic* _status;

		StatusManager* statusManager;

	public:
		static MyBluetooth* getInstance();
		void init();
		void sendNotif();
		bool setConnected();
		bool setDisconnected();
		bool isConnected();

		void setBatteryLvl(float lvl);
};


#endif
