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

#ifndef CENTRAL_SERVER_FASTCGI_SERVER_HPP
#define CENTRAL_SERVER_FASTCGI_SERVER_HPP

/* #####   HEADER FILE INCLUDES   ########################################## */

#include "connection.hpp"
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <vector>
#include <string>
#include <pthread.h>
#include <signal.h>

#include <iostream>

/* #####   EXPORTED MACROS   ############################################### */
/* #####   EXPORTED TYPE DEFINITIONS   ##################################### */

namespace boomberman {
	namespace server {
		namespace fastcgi_impl {

			using std::string;
			using std::size_t;

/* #####   EXPORTED DATA TYPES   ########################################### */
/* #####   EXPORTED CLASS DEFINITIONS   #################################### */
			/** 
			 * @brief Classe de um servidor de comunicação usando fcgi.
			 */
			class server
				: private boost::noncopyable
			{
				public:
					/** 
					 * @brief Armazena callback que trata conexão
					 *
					 * Aqui ficara armazenado a função reposavel por tratar
					 * a logica da conexão, vendo qual a nescessidade do
					 * cliente.
					 */
					Handle_function connection_handle;
					/** 
					 * @brief Construtor.
					 *
					 * Pega algumas informações genericas para a comunicação e as usa dependendo
					 * da implementação por baixo. Como esse servidor vai ser um serviço,
					 * porta e endereço não fazem muito sentido.
					 * 
					 * @param address Endereço que ele vai escutar. Utilidade não implementada.
					 * @param port	Porque que vai escuta novas conexões. Utilidade não implementada.
					 * @param handle Função que vai tratar cada conexão feita por clientes.
					 * @param thread_pool_size Numero de threads que o servidor vai ter.
					 */
					template<typename fun>
					explicit server(const string& address, const string& port,
							fun handle, size_t thread_pool_size=1)
						: connection_handle(handle),
						thread_pool_size_(thread_pool_size)
						{
							FCGX_InitRequest( &acceptor_, 0, 0);
						}
					/** 
					 * @brief Construtor. Esse só recebe o handle da conexão.
					 *
					 * Pega algumas informações genericas para a comunicação e as
					 * usa dependendo da implementação por baixo. Como esse servidor
					 * vai ser um serviço web, porta e endereço não fazem muito
					 * sentido.
					 * 
					 * @param handle Armazena a função que trata cada conexão.
					 */
					template<typename fun>
					explicit server( fun handle )
						: connection_handle(handle)
						{
							FCGX_InitRequest( &acceptor_, 0, 0);
						}

					/** 
					 * @brief Para o servidor. Ainda não implementado.
					 */
					void stop();

					/** 
					 * @brief Da start e executa o servidor.
					 * 
					 * @return Codigo de retorno do servidor para testar sua execução.
					 */
					int exec();

				private:
					/** 
					 * @brief Handle completion of an asynchronous accept operation.
					 */
					void handle_accept();

					/** 
					 * @brief Run the server to accept conections.
					 */
					void run();

					/** 
					 * @brief The number of threads that will call run().
					 */
					std::size_t thread_pool_size_;

					/** 
					 * @brief Acceptor used to listen for incoming connections.
					 *
					 * Usado pela implementação com o fatcgi. Esse é o handle que identifica
					 * uma coneção na API do fastcgi. Internamente ele é transparente devido
					 * ao uso de biblioteca.
					 */
					FCGX_Request acceptor_;
			};

		} // namespace fastcgi_impl
	} // namespace server
} // namespace boomberman

#endif // CENTRAL_SERVER_FASTCGI_HPP
#endif // SERVER_USE_FASTCGI

