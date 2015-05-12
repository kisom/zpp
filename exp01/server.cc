#include <iostream>
#include <cstring>
#include <stdexcept>

#include <zmq.hpp>
#include "messages.pb.h"
#include "util.h"


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	sock(ctx, ZMQ_REP);
	sock.bind("tcp://*:5554");

	while (true) {
		msg::Message	m;
		if (!zmq_receive(&sock, &m)) {

			throw std::runtime_error("failed to parse message");
		}

		std::cout << "Received message " << m.contents()
			  << " from UID " << m.uid() << std::endl;

		msg::Ack	ack;
		ack.set_ok(true);

		if (!zmq_send(&sock, &ack)) {
			throw std::runtime_error("failed to serialize ack");
		}
	}
}
