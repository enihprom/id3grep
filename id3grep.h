
/* id3grep.h  ********/
/*

id3grep.h - include-wrapper, macros and helper-methods for module id3grep
Copyright (C) 2006  T.Bastian

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/

#ifndef __ID3GREP__H__
#define __ID3GREP__H__

extern "C" {
#include <libgen.h>
#include <regex.h>
}
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <strstream>
#include <cstdlib>

#include "id3read.h"
#include "directory.h"

#define M3U 1
#define PLS 2

#define BRANDING "id3grep-0.7.1     2006  by T.Bastian    tinobastian@linuxmail.org"

#pragma ident BRANDING

void print_usage(int err) {
  //std::cerr << std::endl;
  std::cerr << BRANDING << std::endl;
  //std::cerr << std::endl;
  std::cerr << "usage:" << std::endl;
  std::cerr << "\tid3grep [-m|p] [-x expression] [-i] [-d dir]" << std::endl;
  std::cerr << "\twhere" << std::endl;
  std::cerr << "\t -x[expr]  the regular expression to find" << std::endl;
  std::cerr << "\t -m        print results as m3u" << std::endl;
  std::cerr << "\t -p        print results as pls" << std::endl;
  std::cerr << "\t -i        treat expression case insensitive" << std::endl; 
  std::cerr << "\t -d[dir]   directory to search. where '.' is default" << std::endl; 
  std::cerr << "\t           and '-' will read each filename linewise via stdin." << std::endl;
  std::cerr << "\t -v        more info (via stderr)" << std::endl;
  std::cerr << "\t -h        print this help" << std::endl;
  //std::cerr << "" << std::endl;
  //std::cerr << "" << std::endl;
  std::cerr << "THIS SOFTWARE COMES WITH ABSOLUTELY NO WARRANTY :P" << std::endl;
  //std::cerr << "" << std::endl;
  //std::cerr << "" << std::endl;
  //std::cerr << std::endl;
  exit(err);
}

void mperr() {
  std::cerr << "ERROR: -m and -p flags are not compatible (cannot create both in one)"
	    << std::endl;
}

bool  match(const char *string, const char *pattern, int flags);

class bad_re {
 public:
  bad_re(){}
};

#endif

/**********************/

