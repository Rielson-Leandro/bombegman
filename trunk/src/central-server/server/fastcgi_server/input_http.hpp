/*
 * =====================================================================================
 *
 *       Filename:  input_http.hpp
 *
 *    Description:  Headers files of a lib to parser an get all html input vars.
 *
 *        Version:  1.0
 *        Created:  08-09-2009 14:38:30
 *       Revision:  none
 *       Compiler:  g++
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
 * @file input_http.hpp
 * @brief Header file of a lib to parser an get all html input vars.
 * @author Psycho Mantys
 * @date 2010-07-06
 */


#ifndef	_INPUT_HTTP_HPP_INC
#define	_INPUT_HTTP_HPP_INC

/* #####   HEADER FILE INCLUDES   ################################################### */
#include	<map>
#include	<string>
#include	<vector>
#include	<iostream>


namespace webcpp {

using	std::map;
using	std::string;
using	std::vector;
using	std::istream;

/* #####   EXPORTED MACROS   ######################################################## */
/* #####   EXPORTED TYPE DEFINITIONS   ############################################## */
/* #####   EXPORTED DATA TYPES   #################################################### */
/* #####   EXPORTED CLASS DEFINITIONS   ############################################# */

/**
 * @brief Class to handler input of http protocol.
 */
class HTTPEnvHandler {
	public:
		/* ====================  LIFECYCLE     ======================================= */
		HTTPEnvHandler( char ** env, istream &r_in);	/* constructor */

		/* ====================  ACCESSORS     ======================================= */
		/* ====================  MUTATORS      ======================================= */
		/* ====================  OPERATORS     ======================================= */
		/* ====================  DATA MEMBERS  ======================================= */
		/** 
		 * @brief map content a vector of string of the GET envs, passed through the URL
		 */
		map<string, vector<string> >	GET;
		/** 
		 * @brief map content a vector of string of the cookies envs, passed from http
		 * headers.
		 */
		map<string, vector<string> >	COOKIE;
		/** 
		 * @brief map content a vector of string of the GET envs, passed through the
		 * standart input.
		 */
		map<string, vector<string> >	POST;

		const unsigned long int max_post_length;
	protected:

	private:
		/** 
		 * @brief Update the content of GET env passed through QUERY_REQUEST string
		 * 
		 * @param QUERY The string content the GET envs in http
		 * format.
		 */
		void updateGET( const char *QUERY );
		/** 
		 * @brief Function to update cookie env of map COOKIE.
		 * 
		 * @param cookie_env The string content the COOKIE env in
		 * cgi format.
		 */
		void updateCOOKIE( const char* cookie_env );
		void updatePOST( istream &request_input );
}; /* -----  end of class HTTPEnvHandler  ----- */


/* #####   EXPORTED VARIABLES   ##################################################### */
/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */

/** 
 * @brief A function to encode a string in url encode format.
 *
 * @param str string to be encode in URL encode format.
 * 
 * @return string encode in URL string format
 */
string url_encode(const char *str);

/** 
 * @brief A function to decode a string in url encode format.
 *
 * @param str URL string to be decode.
 * 
 * @return a decoded string
 */
string url_decode(const char *encode_str);

}	/* -----  end of namespace webcpp  ----- */

#endif	/* ----- #ifndef _INPUT_HTTP_HPP_INC  ----- */

