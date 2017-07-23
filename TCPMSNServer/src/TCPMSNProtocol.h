/*
 * TCPMSNProtocol.h
 *
 *  Created on: Jul 7, 2017
 *      Author: user
 */

#ifndef SRC_TCPMSNPROTOCOL_H_
#define SRC_TCPMSNPROTOCOL_H_

/**
 * TCP Messenger protocol:
 * all messages are of the format [Command 4 byte int]
 * and optionally data follows in the format [Data length 4 byte int][ Data ]
 */
#define MSNGR_PORT 3352

#define CLOSE_SESSION_WITH_PEER 		1
#define OPEN_SESSION_WITH_PEER 			2
#define EXIT							3
#define SEND_MSG_TO_PEER				4
#define SESSION_REFUSED					5
#define SESSION_ESTABLISHED				6
#define INTERRUPT_SOCKET                7

#define TEST_PEER_NAME "test"
#define SESSION_REFUSED_MSG "Connection to peer refused, peer might be busy or disconnected, try again later"




#endif /* SRC_TCPMSNPROTOCOL_H_ */
