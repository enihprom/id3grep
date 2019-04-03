
/* id3grep.cc  ********/
/*

id3grep.cc - command-line frontend, core-implementation and main-method for module id3grep
Copyright (C) 2006  T.Bastian

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/

#include "id3grep.h"



bool  match(const char *string,  const char *pattern, int flags)
{       	
  int status;
  regex_t rxp;
  if (regcomp(&rxp, pattern, flags) != 0) {
    throw bad_re();
  }
  status = regexec(&rxp, string, (size_t) 0, NULL, 0);
  regfree(&rxp);
  if (status != 0) {
    return false; 
  }

  return true;
}



int main(int argc, char** argv)
{
  int om = 0; // output mode
  std::string expr = ""; // expression
  std::string dir = "."; // directory to search
  bool ins=false; // case insensitive
  bool verb=false; // verbose
  bool hasexpopt=false;

  int index;
  int c;
  bool viastdin = true;

  while ((c = getopt (argc, argv,  "mpivhx:d:"))  != -1)
    {   
      switch (c)  
	{  
	case 'm': if(om!=PLS) { om  =  M3U; } else { mperr(); }   break;   
	case 'p': if(om!=M3U) { om  =  PLS; } else { mperr(); }   break;  
	case 'h': print_usage(0); break;
	case 'i': ins=true; break;
	case 'v': verb=true; break;
	case 'x': expr=optarg; hasexpopt=true; break;
	case 'd': dir=optarg; break;
	case  '?': 	  
	  if  (isprint (optopt)) 
	    {
	      fprintf(stderr, "Unknown option  `-%c'.\n",  optopt); 
	      print_usage(1);
	    }
	  else {
	    fprintf(stderr, "Unknown argument `\\x%x'.\n", optopt); 
	    print_usage(1);
	  } 	  
	  
	default:  abort ();
	}
    }

  for (index = optind; index < argc; index++) {
    if(!hasexpopt) {
      if(verb) {
	std::cerr << "searching for expression '" << argv[index] << "' in filenames and ID3Tag-fields" 
		  << std::endl;
      }
      expr=argv[index];
      break;
    }
  }


  if(argv[1]==NULL) { print_usage(1); }
  if(dir != "-") {viastdin=false;} 

  std::vector<std::string> *filelist = new std::vector<std::string>();
  std::strstream results;
  char is[256];
  int nof=1; // starts at 1
  if(viastdin) {
    while( (gets(is)) != NULL ) 
      {
	std::string ls = is;
	filelist->push_back(ls);      
      }
    // end of reading stdin
  }
  else 
    {
      directory *d = new directory(dir);
      filelist=d->getDirEntries();
    }

  std::vector<std::string>::iterator it;
  
  it = filelist->begin();
  
  int visits =  filelist->size();
  while( it != filelist->end() ) 
    {
      std::string rstr = *it;
      
      try 
	{
	  id3read *reader = new id3read(*it);

	  rstr += " " + reader->getTitle(); 
	  rstr += " " + reader->getArtist();
	  rstr += " " + reader->getAlbum();
	  rstr += " " + reader->getYear();
	  rstr += " " + reader->getComment();
	  rstr += " " + reader->getAlbumTrack();
	  rstr += " " + reader->getGenreID();
	} catch(bad_tag xbt)
	  {
	    // nothing
	  } 
	catch(bad_fd xbf) {
	  std::cout << *it << ": file is not readable" << std::endl;
	} catch(bad_openr xbor) {
	  std::cout << *it << ": error opening file" << std::endl;
	}
      

      //int pos = strfind(rstr.c_str(), expr.c_str());
      //if( pos != -1 ) 

      // expr-flags
      int reflags=REG_EXTENDED|REG_NOSUB; // default
      // case insensitive
      if(ins) { reflags =  REG_EXTENDED|REG_NOSUB|REG_ICASE; }

      try {
	if(match(rstr.c_str(), expr.c_str(), reflags))
	  {
	    if(om==PLS) 
	      {	      
		results << "File" << nof << "=";
		nof++;
	      }
	    results << *it << std::endl; // filename	    
	  }
      } catch (bad_re xbr) {
	std::cerr << "could not compile expression: " << 
	  "'" << expr << "'" << std::endl;
	exit(1);
      }
      it++;
    } 

  if(om==PLS) 
    {
      std::cout << "[playlist]" << std::endl;
      std::cout << "NumberOfEntries=" << nof << std::endl;
    }
  if(om==M3U) 
    {
      std::cout << "#EXTM3U" << std::endl;
    }

  std::cout << results.str() << std::endl;
  
  if(verb) {
    std::cerr << visits << " files visited." << std::endl;
  }
  delete filelist;
  return(0);
}


/**********************/

