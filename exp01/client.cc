#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include <zmq.hpp>
#include "messages.pb.h"
#include "util.h"


int
main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " message uid\n";
		exit(1);
	}

	zmq::context_t	ctx(1);
	zmq::socket_t	sock(ctx, ZMQ_REQ);
	sock.connect("tcp://localhost:5554");

	msg::Message	m;
	m.set_contents(argv[1]);
	m.set_uid((uint32_t)atoi(argv[2]));

	if (!zmq_send(&sock, &m)) {
		throw std::runtime_error("failed to serialise message");
	}
	std::cout << "Message sent.\n";

	msg::Ack	ack;
	if (!zmq_receive(&sock, &ack)) {
		throw std::runtime_error("failed to parse ack");
	}

	if (ack.ok()) {
		std::cout << "OK\n";
	} else {
		std::cout << "Failed\n";
	}

	sock.close();
	ctx.close();
}
