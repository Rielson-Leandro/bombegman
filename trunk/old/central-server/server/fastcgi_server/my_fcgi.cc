/*
 * =====================================================================================
 *
 *       Filename:  my_fcgi.cpp
 *
 *    Description:  Implementação do my_fcgi_lib
 *
 *        Version:  1.0
 *        Created:  25-08-2009 16:48:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Psycho Mantys (P.M.), psycho.mantys(.AT,)gmail dot com
 *        Company:  LCCV
 *
 * =====================================================================================
 */
/* Copyright (C) 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */
/** 
 * @file my_fcgi.cpp
 * @brief Implementation of aux. functions and class to programing in fast cgi enviroment.
 * @author Psycho Mantys
 * @date 2009-08-25
 */

/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_FASTCGI

/* #####   HEADER FILE INCLUDES   ################################################### */
#include "my_fcgi.hpp"

#include <cstdio>
#include <fcgiapp.h>
#include <fcgio.h>
#include <exception>
#include <boost/thread/mutex.hpp>

using	boost::mutex ;

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */
/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ######################### */
/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ############################### */
/* #####   CLASS DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ######################## */
/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ################################ */

static mutex	accept_request_mutex;

/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ############################### */
/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ############################ */
/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */

namespace webcpp {

	FCGX_Request *RequestHandle::GetRequest( FCGX_Request &request ){
		int rc = 0 ;
		{
			boost::mutex::scoped_lock lock_for_request(accept_request_mutex);

			rc = FCGX_Accept_r(&request);
		}

		if (rc < 0){
			char temp[100];
			sprintf(temp,"FCGX_Accept_r: Request can't be retrived(%d).",rc) ;
			throw std::runtime_error(temp) ;
		}
		return &request ;
	}

	RequestHandle::RequestHandle ( FCGX_Request &_request ) : request(&_request),
		streambuf_in ( request->in ),
		streambuf_out( request->out ),
		streambuf_err( request->err ),
		cin ( &streambuf_in ),
		cout( &streambuf_out ),
		cerr( &streambuf_err ),
//		cin( NULL ),
//		cout( NULL ),
//		cerr( NULL ),
		env( request->envp )
	{
//		#ifdef HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
//		this->cin  = &streambuf_in ;
//		this->cout = &streambuf_out ;
//		this->cerr = &streambuf_err ;
//	        //cin  = &cin_fcgi_streambuf;
//	        //cout = &cout_fcgi_streambuf;
//	        //cerr = &cerr_fcgi_streambuf;
//		#else
//	        this->cin.rdbuf(&streambuf_in);
//	        this->cout.rdbuf(&streambuf_out);
//	        this->cerr.rdbuf(&streambuf_err);
//		#endif
	}	/* -----  end of method RequestHandle::RequestHandle  (constructor)  ----- */

	void RequestHandle::operator()() {
		this->run();
	}

	char *RequestHandle::GetParam( const char *var_name ) {
		return FCGX_GetParam( var_name, this->env );
	}

	RequestHandle::~RequestHandle(){
		FCGX_Finish_r(request);
	}

}	/* -----  end of namespace webcpp  ----- */

/* #####   CLASS IMPLEMENTATIONS  -  LOCAL CLASSES   ################################ */

#endif // SERVER_USE_FASTCGI

