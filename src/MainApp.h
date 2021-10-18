#ifndef DEF_MAINAPP
#define DEF_MAINAPP


#include "setting.h"
#include "MyBluetooth.h"
#include "LedManager.h"
#include "StatusManager.h"


class MainApp { //création nouvelle classe MainApp

	private:
		MyBluetooth* myBluetooth;
		LedManager* ledManager;
		StatusManager* statusManager;

		int _btnIn;
		int _battery;

	public:
		MainApp();
		void init();
		void step();

		void stepReady();

};

#endif
