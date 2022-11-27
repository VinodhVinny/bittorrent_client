#ifndef _TRACKER_
#define _TRACKER_

#include <iostream>
#include <json/json.h>

#include "../include/torrent_file.h"

static const std::string PEER_ID = "fYfaiT5kmlzb3aojRBYW";

class TrackerRequest {
public:
    std::string announce_url;
    std::string info_hash;
    std::string peer_id = PEER_ID;
    int port;
    int uploaded;
    int downloaded;
    int left;
    bool compact;

    TrackerRequest(TorrentFile &torrent_file, int port);
    std::string build_tracker_url();
    std::string announce();
};

#endif
