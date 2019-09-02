//===================================================================================================================
//  test00005.cc -- Ensure that we can get a copy of the singleton instnace already created.
//
//  -----------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Programmer  Description
//  -----------  -------  -------  ----------  ----------------------------------------------------------------------
//  2019-Sep-01  Initial   0.0.2      ADCL     Initial version
//
//===================================================================================================================


#include "cba.h"
#include "cba-session.h"
#include "clog.h"

#include <cstdlib>


int main()
{
    eryjus::cba::CbaSession &sess1 = eryjus::cba::CbaSession::Singleton("cba", "P@ssw0rd");
    eryjus::cba::CbaSession &sess2 = eryjus::cba::CbaSession::Singleton();

    return EXIT_SUCCESS;
}

