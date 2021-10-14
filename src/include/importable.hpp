#pragma once


#include <string>
#include "exportable.hpp"


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
class Importable {
	private:
		std::string _filepath;
		void *module;
		
	public:
		Importable(std::string filepath);
		~Importable();
		
		Mosaic::Exportable *exported;
		
		Mosaic::createConfig_t *createConfig;
		Mosaic::createInstance_t *createInstance;
		
		Mosaic::destroyConfig_t *destroyConfig;
		Mosaic::destroyInstance_t *destroyInstance;
		
		std::string name();
		uint32_t version();
		std::string versionString();
		static std::string versionToString(uint32_t version);
		static uint32_t versionToInt(std::string version_str);
		std::string langauge();
		JSON definition();
};

