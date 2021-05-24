#include "MyString.h"

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cassert>

MyString::MyString(const char* rawString) {
	// TODO
	if (rawString == nullptr) {
		_string.StringType.Short._size = 0;
		_string.StringType.Short._data[0] = '\0';
	}
	else {
    if(sizeof(_string.StringType.Long) - sizeof(char) > strlen(rawString)){
      _string.StringType.Short._size = strlen(rawString);
      for (int i = 0; i < _string.StringType.Short._size; ++i) {
        _string.StringType.Short._data[i] = rawString[i];
      }
      _string.StringType.Short._data[_string.StringType.Short._size] = '\0';
    }
    else {
      _string.StringType.Long._size = strlen(rawString);
      _string.StringType.Long._data = new char[_string.StringType.Long._size + 1];
      for (int i = 0; i < _string.StringType.Long._size; ++i) {
        _string.StringType.Long._data[i] = rawString[i];
      }
      _string.StringType.Long._data[_string.StringType.Long._size] = '\0';
      _string.isLong = true;
    }
	}
}

MyString::MyString(const MyString& other) {
    // TODO
  //std::cout << "Okkcopy" << std::endl;
	if (other == nullptr) {
		_string.StringType.Short._size = 0;
		_string.StringType.Short._data[0] = '\0';
	}
	else {
    clear();
    if(other._string.isLong){
      _string.StringType.Long._size = other._string.StringType.Long._size;
      _string.StringType.Long._data = new char[_string.StringType.Long._size + 1];
      for (int i = 0; i < _string.StringType.Long._size; ++i) {
        _string.StringType.Long._data[i] = other._string.StringType.Long._data[i];
      }
      _string.StringType.Long._data[_string.StringType.Long._size] = '\0';
      _string.isLong = true;
    }
    else {
      _string.StringType.Short._size = other._string.StringType.Short._size;
      for (int i = 0; i < _string.StringType.Short._size; ++i) {
        _string.StringType.Short._data[i] = other._string.StringType.Short._data[i];
      }
      _string.StringType.Short._data[_string.StringType.Short._size] = '\0';
    }
	}
}

MyString::MyString(MyString&& other) noexcept {
  //std::cout << "Okkmove" << std::endl;
  if (other._string.isLong){
    _string.StringType.Long._size = other._string.StringType.Long._size;
    _string.StringType.Long._data = new char[_string.StringType.Long._size];
    for (int i = 0; i < _string.StringType.Long._size; ++i) {
      _string.StringType.Long._data[i] = other._string.StringType.Long._data[i];
    }
    _string.StringType.Long._data[_string.StringType.Long._size] = '\0';
    other._string.StringType.Long._size = 0;
    other._string.StringType.Long._data = nullptr;
    _string.isLong = true;
  }

  else {
    _string.StringType.Short._size = other._string.StringType.Short._size;
    for (int i = 0; i < _string.StringType.Short._size; ++i) {
      _string.StringType.Short._data[i] = other._string.StringType.Short._data[i];
    }
    _string.StringType.Short._data[_string.StringType.Short._size] = '\0';
    other._string.StringType.Short._size = 0;
    other._string.StringType.Short._data[0] = '\0';
  }
}

MyString& MyString::operator=(const MyString& other) {
    // TODO
	if (&other == this)
		return *this;
  clear();
  if (other._string.isLong){
    _string.StringType.Long._size = other._string.StringType.Long._size;
    _string.StringType.Long._data = new char[_string.StringType.Long._size + 1];
    for (int i = 0; i < _string.StringType.Long._size; ++i) {
      _string.StringType.Long._data[i] = other._string.StringType.Long._data[i];
    }
    _string.StringType.Long._data[_string.StringType.Long._size] = '\0';
    _string.isLong = true;
      return *this;
  }
  else {
    _string.StringType.Short._size = other._string.StringType.Short._size;
    for (int i = 0; i < _string.StringType.Short._size; ++i) {
      _string.StringType.Short._data[i] = other._string.StringType.Short._data[i];
    }
    _string.StringType.Short._data[_string.StringType.Short._size] = '\0';
      return *this;
  }
}

