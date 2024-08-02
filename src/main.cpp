#include <GEARSystem/gearsystem.hh>
#include <QtCore/QtCore>
#include <iostream>

using namespace GEARSystem;

// Cria classe que herda da classe Actuator do GEARSystem
class ActuatorTest : public Actuator {
	public:
		// Chama construtor da classe pai
		ActuatorTest(const QString &actuatorName) : Actuator(actuatorName) {}
		~ActuatorTest() {}
		void setSpeed(uint8 teamNum, uint8 playerNum, float x, float y, float theta) {}
		void kick(uint8 teamNum, uint8 playerNum, float power) {}
		void chipKick(uint8 teamNum, uint8 playerNum, float power){}
		void kickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) {}
		void chipKickOnTouch(uint8 teamNum, uint8 playerNum, bool enable, float power) {}
		void holdBall(uint8 teamNum, uint8 playerNum, bool enable) {}
};

bool initSensor(Sensor *sensor) {
	bool ok = sensor->connect("localhost", 0);
	if(!ok || !sensor->isConnected()) {
		return false;
	}
	
	qint8 ballNum = 1;
	Position ballPos = Position(true, 1.0f, 0.0f, 0.0f);
	sensor->addBall(ballNum);
	sensor->setBallPosition(ballNum, ballPos);

	return true;
}

bool initController(Controller *controller) {
	bool ok = controller->connect("localhost", 0);
	if(!ok) {
		return false;
	}

	qint8 numBalls = controller->balls().size();
	std::cout << "Numero de bolas: " << (int) numBalls << std::endl;
		
	return true;
}

int main() {
	// Inicializa sensor
	Sensor *sensor = new Sensor();
	if(initSensor(sensor)) {
		std::cout << "sensor inicializado" << std::endl;
	}
	else {
		std::cout << "sensor não inicializado" << std::endl;
		return 1;	
	}

	// Inicializa controller
	Controller *controller = new Controller();
	initController(controller);

	// Inicializa actuator
	QString actuatorName = QString("atuador");
	ActuatorTest *actuator = new ActuatorTest(actuatorName);
	//actuator->connect(const QString &address, quint16 port)		
	// Seta variavel interna do controller para apontr para commandBus do server: getCommandBus
	
	
	sensor->disconnect();
	controller->disconnect();
	actuator->disconnect();
	delete sensor;
	delete controller;
	delete actuator;
}
