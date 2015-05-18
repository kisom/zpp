#include <iostream>

#include "zhelpers.h"


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	sub(ctx, ZMQ_SUB);
	sub.connect("tcp://localhost:5563");
	sub.setsockopt(ZMQ_SUBSCRIBE, "B", 1);

	std::cout << "subscribed.\n";

	while (true) {
		std::string	addr = s_recv(sub);
		std::string	data = s_recv(sub);

		std::cout << "[" << addr << "] " << data << std::endl;
	}

	return 0;
}
