#include <iostream>
#include <string>

#include <zmq.hpp>


static std::string
msg_contents(zmq::message_t *msg)
{
	auto mlen = msg->size()+1;
	auto mchar = new char[mlen];
	memcpy(mchar, (void *)msg->data(), mlen-1);
	std::string mstr(mchar);
	free(mchar);
	return mstr;
}


int
main(void)
{
	zmq::context_t	ctx(1);
	zmq::socket_t	sock(ctx, ZMQ_REP);
	sock.bind("tcp://*:5555");

	std::cout << "Listening on *:5555…\n";
	while(true) {
		zmq::message_t	req;
		sock.recv(&req);
		std::cout << "Message received\n";

		std::string msg = msg_contents(&req);
		std::cout << "Message: " << msg << std::endl;

		zmq::message_t	res(2);
		memcpy((void *)res.data(), "OK", 2);
		sock.send(res);
	}

	return 0;
}
