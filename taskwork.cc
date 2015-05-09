#include "zhelpers.h"

int
main(int argc, char *argv[])
{
	zmq::context_t	context(1);

	zmq::socket_t	receiver(context, ZMQ_PULL);
	receiver.connect("tcp://localhost:5557");

	zmq::socket_t	sender(context, ZMQ_PUSH);
	sender.connect("tcp://localhost:5558");

	while (true) {
		zmq::message_t	task;
		int		workload;

		receiver.recv(&task);
		std::istringstream	iss(static_cast<char *>(task.data()));
		iss >> workload;

		s_sleep(workload);

		task.rebuild();
		sender.send(task);

		std::cout << "." << std::flush;
	}

	std::cout << std::endl;
	return 0;
}
