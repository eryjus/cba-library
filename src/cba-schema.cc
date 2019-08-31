//===================================================================================================================
//  cba-schema.cc -- implementation of the schema interface
//
//  -----------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Programmer  Description
//  -----------  -------  -------  ----------  ----------------------------------------------------------------------
//  2019-Aug-30  Initial   0.0.0      ADCL     Initial version
//
//===================================================================================================================


#include <mysqlx/xdevapi.h>
#include <iostream>

// Scope controls life-time of objects such as session or schema
int main(void)
{
    mysqlx::Session sess("localhost", 33060, "cba", "P@ssw0rd");
}