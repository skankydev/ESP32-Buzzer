#ifndef DEF_LEDMANAGER
#define DEF_LEDMANAGER

#include "setting.h"
#include <ESP32Ticker.h>

class LedManager{

	private:
		static LedManager* instance;
		LedManager();

		int _redPin;
		int _redStatus;



		Ticker* blinker;

	public:
		static LedManager* getInstance();
		
		int _greenPin;
		int _greenStatus;

		void init();
		void step();

		
		void startBlinkerRed();
		void blinkRed();
		void startBlinkerGreen();
		void blinkGreen();

		void stopBlinker();
};


#endif
