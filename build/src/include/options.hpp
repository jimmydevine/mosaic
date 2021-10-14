#pragma once


#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include "global.hpp"


#define MOSAIC_RUNTIME_VERSION_MAJOR 1
#define MOSAIC_RUNTIME_VERSION_MINOR 0
#define MOSAIC_RUNTIME_VERSION_REVISION 0
#define MOSAIC_RUNTIME_INSTALL_PREFIX "/home/jiffe/.local"
#define MOSAIC_RUNTIME_BINARY_DIR "/home/jiffe/mosaic/build"
#define MOSAIC_CONFIG_DIR "/home/jiffe/.local/etc/mosaic"
#define MOSAIC_DATA_DIR "/home/jiffe/.local/var/lib/mosaic"
#define MOSAIC_MODULE_DIR "/home/jiffe/.local/lib/mosaic"

/* #undef MOSAIC_RUNTIME_OPTION_RESET */

namespace fs = std::filesystem;


enum MosaicOptionType {
	MosaicOptionTypeNone=0,
	MosaicOptionTypeBool,
	MosaicOptionTypeInt,
	MosaicOptionTypeString,
};

/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
struct MosaicOption {
	MosaicOptionType type;
	bool required;
	char short_identifier;
	std::string long_identifier;
	std::string option_description;
	bool param_optional;
	std::string param_description;
	std::string default_value;
	std::string optional_default_value;
};


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
class MosaicImportableDetails {
	private:
		std::string _filepath;
		JSON _details;
	
	public:
		MosaicImportableDetails(std::string directory, std::string filepath, JSON details) {
			fs::path path = fs::path(directory);
			path /= filepath;
			this->_filepath = path;
			this->_details = details;
		}
        std::string filepath() { return this->_filepath; }
		JSON details() { return this->_details; }
};


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
class MosaicOptions {
	
	private:
		static MosaicOptions *instance;
        std::string program_name;
		std::string _system_name;
		std::string _task_name;
        
        /* options */
		JSON _options;
		JSON _config;
		
		JSON _systems;
		std::map<std::string, int> _debug;
		bool _reset;
		bool _create;
		
		
        std::vector<MosaicImportableDetails> _modules;
		std::vector<MosaicImportableDetails> _languages;
        JSON _storage;
		
		MosaicOptions();
        void loadCommandLine(std::vector<MosaicOption> &options, int argc, char **argv);
        void loadConfigFiles();
		int usage(std::vector<MosaicOption> &options, std::string error);
        int version();
		void loadConfig();
	
	public:
		static MosaicOptions *getInstance();
		
		void load(int argc, char **argv);
		void setConfig(const JSON &config);
		
		bool reset();
		bool create();
		
        std::string getVersionString();
        std::vector<MosaicImportableDetails> modules() { return this->_modules; }
        JSON storage();
		
		JSON getConfigJSON(std::string path);
		JSON getTaskConfig();
		
		bool getBooleanOption(std::string option_name);
		int getIntegerOption(std::string option_name);
		std::string getStringOption(std::string option_name);
		
		JSON getOption(std::string option_name) {
			if (this->_options.find(option_name) == this->_options.end())
			{
				THROW("Failed to find option ", option_name);
			}
			return this->_options[option_name];
		}
};


#define OPT MosaicOptions::getInstance()

