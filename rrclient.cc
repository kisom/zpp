#include "zhelpers.h"

int
main(int argc, char *argv[])
{
	zmq::context_t	ctx(1);
	zmq::socket_t	req(ctx, ZMQ_REQ);
	req.connect("tcp://localhost:5559");

	for (int i = 0; i < 10; i++) {
		s_send(req, "Hello");
		auto reply = s_recv(req);
		std::cout << "Reply " << i << ": " << reply << std::endl;
	}
}
