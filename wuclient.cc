#include <iostream>
#include <sstream>

#include <zmq.hpp>


int
main(int argc, char *argv[])
{
	zmq::context_t	context(1);
	zmq::socket_t	subscriber(context, ZMQ_SUB);
	subscriber.connect("tcp://localhost:5556");

	const char	*filter = (argc > 1) ? argv[1] : "10001 ";
	subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));

	int	i;
	long	total_temp = 0;
	for (i = 0; i < 10000000; i++) {
		zmq::message_t	update;
		size_t		counter;
		int		zipcode, temp, relhumidity;

		subscriber.recv(&update);
		std::istringstream iss(static_cast<char *>(update.data()));
		iss >> zipcode >> counter >> temp >> relhumidity;

		std::cout << "Received update #" << counter << std::endl;
		total_temp += temp;
	}

	std::cout << "Average temperature for zipcode '" << filter
		  << "' was " << (int)(total_temp / i) << "F.\n";
	return 0;
}
