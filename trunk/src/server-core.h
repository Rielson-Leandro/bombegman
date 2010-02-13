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
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <pthread.h>
}
#include <cstdlib>

#include "berror.h"
#include "utils.h"

namespace server
{

  class Resident
  {
  public:
    virtual void set_x (uint_fast8_t) = 0;
    virtual void set_y (uint_fast8_t) = 0;
  };

  class Cell
  {
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
    MapFile * visual_map;
    uint_fast8_t width, height;
    //static_map é  de tamanho [width][heigth] e armazena os códigos dos tiles.
    //os objetos pertencentes a esse mapa são denominados scell, abrivação para
    //static map cell
    uint_fast8_t * static_map;
    //dynamic_map é 4 vezes maior que static_map e é um array de Cells
    Cell * dynamic_map;
    bool is_time_infinite;
    //o padrão é 1 minuto, que é 60000 milisegundos
    uint_least32_t match_time, time_left;
    //os atributos auxiliam no uso do objeto sistemas que usem threads
    bool is_started, stop_msg;
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
    inline Cell * ref_dcell (uint_fast8_t x, uint_fast8_t y);
    /**
      @brief Algoritmo for_each espcializado para o Mapa
     */
    inline void for_each_scell (void (* make)(uint_fast8_t & cell, uint_fast8_t,
					      uint_fast8_t));
  public:
    Map (uint32_t match_time);
    void generate_random (uint_fast8_t width, uint_fast8_t height) throw ();
    bool add_player (Animated * anima);
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
    uint_fast8_t bombs_max;
    uint_fast8_t bombs_range;
  };

  //Quando o jogo estiver um pouco mais completo fará sentido fazer Bomb herdar
  //de Animated
  class Bomb
  {
    Bomber * owner;
    int_fast16_t time_left;
    uint_fast8_t range;
  };

}

#endif
