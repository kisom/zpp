#include <iostream>

#include "zhelpers.h"


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	frontend(ctx, ZMQ_ROUTER);
	zmq::socket_t	backend(ctx, ZMQ_DEALER);
	frontend.bind("tcp://*:5559");
	backend.bind("tcp://*:5560");

	zmq::proxy(frontend, backend, NULL);

	return 0;
}
