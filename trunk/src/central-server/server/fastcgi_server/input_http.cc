/*
 * =====================================================================================
 *
 *       Filename:  input_http.cpp
 *
 *    Description:  Implementation of a lib to parser an get all html input vars.
 *
 *        Version:  1.0
 *        Created:  08-09-2009 14:38:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Psycho Mantys (P.M.), psycho.mantys(.AT,)gmail dot com
 *        Company:  LCCV
 *
 * =====================================================================================
 */
/* Copyright (C) 2010 - Psycho Mantys
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */
/** 
 * @file input_http.cpp
 * @brief Implementation of a lib to parser an get all html input vars.
 * @author Psycho Mantys
 * @date 2010-07-06
 */

/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_FASTCGI

/* #####   HEADER FILE INCLUDES   ################################################### */
#include "input_http.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>

namespace webcpp {

	using	std::istream ;

	/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */
	/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ######################### */
	/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ############################### */
	/* #####   CLASS DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ######################## */
	/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ################################ */
	/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ############################### */

	/**
	 * @brief Converts a hex character to its integer value
	 * 
	 * @param ch A hexadecimal char
	 * 
	 * @return A 
	 */
	char from_hex(char ch);

	/**
	 * @brief Converts an integer value to its hex character
	 * 
	 * @param code A int for conver to hex
	 * 
	 * @return A hexadecimal char
	 */
	char to_hex(char code);

	/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ############################ */

	string url_encode(const char *str){
		string ret;
		ret.reserve(strlen(str) * 3 + 1);

		while(*str){
			if( isalnum(*str) )
				ret.append(1,*str);
			else{
				switch(*str){
					case '-':
					case '_':
					case '.':
					case '~':
						ret.append(1,*str);
						break;
					case ' ':
						ret.append(1,'+');
						break;
					default:
						ret.append(1,'%');
						ret.append(1,to_hex(*str >> 4));
						ret.append(1,to_hex(*str & 15));
						break;
				}
			}
			str++;
		}
		return ret;
	}

	string url_decode(const char *encode_str){
		string ret;

		ret.reserve( strlen(encode_str)+1 );

		while( *encode_str ){
			switch (*encode_str){
				case '%':
					if( *(encode_str+1) && *(encode_str+2) ){
						ret.append(1,from_hex( *(encode_str+1) ) << 4 | from_hex( *(encode_str+2)));
						encode_str += 2;
					}
					break;
				case '+':
					ret.append(1,' ');
					break;
				default:
					ret.append(1,*encode_str);
					break;
			}
			encode_str++;
		}
		return ret;
	}

	/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */

	char from_hex(char ch){
		return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
	}

	char to_hex(char code){
		static char hex[] = "0123456789abcdef";
		return hex[code & 15];
	}

	/* #####   CLASS IMPLEMENTATIONS  -  EXPORTED CLASSES   ############################# */

	HTTPEnvHandler::HTTPEnvHandler( char ** env, istream &r_in ) :
		max_post_length(1000)
	{
		const char *get_var_prefix="QUERY_STRING=" ;
		const char *cookie_var_prefix="HTTP_COOKIE=" ;
		for( ; *env ; ++env ){
			if( strncmp( get_var_prefix, *env, strlen(get_var_prefix) ) == 0 ) {
				updateGET((*env)+strlen(get_var_prefix));
			}
			if( strncmp( cookie_var_prefix, *env, strlen(cookie_var_prefix) ) == 0 ) {
				updateCOOKIE( (*env)+strlen(cookie_var_prefix) );
			}
		}
		updatePOST(r_in);
	}	/* -----  end of method HTTPEnvHandler::HTTPEnvHandler(constructor)  ----- */

	void HTTPEnvHandler::updateCOOKIE( const char* cookie_env ){
		if( cookie_env ){
			unsigned int index=0, inicio=0;
			for( ; (cookie_env[index]) ; ++index){
				switch( cookie_env[index] ){
					// Case [&|^]var[^$|&]
					case ';' :{
							  string aux( &(cookie_env[inicio]), index-inicio );
							  COOKIE[aux].push_back( "" );
							  inicio=index+2;
						  }
						  break;
						  // Case [&|^]var=value[^$|&]
					case '=' :{
							  string aux( &(cookie_env[inicio]), index-inicio );
							  inicio=index+1;
							  for( ; (cookie_env[index])!=';' && (cookie_env[index])!=(char)(NULL) ; ++index)
							  {}
							  string aux2( cookie_env, inicio, index-inicio);
							  COOKIE[aux].push_back( aux2 );
							  inicio=index+2;
							  if( (cookie_env[index])==(char)(NULL) )
								  index--;
						  }
						  break;
				}
			}
			// For case "tes=dasds&foo" and not ""
			//			^
			if( inicio!=index+2 and 0!=index ){
				string aux( &(cookie_env[inicio]), index-inicio );
				COOKIE[aux].push_back( "" );
				inicio=index+2;
			}
		}
	}

	void HTTPEnvHandler::updatePOST( istream &r_in ){
		char post_str[this->max_post_length];
		r_in.read(post_str,this->max_post_length) ;

		unsigned int index=0, inicio=0;
		for( ; (post_str[index]) ; ++index){
			switch( post_str[index] ){
				// Case [&|^]var[^$|&]
				case '&' :{
						  string aux( &(post_str[inicio]), index-inicio );
						  POST[aux].push_back( "" );
						  inicio=index+1;
					  }
					  break;
					  // Case [&|^]var=value[^$|&]
				case '=' :{
						  string aux( &(post_str[inicio]), index-inicio );
						  inicio=index+1;
						  for( ; (post_str[index])!='&' && (post_str[index])!=(char)(NULL) ; ++index)
						  {}
						  string aux2( post_str, inicio, index-inicio);
						  POST[aux].push_back( aux2 );
						  inicio=index+1;
						  if( (post_str[index])==(char)(NULL) )
							  index--;
					  }
					  break;
			}
		}
		// For case "tes=dasds&foo" and not ""
		//			^
		if( inicio!=index+1 and 0!=index ){
			string aux( &(post_str[inicio]), index-inicio );
			POST[aux].push_back( "" );
			inicio=index+1;
		}
	}

	void HTTPEnvHandler::updateGET( const char* QUERY ){
		if( QUERY ){
			unsigned int index=0, inicio=0;
			for( ; (QUERY[index]) ; ++index){
				switch( QUERY[index] ){
					// Case [&|^]var[^$|&]
					case '&' :{
							  string aux( &(QUERY[inicio]), index-inicio );
							  GET[aux].push_back( "" );
							  inicio=index+1;
						  }
						  break;
						  // Case [&|^]var=value[^$|&]
					case '=' :{
							  string aux( &(QUERY[inicio]), index-inicio );
							  inicio=index+1;
							  for( ; (QUERY[index])!='&' && (QUERY[index])!=(char)(NULL) ; ++index)
							  {}
							  string aux2( QUERY, inicio, index-inicio);
							  GET[aux].push_back( aux2 );
							  inicio=index+1;
							  if( (QUERY[index])==(char)(NULL) )
								  index--;
						  }
						  break;
				}
			}
			// For case "tes=dasds&foo" and not ""
			//			^
			if( inicio!=index+1 and 0!=index ){
				string aux( &(QUERY[inicio]), index-inicio );
				GET[aux].push_back( "" );
				inicio=index+1;
			}
		}

	}

	/* #####   CLASS IMPLEMENTATIONS  -  LOCAL CLASSES   ################################ */

}	/* -----  end of namespace webcpp  ----- */

#endif // SERVER_USE_FASTCGI

