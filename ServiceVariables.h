#pragma once
#include "ConnectedLibraries.h"

enum class Demonstration { Off, On };
enum PressedKey { BACKSPACE=8, UP = 38, TAB = 9, DOWN = 40, ENTER = 13};

class ServiceVariables
{
public:
	static inline HWND consoleWindow = GetForegroundWindow();
	static inline  HANDLE hInputBuffer = GetStdHandle(STD_INPUT_HANDLE);
	static inline HANDLE hOutputBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	static inline CONSOLE_SCREEN_BUFFER_INFO cScrBufferInfo;
};
