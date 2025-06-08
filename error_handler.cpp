#include <erpc_common.h>

#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void error_handler(erpc_status_t status)
{
	/* print error description */
	switch (status) {
	case kErpcStatus_Fail:
		std::cerr << "\r\nGeneric failure.";
		break;
	case kErpcStatus_InvalidArgument:
		std::cerr << "\r\nArgument is an invalid value.";
		break;
	case kErpcStatus_Timeout:
		std::cerr << "\r\nOperated timed out.";
		break;
	case kErpcStatus_InvalidMessageVersion:
		std::cerr << "\r\nMessage header contains an unknown version.";
		break;
	case kErpcStatus_ExpectedReply:
		std::cerr << "\r\nExpected a reply message but got another message type.";
		break;
	case kErpcStatus_CrcCheckFailed:
		std::cerr << "\r\nMessage is corrupted.";
		break;
	case kErpcStatus_BufferOverrun:
		std::cerr << "\r\nAttempt to read or write past the end of a buffer.";
		break;
	case kErpcStatus_UnknownName:
		std::cerr << "\r\nCould not find host with given name.";
		break;
	case kErpcStatus_ConnectionFailure:
		std::cerr << "\r\nFailed to connect to host.";
		break;
	case kErpcStatus_ConnectionClosed:
		std::cerr << "\r\nConnected closed by peer.";
		break;
	case kErpcStatus_MemoryError:
		std::cerr << "\r\nMemory allocation error.";
		break;
	case kErpcStatus_ServerIsDown:
		std::cerr << "\r\nServer is stopped.";
		break;
	case kErpcStatus_InitFailed:
		std::cerr << "\r\nTransport layer initialization failed.";
		break;
	case kErpcStatus_ReceiveFailed:
		std::cerr << "\r\nFailed to receive data.";
		break;
	case kErpcStatus_SendFailed:
		std::cerr << "\r\nFailed to send data.";
		break;
	/* no error occurred */
	case kErpcStatus_Success:
		std::cerr << "\r\nNo error. Successed.";
		break;
	/* unhandled error */
	default:
		std::cerr << "\r\nUnhandled error occurred.";
		break;
	}
	std::cout << "\r\n";
	return;
}
