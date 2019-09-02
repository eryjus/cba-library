//===================================================================================================================
//  test00003.cc -- Test the logger output
//
//  Ensure that the logger is outputting test properly.
//
//  -----------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Programmer  Description
//  -----------  -------  -------  ----------  ----------------------------------------------------------------------
//  2019-Sep-01  Initial   0.0.2      ADCL     Initial version
//
//===================================================================================================================


#include "cba.h"
#include "clog.h"


int main()
{
    clog_init_fd(CBA_STDERR, 2);
    clog_debug(CLOG(CBA_STDERR), "This is a debug message");
    clog_info(CLOG(CBA_STDERR), "This is an info message");
    clog_warn(CLOG(CBA_STDERR), "This is a warning message");
    clog_error(CLOG(CBA_STDERR), "This is an error message");
    clog_free(CBA_STDERR);
}

