#ifndef DEF_MAINAPP
#define DEF_MAINAPP


#include "setting.h"

class MainApp { //création nouvelle classe MainApp

	private:
		int _ledPin;

	public:
		MainApp();
		void init();
		void step();
};

#endif
