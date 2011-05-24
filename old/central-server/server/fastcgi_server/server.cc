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
#include "server.hpp"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>
#include <pthread.h>
#include <signal.h>

/* So precisa para os cout e fazer o debug no estilo printf */
#include <iostream>

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ########################## */
/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################ */

namespace boomberman {
	namespace server {
		namespace fastcgi_impl {
			using webcpp::RequestHandle;

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */
/* #####   CLASS DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############### */
/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ####################### */
/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */
/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ################### */
/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############ */
/* #####   CLASS IMPLEMENTATIONS  -  EXPORTED CLASSES   #################### */
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
				std::vector<boost::shared_ptr<boost::thread> > threads;
				threads.reserve(thread_pool_size_);

				std::vector<boost::shared_ptr<server> > servers;
				servers.reserve(thread_pool_size_);

				for (std::size_t i = 0; i < thread_pool_size_; ++i)
				{
					boost::shared_ptr<server> s( new server(this->connection_handle ) );
					servers.push_back( s );

					boost::shared_ptr<boost::thread> thread(new boost::thread(
							boost::bind(&server::handle_accept, &*servers[i])
						));

					threads.push_back(thread);
				}


				// Wait for all threads in the pool to exit.
				for (std::size_t i = 0; i < threads.size(); ++i)
					threads[i]->join();

				return;
			}

			void server::stop()
			{
				// Nothing wet
			}

			int server::exec()
			{
				/* Inicia o fast-cgi ...*/
				FCGX_Init();

				// Block all signals for background thread.
//				sigset_t new_mask;
//				sigfillset(&new_mask);
//				sigset_t old_mask;
//				pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);

				// Run server in background thread.
//				std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);
//				boomberman::server::boost_impl::server s(argv[1], argv[2], h, num_threads==0?1:num_threads );
				boost::thread t(boost::bind(&boomberman::server::fastcgi_impl::server::run, this));

				// Restore previous signals.
//				pthread_sigmask(SIG_SETMASK, &old_mask, 0);

				// Wait for signal indicating time to shut down.
//				sigset_t wait_mask;
//				sigemptyset(&wait_mask);
//				sigaddset(&wait_mask, SIGINT);
//				sigaddset(&wait_mask, SIGQUIT);
//				sigaddset(&wait_mask, SIGTERM);
//				pthread_sigmask(SIG_BLOCK, &wait_mask, 0);
//				int sig = 0;
//				sigwait(&wait_mask, &sig);

				// Stop the server.
				stop();
				t.join();
				return 0;
			}

			void server::handle_accept()
			{
				while( RequestHandle::GetRequest(acceptor_) ){
					connection Cur( acceptor_, connection_handle);
					Cur();
				}
			}

/* #####   CLASS IMPLEMENTATIONS  -  LOCAL CLASSES   ####################### */

		} // namespace fastcgi_impl
	} // namespace server
} // namespace boomberman 

#endif // SERVER_USE_FASTCGI

