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
		zmq::message_t	msg;
		sock.recv(&msg);

		msg::Message	m;
		if (!parse_zmq_message(&msg, &m)) {

			throw std::runtime_error("failed to parse message");
		}

		std::cout << "Received message " << m.contents()
			  << " from UID " << m.uid() << std::endl;

		zmq::message_t	rep;
		msg::Ack	ack;
		ack.set_ok(true);

		if (!serialize_zmq_message(&rep, &ack)) {
			throw std::runtime_error("failed to serialize ack");
		}
		sock.send(rep);
	}
}
