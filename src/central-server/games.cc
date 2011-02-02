/* #####   HEADER FILE INCLUDES   ########################################## */
#include "server.hpp"
#include "games.hpp"

#include <algorithm>
#include <list>

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ########################## */
/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################ */

using std::for_each;
using std::find;
using std::list;
using std::string;

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */
/* #####   CLASS DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############### */

/** 
 * @brief Classe para auxiliar a passagem de informações para um stream.
 *
 * Classe para ser usada como um objeto-função para imprimir em um stream
 * as informações de um jogo. Normalmente usada por funções de algorithms,
 * como por exemplo for_each().
 * Como for_each aceita uma função com um argumento, não pode ser feita só
 * uma função para passar o jogo e o stream, por isso esse objeto.
 * Ex:.
 *	for_each(l.begin(),l.end(),fe_print_game<client_ostream>(oclient) );
 *	for_each(l.begin(),l.end(),fe_print_game<std::ostream>(std::cout) );
 *
 */
template<typename stream>
struct fe_print_game {
	/** 
	 * @brief Stream de saida do jogo.
	 * Variavel que fica a referencia ao stream de saida para os dados
	 * do Game.
	 */
	stream &out;
	/** 
	 * @brief Construtor que só recebe o stream de saida.
	 * 
	 * @param &out Stream de saida dos dados do Game.
	 */
	fe_print_game( stream &out );
	/** 
	 * @brief Função para imprimir um dado jogo
	 * Função objeto que dado um jogo, imprime as informações dele para o
	 * stream de saida armazenado na classe.
	 * 
	 * @param &game Jogo que sera passado para o stream de dados.
	 */
	void operator()( const Game &game );
};

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ####################### */
/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */
/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ################### */
/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############ */
/* #####   CLASS IMPLEMENTATIONS  -  EXPORTED CLASSES   #################### */

game_server::game_server()
{
}

void game_server::subscribe( const Game& new_game, const string &gameService)
{
	list<Game>::iterator current=find(services[gameService].begin(),services[gameService].end(),new_game);

	if ( current==services[gameService].end() ){
		services[gameService].push_back(new_game);
	}else{
		*current=new_game;
	}
}

void game_server::unsubscribe(const string &server, const string &gameService,
		int port)
{
	if( services.find(gameService)==services.end() ){
		return;
	}

	services[gameService].remove( Game(server, port, 0,0) );
}

void game_server::unsubscribe( const Game& new_game, const string &gameService )
{
	if( services.find(gameService)==services.end() ){
		return;
	}

	services[gameService].remove( new_game );
}

void game_server::operator()(client_ostream &oclient, client_istream &iclient, string &client_addr){
	this->ready_read(oclient,iclient,client_addr);
}

void game_server::ready_read( client_ostream &oclient, client_istream &iclient, string &client_addr){

	string server_addr;
	string msg;
	int port;
	int players_number;
	int players_max;

	// Pega a primeira frase da entrada, para saber qual tipo de mensagem
	iclient >> msg;

	if ( msg==Message::subscribe ){
		iclient >> msg>> port>> players_number>> players_max;
		subscribe(Game(client_addr, port, players_number, players_max), msg );
	} else if ( msg==Message::unsubscribe ){
		iclient >> msg >> port;
		unsubscribe( Game(client_addr, port), msg );
	} else if ( msg==Message::listall ){
		iclient >> msg;

		map<string, list<Game> >::iterator request=services.find(msg);

		if( request==services.end() ){
			return;
		}

		for_each(request->second.begin(), request->second.end(), fe_print_game<client_ostream>(oclient) );
		//for_each(services[server_addr].begin(),services[server_addr].end(), fe_print_game<std::ostream>(std::cout) );
	}
}

bool Game::operator ==(const Game& r){
		return (this->port==r.port)&&(this->server==r.server);
}

/* #####   CLASS IMPLEMENTATIONS  -  LOCAL CLASSES   ####################### */

template<typename stream>
fe_print_game<stream>::fe_print_game( stream &out ) : out(out)
	{}

template<typename stream>
void fe_print_game<stream>::operator()( const Game &game ){
	out << game.server.c_str();
	out << " " ;
	out << game.port ;
	out << " " ;
	out << game.players_num ;
	out << " " ;
	out << game.players_max ;
	out << std::endl ;
}

