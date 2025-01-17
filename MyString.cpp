#include "MyString.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

MyString::MyString(const char* rawString) {
	// TODO
	if (rawString == nullptr) {
		_size = 0;
		_data = nullptr;
	}
	else {
		_size = strlen(rawString);
		_data = new char[_size + 1];
		for (int i = 0; i < _size; ++i) {
			_data[i] = rawString[i];
		}
		_data[_size] = '\0';
	}
}

MyString::MyString(const MyString& other) {
	// TODO
	if (other == nullptr) {
		_size = 0;
		_data = nullptr;
	}
	else {
		_size = other._size;
		_data = new char[_size];
		for (int i = 0; i < _size; ++i) {
			_data[i] = other[i];
		}
		_data[_size] = '\0';
	}
}

MyString::MyString(MyString&& other) noexcept {
	_size = other._size;
	_data = new char[_size];
	for (int i = 0; i < _size; ++i) {
		_data[i] = other[i];
	}
	_data[_size] = '\0';
	other._size = 0;
	other._data = nullptr;
}

MyString& MyString::operator=(const MyString& other) {
	// TODO
	if (&other == this)
		return *this;
	_size = other._size;
	delete[] _data;
	_data = new char[_size];
	for (int i = 0; i < _size; ++i) {
		_data[i] = other[i];
	}
	_data[_size] = '\0';
	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
	// TODO
	if (&other == this)
		return *this;
	_size = other._size;
	delete[] _data;
	_data = new char[_size];
	for (int i = 0; i < _size; ++i) {
		_data[i] = other[i];
	}
	_data[_size] = '\0';
	other._size = 0;
	other._data = nullptr;
	return *this;
}

MyString::~MyString() {
	_size = 0;
	delete[] _data;
	_data = nullptr;
}

void MyString::append(const MyString& appendedString) {
	int lengthTemp = this->_size + appendedString._size;
	char* temp = new char[lengthTemp + 1];
	int i;
	for (i = 0; i < this->_size; i++) {
		temp[i] = this->_data[i];
	}
	for (i = 0; i < appendedString._size; i++) {
		temp[i + _size] = appendedString._data[i];
	}
	temp[lengthTemp] = '\0';
	delete[] _data;
	this->_data = temp;
	this->_size = lengthTemp;
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
  if (pos > size()) {
    throw MyString::InsertException(pos, size());
  }
	int lengthTemp = insertedString._size + this->_size;
	char* temp = new char[lengthTemp + 1];
	int i;
	for (i = 0; i < pos; i++) {
		temp[i] = this->_data[i];
	}
	for (i = pos; i < pos + insertedString._size; i++) {
		temp[i] = insertedString._data[i - pos];
	}
	for (i = pos; i < this->_size; i++) {
		temp[i + insertedString._size] = this->_data[i];
	}
	temp[lengthTemp] = '\0';
	delete[] _data;
	this->_data = temp;
	this->_size = lengthTemp;
}

void MyString::clear() {
	delete[] _data;
	this->_data = 0;
	this->_size = 0;
}

void MyString::erase(unsigned int pos, unsigned int count) {
  if (pos > size()) {
    throw MyString::EraseException(pos, size());
  }
	if (count > this->_size - pos) {
		count = this->_size - pos;
	}
	int lengthTemp = this->_size - count;
	char* temp = new char[lengthTemp + 1];
	int i;
	for (i = 0; i < pos; i++) {
		temp[i] = this->_data[i];
	}
	for (i = pos; i < this->_size - count + 1; i++) {
		temp[i] = this->_data[i + count];
	}
	temp[lengthTemp] = '\0';
	delete[] _data;
	this->_data = temp;
	this->_size = lengthTemp;
}

char& MyString::at(const unsigned int idx) {
	if (idx < size()){
    throw AtException(idx, size());
  }
	return _data[idx];
}

const char& MyString::at(const unsigned int idx) const {
	if (idx < size()){
    throw AtException(idx, size());
  }
	return _data[idx];
}

unsigned int MyString::size() const {
	return this->_size;
}

bool MyString::isEmpty() const {
	if (this->_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

const char* MyString::rawString() const {
	if (_data == 0) {
		return "";
	}
	return _data;
}

unsigned int MyString::find(const MyString& substring, unsigned int pos) {
	bool findFlag;
	int coincidence = 0;
	for (int i = pos; i < _size; i++) {
		if (substring._data[0] == _data[i]) {
			coincidence++;
			for (int j = 0; j < substring._size; j++) {
				if (substring._data[j] != _data[j + i]) {
					coincidence = 0;
					break;
				}
				else {
					coincidence++;
				}
				if (coincidence == substring._size) {
					pos = i;
					findFlag = true;
				}
			}
		}
	}
	if (findFlag) {
		return pos;
	}
	else {
		return 0;
	}
}

int MyString::compare(const MyString& comparableString) const {
	if (_size != comparableString._size) {
		return (_size - comparableString._size);
	}
	int i;
	for (i = 0; i < _size; i++) {
		if (_data[i] != comparableString._data[i]) {
			break;
		}
	}
	return (_data[i] - comparableString._data[i]);
}

//Overloads

char& MyString::operator[](const unsigned int idx) {
	return at(idx);
}

const char& MyString::operator[](const unsigned int idx) const {
	return at(idx);
}


MyString& MyString::operator+(const MyString& appendedString) {
	append(appendedString);
	return *this;
}

bool MyString::operator==(const MyString& comparableString) const {
	if (compare(comparableString) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool MyString::operator!=(const MyString& comparableString) const {
	if (compare(comparableString) != 0) {
		return true;
	}
	else {
		return false;
	}
}

bool MyString::operator>(const MyString& comparableString) const {
	if (compare(comparableString) > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool MyString::operator<(const MyString& comparableString) const {
	if (compare(comparableString) < 0) {
		return true;
	}
	else {
		return false;
	}
}

bool MyString::operator>=(const MyString& comparableString) const {
	if (compare(comparableString) >= 0) {
		return true;
	}
	else {
		return false;
	}
}

bool MyString::operator<=(const MyString& comparableString) const {
	if (compare(comparableString) <= 0) {
		return true;
	}
	else {
		return false;
	}
}