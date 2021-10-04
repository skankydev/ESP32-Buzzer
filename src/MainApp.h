#ifndef DEF_MAINAPP
#define DEF_MAINAPP


#include "setting.h"
#include "BluetoothSerial.h"

class MainApp { //création nouvelle classe MainApp

	private:
		int _ledPin;
		int _battery;
		BluetoothSerial* bleuSerial;

	public:
		MainApp();
		void init();
		void step();
		String readBleu();
};

#endif