MyString& MyString::operator=(MyString&& other) noexcept {
	// TODO
	if (&other == this)
		return *this;
  clear();
  if (other._string.isLong) {
    _string.StringType.Long._size = other._string.StringType.Long._size;
    _string.StringType.Long._data = new char[_string.StringType.Long._size + 1];
    for (int i = 0; i < _string.StringType.Long._size; ++i) {
      _string.StringType.Long._data[i] = other._string.StringType.Long._data[i];
    }
    _string.StringType.Long._data[_string.StringType.Long._size] = '\0';
    other.clear();
    _string.isLong = true;
    return *this;
  }
  else {
    _string.StringType.Short._size = other._string.StringType.Short._size;
    for (int i = 0; i < _string.StringType.Short._size; ++i) {
      _string.StringType.Short._data[i] = other[i];
    }
    _string.StringType.Short._data[_string.StringType.Short._size] = '\0';
    for (int i = 0; i < other._string.StringType.Short._size; i++){
      other._string.StringType.Short._data[i] = '\0';
    }
    other._string.StringType.Short._size = 0;
    return *this;
  }
} 

MyString::~MyString() {
  if (_string.isLong) {
    _string.StringType.Long._size = 0;
    delete[] _string.StringType.Long._data;
    _string.StringType.Long._data = nullptr;
  }
  else {
    _string.StringType.Short._data[0] = '\n';
    _string.StringType.Short._size = 0;
  }
  _string.isLong = false;
}

///

void MyString::append(const MyString& appendedString) {
  insert(this->size(), appendedString);
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
	unsigned int lengthTemp = sizeAfterOperation(insertedString);
  bool outStringIsLong = false;
  
  if (lengthTemp > sizeof(_string.StringType.Long) - sizeof(char)){
    outStringIsLong = true;
  }
  
  unsigned int sizeOfInsertedString;
  const char* dataOfInsertedString;
  // 
  if (insertedString._string.isLong){
    sizeOfInsertedString = insertedString._string.StringType.Long._size;
    dataOfInsertedString = insertedString._string.StringType.Long._data;
  }
  else{
    sizeOfInsertedString = insertedString._string.StringType.Short._size;
    dataOfInsertedString = insertedString._string.StringType.Short._data;
  }
  //
	if (_string.isLong){
      char* temp = new char[lengthTemp + 1];
      int i;
      for (i = 0; i < pos; i++) {
        temp[i] = _string.StringType.Long._data[i];
      }
      for (i = pos; i < pos + sizeOfInsertedString; i++) {
        temp[i] = dataOfInsertedString[i - pos];
      }
      for (i = pos; i < _string.StringType.Long._size; i++) {
        temp[i + sizeOfInsertedString] = _string.StringType.Long._data[i];
      }
      temp[lengthTemp] = '\0';
      delete [] _string.StringType.Long._data;
      _string.StringType.Long._data = temp;
      _string.StringType.Long._size = lengthTemp;
  }
  else {
    if (outStringIsLong){
      char* temp = new char[lengthTemp + 1];
      int i;
      for (i = 0; i < pos; i++) {
        temp[i] = _string.StringType.Short._data[i];
      }
      for (i = pos; i < pos + sizeOfInsertedString; i++) {
        temp[i] = dataOfInsertedString[i - pos];    
      }
      for (i = pos; i < _string.StringType.Short._size; i++) {
        temp[i + sizeOfInsertedString] = _string.StringType.Short._data[i];
      }
      temp[lengthTemp] = '\0';
      _string.StringType.Short._size = 0;
      _string.StringType.Short._data[0] = '\0';
      _string.StringType.Long._data = temp;
      _string.StringType.Long._size = lengthTemp;
      _string.isLong = true;
    }
    else{
      char temp[lengthTemp + 1];
      int i;
      for (i = 0; i < pos; i++) {
        temp[i] = _string.StringType.Short._data[i];
      }
      for (i = pos; i < pos + sizeOfInsertedString; i++) {
        temp[i] = dataOfInsertedString[i - pos];
      }
      for (i = pos; i < _string.StringType.Short._size; i++) {
        temp[i + sizeOfInsertedString] = _string.StringType.Short._data[i];
      }
      temp[lengthTemp] = '\0';
      for (int i = 0; i < lengthTemp; ++i) {
          _string.StringType.Short._data[i] = temp[i];
      }
      _string.StringType.Short._size = lengthTemp;
    }
  }
}

void MyString::clear() {
  if (_string.isLong){
    delete[] _string.StringType.Long._data;
    _string.StringType.Long._data = 0;
    _string.StringType.Long._size = 0;
  }
  else {
    _string.StringType.Short._data[0] = '\n';
    _string.StringType.Short._size = 0;
  }
  _string.isLong = false;
}

