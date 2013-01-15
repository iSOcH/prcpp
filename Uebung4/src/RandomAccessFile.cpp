#include "RandomAccessFile.hpp"
#include <cassert>
#include <cstdio>

// template instantiation
template int RandomAccessFile::read<int>(streampos pos);
template void RandomAccessFile::write<int>(const int& data, streampos pos);


RandomAccessFile::RandomAccessFile(const string& fileName) : m_fileName(fileName) {
	// try to open file for reading and writing
	m_file.open(fileName.c_str(), ios::in|ios::out|ios::binary);
	if (!m_file) {
		// file doesn't exist
		m_file.clear();
		// create new file
		m_file.open(fileName.c_str(), ios::out | ios::binary);
		m_file.close();

		// try to open file for reading and writing
		m_file.open(fileName.c_str(), ios::in|ios::out|ios::binary);
		if (!m_file) {
			// same as setf(ios::failbit) ?
			m_file.fail();
		}
	}
}

streamsize RandomAccessFile::length() {
	streampos pos = m_file.tellg();

	m_file.seekg(0, ios::end);
	streampos len = m_file.tellg();
	m_file.seekg(pos);
	return len;
}

bool RandomAccessFile::truncate(streamsize length) {
	if (length < 0) return false;

	char buffer[128];
	char *fileName = tmpnam(nullptr);

	// create temporary file
	ofstream tmp(fileName, ios::out | ios::trunc | ios::binary);

	// copy first length bytes of this file to temporary file
	m_file.seekg(0);
	if (m_file.bad()) return false;

	streamsize n;
	while(length) {
		n = min((streamsize)128, length);
		m_file.read(buffer, n);
		tmp.write(buffer, n);
		length -= n;
	}

	// close both files
	m_file.close();
	tmp.close();

	// delete this file and rename temporary file
	if (remove(m_fileName.c_str())) return false;
	if (rename(fileName, m_fileName.c_str())) return false;

	// open this file
	m_file.open(m_fileName.c_str(), ios::in|ios::out|ios::binary);
	return m_file.good();
}

template<class T> T RandomAccessFile::read(streampos pos) {
	return 0;
}

template<class T> void RandomAccessFile::write(const T & data, streampos pos) {

}
