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

#ifndef CENTRAL_SERVER_BOOST_CONNECTION_HPP
#define CENTRAL_SERVER_BOOST_CONNECTION_HPP

#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using std::string;

//using boost::asio::ip::tcp;
//typedef boost::asio::ip::tcp::iostream client_stream;
//typedef void(*Handle_function)(client_stream&);

namespace boomberman {
	namespace server {
		namespace boost_impl {
			using boost::asio::ip::tcp;
			typedef boost::asio::ip::tcp::iostream client_ostream;
			typedef boost::asio::ip::tcp::iostream client_istream;
			typedef void(*Handle_function)(client_ostream&,client_istream&,string&);

			/// Represents a single connection from a client.
			class connection
				: public boost::enable_shared_from_this<connection>,
				private boost::noncopyable
			{
				public:
					Handle_function connection_handle;
					/// Construct a connection with the given io_service.
//					explicit connection(boost::asio::io_service& io_service, Handle_function handle);
					template<typename fun>
					connection(boost::asio::io_service& io_service,
						fun handle )
						: strand_(io_service),
						socket_(io_service),
//						connection_handle(handle),
						timer_(io_service)
					{
						this->connection_handle=handle;
					}

					/// Get the socket associated with the connection.
					boost::asio::ip::tcp::socket& socket();

					/// Start the first asynchronous operation for the connection.
					void start();

					tcp::iostream client;

				private:
					/// Handle completion of a read operation.
					void handle_read();

					/// Handle completion of a write operation.
					void handle_write(const boost::system::error_code& e);

					/// Strand to ensure the connection's handlers are not called concurrently.
					boost::asio::io_service::strand strand_;

					/// Socket for the connection.
					boost::asio::ip::tcp::socket socket_;

					/// Buffer for incoming data.
					boost::array<char, 8192> buffer_;

					boost::asio::deadline_timer timer_;

//					void close();
					void close( const boost::system::error_code& error );

			};

			typedef boost::shared_ptr<connection> connection_ptr;

		} // namespace boost_impl
	} // namespace server
} // namespace boomberman

#endif // CENTRAL_SERVER_BOOST_CONNECTION_HPP

#endif // SERVER_USE_BOOST