void MyString::erase(unsigned int pos, unsigned int count) {
  bool finalString;
  if (_string.isLong){
    if (sizeof(_string.StringType.Long) - sizeof(char) > _string.StringType.Long._size - count) {
      finalString = false;
    }
  }
  else {
    finalString = _string.isLong;
  }

  if (_string.isLong == finalString){
    if (_string.isLong){
      if (count > _string.StringType.Long._size - pos) {
        count = _string.StringType.Long._size - pos;
      }
      int lengthTemp = _string.StringType.Long._size - count;
      char* temp = new char[lengthTemp + 1];
      int i;
      for (i = 0; i < pos; i++) {
        temp[i] = _string.StringType.Long._data[i];
      }
      for (i = pos; i < _string.StringType.Long._size - count + 1; i++) {
        temp[i] = _string.StringType.Long._data[i + count];
      }
      temp[lengthTemp] = '\0';
      delete[] _string.StringType.Long._data;
      _string.StringType.Long._data = temp;
      _string.StringType.Long._size = lengthTemp;
    }
    else{
      if (count > _string.StringType.Short._size - pos) {
        count = _string.StringType.Short._size - pos;
      }
      int lengthTemp = _string.StringType.Short._size - count;
      char temp [lengthTemp + 1];
      int i;
      for (i = 0; i < pos; i++) {
        temp[i] = _string.StringType.Short._data[i];
      }
      for (i = pos; i < _string.StringType.Short._size - count + 1; i++) {
        temp[i] = _string.StringType.Short._data[i + count];
      }
      temp[lengthTemp] = '\0';
      for (int i = 0; i < _string.StringType.Short._size; ++i) {
        _string.StringType.Short._data[i] = temp[i];
      }
      _string.StringType.Short._size = lengthTemp;
    }
  }
  else {
    if (count > _string.StringType.Long._size - pos) {
      count = _string.StringType.Long._size - pos;
    }
    int lengthTemp = _string.StringType.Long._size - count;
    char temp[lengthTemp + 1];
    int i;
    for (i = 0; i < pos; i++) {
      temp[i] = _string.StringType.Long._data[i];
    }
    for (i = pos; i < _string.StringType.Long._size - count + 1; i++) {
      temp[i] = _string.StringType.Long._data[i + count];
    }
    temp[lengthTemp] = '\0';
    delete[] _string.StringType.Long._data;
    _string.StringType.Long._size = 0;
    for (int i = 0; i < _string.StringType.Short._size; ++i) {
      _string.StringType.Short._data[i] = temp[i];
    }
    _string.StringType.Short._size = lengthTemp;
  }
}

char& MyString::at(const unsigned int idx) {
	assert(idx < size());
  if (_string.isLong){
    return _string.StringType.Long._data[idx];
  }
	return _string.StringType.Short._data[idx];
}

const char& MyString::at(const unsigned int idx) const {
	assert(idx < size());
	if (_string.isLong){
    return _string.StringType.Long._data[idx];
  }
	return _string.StringType.Short._data[idx];
}

unsigned int MyString::size() const {
  if (_string.isLong){
    return _string.StringType.Long._size;
  }
	return _string.StringType.Short._size;
}

bool MyString::isEmpty() const {
  if (_string.isLong){
    if (_string.StringType.Long._size == 0) {
		return true;
	  }
	  else {
		  return false;
    }
  }
  else {
	  if (_string.StringType.Short._size == 0) {
		  return true;
	    }
	  else {
		  return false;
    }
  }
}

const char* MyString::rawString() const {
  if (_string.isLong){
    if (_string.StringType.Long._data == nullptr){
      return "";
    }
	  return _string.StringType.Long._data;
  }
  else{
    if (_string.StringType.Short._size == 0){
      return "";
    }
	  return _string.StringType.Short._data;
  }
}

