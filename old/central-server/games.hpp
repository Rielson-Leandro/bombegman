#ifndef GAMES_H
#define GAMES_H

/* #####   HEADER FILE INCLUDES   ########################################## */

#include <list>
#include <string>
#include <map>
#include <algorithm>

using std::string;
using std::map;
using std::list;

/* #####   EXPORTED MACROS   ############################################### */
/* #####   EXPORTED TYPE DEFINITIONS   ##################################### */
/* #####   EXPORTED DATA TYPES   ########################################### */
/* #####   EXPORTED CLASS DEFINITIONS   #################################### */

/** 
 * @brief Classe que representa um jogo remoto.
 * Nessa classe estão as informações que dizem onde o jogo esta rodando e
 * armazena algumas informações sobre os jogos.
 */
struct Game{
	/* ====================  LIFECYCLE     ===================== */

	Game(){}

	Game(const string &server, int port, int players_num=0, int players_max=0) :
		server(server), port(port),
		players_num(players_num), players_max(players_max)
	{ }

	/* ====================  OPERATORS     ===================== */

	bool operator ==(const Game& r);

	/* ====================  DATA MEMBERS  ===================== */
	/** 
	 * @brief Endereço do servidor onde esta rodando esse jogo.
	 */
	string server;
	int port;
	/** 
	 * @brief Numero de jogadores nesse jogo atual.
	 */
	int players_num;
	/** 
	 * @brief Numero maxima de jogadores que esse jogo pode ter.
	 */
	int players_max;

};	/* -----  end of class Game  ----- */

/** 
 * @brief Classe que representa o servidor que concetra os Jogos.
 * Essa classe contem todos os jogos que um servidor esta abrigando,
 * sendo que com ela você pode cadastrar, remover ou listar jogos.
 */
class game_server{
	public:
		/* ====================  LIFECYCLE     ===================== */
		explicit game_server();

		/* ====================  OPERATORS     ===================== */
		/** 
		 * @brief Função que trata as conexões de clientes
		 * Toda vez que uma conexão com um cliente é feita, essa função
		 * é chamada, e ela chama o membro ready_read para tratar a
		 * logica da conexão.
		 *
		 * @see game_server::ready_read
		 * @param &oclient Stream de saida de dados para o cliente
		 * @param &iclient Stream de entrada de dados do cliente.
		 * @param &client_addr Endereço do cliente que esta conectado.
		 */
		void operator()(client_ostream &oclient, client_istream &iclient,
			string &client_addr);

	private:
		/* ====================  MUTATORS      ===================== */
		/** 
		 * @brief Inscreve um servidor com um jogo.
		 * Essa função dado um Game, inscreve ele no servidor para que
		 * futuramente ele seja listado a quem requisitar.
		 * 
		 * @param new_game	Novo jogo a ser cadastrado.
		 * @param &gameService	Nome do jogo a ser cadastrado.
		 */
		void subscribe( const Game& new_game, const string &gameService);
		/** 
		 * @brief Remove Game da lista de jogos.
		 * Faz com que um dado jogo seja removido da lista de jogos desse
		 * servidor, para que ele não seja mais listado.
		 *
		 * @param new_game	Game que vai ser removido
		 * @param &gameService	Nome do jogo a ser removido.
		 */
		void unsubscribe( const Game& new_game, const string &gameService );
		/** 
		 * @brief Remove Game da lista de jogos.
		 * Remove jogo, só que tem que passar nome e endereço manualmente.
		 *
		 * @see game_server::unsubscribe
		 */
		void unsubscribe( const string &server, const string &gameService, int port);
		/** 
		 * @brief 
		 * Essa função deve fazer o parser do pedido do cliente que é
		 * feito via stream e devolver via stream a sua resposta.
		 * Sua função e cuidar da logica do pedido.
		 * 
		 * @param &oclient Stream de saida de dados para o cliente
		 * @param &iclient Stream de entrada de dados do cliente.
		 * @param &client_addr Endereço do cliente que esta conectado.
		 */
		void ready_read( client_ostream &oclient, client_istream &iclient,
			string &cliente_addr);

		/* ====================  DATA MEMBERS  ===================== */
		/** 
		 * @brief Map que armazena os Games que este servidor conhece
		 */
		map<string, list<Game> > services;

};	/* -----  end of class game_server  ----- */

/* #####   EXPORTED VARIABLES   ############################################ */

/** 
 * @brief Contem as constantes das mensagens que são passadas ao servidor.
 */
namespace Message{
	static const string subscribe("SUBSCRIBE");
	static const string unsubscribe("UNSUBSCRIBE");
	static const string listall("LISTALL");
}

/* #####   EXPORTED FUNCTION DECLARATIONS   ################################ */

#endif // GAMES_H

