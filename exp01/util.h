//
// Created by kyle on 5/11/15.
//

#ifndef SIKEVAS_UTIL_H
#define SIKEVAS_UTIL_H


bool    zmq_receive(zmq::socket_t *, google::protobuf::Message *);
bool    zmq_send(zmq::socket_t *, google::protobuf::Message *);


#endif //SIKEVAS_UTIL_H
