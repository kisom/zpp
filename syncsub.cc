#include <iostream>

#include "zhelpers.h"


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	sub(ctx, ZMQ_SUB);
	sub.connect("tcp://localhost:5561");
	sub.setsockopt(ZMQ_SUBSCRIBE, "", 0);

	// Need to wait for subscription.
	sleep(2);

	std::cout << "waiting for subscription\n";

	zmq::socket_t	sync(ctx, ZMQ_REQ);
	sync.connect("tcp://localhost:5562");
	std::cout << "synchronise... ";
	s_send(sync, "");
	s_recv(sync);
	std::cout << "OK\n";

	int	i = 0;
	while (true) {
		std::string	data = s_recv(sub);
		if (data == "END") {
			break;
		}

		i++;
	}

	std::cout << "received " << i << " updates\n";
	return 0;
}
