//===================================================================================================================
//  test00006.cc -- Getting a singleton instance without credentials throws an exception.
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
    try {
        eryjus::cba::CbaSession &sess = eryjus::cba::CbaSession::Singleton();
    } catch(...) {
        return EXIT_SUCCESS;
    }

    throw std::runtime_error("Expected an exception trying to reference a singleton which did not exist.");
    return EXIT_FAILURE;
}

