/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_QT


#include "server.hpp"
#include <QtCore/QCoreApplication>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>


#include <iostream>

namespace boomberman {
	namespace server {
		namespace qt_impl {

			server::server( const std::string& address,
				const std::string& port,
				Handle_function handle,
				std::size_t thread_pool_size, QObject *parent)
				: address_(address),
				port_(port),
				connection_handle(handle),
				thread_pool_size_(thread_pool_size),
				QTcpServer(parent)
			{
				connect(this, SIGNAL(newConnection()), this, SLOT(handle_accept()));
			}

			void server::run()
			{
				this->listen(address_.c_str(), port_.c_str());
			}

			void server::stop()
			{
			}

			int server::exec()
			{
				QCoreApplication a;

				this->run();

				return a.exec();
			}

			void server::handle_accept()
			{

				new_connection_.reset(new connection( nextPendingConnection(), connection_handle, this));
				connect(new_connection, SIGNAL(subscribe(QHostAddress,QByteArray,quint16,int,int)),
						this, SLOT(onSubscribe(QHostAddress,QByteArray,quint16,int,int)));
				connect(new_connection, SIGNAL(unsubscribe(QHostAddress,QByteArray,quint16)),
						this, SLOT(onUnsubscribe(QHostAddress,QByteArray,quint16)));

			}

		} // namespace boost_impl
	} // namespace server
} // namespace boomberman 

#endif // SERVER_USE_QT

