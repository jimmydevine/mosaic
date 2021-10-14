#include <csignal>
#include <unistd.h>
#include "mosaic.hpp"
#include "modules.hpp"
#include "interfaces/com.jiffe.mosaic/loggable.hpp"


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
class MosaicRuntime : public MosaicPublic {
	private:
		int loop();
	
	public:
		static MosaicRuntime *getInstance();
		static void signalHandler(int signum);
		int run(int argc, char **argv);
		void stop();
};

/***********************************************************************************************************************************
* Define the initial state of the MosaicPublic singleton instance
***********************************************************************************************************************************/
MosaicPublic* MosaicPublic::instance = nullptr;


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
MosaicRuntime *MosaicRuntime::getInstance() {
	if (MosaicRuntime::instance == NULL)
	{
		MosaicRuntime::instance = new MosaicRuntime();
	}
	return static_cast<MosaicRuntime *>(MosaicRuntime::instance);
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
void MosaicRuntime::signalHandler(int signum) {
	switch (signum)
	{
		case SIGKILL:
		case SIGTERM:
		case SIGINT:
			MOS->stop();
			break;
	}
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
void MosaicRuntime::stop() {
	this->_running = false;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
int MosaicRuntime::loop() {
	return 0;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
int MosaicRuntime::run(int argc, char **argv) {
	int result;
	
	try
	{
		OPT->load(argc, argv);
		this->_modules->load();
	}
	catch(Mosaic::Throwable t)
    {
        t.display();
		return -1;
    }
	
	signal(SIGKILL, MosaicRuntime::signalHandler); 
	signal(SIGINT, MosaicRuntime::signalHandler); 
	signal(SIGTERM, MosaicRuntime::signalHandler); 
	
	while (this->_running)
	{
		result = this->loop();
		if (result < 0)
		{
			break;
		}
		if (result == 0)
		{
			usleep(1000);
		}
	}
	
	DEBUG1("Kernel is stopped...");
	
	return 0;
}



/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
int main(int argc, char **argv) {
    return MosaicRuntime::getInstance()->run(argc, argv);
}

