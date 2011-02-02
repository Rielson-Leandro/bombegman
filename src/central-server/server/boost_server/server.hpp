/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_BOOST

#ifndef CENTRAL_SERVER_BOOST_SERVER_HPP
#define CENTRAL_SERVER_BOOST_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "connection.hpp"

#include <vector>
#include <string>
#include <pthread.h>
#include <signal.h>


#include <iostream>


/////

namespace boomberman {
	namespace server {
		namespace boost_impl {

			class server
				: private boost::noncopyable
			{
				public:
					Handle_function connection_handle;
					/// Construct the server to listen on the specified TCP address and port, and
					/// serve up files from the given directory.
					template<typename fun>
					explicit server(const std::string& address, const std::string& port,
							fun handle,std::size_t thread_pool_size=1)
						: connection_handle(handle),
						thread_pool_size_(thread_pool_size),
						acceptor_(io_service_),
						new_connection_(new connection(io_service_,this->connection_handle))
						{
							boost::asio::ip::tcp::resolver resolver(io_service_);
							boost::asio::ip::tcp::resolver::query query(address, port);
							boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
							acceptor_.open(endpoint.protocol());
							acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
							acceptor_.bind(endpoint);
							acceptor_.listen();
							acceptor_.async_accept(*(new_connection_->client.rdbuf()),
							boost::bind(&server::handle_accept, this,
								boost::asio::placeholders::error));
						}

					/// Run the server's io_service loop.
					void run();

					/// Stop the server.
					void stop();

					/// Exec the server.
					int exec();

				private:
					/// Handle completion of an asynchronous accept operation.
					void handle_accept(const boost::system::error_code& e);

					/// The number of threads that will call io_service::run().
					std::size_t thread_pool_size_;

					/// The io_service used to perform asynchronous operations.
					boost::asio::io_service io_service_;

					/// Acceptor used to listen for incoming connections.
					boost::asio::ip::tcp::acceptor acceptor_;

					/// The next connection to be accepted.
					connection_ptr new_connection_;
			};

		} // namespace boost_impl
	} // namespace server
} // namespace boomberman

#endif // CENTRAL_SERVER_BOOST_HPP

#endif // SERVER_USE_BOOST

