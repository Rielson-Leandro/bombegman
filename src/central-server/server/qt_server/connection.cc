/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_QT


#include "connection.hpp"
#include <vector>

#include <QTcpSocket>
#include <QTextStream>

#include <iostream>

namespace boomberman {
	namespace server {
		namespace qt_impl {

			connection::connection( const QTcpSocket &socket,
				Handle_function handle )
				: socket_(socket)
			{
				this->connection_handle=handle;
				connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
//				connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
			}

			QTcpSocket& connection::socket()
			{
				return socket_;
			}

//			void connection::close( const boost::system::error_code& error )
			void connection::close()
			{
				// Initiate graceful connection closure.
				socket_.close();
			}

			void connection::handle_read()
			{
				buffer.append(socket->readAll());

				if (!buffer.contains('\n')) {
					return;
				}

//				QByteArray gameService;
				QTextStream client(&buffer);

				try{
					connection_handle(client);
					std::cout << "saiu\n" ;
				}catch(...){
					std::cout << "saiu exp \n" ;
				}
				std::cout << "saiu exp \n" ;
			}

		} // namespace qt_impl
	} // namespace server
} // namespace boomberman

#endif // SERVER_USE_QT

