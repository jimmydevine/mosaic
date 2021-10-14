#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <getopt.h>
#include "options.hpp"
#include "json.hpp"
#include "interfaces/com.jiffe.mosaic/loggable.hpp"


/***********************************************************************************************************************************
* Define the initial state of the MosaicConfig singleton instance
***********************************************************************************************************************************/
MosaicOptions* MosaicOptions::instance = NULL;


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
MosaicOptions::MosaicOptions() {
	
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
MosaicOptions *MosaicOptions::getInstance() {
	if (MosaicOptions::instance == NULL)
	{
		MosaicOptions::instance = new MosaicOptions();
	}
	return MosaicOptions::instance;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
int MosaicOptions::usage(std::vector<MosaicOption> &options, std::string error="") {
    if (!error.empty())
    {
        std::cout << "Error: " << error << std::endl;
    }
    
	std::cout << this->program_name << " [-d [<module>:]<level>] ";
	for (auto option : options)
	{
		std::cout << (option.required ? "<" : "[");
		if ((option.short_identifier >= 'a' && option.short_identifier <= 'z') || (option.short_identifier >= 'A' && option.short_identifier <= 'Z'))
		{
			std::cout << "-" << option.short_identifier;
		}
		else
		{
			std::cout << "---" << option.long_identifier;
		}
		if (option.type > MosaicOptionTypeBool)
		{
			std::cout << " " << (option.param_description.empty() ? "<param>" : option.param_description);
		}
		std::cout << (option.required ? "> " : "] ");
	}
	
	std::cout << std::endl << std::endl;
	
	std::sort(std::begin(options), std::end(options), [](auto a, auto b) {return a.short_identifier < b.short_identifier; });
	
	int max_long_size = 0;
	for (auto option : options)
	{
		int size = 0;
		if (!option.long_identifier.empty()) size += option.long_identifier.size();
		if (!option.param_description.empty()) size += option.param_description.size() + 1;
		if (size > max_long_size) max_long_size = size;
	}
	
	for (auto option : options)
	{
		std::cout << "  ";
		if ((option.short_identifier >= 'a' && option.short_identifier <= 'z') || (option.short_identifier >= 'A' && option.short_identifier <= 'Z'))
		{
			std::cout << "-" << option.short_identifier;
		}
		else
		{
			std::cout << "  ";
		}
		int size = 0;
		if (!option.long_identifier.empty())
		{
			if ((option.short_identifier >= 'a' && option.short_identifier <= 'z') || (option.short_identifier >= 'A' && option.short_identifier <= 'Z'))
			{
				std::cout << "|---";
			}
			else
			{
				std::cout << " ---";
			}
			std::cout << option.long_identifier;
			size = option.long_identifier.size();
			if (!option.param_description.empty())
			{
				std::cout << " " << option.param_description;
				size += option.param_description.size() + 1;
			}
		}
		if (!option.option_description.empty())
		{
			std::cout << std::string(max_long_size - size + 4, ' ') << option.option_description;
		}
		std::cout << std::endl;
	}
	
	std::cout << std::endl;
	
    exit(0);
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
int MosaicOptions::version() {
    std::cout << this->program_name + " v" + this->getVersionString() << std::endl;
    return -1;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
void MosaicOptions::load(int argc, char **argv) {
	char *program_name = argv[0];
	char *ptr = program_name;
	while (*ptr)
	{
		if (*ptr == '/') program_name = ptr + 1;
		ptr++;
	}
    this->program_name = std::string(program_name);
	
	std::vector<MosaicOption> options = {
		{ MosaicOptionTypeBool,   false, 0, "create", "Create and initialize mosaic database if needed", false, "", "0" },
#ifdef Mosaic_Runtime_OPTION_RESET
		{ MosaicOptionTypeString, false, 0, "reset",  "Perform a reset of the given module", true, "[<module>]", "", "*" },
#endif
		{ MosaicOptionTypeString, false, 0, "system", "System to run", false, "", "default" },
		{ MosaicOptionTypeString, false, 0, "subsystem", "System to run", false, "", "default" },
		{ MosaicOptionTypeString, false, 0, "task",   "Task to run", false, "", this->program_name },
		
		{ MosaicOptionTypeString, false, 0, "module-path",   "Path to the modules directory", false, "", MOSAIC_MODULE_DIR },
	};
	
	JSON passed_options;
	
	std::string opt_name = "";
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '-' && argv[i][3] != '-')
		{
			char *sptr = argv[i];
			char *eptr = argv[i];
			
			while (*sptr == '-') sptr++;
			while (*eptr != 0 && *eptr != '=') eptr++;
			
			if (*eptr == '=')
			{
				eptr++;
				opt_name = std::string(sptr, eptr - sptr);
				if (passed_options.count(opt_name) == 0)
				{
					passed_options[opt_name] = JSON::array();
				}
				passed_options[opt_name].push_back(std::string(eptr));
				sptr = eptr = NULL;
			}
			else
			{
				opt_name = std::string(sptr, eptr - sptr);
				if (passed_options.count(opt_name) == 0)
				{
					passed_options[opt_name] = JSON::array();
				}
			}
		}
		else
		{
			if (passed_options.count(opt_name) == 0)
			{
				passed_options[opt_name] = JSON::array();
			}
			passed_options[opt_name].push_back(std::string(argv[i]));
			opt_name = "";
		}
	}
	
	if (passed_options.count("help"))
	{
		this->usage(options);
	}
	
	if (passed_options.count("debug"))
	{
		for (std::string level : passed_options["debug"])
		{
			std::string module = "";
			std::string::size_type pos = level.find(':');
			if (pos != std::string::npos)
			{
				module = level.substr(0, pos);
			}
			level.erase(0, pos + 1);
			int level_value = std::stoi(level);
			this->_debug[module] = level_value;
			LOGGER->setLogLevel((Mosaic::LogLevel)(Mosaic::LogLevel::info + level_value));
		}
	}
	
	if (passed_options.count("system"))
	{
		this->_system_name = passed_options["system"][0];
	}
	else
	{
		this->_system_name = "default";
	}
	
	if (passed_options.count("task"))
	{
		this->_task_name = passed_options["task"][0];
	}
	else
	{
		this->_task_name = this->program_name;
	}
	
	if (passed_options.count("reset"))
	{
		this->_reset = true;
	}
	if (passed_options.count("create"))
	{
		this->_create = true;
	}
	
	/*std::string config_file = MOSAIC_RUNTIME_INSTALL_PREFIX + std::string("/etc/mosaic/mosaic.conf");
    DEBUG1("Config File: " + config_file);
	
	std::array<char, 1024> buffer;
    std::string result;
	std::string cmd = "hocon2json " + config_file;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe)
	{
        THROW("Command '" + cmd + "' failed: popen()");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
        result += buffer.data();
    }
	
	try
	{
		this->_config = JSON::parse(result);
	}
	catch (nlohmann::detail::parse_error error)
	{
		THROW("Failed to parse config:\n" + result);
	}
    
    this->loadConfig();*/
	
	
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
void MosaicOptions::setConfig(const JSON &config) {
	this->_config = config;
	this->loadConfig();
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
void MosaicOptions::loadConfig() {
	if (this->_config.count("languages") != 0)
	{
		for (auto & [directory, languages] : this->_config["languages"].items())
		{
			for (auto & [filename, details] : languages.items())
			{
				this->_languages.push_back(MosaicImportableDetails(directory, filename, details));
			}
		}
	}
	
	if (this->_config.count("modules") == 0)
	{
		THROW("No modules found in config");
	}
	for (auto & [directory, modules] : this->_config["modules"].items())
	{
		for (auto & [filename, details] : modules.items())
		{
			this->_modules.push_back(MosaicImportableDetails(directory, filename, details));
		}
	}
    
    if (this->_config.count("storage") == 0)
	{
        THROW("Missing storage configuration");
    }
    this->_storage = this->_config["storage"];
	
	if (this->_config.count("systems") == 0)
	{
		THROW("No systems found in config");
	}
	this->_systems = this->_config["systems"];
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
JSON MosaicOptions::getTaskConfig() {
	if (this->_systems.count(this->_system_name) == 0)
	{
		THROW("No configuration for system ", this->_system_name);
	}
	if (this->_systems[this->_system_name].count("tasks") == 0)
	{
		THROW("Configuration for system ", this->_system_name, " missing tasks");
	}
	if (this->_systems[this->_system_name]["tasks"].count(this->_task_name) == 0)
	{
		THROW("No configuration for system ", this->_system_name, " task ", this->_task_name);
	}
	return this->_systems[this->_system_name]["tasks"][this->_task_name];
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
std::string MosaicOptions::getVersionString() {
    return std::to_string(MOSAIC_RUNTIME_VERSION_MAJOR) + "." +
           std::to_string(MOSAIC_RUNTIME_VERSION_MINOR) + "." +
           std::to_string(MOSAIC_RUNTIME_VERSION_REVISION);
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
bool MosaicOptions::getBooleanOption(std::string option_name) {
	if (this->_options.find(option_name) == this->_options.end())
	{
		THROW("Failed to find option ", option_name);
	}
	auto option = this->_options[option_name];
	return (option == "1");
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
int MosaicOptions::getIntegerOption(std::string option_name) {
	if (this->_options.find(option_name) == this->_options.end())
	{
		THROW("Failed to find option ", option_name);
	}
	std::string option = this->_options[option_name];
	return std::stoi(option);
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
std::string MosaicOptions::getStringOption(std::string option_name) {
	if (this->_options.find(option_name) == this->_options.end())
	{
		THROW("Failed to find option ", option_name);
	}
	auto option = this->_options[option_name];
	return option;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
JSON MosaicOptions::getConfigJSON(std::string path) {
	JSON ptr = this->_config;
	while (path[0] == '/')
	{
		path.erase(0, 1);
	}
	
	std::istringstream split(path);
	for (std::string element; std::getline(split, element, '/'); ) {
		if (ptr.count(element) == 0)
		{
			THROW("Failed to find element ", element);
		}
		ptr = ptr[element];
	}
	
	return ptr;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
bool MosaicOptions::reset() {
	return this->_reset;
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
bool MosaicOptions::create() {
	return this->_create;
}

