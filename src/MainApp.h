#ifndef DEF_MAINAPP
#define DEF_MAINAPP


#include "setting.h"
#include "MyBluetooth.h"
#include "LedManager.h"



class MainApp { //création nouvelle classe MainApp

	private:
		MyBluetooth* myBluetooth;
		bool _oldBlueToothStatus;

		LedManager* ledManager;

		int _btnIn;
		
		int _btnOldStatus;

		int _battery;

	public:
		MainApp();
		void init();
		void step();

		void stepReady();
		void stepDisconected();

};

#endif
