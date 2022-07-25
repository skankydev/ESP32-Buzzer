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

		int _btnA;
		int _btnB;
		int _btnC;
		int _btnD;

	public:
		MainApp();
		void init();
		void step();

		void stepReady();
		void stepChoice();

};

#endif
