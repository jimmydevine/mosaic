#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <sys/time.h>
#include "loggable.bpp"


/***************************************************************************************************
*
*
***************************************************************************************************/
namespace Mosaic /* LogLevel */ {
    
    
    /***********************************************************************************************
	*
	*
	***********************************************************************************************/
    enum LogLevel {
       error = 1,
       warning,
       info,
       debug1,
       debug2,
       debug3,
	   undefined
    };
    
    
}


/***************************************************************************************************
*
*
***************************************************************************************************/
namespace Mosaic /* Loggable */ {
    
    
    /***********************************************************************************************
	*
	*
	***********************************************************************************************/
    template <typename LogPolicy> class Loggable : public _LoggableConfig {
        friend class LoggableMaster;
        
        private:
            std::stringstream log_stream;
            LogPolicy* policy;
			LogLevel log_level;
            
            
            /***************************************************************************************
            *
            *
            ***************************************************************************************/
            void print_impl(LogLevel severity, time_t timestamp) {
				if (severity > this->log_level) return;
                this->policy->write(severity, timestamp, this->log_stream.str());
                this->log_stream.str("");
            }
            
            
            /***************************************************************************************
            *
            *
            ***************************************************************************************/
            template <typename First, typename...Rest> void print_impl(LogLevel severity, time_t timestamp, First parm1, Rest...parm) {
				if (severity > this->log_level) return;
                this->log_stream<<parm1;
                this->print_impl(severity, timestamp, parm...);    
            }
            
            
        public:
            
            
            /***************************************************************************************
            *
            *
            ***************************************************************************************/
            Loggable() : _LoggableConfig() {
                this->policy = new LogPolicy;
                if (!this->policy)
                {
                   THROW("LOGGER: Unable to create the logger instance"); 
                }
				this->log_level = LogLevel::undefined;
            }
            
            
            /***************************************************************************************
            *
            *
            ***************************************************************************************/
            template <LogLevel severity, typename...Args> void print(Args...args) {
                struct timeval tv;
                gettimeofday(&tv, NULL);
                this->print_impl(severity, tv.tv_sec, args...);
            }
            
            
            /***************************************************************************************
            *
            *
            ***************************************************************************************/
            template <typename...Args> void print(LogLevel severity, time_t timestamp, Args...args) {
                this->print_impl(severity, timestamp, args...);
            }
            
            
            /***************************************************************************************
            *
            *
            ***************************************************************************************/
            ~Loggable() {
                if (this->policy)
                {
                   this->policy->close();
                   delete this->policy;
                }
            }
    };
    

}


/***************************************************************************************************
*
*
***************************************************************************************************/
namespace Mosaic /* LoggableInstance */ {
    
    
    /***********************************************************************************************
	*
	*
	***********************************************************************************************/
    class LoggableInstance {
        public:
            virtual void open() { }
            virtual void close() { }
            virtual void write(LogLevel severity, time_t timestamp, const std::string &msg)=0;
    };
    
    
}


/***********************************************************************************************************************************
*
*
***********************************************************************************************************************************/
namespace Mosaic /* LoggableSTDOUTInstance */ {
    
    
    /*******************************************************************************************************************************
    *
    *
    *******************************************************************************************************************************/
    class LoggableSTDOUTInstance : public LoggableInstance {
        private:
            
        public:
            LoggableSTDOUTInstance() {}
            void write(LogLevel severity, time_t timestamp, const std::string &msg) {
                std::string time_str;
                std::string sevstr = "";
                switch (severity)
                {
                    case LogLevel::error:   sevstr = "  ERROR"; break;
                    case LogLevel::warning: sevstr = "WARNING"; break;
                    case LogLevel::info:    sevstr = "   INFO"; break;
                    case LogLevel::debug1:  sevstr = " DEBUG1"; break;
                    case LogLevel::debug2:  sevstr = " DEBUG2"; break;
                    case LogLevel::debug3:  sevstr = " DEBUG3"; break;
                };
                time_str = ctime(&timestamp);
                
                std::cout << "[" << time_str.substr(0 , time_str.size() - 1) << " " << sevstr << "] " << msg << std::endl;
            }
            ~LoggableSTDOUTInstance() { }
    };
    
    
}


/***************************************************************************************************
*
*
***************************************************************************************************/
namespace Mosaic /* LoggableMasterLogger */ {
    
    
    /***********************************************************************************************
	*
	*
	***********************************************************************************************/
    class LoggableMasterLogger : public LoggableInstance {
        friend class LoggableMaster;
        
        private:
            std::vector<Loggable<LoggableInstance> *> loggers;
            Loggable<LoggableInstance> *default_logger;
        
        public:
            void write(LogLevel severity, time_t timestamp, const std::string &msg) {
                if (this->loggers.size())
                {
                    for (auto logger : this->loggers)
                    {
                        logger->print(severity, timestamp, msg);
                    }
                }
                else
                {
                    this->default_logger->print(severity, timestamp, msg);
                }
            }
    };
    
    
}


/***************************************************************************************************
*
*
***************************************************************************************************/
namespace Mosaic /* LoggableMaster */ {
    
    
    /***********************************************************************************************
	*
	*
	***********************************************************************************************/
    class LoggableMaster : public Loggable<LoggableMasterLogger> {
        private:
            static LoggableMaster *instance;
            
        public:
            static LoggableMaster *getInstance() {
                if (LoggableMaster::instance == NULL)
                {
                    LoggableMaster::instance = new LoggableMaster();
                }
                return LoggableMaster::instance;
            }
            LoggableMaster() {
                static_cast<LoggableMasterLogger *>(this->policy)->default_logger = (Loggable<LoggableInstance> *)(new Loggable<LoggableSTDOUTInstance>());
				this->log_level = LogLevel::info;
            }
			void setLogLevel(LogLevel level) {
				this->log_level = level;
			}
            void registerLogger(Loggable<LoggableInstance> *logger) {
                static_cast<LoggableMasterLogger *>(this->policy)->loggers.push_back(logger);
            }
    };
    
    
}


#define LOGGER Mosaic::LoggableMaster::getInstance()
#define ERROR Mosaic::LoggableMaster::getInstance()->print<Mosaic::LogLevel::error>
#define WARN Mosaic::LoggableMaster::getInstance()->print<Mosaic::LogLevel::warning>
#define INFO Mosaic::LoggableMaster::getInstance()->print<Mosaic::LogLevel::info>
#define DEBUG1 Mosaic::LoggableMaster::getInstance()->print<Mosaic::LogLevel::debug1>
#define DEBUG2 Mosaic::LoggableMaster::getInstance()->print<Mosaic::LogLevel::debug2>
#define DEBUG3 Mosaic::LoggableMaster::getInstance()->print<Mosaic::LogLevel::debug3>

