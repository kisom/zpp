#include <iostream>
#include "zhelpers.h"

const int	EXPECTED_SUBS = 10;


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	pub(ctx, ZMQ_PUB);
	pub.bind("tcp://*:5561");

	zmq::socket_t	sync(ctx, ZMQ_REP);
	sync.bind("tcp://*:5562");

	int	subscribers	= 0;
	std::cout << "waiting for subscribers\n";
	while (subscribers < EXPECTED_SUBS) {
		s_recv(sync);
		s_send(sync, "");
		subscribers++;
		std::cout << "." << std::flush;
	}
	std::cout << std::endl;

	std::cout << "broadcasting\n";
	for (int i = 0; i < 1000000; i++) {
		s_send(pub, "data");
	}
	s_send(pub, "END");

	sleep(1);

	return 0;
}
