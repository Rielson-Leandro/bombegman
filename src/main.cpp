/*
 * main.cpp
 * Copyright (C) Vinícius dos Santos Oliveira 2010 <vini.ipsmaker@gmail.com>
 *
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
#include "main.h"


int
main (int argc,char **argv)
{
    if(init()){
        return 0;
    }
    //...
    exit(0);
}
