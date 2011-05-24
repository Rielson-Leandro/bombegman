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
#ifdef SERVER_USE_BOOST

#ifndef CENTRAL_SERVER_BOOST_CONNECTION_HPP
#define CENTRAL_SERVER_BOOST_CONNECTION_HPP


/* #####   HEADER FILE INCLUDES   ########################################## */

#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

/* #####   EXPORTED MACROS   ############################################### */
/* #####   EXPORTED TYPE DEFINITIONS   ##################################### */

using std::string;

namespace boomberman {
	namespace server {
		namespace boost_impl {

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
			typedef boost::asio::ip::tcp::iostream client_ostream;
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
			typedef boost::asio::ip::tcp::iostream client_istream;
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
/* #####   EXPORTED VARIABLES   ############################################ */
/* #####   EXPORTED FUNCTION DECLARATIONS   ################################ */

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
				private boost::noncopyable
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
					 * pela boost e quem vai tratar a conexão via stream dessa
					 * conexão.
					 * 
					 * @param io_service Handle da conexão que sera tratada
					 * @param handle Handle que vai ser chamado via callback para tratar a conexão.
					 */
					template<typename fun>
					connection(boost::asio::io_service& io_service,
						fun handle )
						: strand_(io_service),
						socket_(io_service),
						timer_(io_service)
					{
						this->connection_handle=handle;
					}

					/// Get the socket associated with the connection.
					boost::asio::ip::tcp::socket& socket();

					/// Start the first asynchronous operation for the connection.
					void start();

					tcp::iostream client;

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

			};

			typedef boost::shared_ptr<connection> connection_ptr;

		} // namespace boost_impl
	} // namespace server
} // namespace boomberman

#endif // CENTRAL_SERVER_BOOST_CONNECTION_HPP

#endif // SERVER_USE_BOOST

