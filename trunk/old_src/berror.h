//Se você editar esse arquivo, coloque seu nome nos créditos

/**
   @file berror.h

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

#ifndef BOMBEGMAN_EXCEPTION_H
#define BOMBEGMAN_EXCEPTION_H
#ifndef __cplusplus
#error "Use C++ compiler"
#endif

#include <exception>
using std::exception;

namespace utils
{

  /**
     @brief Esta excessão é lançada quando tenta-se usar um dos comandos que não
     podem ser usados com a partida em andamento.
     @details Como exemplo desses comandos está o de gerar o mapa
     aleatoriamente.
   */
  class RunningMatchException: public exception
  {
  public:
    /**
       @brief Retorna uma c-string informando o erro.
       @details "You can't use this command while the match is running".
     */
    virtual const char * what () const throw ();
    virtual ~RunningMatchException () throw ();
  };

  /**
     @brief Essa excessão é lançada quando tenta-se criar um mapa muito grande.
     @details O mapa é considerado grande quando uma de suas dimensões
     ultrapassa o limite de UINT_FAST8_MAX / 4, que geralmente é igual a 63.
   */
  class LargeMapException: public exception
  {
  public:
    /**
       @brief Retorna uma c-string informando o erro.
       @details "The map area is too large".
     */
    virtual const char * what () const throw ();
    virtual ~LargeMapException () throw ();
  };

}

#endif
