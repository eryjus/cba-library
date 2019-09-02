//===================================================================================================================
//  test00002.cc -- Test the basic session connectivity -- failure expected
//
//  This test that connectivity fails propery.
//
//  -----------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Programmer  Description
//  -----------  -------  -------  ----------  ----------------------------------------------------------------------
//  2019-Sep-01  Initial   0.0.2      ADCL     Initial version
//
//===================================================================================================================


#include "cba-session.h"
#include <cstdlib>


int main()
{
    try {
        eryjus::cba::CbaSession &sess = eryjus::cba::CbaSession::Singleton("cba", "Invalid");
    } catch(...) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
