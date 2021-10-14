#include "modules.hpp"
#include "options.hpp"
#include "interfaces/com.jiffe.mosaic/loggable.hpp"


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
MosaicModules::MosaicModules() {
    
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
void MosaicModules::load() {
	DEBUG3("MosaicModules::load ", MosaicOptions::getInstance().getConfigJSON("module_path"));
    /*for (auto config_module : CFG->modules())
    {
        this->loadModule(config_module.filepath());
    }*/
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
void MosaicModules::loadModule(std::string filepath) {
	DEBUG1("Loading module " + filepath);
		
	Importable *module = new Importable(filepath);
	
	this->_modules.push_back(module);
	this->_module_filepaths[filepath] = module;
	this->_module[module->name()][module->version()] = module;
	
	if (this->_module[module->name()].find(0) == this->_module[module->name()].end() ||
		this->_module[module->name()][0]->version() < module->version())
	{
		this->_module[module->name()][0] = module;
	}
	
	DEBUG1("Loaded module " + module->name() + " v" + module->versionString() + ", lang " + module->langauge());
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
void MosaicModules::unload() {
    this->_modules.clear();
    this->_module_filepaths.clear();
    this->_module.clear();
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
JSON MosaicModules::list() {
	JSON modules = JSON::array();
	
	for (auto [module_name, versions] : this->_module)
	{
		modules.push_back(module_name);
	}
	
	return modules;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
JSON MosaicModules::versions(std::string module_name) {
	if (this->_module.find(module_name) == this->_module.end())
	{
		return nullptr;
	}
	JSON versions = JSON::array();
	for (auto [version, importable] : this->_module[module_name])
	{
		if (version == 0)
		{
			continue;
		}
		versions.push_back(version);
	}
	return versions;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
JSON MosaicModules::versionsString(std::string module_name) {
	if (this->_module.find(module_name) == this->_module.end())
	{
		return nullptr;
	}
	JSON versions = JSON::array();
	for (auto [version, importable] : this->_module[module_name])
	{
		if (version == 0)
		{
			continue;
		}
		versions.push_back(importable->versionString());
	}
	return versions;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
Importable *MosaicModules::module(std::string module_name, uint32_t module_version) {
    if (this->_module.find(module_name) != this->_module.end())
    {
        if (this->_module[module_name].find(module_version) != this->_module[module_name].end())
        {
            return this->_module[module_name][module_version];
        }
    }
    return NULL;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
Importable *MosaicModules::module(std::string module_name, std::string module_version) {
	int version = Importable::versionToInt(module_version);
    if (this->_module.find(module_name) != this->_module.end())
    {
        if (this->_module[module_name].find(version) != this->_module[module_name].end())
        {
            return this->_module[module_name][version];
        }
    }
    return NULL;
}

