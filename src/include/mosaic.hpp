#pragma once


#include "options.hpp"

class MosaicModules;

class MosaicPublic {
	protected:
		static MosaicPublic *instance;
		MosaicModules *_modules;
		bool _running;
	
	public:
		static MosaicPublic *getInstance() {
			return MosaicPublic::instance;
		}
		
		MosaicPublic();
		//virtual void pause() = 0;
		virtual void stop() = 0;
		//virtual void upgrade() = 0;
};

#define MOS MosaicPublic::getInstance()

