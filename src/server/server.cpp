#include <GEARSystem/CORBAImplementations/corbacommandbus.hh>
#include <GEARSystem/CORBAImplementations/corbacontroller.hh>
#include <GEARSystem/CORBAImplementations/corbasensor.hh>
#include <GEARSystem/gearsystem.hh>
#include <GEARSystem/server.hh>
#include <QtCore/QtCore>
#include <csignal>
#include <iostream>

using namespace GEARSystem;

class ServerHandler {
	private:
		static ServerHandler *_instance;

	public:
		ServerHandler(CORBAImplementations::Controller &controller, CORBAImplementations::Sensor &sensor, CORBAImplementations::CommandBus &commandBus) : 
			_server(&controller, &sensor, &commandBus) {}
		
		Server _server;

		static void interruptHandler(int sigType) {
			std::cout << "Stopping server" << std::endl;
			_instance->_server.stop();	
		}
		
		void setInstance(ServerHandler *svh) {
			_instance = svh;
		}
};


ServerHandler *ServerHandler::_instance = nullptr;

int main() {	
	WorldMap worldMap;
	CommandBus commandBus;
	CORBAImplementations::Controller controller_server(&worldMap, &commandBus);	
	CORBAImplementations::Sensor sensor_server(&worldMap);
	CORBAImplementations::CommandBus commandBus_server(&commandBus);

	ServerHandler serverHandler = ServerHandler(controller_server, sensor_server, commandBus_server);

	serverHandler.setInstance(&serverHandler);
	
	std::signal(SIGINT, serverHandler.interruptHandler);
	
	(void) serverHandler._server.initialize();
	// Inicializa e starta servidor
	serverHandler._server.start();
}
