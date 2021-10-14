#include "importable.hpp"
#include "throwable.hpp"


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
Importable::Importable(std::string filepath) {
	this->_filepath = filepath;
	
	this->module = dlopen(this->_filepath.c_str(), RTLD_LAZY);
	if (!this->module)
    {
		THROW("Cannot load module '", filepath, "' library: ", dlerror());
	}
	
	Mosaic::export_t *getExported = (Mosaic::export_t *)dlsym(this->module, "getExported");
	if (getExported == NULL)
	{
		THROW("Cannot load module '", filepath, "', failed to link getExported: ", dlerror());
	}
	
	this->exported = (*getExported)();
	if (this->exported == NULL)
	{
		THROW("Cannot load module '", filepath, "', failed to get exported");
	}
	
	this->createConfig = exported->createConfig();
	this->createInstance = exported->createInstance();
	this->destroyConfig = exported->destroyConfig();
	this->destroyInstance = exported->destroyInstance();
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
Importable::~Importable() {
	
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
std::string Importable::name() {
	return this->exported->name();
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
uint32_t Importable::version() {
	return this->exported->version();
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
std::string Importable::versionString() {
	return Importable::versionToString(this->exported->version());
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
std::string Importable::versionToString(uint32_t version) {
	std::string version_str = std::to_string(version / 1000000);
	version %= 1000000;
	
	version_str += "." + std::to_string(version / 1000);
	version %= 1000;
	
	version_str += "." + std::to_string(version);
	
	return version_str;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
uint32_t Importable::versionToInt(std::string version_str) {
	size_t pos = 0;
	uint32_t version = 0;
	
	pos = version_str.find(".");
	if (pos == std::string::npos)
	{
		THROW("Invalid version string");
	}
	version += std::stoi(version_str.substr(0, pos)) * 1000000;
	version_str.erase(0, pos + 1);
	
	pos = version_str.find(".");
	if (pos == std::string::npos)
	{
		THROW("Invalid version string");
	}
	version += std::stoi(version_str.substr(0, pos)) * 1000;
	version_str.erase(0, pos + 1);
	
	version += std::stoi(version_str);
	
	return version;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
std::string Importable::langauge() {
	return this->exported->language();
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
JSON Importable::definition() {
	return this->exported->definition();
}

