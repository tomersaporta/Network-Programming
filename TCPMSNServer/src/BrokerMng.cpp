/*
 * BrokerMng.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#include "BrokerMng.h"

namespace networkingLab {

BrokerMng::BrokerMng(BrokerMngHandler* handler){
	this->handler = handler;
}

void BrokerMng::createBroker(TCPSocket* peer1, TCPSocket* peer2){
	//create new Borker
	Broker * broker =new Broker(peer1, peer2, this);

}

void BrokerMng::rleasePeer(TCPSocket* peer){
	this->handler->handleReturnedPeer(peer);
}
//void BrokerMng::deleteBroker(Broker* broker){
//	// remove the broker from the broker list
//}

BrokerMng::~BrokerMng() {
	if(this->handler!=NULL){
		delete this->handler;
		this->handler=NULL;
	}
}

} /* namespace networkingLab */
