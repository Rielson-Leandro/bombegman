/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_QT


#ifndef CENTRAL_SERVER_QT_CONNECTION_HPP
#define CENTRAL_SERVER_QT_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <QTextStream>

#include <boost/enable_shared_from_this.hpp>

namespace boomberman {
	namespace server {
		namespace qt_impl {
//			using boost::asio::ip::tcp;
			typedef QTextStream client_stream;
			typedef void(*Handle_function)(client_stream&);

			/// Represents a single connection from a client.
			class connection
				: public boost::enable_shared_from_this<connection>,
				private boost::noncopyable
			{
				public:
					Handle_function connection_handle;
					/// Construct a connection with the given io_service.
					explicit connection(boost::asio::io_service& io_service, Handle_function handle);

					/// Get the socket associated with the connection.
					boost::asio::ip::tcp::socket& socket();

					/// Start the first asynchronous operation for the connection.
					void start();

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

					QByteArray client;

			};

			typedef boost::shared_ptr<connection> connection_ptr;

		} // namespace qt_impl
	} // namespace server
} // namespace boomberman

#endif // CENTRAL_SERVER_QT_CONNECTION_HPP

#endif // SERVER_USE_QT

