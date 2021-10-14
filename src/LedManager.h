#ifndef DEF_LEDMANAGER
#define DEF_LEDMANAGER

#include "setting.h"
#include <ESP32Ticker.h>

class LedManager{

	private:
		static LedManager* instance;
		LedManager();

		int _redPin;
		int _greenPin;
		int _buzzerPin;

		Ticker* blinker;

	public:
		static LedManager* getInstance();
		
		int _redStatus;
		int _greenStatus;
		int _buzzerStatus;

		void init();
		void step();
		
		void startBlinkerRed();
		void blinkRed();

		void startBlinkerGreen();
		void blinkGreen();

		void startBlinkerBuzzer();
		void blinkBuzzer();

		void stopBlinker();
};


#endif
