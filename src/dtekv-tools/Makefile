CXX=g++
CXXFLAGS=-O2 -Wall
LDFLAGS=-L. -Wl,-rpath='$$ORIGIN'
LDLIBS=-ljtag_atlantic -ljtag_client

all: dtekv-run dtekv-upload dtekv-download dtekv-jtag-server

dtekv-run: dtekv-run.c
	$(CXX) $(CXXFLAGS) dtekv-run.c -o dtekv-run $(LDLIBS) $(LDFLAGS)

dtekv-upload: dtekv-upload.c
	$(CXX) $(CXXFLAGS) dtekv-upload.c -o dtekv-upload $(LDLIBS) $(LDFLAGS)

dtekv-download: dtekv-download.c
	$(CXX) $(CXXFLAGS) dtekv-download.c -o dtekv-download $(LDLIBS) $(LDFLAGS)

dtekv-jtag-server: dtekv-jtag-server.c
	$(CXX) $(CXXFLAGS) dtekv-jtag-server.c -o dtekv-jtag-server $(LDLIBS) $(LDFLAGS)

clean:
	rm -f dtekv-run dtekv-upload dtekv-download dtekv-jtag-server
