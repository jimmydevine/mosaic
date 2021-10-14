#pragma once


#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include "importable.hpp"


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
class MosaicModules {
	private:
		std::vector<Importable *> _modules;
		std::map<std::string, Importable *> _module_filepaths;
		std::map<std::string, std::map<uint32_t,Importable *> > _module;
	
	public:
        MosaicModules();
        void load();
		void loadModule(std::string filepath);
        void unload();
		JSON list();
		JSON versions(std::string module_name);
		JSON versionsString(std::string module_name);
        Importable *module(std::string module_name, uint32_t module_version=0);
		Importable *module(std::string module_name, std::string module_version);
};

