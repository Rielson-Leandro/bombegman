/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_BOOST


#include "server.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>
#include <pthread.h>
#include <signal.h>


#include <iostream>

namespace boomberman {
	namespace server {
		namespace boost_impl {
/*
			template<typename fun>
			server::server( const std::string& address,
				const std::string& port,
				fun handle, std::size_t thread_pool_size)
				: connection_handle(handle),
				thread_pool_size_(thread_pool_size),
				acceptor_(io_service_),
				new_connection_(new connection(io_service_,handle))
			{
				// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
//				std::cout << "passou 111\n";
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
*/
			void server::run()
			{
				// Create a pool of threads to run all of the io_services.
				std::vector<boost::shared_ptr<boost::thread> > threads;
				for (std::size_t i = 0; i < thread_pool_size_; ++i)
				{
					boost::shared_ptr<boost::thread> thread(new boost::thread(
						boost::bind(&boost::asio::io_service::run, &io_service_)));
					threads.push_back(thread);
				}

				// Wait for all threads in the pool to exit.
				for (std::size_t i = 0; i < threads.size(); ++i)
					threads[i]->join();
			}

			void server::stop()
			{
				io_service_.stop();
			}

			int server::exec()
			{
				// Block all signals for background thread.
				sigset_t new_mask;
				sigfillset(&new_mask);
				sigset_t old_mask;
				pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);

				// Run server in background thread.
//				std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);
//				boomberman::server::boost_impl::server s(argv[1], argv[2], h, num_threads==0?1:num_threads );
				boost::thread t(boost::bind(&boomberman::server::boost_impl::server::run, this));

				// Restore previous signals.
				pthread_sigmask(SIG_SETMASK, &old_mask, 0);

				// Wait for signal indicating time to shut down.
				sigset_t wait_mask;
				sigemptyset(&wait_mask);
				sigaddset(&wait_mask, SIGINT);
				sigaddset(&wait_mask, SIGQUIT);
				sigaddset(&wait_mask, SIGTERM);
				pthread_sigmask(SIG_BLOCK, &wait_mask, 0);
				int sig = 0;
				sigwait(&wait_mask, &sig);

				// Stop the server.
				stop();
				t.join();
				return 0;
			}

			void server::handle_accept(const boost::system::error_code& e)
			{
				if (!e)
				{
					new_connection_->start();
					new_connection_.reset(new connection(io_service_,connection_handle)); //, request_handler_));
					acceptor_.async_accept(*(new_connection_->client.rdbuf()),
						boost::bind(&server::handle_accept, this,
							boost::asio::placeholders::error));
				}
			}

		} // namespace boost_impl
	} // namespace server
} // namespace boomberman 

#endif // SERVER_USE_BOOST

