CC = g++
CPPFLAGS = -g --std=c++14 -I$(IDIR)
IDIR = include
LIBS = -ljsoncpp -lssl -lcrypto -lcpr

%.o: src/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS)

main: main.o bencode_decode.o bencode_encode.o torrent_file.o tracker.o utils.o
	$(CC) -o $@ $^ $(CPPFLAGS) $(LIBS)

clean:
	rm -rf *.o main
