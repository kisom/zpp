#include "zhelpers.h"


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	rcvr(ctx, ZMQ_PULL);
	rcvr.connect("tcp://localhost:5557");
	
	zmq::socket_t	sender(ctx, ZMQ_PUSH);
	sender.connect("tcp://localhost:5558");

	zmq::socket_t	ctl(ctx, ZMQ_SUB);
	ctl.connect("tcp://localhost:5559");
	ctl.setsockopt(ZMQ_SUBSCRIBE, "", 0);

	zmq::pollitem_t items[] = {
		{rcvr, 0, ZMQ_POLLIN, 0},
		{ctl,  0, ZMQ_POLLIN, 0}
	};

	while (true) {
		zmq::message_t	m;
		zmq::poll(items, 2, -1);

		if (items[0].revents & ZMQ_POLLIN) {
			int			workload;
			std::istringstream	iss(static_cast<char*>(m.data()));

			iss >> workload;
			s_sleep(workload);

			m.rebuild();
			sender.send(m);
		}

		if (items[1].revents & ZMQ_POLLIN) {
			break;
		}
	}
}
