#ifndef _TORRENT_
#define _TORRENT_

#include <iostream>
#include <map>

class TorrentInfo {
public:
    std::map<std::string, std::string> _torr_info_map;
};

class TorrentFile {
public:
    std::string torr_file;
    std::map<std::string, std::string>  _torr_file_map;
    TorrentInfo _torr_info;

    TorrentFile(const std::string &torr_file);
};


#endif
