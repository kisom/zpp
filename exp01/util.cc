//
// Created by kyle on 5/11/15.
//

#include <cstring>

#include <google/protobuf/message.h>
#include <zmq.hpp>

#include "util.h"


bool
parse_zmq_message(zmq::message_t *zmsg, google::protobuf::Message *pbmsg)
{
    std::string data((char *)zmsg->data(), zmsg->size());
    return pbmsg->ParseFromString(data);
}

bool
serialize_zmq_message(zmq::message_t *zmsg, google::protobuf::Message *pbmsg)
{
    std::string data;

    if (!pbmsg->SerializeToString(&data)) {
        return false;
    }
    zmsg->rebuild(data.size());
    memcpy((void *)zmsg->data(), data.c_str(), data.size());
    return true;
}
