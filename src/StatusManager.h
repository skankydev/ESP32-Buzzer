#ifndef DEF_STATUSMANAGER
#define DEF_STATUSMANAGER

#include "setting.h"
#include "LedManager.h"


class StatusManager
{
	private:

		static StatusManager* instance;
		LedManager* ledManager;

		StatusManager();
		String _status;

	public:
		static StatusManager* getInstance();
		void init();
		void setStatus(String status);
		String getStatus();

};

#endif