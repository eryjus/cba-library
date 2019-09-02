//===================================================================================================================
//  cba-session.cc -- The implementation details of a MySQL server session
//
// ------------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  ----------------------------------------------------------------------------
//  2019-Aug-30  Iniial   0.0.1   ADCL  Initial version
//
//===================================================================================================================


//
// -- include the header files we will require
//--------------------------------------------
#include "cba.h"
#include "cba-session.h"
#include "clog.h"

#include <string>


//
// -- This is the connection we will use
//    ----------------------------------
const int port = 33060;


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
CbaSession::CbaSession(const std::string &u, const std::string &p, const std::string &h)
        : Session(h, 33060, u, p), user(u), pwd(p), host(h)
{
    if (clog_init_path(CBA_SESSION, "cba_session.log") != 0) {
        throw std::runtime_error("Unable to create log file");
    }

    clog_debug(CLOG(CBA_SESSION), "processed request to create a new CbaSession instance.");
	clog_debug(CLOG(CBA_SESSION), "  The host for this connection is: %s", host.c_str());
	clog_debug(CLOG(CBA_SESSION), "  The user for this conenction is: %s", user.c_str());
}


//
// -- This is the function to grab the singleton instance, creating a new one if appropriate
//    --------------------------------------------------------------------------------------
CbaSession &CbaSession::Singleton(const std::string &u, const std::string &p, const std::string &h)
{
	if (singleton == NULL) {
		singleton = new CbaSession(u, p, h);
		clog_debug(CLOG(CBA_SESSION), "Singleton instance of CbaSession is NULL; creating a new one.");
	} else if (u != singleton->user || h != singleton->host) {
        clog_error(CLOG(CBA_SESSION), "Singleton() tries to redefine connection credentials; new credentials ignored.");
    }

	return *singleton;
}


//
// -- Return an existing singleton instance
//    -------------------------------------
CbaSession &CbaSession::Singleton(void)
{
	if (singleton == NULL) {
        clog_init_fd(CBA_STDERR, 2);
		clog_error(CLOG(CBA_STDERR), "Singleton instance of CbaSession is NULL; You must establish one before retrieving");
        throw std::runtime_error("Estabish a CbaSession before retrieving it");
	}

	return *singleton;
}

