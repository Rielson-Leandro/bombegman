/*
 * =============================================================================
 *
 *       Filename:  my_fcgi.cpp
 *
 *    Description:  Biblioteca fcgi para usar em exemplos.
 *
 *        Version:  1.0
 *        Created:  25-08-2009 10:09:02
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Psycho Mantys (P.M.), psycho.mantys(.AT,)gmail dot com
 *        Company:  LCCV
 *
 * =============================================================================
 */

#ifndef	_MY_FCGI_HPP_INC
#define	_MY_FCGI_HPP_INC

/* #####   HEADER FILE INCLUDES   ################################################### */

#include <fcgiapp.h>
#include <fcgio.h>

#include <iostream>

using std::ostream ;
using std::istream ;

/* #####   EXPORTED MACROS   ######################################################## */
/* #####   EXPORTED TYPE DEFINITIONS   ############################################## */
/* #####   EXPORTED DATA TYPES   #################################################### */
/* #####   EXPORTED CLASS DEFINITIONS   ############################################# */

/** 
 * @brief Main namespace of the library
 */
namespace webcpp {

	/*
	 * =====================================================================================
	 *        Class:  RequestHandle
	 *  Description:  Classe que trata do handle de uma conexão fcgi.
	 * =====================================================================================
	 */
	/** 
	 * @brief A abstract class.
	 *
	 * His is responsible for handler a request of a client. Is required you
	 * inherit from him and override abstract method "RequestHandle::run()".
	 * See the ctor "RequestHandle::RequestHandle()" and method "RequestHandle::run()" for more
	 * information.
	 */
	class RequestHandle {
		protected:
			/** 
			 * @brief The request which this class make a handler
			 */
			FCGX_Request	*request;
			/*
			 * Buffers used for input and output streams.
			 */
			fcgi_streambuf	streambuf_in;
			fcgi_streambuf	streambuf_out;
			fcgi_streambuf	streambuf_err;
			/** 
			 * @brief Input stream of request.
			 * This stream represent the data send of client coming
			 * to server. Through this stream, you can treat GET and
			 * POST method and upload.
			 */
			istream	cin ;
			/** 
			 * @brief Output stream of request.
			 * This stream represent the data send to client. All
			 * data send to this stream is send to client browser.
			 */
			ostream	cout ;
			/** 
			 * @brief Output stream of request.
			 * This stream is equivalent to cerr of c++. The data
			 * send to this stream the erro mensage.
			 * The more common action, is write data in error log of
			 * webserver.
			 */
			ostream	cerr ;

		public:
			static FCGX_Request *GetRequest( FCGX_Request &request );
			/* ====================  LIFECYCLE     ======================================= */
			/** 
			 * @brief The ctor of class accept the request handler of one
			 * conection. This is a assign.
			 * 
			 * @param &_request The request handle of one conection.
			 *
			 * @todo Write exceptions for this method
			 */
			RequestHandle( FCGX_Request &_request );
			~RequestHandle();

			/* ====================  ACCESSORS     ======================================= */
			/** 
			 * @brief method to get the enviroment parameters of
			 * this request.
			 * 
			 * @param var_name The name of enviromento to be get.
			 * 
			 * @return A string with the vavule os parameter
			 * requested.
			 *
			 * @todo Write exceptions for this method
			 */
			char *GetParam( const char* var_name ) ;
			/* ====================  MUTATORS      ======================================= */
			virtual void run() = 0;

			/* ====================  OPERATORS     ======================================= */
			void operator()();
			/* ====================  DATA MEMBERS  ======================================= */
			char ** &env;

	};	/* -----  end of class RequestHandle  ----- */

}	/* -----  end of namespace webcpp  ----- */

/* #####   EXPORTED VARIABLES   ##################################################### */
/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */

#endif	/* ----- #ifndef _MY_FCGI_HPP_INC ----- */

