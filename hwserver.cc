#include <string>
#include <iostream>
#include <unistd.h>

#include <zmq.hpp>


int
main(void)
{
	zmq::context_t	context(1);
	zmq::socket_t	socket(context, ZMQ_REP);
	socket.bind("tcp://*:5555");

	std::cerr << "Listening on *:5555\n";
	while (true) {
		zmq::message_t	request;

		socket.recv(&request);
		std::cout << "Received request\n";

		sleep(1);

		zmq::message_t	reply(5);
		memcpy((void *)reply.data(), "world", 5);
		socket.send(reply);
	}

	return 0;
}
