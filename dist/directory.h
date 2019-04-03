/* directory.h  ********/
/*

directory.h - simple directory-reader - declarations (module directory)
Copyright (C) 2006  T.Bastian

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/

#ifndef __DIRECTORY__H__
#define __DIRECTORY__H__

extern "C" {
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
}

#include <vector>
#include <string>


class directory
{
 public:
  directory(void);
  directory(const std::string& dirp);
  directory(const char* dirp);
  ~directory();

  std::vector<std::string>* getDirEntries(void);
  void refreshDir(void);

 private:
  std::vector<std::string> *files;
  DIR *dir;
  std::string path;

};



#endif

/**********************/
