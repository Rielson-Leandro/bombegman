//Se você editar esse arquivo, coloque seu nome nos créditos

/**
   @file server-core.cpp

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

#include "server-core.h"
using namespace utils;

namespace server
{

  Cell::Cell ()
  {
    mirror = NULL;
    resident = NULL;
  }

  inline void
  Map::destroy_maps ()
  {
    if(static_map){
      delete[] static_map;
      static_map = NULL;
    }
    if(dynamic_map){
      delete[] dynamic_map;
      dynamic_map = NULL;
    }
    width = height = 0;
    time_left = match_time;
  }

  inline uint_fast8_t &
  Map::ref_scell (uint_fast8_t x, uint_fast8_t y)
  {
    return *(static_map + x + y * width);
  }

  inline Cell &
  Map::ref_dcell (uint_fast8_t x, uint_fast8_t y)
  {
    //Por questões de otimização de desempenho a operação de multiplicação
    //por 4 foi transformada em uma operação de deslocamento de bits
    return *(dynamic_map + x + y * (width << 2));
  }

  inline void
  Map::for_each_scell (void (* function)(uint_fast8_t &, uint_fast8_t,
                                         uint_fast8_t))
  {
    for(uint_fast8_t i = 0;i < width;++i){
      for(uint_fast8_t j = 0;j < height;++j){
        function(ref_scell(i,j),i,j);
      }
    }
  }

  inline void
  assign_zero (uint_fast8_t & cell, uint_fast8_t unused, uint_fast8_t also_unused)
  {
    cell = 0;
  }

  inline void
  generate_right_scell (uint_fast8_t & cell, uint_fast8_t x, uint_fast8_t y)
  {
    // AQUI É ONDE O PC COMPUTA SE A CÉLULA PODE OU NÃO CONTER UM BLOCO, E, CASO
    //POSSA, "JOGA UM DADO" PARA DECIDIR SE A CÉLULA CONTERÁ, OU NÃO, UM BLOCO
  }

  Map::Map (uint32_t time)
  {
    width = height = 0;
    static_map = NULL;
    dynamic_map = NULL;
    match_time = time_left = time;
    if(time){
      is_time_infinite = false;
    }else{
      is_time_infinite = true;
    }
    is_started = stop_msg = false;
  }

  void
  Map::generate_random (uint_fast8_t width, uint_fast8_t height) throw ()
  {
    try{
      if(is_started){
        throw RunningMatchException();
        return;
      }
      if(((width * 4) > UINT_FAST8_MAX) || ((height * 4) > UINT_FAST8_MAX)){
        throw LargeMapException();
        return;
      }
    }
    catch(...){
      throw;
    }
    this->width = width;
    this->height = height;
    static_map = new uint_fast8_t[width*height];
    dynamic_map = new Cell[width*height*16];
    //embaralha o mapa
    for_each_scell(assign_zero);
  }

}
