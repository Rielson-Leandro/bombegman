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
#ifdef SERVER_USE_BOOST


/* #####   HEADER FILE INCLUDES   ########################################## */
#include "connection.hpp"
#include <vector>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <exception>

/* So precisa para os cout e fazer o debug no estilo printf */
#include <iostream>

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ########################## */
/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################ */

namespace boomberman {
	namespace server {
		namespace boost_impl {

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */
/* #####   CLASS DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############### */
/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ####################### */
/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */
/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ################### */
/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############ */
/* #####   CLASS IMPLEMENTATIONS  -  EXPORTED CLASSES   #################### */

		boost::asio::ip::tcp::socket& connection::socket()
		{
			return socket_;
		}

		void connection::start()
		{
			socket_.async_read_some(boost::asio::buffer(buffer_),
					strand_.wrap(
						boost::bind(&connection::handle_read, shared_from_this())));
		}

		void connection::close( const boost::system::error_code& error )
		{
			// Initiate graceful connection closure.
			if( ! error ){
				std::cout << "saiu close\n" ;
//				client << std::endl;
//				socket_.cancel();
				std::cout << "saiu close 1\n" ;
				std::cout << "saiu close 2\n" ;
//				client.exceptions( );
//				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
				std::cout << "saiu close 3\n" ;

				client.rdbuf()->cancel();
//				socket_.cancel();
				std::cout << "saiu close 4\n" ;
				client.flush();
				client.close();
				client.flush();
//				socket_.cancel();
//				socket_.close();
				std::cout << "saiu close 5\n" ;
				boost::system::error_code ignored_ec;
				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
				client.rdbuf()->io_service().stop();
				client.rdbuf()->io_service().reset();
				client.rdbuf()->io_service().run_one();
//				socket_.close();
				std::cout << "saiu close fim\n" ;
//				client << std::endl;
//				client.exceptions( std::ios::badbit | std::ios::failbit | std::ios::eofbit );
			}else{
				std::cout << " Timeout canceled\n";
			}
		}

		void connection::handle_read()
		{
////			timer_.expires_from_now(boost::posix_time::seconds(5));
////			timer_.async_wait(boost::bind(&connection::close, shared_from_this(),_1)); //shared_from_this() ));
			client.exceptions( std::ios::badbit | std::ios::failbit | std::ios::eofbit );
			client.rdbuf()->pubsetbuf(0, 0);
			try{
				string client_addr=client.rdbuf()->remote_endpoint().address().to_string();
				connection_handle(client, client, client_addr);
			}catch( std::exception &e){
				std::cout << e.what() << std::endl ;
			}catch(...){
				std::clog << "Connection handle worst exception\n" ;
			}
			client.exceptions();
////			timer_.cancel();
		}

		void connection::handle_write(const boost::system::error_code& e)
		{
			if (!e)
			{
				// Initiate graceful connection closure.
				boost::system::error_code ignored_ec;
				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
			}

			//No new asynchronous operations are started. This means that all shared_ptr
			//references to the connection object will disappear and the object will be
			//destroyed automatically after this handler returns. The connection class's
			//destructor closes the socket.
		}

/* #####   CLASS IMPLEMENTATIONS  -  LOCAL CLASSES   ####################### */

		} // namespace boost_impl
	} // namespace server
} // namespace boomberman

#endif // SERVER_USE_BOOST

