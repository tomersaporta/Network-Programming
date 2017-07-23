/*
 * DispatcherHandler.h
 *
 *  Created on: Jul 7, 2017
 *      Author: user
 */

#ifndef SRC_DISPATCHERHANDLER_H_
#define SRC_DISPATCHERHANDLER_H_
#include "TCPSocket.h"

namespace networkingLab {

class DispatcherHandler {
public:
	virtual void managePeerSession(TCPSocket* peer1, TCPSocket* peer2)=0;
	virtual ~DispatcherHandler(){};
};

} /* namespace networkingLab */

#endif /* SRC_DISPATCHERHANDLER_H_ */
