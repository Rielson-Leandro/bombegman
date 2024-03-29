#ifndef CENTRAL_SERVER_HPP
#define CENTRAL_SERVER_HPP

#define	SERVER_USE_BOOST

#ifdef	SERVER_USE_BOOST
	#include "server/boost_server/server.hpp"

	#define	SERVER_TYPE boomberman::server::boost_impl::server
	#define HANDLE_CLIENT boomberman::server::boost_impl::Handle_function
	#define CLIENT_OSTREAM boomberman::server::boost_impl::client_ostream
	#define CLIENT_ISTREAM boomberman::server::boost_impl::client_istream

#elif	defined(SERVER_USE_QT)
	#include "server/qt_server/server.hpp"

	#define	SERVER_TYPE boomberman::server::qt_impl::server
	#define HANDLE_CLIENT boomberman::server::qt_impl::Handle_function
	#define CLIENT_OSTREAM boomberman::server::qt_impl::client_ostream
	#define CLIENT_ISTREAM boomberman::server::qt_impl::client_istream

#elif	defined(SERVER_USE_FASTCGI)
	#include "server/fastcgi_server/server.hpp"

	#define	SERVER_TYPE boomberman::server::fastcgi_impl::server
	#define HANDLE_CLIENT boomberman::server::fastcgi_impl::Handle_function
	#define CLIENT_OSTREAM boomberman::server::fastcgi_impl::client_ostream
	#define CLIENT_ISTREAM boomberman::server::fastcgi_impl::client_istream

#else
	#error "No implementation choosen."
#endif


typedef SERVER_TYPE transmission;
typedef HANDLE_CLIENT Handle_function;
typedef CLIENT_OSTREAM client_ostream;
typedef CLIENT_ISTREAM client_istream;


#undef SERVER_TYPE
#undef HANDLE_CLIENT
#undef CLIENT_ISTREAM
#undef CLIENT_OSTREAM

#endif // CENTRAL_SERVER_HPP

