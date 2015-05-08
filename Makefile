CPPFLAGS =	-std=c++14 -stdlib=libstdc++
LDFLAGS =	-lzmq -lstdc++
TARGETS =	hwserver hwclient echo_server

all: $(TARGETS)

hwserver: hwserver.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS)

hwclient: hwclient.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS)

echo_server: echo_server.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGETS) 
