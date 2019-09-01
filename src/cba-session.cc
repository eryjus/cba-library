//===================================================================================================================
//  cba-session.cc -- The implementation details of a MySQL server session
//
// ------------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  ----------------------------------------------------------------------------
//  2019-Aug-22  Initial   0.0.0   ADCL  Initial version
//
//===================================================================================================================


//
// -- include the header files we will require
//--------------------------------------------
#include "cba-session.h"
#include "logger.h"

#include <string>


//
// -- This is the connection we will use
//    ----------------------------------
const std::string host = "localhost";
const int port = 33060;
const std::string user = "cba";
const std::string pwd = "P@ssw0rd";
const std::string db = "mysql";


//
// -- This is a logger for this file in case we want to log something
//    ---------------------------------------------------------------
eryjus::cba::Logger<eryjus::cba::FileLogPolicy> logger("cba-session");
#define ENABLE_LOG logger


//
// -- Everything in this file belongs to the eryjus::cba namespace
//    ------------------------------------------------------------
using namespace eryjus::cba;


//
// -- Keep track of the singleton instance
//    ------------------------------------
CbaSession *CbaSession::singleton = NULL;


//
// -- The constructor, which establishes a session
//    --------------------------------------------
CbaSession::CbaSession(const std::string &db) : Session(host, port, user, pwd, db), initialDb(db)
{
	LOG("processed request to create a new CbaSession instance.");
	LOG("  The host for this connection is: ", host);
	LOG("  The user for this conenction is: ", user);
	LOG("  The initial database for this connection is: ", db);
}


//
// -- This is the function to grab the singleton instance, creating a new one if appropriate
//    --------------------------------------------------------------------------------------
CbaSession &CbaSession::Singleton(void)
{
	if (singleton == NULL) {
		LOG("Singleton instance of CbaSession is NULL; creating a new one.");
		singleton = new CbaSession(db);
	}

	return *singleton;
}

