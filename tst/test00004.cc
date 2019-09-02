//===================================================================================================================
//  test00004.cc -- Ensure that a new singleton instance with different credentials are ignored.
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
#include <cstdlib>


int main()
{
    eryjus::cba::CbaSession &sess1 = eryjus::cba::CbaSession::Singleton("cba", "P@ssw0rd");
    eryjus::cba::CbaSession &sess2 = eryjus::cba::CbaSession::Singleton("root", "unknown");

    return EXIT_SUCCESS;
}

