//Se você editar esse arquivo, coloque seu nome nos créditos

/**
   @file server-core.h

   @author Copyright 2010 Vinícius dos Santos Oliveira
   \n
   bombegman is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   bombegman is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BOMBEGMAN_SERVER_H
#define BOMBEGMAN_SERVER_H
#ifndef __cplusplus
#error "Use C++ compiler"
#endif

#include <vector>
#include <algorithm>
#include <string>
extern "C"
{
/**
   Esta macro é usado para que sejam definidos os limites dos tipos definidos em
   stdint.
 */
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <pthread.h>
}
#include <cstdlib>

#include "berror.h"
#include "utils.h"

namespace server
{

  /**
     @brief Essa é a classe base para qualquer objeto que deva estar no mapa.
     @details Os objetos que devem ficar no mapa devem herdar da classe Resident
   */
  class Resident
  {
  public:
    virtual void set_x (uint_fast8_t) = 0;
    virtual void set_y (uint_fast8_t) = 0;
  };

  /**
     @brief A classe célula representa uma célula no mapa dinâmico.
     @details O objeto dessa célula pode conter um objeto Resident ou apontar
     para um objeto Cell que contenha o Resident. Esta técnica é utilizada para
     objetos que ocupam mais de uma célula. Nesse caso, um objeto Cell o
     gerencia no mapa e outras células apontam para esta.
   */
  class Cell
  {
    /**
       @brief Um ponteiro para a célula que contém um Resident.
     */
    Cell * mirror;
    Resident * resident;
  public:
    Cell ();
  };

  class Animated: public Resident
  {
    //sprites_set
    uint_fast8_t lives;
    bool immortal;
    uint_fast8_t hit_points;
    //tempo restante em milisegundos para que o Anima possa mover-se novamente
    uint_fast16_t paralyzed_time;
    //  enum WalkOptions walk_options;
    uint_fast8_t speed;
  };

  class MapFile
  {
    //Por motivos de desempenho, usaremos EBML para representar os mapas
    //utils::EBML:IStream file;
  public:
    MapFile (std::string ebml_file);
  };

  class MapDirIterator
  {
    utils::XML::IStream dir_stream;
    //utils::XML::StartElement current_file;
    std::string current_file_name;
  public:
    MapDirIterator (utils::XML::IStream dir);
    MapDirIterator (const MapDirIterator &);
    virtual ~MapDirIterator ();
    MapFile & operator* ();
    const MapDirIterator & operator++ ();
    const MapDirIterator & operator-- ();
    const MapDirIterator & operator+ (size_t offset);
    const MapDirIterator & operator- (size_t offset);
  };

  class MapDir
  {
    std::string dir_index_file_name;
    utils::XML::IStream dir_stream;
  public:
    MapDir (std::string);
    MapDir (const MapDir &);
    ~MapDir ();
    MapDirIterator begin ();
    MapDirIterator end ();
  };

