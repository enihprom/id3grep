/* directory.cc  ********/
/*

directory.cc - simple directory-reader (module directory)
Copyright (C) 2006  T.Bastian

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/

#include "directory.h"

directory::directory() 
{
  path=".";
  refreshDir();
}

directory::directory(const std::string& dirp) 
{
  path=dirp;
  refreshDir();
}

directory::directory(const char* dirp) 
{
  path=dirp;
  refreshDir();
}

directory::~directory() 
{
  closedir(dir);
}

std::vector<std::string>* directory::getDirEntries()
{
  return files;
}

// TODO:

// std::vector directory::getDirEntries(const std::string& pattern)
// {
  
// }


void directory::refreshDir()
{
  files = new std::vector<std::string>();
  
    struct dirent *entry;
  if ((dir = opendir(path.c_str())) == NULL)
    {
      perror("opendir()");
    } 
  else 
    {
    while ((entry = readdir(dir)) != NULL)
      {
	//      printf("  %s\n", entry->d_name);
	files->push_back(entry->d_name);
      }
    closedir(dir);

    }
//...
}


/************************/
