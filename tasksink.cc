#include <sys/time.h>

#include <ctime>
#include <iostream>

#include <zmq.hpp>


int
main(int argc, char *argv[])
{
	zmq::context_t	context(1);
	zmq::socket_t	receiver(context, ZMQ_PULL);
	receiver.bind("tcp://*:5558");

	zmq::message_t	message;
	receiver.recv(&message);

	struct timeval	tstart;
	gettimeofday(&tstart, NULL);

	int	i;
	int	total_msec = 0;

	for (i = 0; i < 100; i++) {
		receiver.recv(&message);
		if ((i / 10) * 10 == i) {
			std::cout << ":" << std::flush;
		} else {
			std::cout << "." << std::flush;
		}
	}

	struct timeval	tend, tdiff;
	gettimeofday(&tend, NULL);

	if (tend.tv_usec < tstart.tv_usec) {
		tdiff.tv_sec = tend.tv_sec - tstart.tv_sec - 1;
		tdiff.tv_usec = 1000000 + tend.tv_usec - tstart.tv_usec;
	}
	else {
		tdiff.tv_sec = tend.tv_sec - tstart.tv_sec;
		tdiff.tv_usec = tend.tv_usec - tstart.tv_usec;
	}

	total_msec = tdiff.tv_sec * 1000 + tdiff.tv_usec / 1000;
	std::cout << "\nTotal elapsed time: " << total_msec << " msec\n" << std::endl;
	return 0;
}
