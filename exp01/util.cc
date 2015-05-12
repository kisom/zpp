#include <cstring>

#include <google/protobuf/message.h>
#include <zmq.hpp>

#include "util.h"


bool
zmq_receive(zmq::socket_t *sock, google::protobuf::Message *pbmsg)
{
	zmq::message_t	zmsg;
	if (!sock->recv(&zmsg)) {
		return false;
	}

	std::string data((char *)zmsg.data(), zmsg.size());
	return pbmsg->ParseFromString(data);
}

bool
zmq_send(zmq::socket_t *sock, google::protobuf::Message *pbmsg)
{
	std::string data;

	if (!pbmsg->SerializeToString(&data)) {
		return false;
	}
	zmq::message_t	zmsg(data.size());
	memcpy((void *)zmsg.data(), data.c_str(), data.size());
	return sock->send(zmsg);
}
