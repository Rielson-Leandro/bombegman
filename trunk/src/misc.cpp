/*
 * misc.cpp
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


void
init (void)
{
    //inicializa a SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
    {
        cerr << "Unable to init SDL: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    
    if(SDLNet_Init() < 0){
        cerr << "Unable to init SDL_net" << endl;
        SDL_Quit();
        return 1;
    }

    IPaddress local = {0x0100007F, 0x50};
    cout << "Hostname: " << SDLNet_ResolveIP(&local) << endl;

    atexit(quit);
}

void
quit (void)
{
    SDLNet_Quit();
    SDL_Quit();
}
