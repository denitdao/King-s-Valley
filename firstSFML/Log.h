#pragma once
#include "pch.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Logger {
	stringstream m_stream; // storage
	int m_logLevel; // current output logging level
	int m_defLogLevel; // in no logging level entered, then m_logLevel = m_defLogLevel
	int m_maxLogLevel; // filter messages with logging level > than m_maxLogLevel
public:
	typedef ostream&  (*ManipFn)(ostream&); // means we will get manipulators as function arguments
	// enum with logging levels
	enum LogLevel { 
		ERR,
		WARN,
		INFO,
		DEBUG
	};
	// initialize default and max log levels
	Logger(LogLevel defLogLevel, LogLevel maxLogLevel) {
		m_defLogLevel = m_logLevel = defLogLevel;
		m_maxLogLevel = maxLogLevel;
	}

	template<class T>  // int, double, strings, etc
	Logger& operator<<(const T& output)	{
		m_stream << output;
		return *this;
	}
	// set new max log level
	void ChangeMaxLogLevel(int step) {
		m_maxLogLevel = step;
		(*this)(INFO) << "Max logger mode - " << m_maxLogLevel << endl; // message
	}
	// to finish getting input and flush it into the stream
	Logger& operator<<(ManipFn manip) { // endl, flush, setw, setfill, etc.
		manip(m_stream); // apply manipulators to our string stream

		if (manip == static_cast<ManipFn>(std::flush)
			|| manip == static_cast<ManipFn>(endl))
			this->flush();

		return *this;
	}
	// get log level
	Logger& operator()(LogLevel e) {
		m_logLevel = e;
		return *this;
	}
	// write message to the console / file ...
	void flush() {
		/*
		  m_stream.str() has full message here.
		*/

		if (m_logLevel <= m_maxLogLevel) {
			cout << m_stream.str();
		}

		m_logLevel = m_defLogLevel; // if no log level entered
		m_stream.str(string()); // clear buffer
		m_stream.clear(); // clear the error state
	}
};