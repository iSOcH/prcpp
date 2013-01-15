#pragma once

#include <exception>
#include <fstream>
using namespace std;

class RandomAccessFile {
	fstream m_file;
	string m_fileName;

public:
	class IOException: public exception {
		const char * msg;
		public:
		IOException(const char* msg) : exception(), msg(msg) {}
	};

	RandomAccessFile(const string& fileName);
	virtual ~RandomAccessFile()		{ m_file.close(); }

	streamsize length();
	operator bool() const			{ return m_file.good(); }
	bool truncate(streamsize);

	// generic members
	template<class T> T read(streampos pos = -1);
	template<class T> void write(const T& data, streampos pos = -1);
};
