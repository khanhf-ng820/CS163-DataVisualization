#include "initData.h"



// --- Initialize data structures
void Program::initSLL(const int dataInitOption) {
	switch (dataInitOption) {
	case DATA_INIT_RANDOMIZED:
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
		visEngine_SLL.initSLLData(rng);
		break;
	case DATA_INIT_CUSTOM:
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
		break;
	case DATA_INIT_FROM_FILE:
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
		break;
	case DATA_INIT_EMPTY:
	default:
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
		visEngine_SLL.initSLLData();
		break;
	}
}
