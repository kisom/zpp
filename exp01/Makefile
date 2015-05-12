targets =	server client
LDFLAGS =	-lprotobuf -lzmq -lstdc++
CPPFLAGS =	-g -std=c++14 messages.pb.cc

.PHONY: all
all: $(targets)

server: server.cc messages.pb.cc messages.pb.h
	clang -o $@ $(CPPFLAGS) server.cc $(LDFLAGS)

client: client.cc messages.pb.cc messages.pb.h
	clang -o $@ $(CPPFLAGS) client.cc $(LDFLAGS)

messages.pb.cc: messages.proto
	protoc messages.proto --cpp_out .

messages.pb.h: messages.proto
	protoc messages.proto --cpp_out .

clean:
	rm -f messages.pb.* $(targets)
