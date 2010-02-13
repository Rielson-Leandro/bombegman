//Se você editar esse arquivo, coloque seu nome nos créditos

/**
   @file utils.h

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

namespace utils
{
  namespace XML
  {
    class IStream
    {
      //TODO: XML Input parser baseado na hierarquia das classes XML da
      //      plataforma Qt, mas com estrutura minimalista e foco em
      //      desempenho
    };
  }

  namespace EBML
  {
    class IStream
    {
      //TODO: EBML (Extensible Binary Markup Language) parser. EBML é um formato
      //      usado pelo formato Matroska, que é extensível e usa uma hierarquia,
      //      assim como o XML, mas é um formato binário e um pouco mais simples,
      //      por motivos de desempenho
    public:
      IStream (/*arquivo,*/ size_t vint_max_size);
    };
  
    class OStream
    {
      //classe de saída
    };
  }
}

#endif
