#pragma once

#include <cstdio>

class Logger {
private:
	static unsigned int mLogLevel;

public:
	/* log if input log level is equal or smaller to log level set */
	template <typename... Args>
	static void log(unsigned int logLevel, Args ... args) {
		if (logLevel <= mLogLevel) {
			std::printf(args ...);
		}
	}

	static void setLogLevel(unsigned int inLogLevel) {
		inLogLevel <= 9 ? mLogLevel = inLogLevel : mLogLevel = 9;
	}
};
