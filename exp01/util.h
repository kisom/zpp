//
// Created by kyle on 5/11/15.
//

#ifndef SIKEVAS_UTIL_H
#define SIKEVAS_UTIL_H


bool    parse_zmq_message(zmq::message_t *, google::protobuf::Message *);
bool    serialize_zmq_message(zmq::message_t *, google::protobuf::Message *);


#endif //SIKEVAS_UTIL_H
