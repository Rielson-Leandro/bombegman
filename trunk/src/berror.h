//Se você editar esse arquivo, coloque seu nome nos créditos

/**
   @file berror.h

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

#ifndef BOMBEGMAN_EXCEPTION_H
#define BOMBEGMAN_EXCEPTION_H
#ifndef __cplusplus
#error "Use C++ compiler"
#endif

#include <exception>
using std::exception;

namespace utils
{

  class RunningMatchException: public exception
  {
  public:
    virtual const char * what () const throw ();
    virtual ~RunningMatchException () throw ();
  };

  class LargeMapException: public exception
  {
  public:
    virtual const char * what () const throw ();
    virtual ~LargeMapException () throw ();
  };

}

#endif
