
/* id3read.h  ********/

#ifndef __ID3READ__H__
#define __ID3READ__H__

#include <exception>
#include <iostream>
#include <fstream>

extern "C" {
#include <string.h>
}

#define BRAND   "id3dump v0.6 Sonntag, 15. Oktober 2006, 16:28:01 Uhr CEST  tb@veljanov "
#define GENRES  128

const char genres[126][24] = 
{
"Blues",
"ClassicRock",
"Country",
"Dance",
"Disco",
"Funk",
"Grunge",
"HipHop",
"Jazz",
"Metal",
"NewAge",
"Oldies",
"Other",
"Pop",
"RhythmBlues",
"Rap",
"Reggae",
"Rock",
"Techno",
"Industrial",
"Alternative",
"Ska",
"DeathMetal",
"Pranks",
"Soundtrack",
"EuroTechno",
"Ambient",
"TripHop",
"Vocal",
"JazzFunk",
"Fusion",
"Trance",
"Classical",
"Instrumental",
"Acid",
"House",
"Game",
"SoundClip",
"Gospel",
"Noise",
"AlternativeRock",
"Bass",
"Soul",
"Punk",
"Space",
"Meditative",
"InstrumentalPop",
"InstrumentalRock",
"Ethnic",
"Gothic",
"DarkWave",
"TechnoIndustrial",
"Electronic",
"PopFolk",
"EuroDance",
"Dream",
"SouthernRock",
"Comedy",
"Cult",
"Gangsta",
"Top40",
"ChristianRap",
"PopFunk",
"Jungle",
"NativeAmerican",
"Cabaret",
"NewWave",
"Psychedelic",
"Rave",
"ShowTunes",
"Trailer",
"LowFi",
"Tribal",
"AcidPunk",
"AcidJazz",
"Polka",
"Retro",
"Musical",
"RockNRoll",
"HardRock",
"EXT_Folk",
"EXT_FolkRock",
"EXT_NationalFolk",
"EXT_Swing",
"EXT_FastFusion",
"EXT_Bebop",
"EXT_Latin",
"EXT_Revival",
"EXT_Celtic",
"EXT_Bluegrass",
"EXT_AvanteGarde",
"EXT_GothicRock",
"EXT_ProgressiveRock",
"EXT_PsychedelicRock",
"EXT_SymphonicRock",
"EXT_SlowRock",
"EXT_BigBand",
"EXT_Chorus",
"EXT_EasyListening",
"EXT_Acoustic",
"EXT_Humour",
"EXT_Speech",
"EXT_Chanson",
"EXT_Opera",
"EXT_ChamberMusic",
"EXT_Sonata",
"EXT_Symphony",
"EXT_BootyBass",
"EXT_Primus",
"EXT_PornGroove",
"EXT_Satire",
"EXT_SlowJam",
"EXT_Club",
"EXT_Tango",
"EXT_Samba",
"EXT_Folklore",
"EXT_Ballad",
"EXT_PowerBallad",
"EXT_RhythmicSoul",
"EXT_Freestyle",
"EXT_Duet",
"EXT_PunkRock",
"EXT_DrumSolo",
"EXT_ACappella",
"EXT_EuroHouse",
"EXT_DanceHall"
};

class bad_fd {
 public:
  bad_fd(){}
};

class bad_open {
 public:
  bad_open(){}
};

class bad_openr : bad_open {
 public:
  bad_openr(){}
};

class bad_openw : bad_open {
 public:
  bad_openw(){}
};

class bad_tag {
 private:
    std::string _instead;
 public:
  const char* get_instead() { 
      if(_instead!="") {
          std::string ts = _instead;             
          char _hext[6];
          sprintf(_hext, "%x", ts.c_str());
          return _hext;
      } else { return "[nothing]"; }
  }
  bad_tag() {
    _instead="";
  }
  bad_tag(const std::string& insteadoftag){
    _instead=insteadoftag;
  }
};

class bad_id {
 public:
  bad_id(){}
};

class bad_file {
 public:
  bad_file(){}
};


class id3read
{
 public:
  id3read(const std::string& _mp3file);
  id3read(const char* _mp3file);
  ~id3read();

  std::string getTitle();
  std::string getArtist();
  std::string getAlbum();
  int getYear();
  std::string getComment();
  int getAlbumTrack(); 
  std::string getGenre();
  int getGenreID();
  
  void setTitle(const std::string&);
  void setArtist(const std::string&);
  void setAlbum(const std::string&);
  void setYear(const std::string&);
  void setComment(const std::string&);
  void setAlbumTrack(const int); 
  void setAlbumTrack(const std::string&);
  void setGenre(const std::string&);
  void setGenreID(const int);
  void setGenreID(const std::string&);
  
  bool isVer11();

  void flush();


 private:
  // base file info vars
  std::string *mp3file2edit;
  bool ver_1_1;

  // file operation spec vars
  std::string ftag;  
  bool touched;

  // members
  //std::string chunk;

  // fields
  std::string title;
  std::string artist;
  std::string album;
  std::string year;
  std::string comment;
  std::string genre;
  unsigned char albumTrack;
  unsigned char genreID; 

  // delegates
  std::ifstream *ifs;
  std::ofstream *ofs;


  /* private methods */
  // ...
  bool checkVer11();
  void _flush();
};

#endif

/**********************/
