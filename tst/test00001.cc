//===================================================================================================================
//  test00001.cc -- Test the basic session connectivity
//
//  This test will confirm that we are able to properly connect to the database using a CbaSession object.
//
//  -----------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Programmer  Description
//  -----------  -------  -------  ----------  ----------------------------------------------------------------------
//  2019-Aug-30  Initial   0.0.0      ADCL     Initial version
//
//===================================================================================================================


#include "cba-session.h"
#include <iostream>
#include <cstdlib>



int main()
{
    eryjus::cba::CbaSession &sess = eryjus::cba::CbaSession::Singleton();
    return EXIT_SUCCESS;
}
