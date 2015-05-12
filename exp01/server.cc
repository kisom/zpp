#include <iostream>
#include <cstring>
#include <stdexcept>

#include <zmq.hpp>
#include "messages.pb.h"


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
		if (!m.ParseFromString(std::string((char *)msg.data(), msg.size()))) {
			throw std::runtime_error("failed to parse message");
		}

		std::cout << "Received message " << m.contents()
			  << " from UID " << m.uid() << std::endl;

		msg::Ack	ack;
		ack.set_ok(true);

		std::string	ack_ser;
		if (!ack.SerializeToString(&ack_ser)) {
			throw std::runtime_error("failed to serialize ack");
		}

		zmq::message_t	rep(ack_ser.size());
		memcpy((void *)rep.data(), ack_ser.c_str(), ack_ser.size());
		sock.send(rep);
	}
}
