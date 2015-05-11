#include <iostream>

#include "zhelpers.h"


int
main(int argc, char *argv[])
{
	zmq::context_t	ctx(4);

	zmq::socket_t	receiver(ctx, ZMQ_PULL);
	receiver.connect("tcp://localhost:5557");

	zmq::socket_t	subscriber(ctx, ZMQ_SUB);
	subscriber.connect("tcp://localhost:5556");
	subscriber.setsockopt(ZMQ_SUBSCRIBE, "10001 ", 6);

	zmq::pollitem_t	pollset[] = {
		{receiver, 0, ZMQ_POLLIN, 0},
		{subscriber, 0, ZMQ_POLLIN, 0}
	};

	zmq::socket_t	sender(ctx, ZMQ_PUSH);
	sender.connect("tcp://localhost:5558");

	size_t		count = 0;
	const size_t	limit = 100;
	int		total_temp = 0, total_work = 0, wup = 0, jobs = 0;

	while (count++ < limit) {
		std::cout << "Polling...\n";
		zmq::message_t	message;
		zmq::poll(&pollset[0], 2, -1);

		if (pollset[0].revents & ZMQ_POLLIN) {
			int	workload;

			receiver.recv(&message);
			std::istringstream	iss(static_cast<char *>(message.data()));
			iss >> workload;

			std::cout << "Received task (" << workload << ")\n";
			s_sleep(workload);
			message.rebuild();
			sender.send(message);
			total_work += workload;
			jobs++;
		}

		if (pollset[1].revents & ZMQ_POLLIN) {
			size_t		counter;
			int		zipcode, temp, relhumidity;

			subscriber.recv(&message);
			std::istringstream iss(static_cast<char *>(message.data()));
			iss >> zipcode >> counter >> temp >> relhumidity;

			std::cout << "Received update #" << counter << std::endl;
			total_temp += temp;
			wup++;
	
		}
	}

	if (wup > 0) {
	std::cout << "Received " << wup 
		  << " weather updates with average temperature "
		  << (int)(total_temp / wup) << std::endl;
	} else {
		std::cout << "No weather updates received.\n";
	}

	std::cout << "Total workload processed: " << total_work
		  << " over " << jobs << " jobs.\n";
	return 0;
}
