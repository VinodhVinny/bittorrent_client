#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h>

#include "../include/bencode_parser.h"
#include "../include/torrent_file.h"
#include "../include/tracker.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "\nUsage: " << argv[0] << "<torrent file>\n\n";
        return 1;
    }

    TorrentFile torrent_file(argv[1]);
    TrackerRequest tracker(torrent_file, 6881);
    std::string tracker_announce = tracker.announce();
    std::cout << bencode_decode(tracker_announce) << '\n';
}