  class Map
  {
    /**
       @brief Um objeto que armazena o arquivo de mapa, usado para representar
       visualmente o mapa no programa cliente.
     */
    MapFile * visual_map;
    /**
       @var width
       @brief A largura do mapa estático
     */
    /**
       @var height
       @brief A "altura" do mapa estático
     */
    uint_fast8_t width, height;
    /**
       @brief Representa o mapa semi-estático do jogo, que contém objetos que
       são mutáveis, mas não podem mover-se e/ou assumir posições arbitrárias.
       @details O tamanho do static_map é width * heigth. O mapa armazena
       números inteiros sem sinais de 8-bit que representam um código, usado
       representar os variados objetos que podem estar contidos no mapa
       semi-estático. Os objetos pertencentes a esse mapa são denominados scell,
       abrivação para "static map cell".
       @see ref_scell
     */
    uint_fast8_t * static_map;
    /**
       @brief Uma matriz de ponteiros para objetos do tipo Cell, usada para
       representar os objetos dinâmicos do mapa.
       @details dynamic_map é 4 vezes maior que static_map para permitir
       posições mais gerais. A princípio, deveríamos usar números em ponto
       flutuante, mas isso elevaria a complexidade de implementação e diminuiria
       o desempenho. Os objetos pertencentes a esse mapa são denominados dcell.
       @see static_map
     */
    Cell * dynamic_map;
    /**
       @brief Usado para indicar o limite de tempo da partida.
       @details A unidade de tempo é milisegundos e 0 indica que não há limite
       de tempo. O padrão é 1 minuto, 60000 milisegundos.
       @see time_left ref_dcell
     */
    uint_least32_t match_time;
    /**
       @brief Representa o tempo restante para acabar a partida, caso haja
       limite de tempo.
       @see match_time
     */
    uint_least32_t time_left;
    /**
       @brief true se a partida já começou
       @see run()
     */
    bool is_running;
    /**
       @brief Variável usada pelo método stop para comunicar-se com a thread
       que gerencia a partida.
       @details A variável recebe true para indicar que a partida deve ser
       encerrada e a thread receptora age sobre essa menssagem.
       @see stop()
     */
    bool stop_cmd_msg;
    /**
      @brief Desaloca o espaço alocado dinâmicamente, mudando também para onde
      ponteiros apontam.
     */
    inline void destroy_maps ();
    /**
      @brief Referencia uma célula do mapa estático
      @param x A coordenada no eixo x
      @param y A coordenada no eixo y
      @return A célula, por referência
     */
    inline uint_fast8_t & ref_scell (uint_fast8_t x, uint_fast8_t y);
    /**
      @brief Referencia uma célula do mapa dinâmico
      @warning As dimensões do mapa dinâmico são 4 vezes maiores que no mapa
      estático
      @param x A coordenada no eixo x
      @param y A coordenada no eixo y
      @return O endereço da célula
     */
    inline Cell & ref_dcell (uint_fast8_t x, uint_fast8_t y);
    /**
      @brief Algoritmo for_each espcializado para o Mapa
      @details Recebe um ponteiro para uma função que recebe uma célula, e as
      coordenadas x e y dessa célula
      @param make O ponteiro para a função
     */
    inline void for_each_scell (void (* make)(uint_fast8_t & cell, uint_fast8_t,
					      uint_fast8_t));
  public:
    Map (uint32_t match_time);
    /**
       @brief Gera um mapa aleatório.
       @details Nas primeiras versões a implementação podemos usar um algoritmo
       genérico, mas depois devemos permitir mapas scriptáveis, que lerão do
       arquivo de mapa parâmetros e farão um mapa pseudo-aleatório.
     */
    void generate_random (uint_fast8_t width, uint_fast8_t height) throw ();
    /**
       @brief Adiciona um objeto da classe Anima na partida/mapa.
     */
    bool add_player (Animated * animated);
    //uma vez que o método run é chamado, a partida começa, e pode ser encerrada
    //previamente se stop for chamado em paralelo
    void run ();
    void stop ();
  };

  /*enum WalkOptions
    {
    STANDARD = 0;
    }*/

  class Bomber: public Animated
  {
    /**
       @brief O número máximo de bombas que o Bomber pode ter simultaneamente no
       mapa.
     */
    uint_fast8_t bombs_max;
    /**
       @brief O alcance do impacto de explosão das bombas que o Bomber possui.
     */
    uint_fast8_t bombs_range;
  };

  //Quando o jogo estiver um pouco mais completo fará sentido fazer Bomb herdar
  //de Animated
  class Bomb
  {
    /**
       @brief O Bomber que criou a bomba.
       @details Nulo se não foi criado por um Bomber
     */
    Bomber * owner;
    /**
       @brief Tempo restante para a bomba explodir.
     */
    int_fast16_t time_left;
    /**
       @brief Alcance do impacto de explosão da bomba.
     */
    uint_fast8_t range;
  };

}

#endif
