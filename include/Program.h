#pragma once



enum class ProgramState {
	MAIN_MENU,
	CHOOSING_DS_MENU
};



class Program {
public:
	Program();

private:
	ProgramState pgState;
};
