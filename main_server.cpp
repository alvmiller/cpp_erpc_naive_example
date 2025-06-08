#include "error_handler.h"

#include "hello_world_server.hpp"
#include "config.h"

#include <erpc_basic_codec.hpp>
#include <erpc_crc16.hpp>
#include <erpc_message_buffer.hpp>
#include <erpc_simple_server.hpp>
#include <erpc_tcp_transport.hpp>

#include <iostream>

/*
https://github.com/EmbeddedRPC/erpc/tree/main/examples/hello_world
https://github.com/EmbeddedRPC
https://docs.erpc.cloud/
https://github.com/Datalong/ERPC-framework/blob/master/readmeEN.md
https://mcuxpresso.nxp.com/mcuxsdk/latest/html/middleware/multicore/mcuxsdk-doc/eRPC_GettingStarted/topics/erpc_example.html

cmake -B ./build
cmake --build ./build --target menuconfig
cmake --build ./build
make
sudo make install
?copy the erpc_c directory into your application sources?
https://github.com/EmbeddedRPC/erpc/blob/main/examples/hello_world/README.md
liberpc.a
erpcgen

hello_world example
erpcgen -gc -o ./c/shim/ hello_world.erpc
cmake -B ./build
?prj.conf -> uncomment all needed modules?
cmake --build ./build/
in main dir level (erpc_main):
cmake --build ./build/ --target menuconfig
cmake --build ./build/
erpc-main/build/examples/hello_world

erpcgen -gc -o ./shim/ hello_world.erpc

g++ \
-o client \
-std=gnu++17 -g3 -O0 -DDEBUG -DYYDEBUG=1 -Werror \
-I/usr/local/include/erpc -Ishim/ \
shim/c_hello_world_client.cpp \
shim/c_hello_world_server.cpp \
shim/hello_world_client.cpp \
shim/hello_world_interface.cpp \
shim/hello_world_server.cpp \
error_handler.cpp \
main_client.cpp \
-L/usr/local/lib -lerpc -lpthread -lrt -lm -lc

g++ \
-o server \
-std=gnu++17 -g3 -O0 -DDEBUG -DYYDEBUG=1 -Werror \
-I/usr/local/include/erpc -Ishim/ \
shim/c_hello_world_client.cpp \
shim/c_hello_world_server.cpp \
shim/hello_world_client.cpp \
shim/hello_world_interface.cpp \
shim/hello_world_server.cpp \
error_handler.cpp \
main_server.cpp \
-L/usr/local/lib -lerpc -lpthread -lrt -lm -lc

./server
./client
*/

#if ERPC_NESTED_CALLS_DETECTION
extern bool nestingDetection;
#pragma weak nestingDetection
bool nestingDetection = false;
#endif

using namespace erpcShim;
using namespace erpc;
using namespace std;

bool g_server_run = true;

////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////

class MyMessageBufferFactory : public MessageBufferFactory
{
public:
	virtual MessageBuffer create() {
		uint8_t *buf = new uint8_t[ERPC_DEFAULT_BUFFER_SIZE];
		return MessageBuffer(buf, ERPC_DEFAULT_BUFFER_SIZE);
	}

	virtual void dispose(MessageBuffer *buf) {
		erpc_assert(buf);
		if (*buf) {
			delete[] buf->get();
		}
	}
};

class TextService : public TextService_interface
{
	bool printText(const char *text) {
		std::cout << text << std::endl;
		return true;
	}

	void stopServer() { g_server_run = false; }
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

int main()
{
	erpc_status_t status;

	/* Init eRPC server components */
	TCPTransport transport(ERPC_HOSTNAME, ERPC_PORT, true);
	MyMessageBufferFactory msgFactory;
	BasicCodecFactory codecFactory;
	SimpleServer server;
	Crc16 crc16;

	/* Init service implementation and handler */
	TextService textServiceImpl;
	TextService_service textService(&textServiceImpl);

	/* Setup transport */
	transport.setCrc16(&crc16);
	status = transport.open();

	/* handle error status */
	if (status != kErpcStatus_Success) {
		error_handler(status);
		return -1;
	}


	/* Setup server */
	server.setTransport(&transport);
	server.setCodecFactory(&codecFactory);
	server.setMessageBufferFactory(&msgFactory);

	/* add custom service implementation to the server */
	server.addService(&textService);

	std::cout << "Starting server." << std::endl;

	while (g_server_run) {
		/* poll for requests */
		status = server.poll();

		/* handle error status */
		if (status != kErpcStatus_Success) {
			error_handler(status);
			return -1;
		}
	}

	std::cout << "Server stopped." << std::endl;

	/* Close transport */
	transport.close();
}
