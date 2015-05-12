targets =	server client
extras =	messages.pb.h messages.pb.cc util.h util.cc
LDFLAGS =	-lprotobuf -lzmq -lstdc++
CPPFLAGS =	-g -std=c++14 messages.pb.cc util.cc

.PHONY: all
all: $(targets)

server: server.cc $(extras)
	clang -o $@ $(CPPFLAGS) server.cc $(LDFLAGS)

client: client.cc $(extras)
	clang -o $@ $(CPPFLAGS) client.cc $(LDFLAGS)

messages.pb.cc: messages.proto
	protoc messages.proto --cpp_out .

messages.pb.h: messages.proto
	protoc messages.proto --cpp_out .

clean:
	rm -f messages.pb.* $(targets)
