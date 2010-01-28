extern "C"
{
#include <stdint.h>
}

class TileSet //TODO: IMPLEMENTAR
{
  //Responsabilidades:
  //-Gerenciamento de arquivos que serão enviados aos clientes, svg
  //-Os clientes deveriam armazenar não só os sprites, mas o mapa inteiro
  // para poderem jogá-lo novamente, caso gostem dele
};

class SpritesSet //TODO: IMPLEMENTAR
{
  //Responsabilidades:
  //-Gerenciamento de arquivos que serão enviados aos clientes
  //-Os clientes devem armazenar esses sprties em pastas de arquivos temporátios
};

/*
  Os valores serão usados em conjunto com os operadores bit-a-bit
 */
enum WalkStyle
  {
    STANDARD = 0; //<A única opção que é usada como valor absoluto
    WALLS_THROUGH = 1;
    //As opções abaixo precisam de um pouco mais de cuidado para serem usadas,
    //pois não podem ambas estarem ativadas. Os 2 bits que são ocupados por elas
    //são reservados para elas.
    BOMBS_THROUGH = 1 << 2;
    BOMBS_KICK = (1 << 2) + (1 << 1);
  };

enum Direction
  {
    NORTH = 0;
    EAST;
    SOUTH;
    WEST;
  }

//Preciso entrar em contaro com alguém mais experiente para discutir qual
//namespace é o mais adequado, mas acho que o desenvolvimento do bombegman
//será suficiente para nos mostrar isso.
namespace bombegman
{
  namespace server
  {

    class Map
    {
      TileSet tileset; //<tileset talvez pudesse ser uma string estilo-C, a ser
      //interpretada pelo núcleo da interface, ou gráfico, ou ainda, fizesse
      //parte só da interface, e fora do servidor
      unsigned int width;
      unsigned int height;
      Tile * map; //<the bi-dimensional array of the map, a cast needs be used
      bool time_infinite;
      uintmax_t time_left;
    public:
      Map (unsigned int width,unsigned int height,Tileset tileset);
      bool set_attr (unsigned int players_max); //There a lot ot thigs yet
      void randomize (void); //<Generate a random map
      bool add_bomber (Bomber * bomber);
      bool add_player (Bomber * bomber);//human player
      void start (void); //<Init the map to be served via net, or local
    };


    class Bomb
    {
      Bomber * owner;
      uintmax_t time_left;
      unsigned short int range; //Alcance da explosão, em tiles
      BombTybe type;
    public:
      Bomb (unsigned int range,BombType type = STANDARD,bool red_bomb = false);
      void explode (void);
      uintmax_t get_time (void);
    };

    class Anima
    {
      SpritesSet sprites_set;
      unsigned int x;
      unsigned int y;
      unsigned short int lives;
      bool immortal;
      enum WalkStyle walking_options;
      unsigned int speed; //Precisamos estudar sobre a implementação disso
    public:
      void move (enum Direction dir,int distance = 1);
    };


    class Bomber: public Anima
    {
      unsigned int bombs_range;
      unsigned short int bombs_max;
      vector<BombType> bombs_type;
      vector<Bomb *> active_bombs;
      bool grab_bombs;
    public:
      void drop_bomb (void);
    };


  }
}
