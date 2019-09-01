//===================================================================================================================
//  logger.h -- This is a logger class to output the results of debugging to an output stream.
//
//  This file is adapted from http://www.drdobbs.com/cpp/a-lightweight-logger-for-c/240147505?pgno=1
//
// ------------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  ----------------------------------------------------------------------------
//  2019-Aug-19  Initial   0.0.0   ADCL  Initial version
//
//===================================================================================================================


#ifndef __LOGGER_H__
#define __LOGGER_H__


#include <memory>
#include <mutex>
#include <fstream>
#include <sstream>
#include <ctime>


namespace eryjus {

	//
	// -- We want to put this stuff into our own namespace to prevent clashes
	//    -------------------------------------------------------------------
	namespace cba {

	    //
	    // -- Define the abstract interface class to that it has a common interface
	    //    ---------------------------------------------------------------------
	    class LogPolicyInterface {
	        public: virtual void OpenOstream(const std::string &name) = 0;
	        public: virtual void CloseOstream(void) = 0;
	        public: virtual void Write(const std::string &msg) = 0;
	    };


	    //
	    // -- This is a policy class for logging to a file
	    //    --------------------------------------------
	    class FileLogPolicy : public LogPolicyInterface {
	        //
	        // -- This is the file where we will log
	        //    ----------------------------------
	        protected: std::unique_ptr<std::ofstream> outStream;


	        //
	        // -- This is the class constructor/destructor
	        //    ----------------------------------------
	        public: FileLogPolicy() : outStream(new std::ofstream) {}
	        public: ~FileLogPolicy() { if (outStream) CloseOstream(); }


	        //
	        // -- Open a file for debugging output
	        //    --------------------------------
	        public: void OpenOstream(const std::string &name) {
	            outStream->open(name.c_str(), std::ios_base::binary | std::ios_base::out);
	            if (!outStream->is_open()) {
	                throw(std::runtime_error("LOGGER: Unable to open an output stream"));
	            }
	        }


	        //
	        // -- Close an output file
	        //    --------------------
	        public: void CloseOstream(void) { if (outStream) outStream->close(); }


	        //
	        // -- Write a message to the file
	        //    ---------------------------
	        public: void Write(const std::string &msg) {
	            (*outStream) << msg << std::endl;
	            outStream->flush();
	        }
	    };


	    //
	    // -- This template is the actual one we will instantiate
	    //    ---------------------------------------------------
	    template<typename LogPolicy>
	    class Logger
	    {
	        Logger() = delete;
	        Logger(const Logger &) = delete;


	        //
	        // -- These are the logging levels defined for this logger interface
	        //    --------------------------------------------------------------
	        public: typedef enum {
	           DEBUG = 1,
	           ERROR,
	           WARNING
	        } SeverityType;


	        //
	        // -- This is the running line number of the log message
	        //    --------------------------------------------------
	        private: unsigned long logLineNumber;


	        //
	        // -- A string stream that is used to build the complete log message
	        //    --------------------------------------------------------------
	        private: std::stringstream logStream;


	        //
	        // -- The policy that controls the output (common interface class)
	        //    ------------------------------------------------------------
	        private: LogPolicy *policy;


	        //
	        // -- Mutex for multi-threaded apps to control access
	        //    -----------------------------------------------
	        private: std::mutex writeMutex;


	        //
	        // -- Constructor for the Logger class
	        //    --------------------------------
	        public: explicit Logger(const std::string &name) {
	            logLineNumber = 0;
	            policy = new LogPolicy;

	            if (!policy) {
	                throw std::runtime_error("LOGGER: Unable to create the logger instance");
	            }

	            policy->OpenOstream(name);
	        }


	        //
	        // -- Destructor for the Logger class
	        //    -------------------------------
	        public: virtual ~Logger() {
	            if(policy) {
	                policy->CloseOstream();
	                delete policy;
	            }
	        }


	        //
	        // -- Get the time to print out to the log
	        //    ------------------------------------
	        private: std::string GetTime(void) {
	            std::string timeStr;
	            time_t rawTime;
	            time(&rawTime);
	            timeStr = ctime(&rawTime);

	            // -- without the newline character
	            return timeStr.substr(0 , timeStr.size() - 1);
	        }


	        //
	        // -- Prepare the common parts of the log line (the header)
	        //    -----------------------------------------------------
	        private: std::string GetLogLineHeader(void) {
	            std::stringstream header;
	            header.str("");
	            header.fill('0');
	            header.width(7);
	            header << ++logLineNumber << " [" << GetTime() << " - ";
	            header.fill('0');
	            header.width(7);
	            header << clock() << "] ~ ";

	            return header.str();
	        }


	        //
	        // -- Core printing functionality (used up all parameters)
	        //    ----------------------------------------------------
	        private: void PrintImpl(void) {
	            policy->Write(GetLogLineHeader() + logStream.str());
	            logStream.str("");
	        }


	        //
	        // -- Core printing functionality (process one parameter and recurse for the rest)
	        //    ----------------------------------------------------------------------------
	        private: template<typename First, typename...Rest> void PrintImpl(First parm1, Rest...parm) {
	            logStream << parm1;
	            PrintImpl(parm...);
	        }


	        //
	        // -- This function will print a line
	        //    -------------------------------
	        public: template<SeverityType severity, typename...Args> void Print(Args...args) {
	            writeMutex.lock();
	            switch (severity) {
	                case SeverityType::DEBUG:
	                    logStream << "<DEBUG>   ";
	                    break;

	                case SeverityType::WARNING:
	                    logStream << "<WARNING> ";
	                    break;

	                case SeverityType::ERROR:
	                    logStream << "<ERROR>   ";
	                    break;
	            };

	            PrintImpl(args...);
	            writeMutex.unlock();
	        }
	    };
	}
}


//
// -- Some C-style macros to make writing to the log simpler
//
//    example usage:
//    --------------
//
//    eryjus::cba::Logger<eryjus::cba::FileLogPolicy> logger("log source");
//    #define ENABLE_LOG logger
//
//    LOG("This is some message to write to the log");
//
//    ---------------------------------------------------------------------
#ifdef ENABLE_LOG
#   define LOG      ENABLE_LOG.Print<eryjus::cba::Logger::SeverityType::DEBUG>
#   define LOG_ERR  ENABLE_LOG.Print<eryjus::cba::Logger::SeverityType::ERROR>
#   define LOG_WARN ENABLE_LOG.Print<eryjus::cba::Logger::SeverityType::WARNING>
#else
#   define LOG(...)
#   define LOG_ERR(...)
#   define LOG_WARN(...)
#endif



#endif