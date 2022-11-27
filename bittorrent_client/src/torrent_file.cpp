#include <fstream>
#include <sstream>
#include <json/json.h>

#include "../include/bencode_parser.h"
#include "../include/torrent_file.h"

TorrentFile::TorrentFile(const std::string &torr_file) : torr_file(torr_file) {
    std::ifstream file(this->torr_file);
    if (!file) {
        std::cout << "\nError: No such file <" << this->torr_file << "> present\n\n";
        exit(1);
    }

    std::stringstream torr_str_buff;
    torr_str_buff << file.rdbuf();
    file.close();

    // new line at the end of torr_str must be removed
    std::string torr_str = torr_str_buff.str();
    if (torr_str[torr_str.length()-1] == '\n') torr_str.pop_back();

    Json::Value torrent_file = bencode_decode(torr_str);
    Json::Value torrent_file_info = torrent_file["info"];

    for (Json::Value::const_iterator itr = torrent_file.begin(); itr != torrent_file.end(); itr++) {
        if (itr.key().asString() == "info") continue;
        if (itr->isString()) this->_torr_file_map[itr.key().asString()] = bencode_encode_str(*itr);
        else if (itr->isInt()) this->_torr_file_map[itr.key().asString()] = bencode_encode_int(*itr);
        else if (itr->isArray()) this->_torr_file_map[itr.key().asString()] = bencode_encode_list(*itr);
        else this->_torr_file_map[itr.key().asString()] = bencode_encode_dict(*itr);
    }

    for (Json::Value::const_iterator itr = torrent_file_info.begin(); itr != torrent_file_info.end(); itr++) {
        if (itr->isString()) this->_torr_info._torr_info_map[itr.key().asString()] = bencode_encode_str(*itr);
        else if (itr->isInt()) this->_torr_info._torr_info_map[itr.key().asString()] = bencode_encode_int(*itr);
        else if (itr->isArray()) this->_torr_info._torr_info_map[itr.key().asString()] = bencode_encode_list(*itr);
        else this->_torr_info._torr_info_map[itr.key().asString()] = bencode_encode_dict(*itr);
    }

    // to keep torrent info as bencoded string format in TorrentFile class itself
    this->_torr_file_map["torr_info"] = bencode_encode(torrent_file_info);
}
