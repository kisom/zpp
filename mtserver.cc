#include <pthread.h>

#include "zhelpers.h"


static void *
worker_routine(void *ctx)
{
	zmq::socket_t	rcvr((zmq::context_t &)ctx, ZMQ_REP);
	rcvr.connect("inproc://workers");

	while (true) {
		std::string	data = s_recv(rcvr);
		std::cout << "Received request: " << data << std::endl;
		sleep(1);

		data = "World";
		s_send(rcvr, data);
	}

	return NULL;
}


int
main(int argc, char *argv[])
{
	zmq::context_t	ctx(1);

	zmq::socket_t	clients(ctx, ZMQ_ROUTER);
	clients.connect("tcp://*:5555");

	zmq::socket_t	workers(ctx, ZMQ_DEALER);
	workers.bind("inproc://workers");

	for (int i = 0; i < 4; i++) {
		pthread_t	worker;
		pthread_create(&worker, NULL, worker_routine, ctx);
	}

	zmq::proxy(clients, workers, NULL);
	return 0;
}
