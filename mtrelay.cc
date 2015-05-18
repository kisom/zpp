#include <iostream>

#include "zhelpers.h"


static void *
step1(void *ctx)
{
	zmq::socket_t	xmitter((zmq::context_t &)ctx, ZMQ_PAIR);
	xmitter.connect("inproc://step2");

	std::cout << "step 1 ready, signalling step 2\n";
	s_send(xmitter, "READY");
	return NULL;
}


static void *
step2(void *ctx)
{
	zmq::socket_t	rcvr((zmq::context_t &)ctx, ZMQ_PAIR);
	rcvr.bind("inproc://step2");

	pthread_t	thread;
	pthread_create(&thread, NULL, step1, ctx);

	s_recv(rcvr);

	zmq::socket_t	xmitter((zmq::context_t &)ctx, ZMQ_PAIR);
	xmitter.connect("inproc://step3");
	std::cout << "step 2 ready, signalling step 3\n";

	s_send(xmitter, "READY");
	return NULL;
}


int
main(void)
{
	zmq::context_t	ctx(1);

	zmq::socket_t	rcvr(ctx, ZMQ_PAIR);
	rcvr.bind("inproc://step3");

	pthread_t	thread;
	pthread_create(&thread, NULL, step2, ctx);

	std::string	data = s_recv(rcvr);
	std::cout << "test succeeds\n";

	return 0;
}
