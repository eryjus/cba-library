//===================================================================================================================
//  cba-session.h -- This class is a singleton session class
//
// ------------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  ----------------------------------------------------------------------------
//  2019-Aug-30  Initial   0.0.1   ADCL  Initial version
//
//===================================================================================================================


#ifndef __CBA_SESSION_H__
#define __CBA_SESSION_H__


#include <mysqlx/xdevapi.h>


namespace eryjus {
	namespace cba {
		class CbaSession : public mysqlx::Session {
			CbaSession() = delete;
			CbaSession(const CbaSession &) = delete;
			void operator=(const CbaSession &) = delete;

		private:
			const std::string initialDb;

		private:
			static CbaSession *singleton;

		private:
			explicit CbaSession(const std::string &db);

		public:
			static CbaSession &Singleton(void);

		private:
			~CbaSession() {}		// -- made private so it cannot be deleted
		};
	}
}


#endif


