//Se você editar esse arquivo, coloque seu nome nos créditos

/**
   @file utils.h

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

#ifndef BOMBEGMAN_UTILS_H
#define BOMBEGMAN_UTILS_H
#ifndef __cplusplus
#error "Use C++ compiler"
#endif

extern "C"
{
#include <stdint.h>
}
#include <cstdlib>

/**
   @brief Contém coleções genéricas úteis de classes e funções.
   @todo Parser XML e parser EBML (Extensible Binary Meta Language).
 */
namespace utils
{
  /**
     @brief Contém procedimentos para manipulação de arquivos XML.
     @details XML é o formato de marcação usado para armazenar dados de forma
     hierárquica de forma padrão criado pela W3C. Seria interessante já utilizar
     uma biblioteca para tal fim do que reimplementá-la, pois é um formato
     amplamente difundido que já possui várias implementações de qualidade.
   */
  namespace XML
  {
    /**
       @brief Parser XML usado para a leitura de um arquivo formatado como XML.
     */
    class IStream
    {
      //TODO: XML Input parser baseado na hierarquia das classes XML da
      //      plataforma Qt, mas com estrutura minimalista e foco em
      //      desempenho
    };
  }

  /**
     @brief Contém procedimentos para manipulação de arquivos EBML.
     @details EBML (Extensible Binary Markup Language) parser. EBML é um formato
     usado pelo formato Matroska, que é extensível e usa uma hierarquia, assim
     como o XML, mas é um formato binário e é mais simples, por motivos de
     desempenho. \n Será usado para armazenar a parte customizável do jogo
     (mapas e outros). \n Mais informações sobre EBML em
     http://en.wikipedia.org/wiki/Extensible_Binary_Meta_Language
   */
  namespace EBML
  {
    /**
       @brief Parser EBML usado para a leitura de fluxos EBML.
       @see OStream
     */
    class IStream
    {
      //TODO
    public:
      IStream (/*arquivo,*/ size_t vint_max_size);
    };

    /**
       @brief Classe para objetos que armazenarão dados em fluxos EBML.
       @see IStream
     */
    class OStream
    {
      //TODO
    };
  }
}

#endif
