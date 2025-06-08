#include "error_handler.h"

#include "hello_world_client.hpp"
#include "config.h"

#include <erpc_basic_codec.hpp>
#include <erpc_client_manager.h>
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

using namespace erpcShim;
using namespace erpc;
using namespace std;

#if ERPC_NESTED_CALLS_DETECTION
extern bool nestingDetection;
#pragma weak nestingDetection
bool nestingDetection = false;
#endif

////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////

class MyMessageBufferFactory : public MessageBufferFactory
{
public:
	virtual MessageBuffer create() {
		uint8_t *buf = new uint8_t[1024];
		return MessageBuffer(buf, 1024);
	}

	virtual void dispose(MessageBuffer *buf) {
		erpc_assert(buf);
		if (*buf) {
			delete[] buf->get();
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

int main()
{
	erpc_status_t status;

	/* Init eRPC client components */
	TCPTransport transport(ERPC_HOSTNAME, ERPC_PORT, false);
	MyMessageBufferFactory msgFactory;
	BasicCodecFactory basicCodecFactory;
	Crc16 crc16;
	ClientManager clientManager;

	/* Init transport */
	transport.setCrc16(&crc16);
	status = transport.open();

	if (status != kErpcStatus_Success) {
		error_handler(status);
		return -1;
	}

	/* Init client manager */
	clientManager.setMessageBufferFactory(&msgFactory);
	clientManager.setTransport(&transport);
	clientManager.setCodecFactory(&basicCodecFactory);

	/* Scope for client service */
	{
		/* Init eRPC client TextService service */
		TextService_client client(&clientManager);

		/* Do eRPC call */
		if (client.printText("Hello world!")) {
			std::cout << "Message received by server." << std::endl;
		}

		/* Stop server */
		client.stopServer();
	}

	/* Deinit objects */
	transport.close();
}
