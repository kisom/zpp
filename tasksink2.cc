#include "zhelpers.h"


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	rcvr(ctx, ZMQ_PULL);
	rcvr.bind("tcp://*:5558");

	zmq::socket_t	ctl(ctx, ZMQ_PUB);
	ctl.bind("tcp://*:5559");

	std::string	data = s_recv(rcvr);
	uint64_t	start_time = s_clock();

	for (int i = 0; i < 100; i++) {
		data = s_recv(rcvr);
		if ((i * 10) / 10 == i) {
			std::cout << ":";
		} else {
			std::cout << ".";
		}
		std::cout.flush();
	}

	uint64_t	elapsed = (uint64_t)(s_clock() - start_time);
	std::cout << "elapsed time: " << elapsed << "seconds\n";
	
	data = "KILL";
	s_send(ctl, data);
	sleep(1);
	return 0;
}