unsigned int MyString::find(const MyString& substring, unsigned int pos) {
  bool findFlag;
	int coincidence = 0;
  if (_string.isLong){
    if (substring._string.isLong){
      for (int i = pos; i < _string.StringType.Long._size; i++){
        if (substring._string.StringType.Long._data[0] == _string.StringType.Long._data[i]) {
          coincidence++;
          for (int j = 0; j < substring._string.StringType.Long._size; j++) {
            if (substring._string.StringType.Long._data[j] != _string.StringType.Long._data[j + i]) {
              coincidence = 0;
              break;
            }
            else {
              coincidence++;
            }
            if (coincidence == substring._string.StringType.Long._size){
              pos = i;
              findFlag = true;
            }
          }
        }
      }
      if (findFlag){
        return pos;
      }
      else {
        return 0;
      }
    }
    else {
        for (int i = pos; i < _string.StringType.Long._size; i++){
        if (substring._string.StringType.Short._data[0] == _string.StringType.Long._data[i]) {
          coincidence++;
          for (int j = 0; j < substring._string.StringType.Short._size; j++) {
            if (substring._string.StringType.Short._data[j] != _string.StringType.Long._data[j + i]) {
              coincidence = 0;
              break;
            }
            else {
              coincidence++;
            }
            if (coincidence == substring._string.StringType.Short._size){
              pos = i;
              findFlag = true;
            }
          }
        }
      }
      if (findFlag){
        return pos;
      }
      else {
        return 0;
      }
    }
  }
  else {
    if (substring._string.isLong){
            for (int i = pos; i < _string.StringType.Short._size; i++){
        if (substring._string.StringType.Long._data[0] == _string.StringType.Short._data[i]) {
          coincidence++;
          for (int j = 0; j < substring._string.StringType.Long._size; j++) {
            if (substring._string.StringType.Long._data[j] != _string.StringType.Short._data[j + i]) {
              coincidence = 0;
              break;
            }
            else {
              coincidence++;
            }
            if (coincidence == substring._string.StringType.Long._size){
              pos = i;
              findFlag = true;
            }
          }
        }
      }
      if (findFlag){
        return pos;
      }
      else {
        return 0;
      }
    }
    else {
      for (int i = pos; i < _string.StringType.Short._size; i++){
        if (substring._string.StringType.Short._data[0] == _string.StringType.Short._data[i]) {
          coincidence++;
          for (int j = 0; j < substring._string.StringType.Short._size; j++) {
            if (substring._string.StringType.Short._data[j] != _string.StringType.Short._data[j + i]) {
              coincidence = 0;
              break;
            }
            else {
              coincidence++;
            }
            if (coincidence == substring._string.StringType.Short._size){
              pos = i;
              findFlag = true;
            }
          }
        }
      }
      if (findFlag){
        return pos;
      }
      else {
        return 0;
      }
    }
  }
}

int MyString::compare(const MyString& comparableString) const {
  if (_string.isLong != comparableString._string.isLong){
    if (_string.isLong){
      return (_string.StringType.Long._size - comparableString._string.StringType.Short._size);
    }
    else{
      return (_string.StringType.Short._size - comparableString._string.StringType.Long._size);
    }
  }
  if (_string.isLong){
      if (_string.StringType.Long._size != comparableString._string.StringType.Long._size) {
        return (_string.StringType.Long._size - comparableString._string.StringType.Long._size);
      }
      int i;
      for (i = 0; i < _string.StringType.Long._size; i++) {
        if (_string.StringType.Long._data[i] != comparableString._string.StringType.Long._data[i]) {
          break;
        }
      }
      return (_string.StringType.Long._data[i] - comparableString._string.StringType.Long._data[i]);
    }
  else{
      if (_string.StringType.Short._size != comparableString._string.StringType.Short._size) {
        return (_string.StringType.Short._size - comparableString._string.StringType.Short._size);
      }
      int i;
      for (i = 0; i < _string.StringType.Short._size; i++) {
        if (_string.StringType.Short._data[i] != comparableString._string.StringType.Short._data[i]) {
          break;
        }
      }
      return (_string.StringType.Short._data[i] - comparableString._string.StringType.Short._data[i]);
  }
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
unsigned int MyString::sizeAfterOperation(const MyString& other) const{
  unsigned int newSize;
  switch (char flag = _string.isLong + other._string.isLong) {
    case 0:
      newSize = _string.StringType.Short._size + other._string.StringType.Short._size;
      break;
    case 2:
      newSize = _string.StringType.Long._size + other._string.StringType.Long._size;
      break;
    default:
      if (_string.isLong){
        newSize = _string.StringType.Long._size + other._string.StringType.Short._size;
      }
      else {
        newSize = _string.StringType.Short._size + other._string.StringType.Long._size;
      }
      break;
  }
  return newSize;
}