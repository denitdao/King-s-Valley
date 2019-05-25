#pragma once
#include "pch.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

//typedef enum log_type { log_none, log_error, log_warning, log_info, log_debug } t_log_type;

/*class Log {
	static int m_logLevel;
	time_t t = time(NULL);

public:
	static void setLevel(t_log_type logLevel) {
		m_logLevel = logLevel;
	}
	Log& operator<<(t_log_type manip) /// setiosflags, resetiosflags
	{
		//manip(m_stream);
		return *this;
	}
	static string printTime() {
		time_t rawtime;
		tm * timeInfo;
		char buffer[26];

		time(&rawtime);
		timeInfo = localtime(&rawtime);

		strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", timeInfo);
		return buffer;
	}
	static void write(t_log_type log_level, string message) {
		if (log_level <= m_logLevel) {
			char buffer[255];
			//clog << '[' << log_level << ']' << message << endl;
			clog << sprintf(buffer, "%s [%d] %s", printTime().c_str(), log_level, message.c_str()) << endl;
		}
	}
};
*/
class Logger {
public:
	typedef ostream&  (*ManipFn)(ostream&);
	typedef ios_base& (*FlagsFn)(ios_base&);

	enum LogLevel {
		ERR,
		WARN,
		INFO,
		DEBUG
	};

	Logger(LogLevel defLogLevel, LogLevel maxLogLevel) {
		m_defLogLevel = m_logLevel = defLogLevel;
		m_maxLogLevel = maxLogLevel;
	}

	template<class T>  // int, double, strings, etc
	Logger& operator<<(const T& output)	{
		m_stream << output;
		return *this;
	}

	// to finish getting input and flush it into the stream
	Logger& operator<<(ManipFn manip) { // endl, flush, setw, setfill, etc.
		manip(m_stream);

		if (manip == static_cast<ManipFn>(std::flush)
			|| manip == static_cast<ManipFn>(endl))
			this->flush();

		return *this;
	}
	// get format flags
	Logger& operator<<(FlagsFn manip) { // setiosflags, resetiosflags
		manip(m_stream);
		return *this;
	}
	// get log level
	Logger& operator()(LogLevel e) {
		m_logLevel = e;
		return *this;
	}

	void flush() {
		/*
		  m_stream.str() has your full message here.
		  Good place to prepend time, log-level.
		  Send to console, file, socket, or whatever you like here.
		*/

		if (m_logLevel <= m_maxLogLevel) {
			cout << m_stream.str();
		}

		m_logLevel = m_defLogLevel; // if no log level entered
		m_stream.str(std::string());
		m_stream.clear();
	}

private:
	stringstream m_stream; // storage
	int m_logLevel;
	int m_defLogLevel;
	int m_maxLogLevel;
};