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

#ifndef CENTRAL_SERVER_FASTCGI_CONNECTION_HPP
#define CENTRAL_SERVER_FASTCGI_CONNECTION_HPP

/* #####   HEADER FILE INCLUDES   ########################################## */

#include "my_fcgi.hpp"
#include <string>
#include <sstream>
#include <boost/noncopyable.hpp>

/* #####   EXPORTED MACROS   ############################################### */
/* #####   EXPORTED TYPE DEFINITIONS   ##################################### */

using std::string;

namespace boomberman {
	namespace server {
		namespace fastcgi_impl {

			/** 
			 * @brief Tipo do stream de saida de um cliente.
			 *
			 * Esse é o tipo do stream que quando você escreve
			 * vai levar o que você escreveu para um cliente.
			 * Esse stream é somente leitura, primeiro você deve
			 * ler dele para depois mandar qualquer mensagem para
			 * o cliente.
			 * Semelhante ao cin.
			 */
			typedef std::ostream client_ostream;
			/** 
			 * @brief Tipo do stream de entrada de um cliente.
			 *
			 * Esse é o tipo do stream que quando você lê dele você
			 * vai receber informações do cliente.
			 * Esse stream é somente escrita, e você deve escrever
			 * nele depois de ler todas as informações do cliente
			 * via o stream de entrada.
			 * Semelhante ao cout.
			 */
			typedef std::stringstream client_istream;
			/** 
			 * @brief Tipo da função de callback que trata clientes.
			 * 
			 * Esse sera a função que trata o dado dos clientes.
			 * Como a classe connection só representa as conexões
			 * e o objeito e mater a camada de comunicação separada,
			 * essa função tem que ser definida e implementada em
			 * outro canto.
			 *
			 * @param client_ostream& Stream de saida de dados
			 * @param client_istream& Stream de entrada de dados
			 * @param string& Endereço do cliente que esta conectando
			 */
			typedef void(*Handle_function)(client_ostream&,client_istream&,string&);

/* #####   EXPORTED DATA TYPES   ########################################### */
/* #####   EXPORTED CLASS DEFINITIONS   #################################### */

			/** 
			 * @brief Representação da coneção de um cliente.
			 *
			 * Esta classe representa a conexão de um cliente com o
			 * servidor. Cada vez que uma conexão é feita, um
			 * objeto é instanciado dessa classe e trata de chamar
			 * o callback responsavel por tratar conexões.
			 * Cada conexão é unica, por isso ela herda de
			 * noncopyable.
			 */
			class connection
				: public boost::enable_shared_from_this<connection>,
				private boost::noncopyable,
				public webcpp::RequestHandle
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
					 * @brief Construtor que voce passa quem vai tratar as coneções
					 *
					 * Nesse construtor voçê passa o handle que trata a conexão
					 * pela fastcgi e quem vai tratar a conexão via stream dessa
					 * conexão.
					 * 
					 * @param acceptor Handle da conexão que sera tratada
					 * @param handle Handle que vai ser chamado via callback para tratar a conexão.
					 */
					template<typename fun>
					connection(FCGX_Request& acceptor, fun handle )
						: RequestHandle( acceptor )
					{
						this->connection_handle=handle;
					}

				private:
					/// Handle completion of a read operation.
					void run(){
						handle_read();
					}

					void handle_read();

					void close();

			};
		} // namespace fastcgi_impl
	} // namespace server
} // namespace boomberman

/* #####   EXPORTED VARIABLES   ############################################ */
/* #####   EXPORTED FUNCTION DECLARATIONS   ################################ */

#endif // CENTRAL_SERVER_FASTCGI_CONNECTION_HPP

#endif // SERVER_USE_FASTCGI

