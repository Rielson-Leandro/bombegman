/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_QT


#ifndef CENTRAL_SERVER_QT_SERVER_HPP
#define CENTRAL_SERVER_QT_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <functional>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "connection.hpp"


namespace boomberman {
	namespace server {
		namespace qt_impl {

			class server : public QTcpServer//, private boost::noncopyable
			{
					Q_OBJECT
				public:
					Handle_function connection_handle;
					/// Construct the server to listen on the specified TCP address and port, and
					/// serve up files from the given directory.
					explicit server(const std::string& address, const std::string& port,
						Handle_function handle,std::size_t thread_pool_size=1, QObject *parent=0 );

					/// Run the server's io_service loop.
					void run();

					/// Stop the server.
					void stop();

					/// Exec the server.
					int exec();

				private:
					/// Handle completion of an asynchronous accept operation.
					void handle_accept();

					/// The number of threads that will call io_service::run().
					std::size_t thread_pool_size_;

					/// The next connection to be accepted.
					connection_ptr new_connection_;
			};

		} // namespace qt_impl
	} // namespace server
} // namespace boomberman

#endif // CENTRAL_SERVER_QT_HPP

#endif // SERVER_USE_QT


