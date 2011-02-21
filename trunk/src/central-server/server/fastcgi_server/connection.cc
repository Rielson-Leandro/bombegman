/*
 * Copyright © 2011 - Baltazar Tavares Vanderlei (Psycho Mantys)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
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

/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_FASTCGI


/* #####   HEADER FILE INCLUDES   ########################################## */
#include "connection.hpp"
#include "input_http.hpp"
#include <vector>
#include <exception>
#include <sstream>

/* So precisa para os cout e fazer o debug no estilo printf */
#include <iostream>

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ########################## */
/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################ */

namespace boomberman {
	namespace server {
		namespace fastcgi_impl {

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */
/* #####   CLASS DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############### */
/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ####################### */
/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */
/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ################### */
/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############ */
/* #####   CLASS IMPLEMENTATIONS  -  EXPORTED CLASSES   #################### */

		void connection::close()
		{
		}

		void connection::handle_read()
		{
			webcpp::HTTPEnvHandler in( env, this->cin );
			// For header. EOL is a empty header for fcgi
			this->cout << "\n" ;
			try{
				string client_addr=this->GetParam("REMOTE_ADDR");
				// Test if "request" is set in GET var
				if( in.GET.find("request") != in.GET.end() ) {
					std::stringstream scin( webcpp::url_decode( in.GET["request"][0].c_str() ) , std::ios_base::in );
					connection_handle(this->cout, scin, client_addr );
				}
			}catch( std::exception &e){
				std::clog << e.what() << std::endl ;
			}catch(...){
				std::clog << "Connection handle worst exception\n" ;
			}
		}

/* #####   CLASS IMPLEMENTATIONS  -  LOCAL CLASSES   ####################### */

		} // namespace fastcgi_impl
	} // namespace server
} // namespace boomberman

#endif // SERVER_USE_FASTCGI

