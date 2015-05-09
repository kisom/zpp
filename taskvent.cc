#include <sys/time.h>

#include <iostream>
#include <ctime>
#include <unistd.h>

#include <zmq.hpp>


inline int
within(int num)
{
	return ((float)num * random()) / (RAND_MAX + 1.0);
}


int
main(int argc, char *argv[])
{
	zmq::context_t	context(1);

	zmq::socket_t	vent(context, ZMQ_PUSH);
	vent.bind("tcp://*:5557");

	std::cout << "Press Enter when the workers are ready: " << std::endl;
	getchar ();
	std::cout << "Sending tasks to workers…\n" << std::endl;

	zmq::socket_t	sink(context, ZMQ_PUSH);
	sink.connect("tcp://localhost:5558");

	zmq::message_t	task(2);
	memcpy(task.data(), "0", 1);
	sink.send(task);

	srandom(0);

	int	i;
	int	total_msec = 0;

	for (i = 0; i < 100; i++) {
		int	workload;

		workload = within(100) + 1;
		total_msec += workload;

		task.rebuild(10);
		sprintf((char *)task.data(), "%d", workload);
		vent.send(task);
	}

	std::cout << "Total expected cost: " << total_msec << " msec" << std::endl;
	sleep(1);

	return 0;
}
