
/* id3read.cc  ********/

#include "id3read.h"

id3read::id3read(const std::string& _mp3file)
{
    id3read(_mp3file.c_str());
}

id3read::id3read(const char* _mp3file)
{
    touched=false;
    char c;
    register char i=0;
    const char* tagchk="TAG";
    bool ver_1_1_124=false;
    bool ver_1_1_125=false;
    
    if(!_mp3file)
    { throw bad_fd(); }
    mp3file2edit = new std::string(_mp3file);
    ifs = new std::ifstream(mp3file2edit->c_str(), std::ios_base::ate);
    if(!ifs)
    {
        throw bad_openr();
    }
    
    ifs->seekg(-128, std::ios_base::end);
    
    if(ifs->tellg()==0)
    {
        //throw bad_tag();
        throw bad_file();
    }
    
    for(i=0; i<3; i++)
    {
        ifs->get(c);
        ftag+=c;
    }
    if(ftag==tagchk)
    {
        // ok
    }
    else
    {
        throw bad_tag(ftag);
    }
    
    for(i=3; i<33; i++)
    {
        ifs->get(c);
        title+=c;
    }
    //std::cout << "debug: title(3-33)=" << title << std::endl;
    
    for(i=33; i<63; i++)
    {
        ifs->get(c);
        artist+=c;
    }
    
    for(i=63; i<93; i++)
    {
        ifs->get(c);
        album+=c;
    }
    
    for(i=93; i<97; i++)
    {
        ifs->get(c);
        year+=c;
    }
    
    for(i=97; i<127; i++)
    {
        ifs->get(c);
        if( (i==124) && (c!='\0') )
        { ver_1_1_124=true; }
        if( (i==125) && (c=='\0') )
        { ver_1_1_125=true; }
        if(ver_1_1_124 && ver_1_1_125)
        { ver_1_1=true; }
        if(checkVer11() &&  (c==126) )
        { albumTrack=c; }
        comment+=c;
    }
    
    // offset=127
    ifs->get(c);
    genreID=(unsigned char)c;
}

id3read::~id3read()
{
    if(touched)
    {
        _flush();
        ofs->close();
    }
}

bool id3read::isVer11()
{
    return(checkVer11());
}

std::string id3read::getTitle()
{
    return title;
}

std::string id3read::getArtist()
{
    return artist;
}

std::string id3read::getAlbum()
{
    return album;
}

int id3read::getYear()
{
    return atoi(year.c_str());
}

std::string id3read::getComment()
{
    return comment;
}

int id3read::getAlbumTrack()
{
    char *buf = new char[6];
    sprintf(buf, "%02d", albumTrack);
    return atoi(buf);
}

int id3read::getGenreID()
{
    char* buf = new char[2];
    sprintf(buf, "%03d", genreID);
    return atoi(buf);
}

std::string id3read::getGenre()
{
    if( (getGenreID()<GENRES) && (getGenreID()>=0) )
    {
        return genres[getGenreID()];
    }
    else
    {
        std::string gidstr = "#" + getGenreID();
    }
}


bool id3read::checkVer11()
{
    return(ver_1_1);
}


void id3read::setTitle(const std::string& _title)
{
    touched=true;
    title=_title;
}

void id3read::setArtist(const std::string& _artist)
{
    touched=true;
    artist=_artist;
}

void id3read::setAlbum(const std::string& _album)
{
    touched=true;
    album=_album;
}

void id3read::setYear(const std::string& _year)
{
    touched=true;
    year=_year;
}

void id3read::setComment(const std::string& _comment)
{
    touched=true;
    comment=_comment;
}

void id3read::setAlbumTrack(const int _track)
{
    if(_track>255)
    { throw bad_id(); }  touched=true;
    albumTrack=_track;
}

void id3read::setAlbumTrack(const std::string& _strack)
{
    setAlbumTrack((char)atoi(_strack.c_str()));
}

void id3read::setGenre(const std::string& _genre)
{
    touched=true;
    genre=_genre;
    // TODO: genreID=getIDByGenre(genre);
}

void id3read::setGenreID(const int _genreid)
{
    if(_genreid>255)
    { throw bad_id(); }
    touched=true;
    genreID=_genreid;
    // TODO: genre=getGenreByID(genreid);
}

void id3read::setGenreID(const std::string& _sgenreid)
{
    setGenreID((char)atoi(_sgenreid.c_str()));
}

void id3read::flush()
{
    if(touched)
    {
        _flush();
    }
}

void id3read::_flush()
{
    signed int tagpos=-128;
    ofs = new std::ofstream(mp3file2edit->c_str(), std::ios_base::ate);
    if(!ofs)
    {
        //       std::cout << "fehler beim �ffen (w) :"
        // 		<< mp3file2edit << std::endl;
        throw bad_openw();
    }
    
    ofs->seekp(tagpos, std::ios_base::end);
    ofs->write("TAG", 3);
    tagpos+=3;
    
    ofs->seekp(tagpos, std::ios_base::end);
    ofs->write(title.c_str(), 30);
    tagpos+=30;
    
    ofs->seekp(tagpos, std::ios_base::end);
    ofs->write(artist.c_str(), 30);
    tagpos+=30;
    
    ofs->seekp(tagpos, std::ios_base::end);
    ofs->write(album.c_str(), 30);
    tagpos+=30;
    
    ofs->seekp(tagpos, std::ios_base::end);
    ofs->write(year.c_str(), 4);
    tagpos+=4;
    
    ofs->seekp(tagpos, std::ios_base::end);
    ofs->write(comment.c_str(), 29);
    tagpos+=29;
    
    ofs->seekp(tagpos, std::ios_base::end);
    ofs->put(albumTrack);
    tagpos+=1;
    
    ofs->seekp(tagpos, std::ios_base::end);
    ofs->put(genreID);
    
    //ofs->flush();
}


/**********************/

