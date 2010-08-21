//Se você editar esse arquivo, coloque seu nome nos créditos

/**
   @file berror.cpp

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

#include "berror.h"

namespace utils
{
  const char *
  RunningMatchException::what () const throw ()
  {
    return "You can't use this command while the match is running";
  }

  RunningMatchException::~RunningMatchException () throw () {}

  const char *
  LargeMapException::what () const throw ()
  {
    return "The map area is too large";
  }

  LargeMapException::~LargeMapException () throw () {}

}
