#include "source/azu_engine.hpp"

int main()
{
	azu_engine::GraphicsEngine azu;
	azu.init();
	azu.loop();
	azu.shutdown();
	return 0;
}