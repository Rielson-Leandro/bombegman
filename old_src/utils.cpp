//Se você editar esse arquivo, coloque seu nome nos créditos

/**
   @file utils.cpp

   @author Copyright 2010 Vinícius dos Santos Oliveira
   \n
   bombegman is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   \n
   bombegman is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.
   \n
   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "utils.h"
#include <iostream>

namespace utils
{
  namespace XML
  {
    //TODO: métodos das classes XML
  }

  namespace EBML
  {
    //Como vint não será utilizado em outras partes do projeto, sua declaração
    //também ficará aqui
    class vint
    {
      size_t size;
      uint8_t * data;
    public:
      vint (void *);
      vint (const vint &);
      ~vint ()
      {
        delete data;
      }
      static size_t size_of (void * v_int)
      {
        uint8_t * data = static_cast<uint8_t *>(v_int);
        size_t length = 1;
        uint8_t i = 0x80;
        //Aqui verificamos o tamanho do vint, supondo, que ele não é um inteiro
        //de tamanho desconhecido
        {
          bool not_finished = true;
          while(not_finished){
            for(i = 0x80;i != 0;i >>= 1){
              if((*data & i) == 0){
                ++length;
              }else{
                not_finished = false;
                i >>= 1;
                break;
              }
            }
            if(not_finished){
              ++data;
            }
          }
        }
        //E aqui verificamos se realmente é um inteiro de tamanho desconhecido, o
        //que é indicado por todos os bits do inteiro serem configurados para 1
        {
          //O primeiro byte é verificado pelo bloco especial logo no começo
          size_t remaining = length -1;

          //primeiro verificamos se todos os bits do byte atual já foram lidos:
          if(i == 0){
            ++data;
          }else{
            //caso contrário nós tratamos os bits restantes
            for(;i != 0;i >>= 1){
              if((*data & i) == 0){
                //o tamanho não é desconhecido
                return length;
              }
            }
            ++data;
          }
          for(;remaining;--remaining){
            if(*data++ != 0xFF){
              //o tamanho não é desconhecido
              return length;
            }
          }
        }
        //o tamanho é desconhecido
        return 0;
      }
      operator uintmax_t () const
      {
        return 1;
      }
      const vint & operator+ (const vint &); 
    };
  }
}
