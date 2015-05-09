#include <iostream>
#include <cstdio>
#include <cstdlib>
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
	zmq::socket_t	publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5556");
	publisher.bind("ipc://weather.ipc");
	int		delay = 0;

	if (argc > 1) {
		delay = atoi(argv[1]);
	}

	srandom(0);
	std::cout << "Start up delay: " << delay << std::endl;
	sleep(delay);
	size_t	counter = 0;
	while (true) {
		int	zipcode, temp, relhumidity;

		zipcode = within(100000);
		temp = within(215) - 80;
		relhumidity = within(50) + 10;

		zmq::message_t	message(31);
		snprintf((char *)message.data(), 31, "%05d %10lu %d %d",
		    zipcode, counter++, temp, relhumidity);
		publisher.send(message);
	}

	return 0;
}
