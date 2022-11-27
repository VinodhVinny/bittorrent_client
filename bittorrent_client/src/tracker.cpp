#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <openssl/sha.h>
#include <cpr/cpr.h>

#include "../include/bencode_parser.h"
#include "../include/torrent_file.h"
#include "../include/tracker.h"
#include "../include/utils.h"

std::string convert_to_sha1(const std::string &str) {
    std::ofstream fp;
    fp.open("info_hash", std::ios::out);
    fp << str;
    fp.close();

    std::string sha_hash = execute_cmd("/usr/bin/sha1sum info_hash");
    remove("info_hash");

    return sha_hash.substr(0, 40);
}

TrackerRequest::TrackerRequest(TorrentFile &torrent_file, int port) : port(port) {
    this->announce_url = bencode_decode_str(torrent_file._torr_file_map["announce"]);
    this->info_hash = convert_to_sha1(torrent_file._torr_file_map["torr_info"]);
    this->uploaded = 0;
    this->downloaded = 0;
    this->left = bencode_decode_int(torrent_file._torr_info._torr_info_map["length"]);
    this->compact = true;
}

std::string TrackerRequest::build_tracker_url() {
    std::stringstream ss;
    ss << this->announce_url << '?';
    ss << "info_hash=" << this->info_hash << '&';
    ss << "peer_id=" << this->peer_id << '&';
    ss << "port=" << this->port << '&';
    ss << "uploaded=" << this->uploaded << '&';
    ss << "downloaded=" << this->downloaded << '&';
    ss << "compact=" << this->compact;

    return ss.str();
}

std::string TrackerRequest::announce() {
    cpr::Response response = cpr::Get(cpr::Url{this->build_tracker_url()});
    std::cout << response.text << '\n';
    return response.text;
}
