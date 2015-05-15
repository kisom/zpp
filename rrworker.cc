#include <iostream>

#include "zhelpers.h"


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	responder(ctx, ZMQ_REP);
	responder.connect("tcp://localhost:5560");

	while (true) {
		std::string	data = s_recv(responder);
		std::cout << "Received request: " << data << std::endl;

		sleep(1);

		data = "World";
		s_send(responder, data);
	}

	return 0;
}
