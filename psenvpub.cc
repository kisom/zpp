#include <iostream>

#include "zhelpers.h"


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	pub(ctx, ZMQ_PUB);
	pub.bind("tcp://*:5563");

	while (true) {
		std::cout << "publish A" << std::endl;
		s_sendmore(pub, "A");
		s_send(pub, "shouldn't see this");

		std::cout << "publish B" << std::endl;
		s_sendmore(pub, "B");
		s_send(pub, "hello there");

		sleep(1);
	}
}
