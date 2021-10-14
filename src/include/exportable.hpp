#pragma once


#include <string>
#include "global.hpp"

class Importable;

namespace Mosaic {
	class Configurable;
    class Instantiable;
    
	typedef Configurable *createConfig_t(Importable *module, std::string field_name, Configurable *parent, const JSON &config);
	typedef Instantiable *createInstance_t(Configurable *config, std::string field_name, Instantiable *parent);
	typedef void destroyConfig_t(Configurable *);
	typedef void destroyInstance_t(Instantiable *);
	
	struct Exportable {
		public:
			JSON _definition;
			
			createConfig_t *_createConfig;
			createInstance_t *_createInstance;
			
			destroyConfig_t *_destroyConfig;
			destroyInstance_t *_destroyInstance;
		
		public:
			JSON definition() { return this->_definition; }
			createConfig_t *createConfig() { return this->_createConfig; }
			createInstance_t *createInstance() { return this->_createInstance; }
			destroyConfig_t *destroyConfig() { return this->_destroyConfig; }
			destroyInstance_t *destroyInstance() { return this->_destroyInstance; }
			
			std::string name() { return this->_definition["name"]; }
			uint32_t version() { return (uint32_t)this->_definition["version"]; }
			std::string language() { return this->_definition["language"]; }
	};
	
	typedef Exportable *export_t();


}

