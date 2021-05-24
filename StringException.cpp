#include "MyString.h"
#include <stdio.h>

MyString::StringException::StringException(int idx, int size) {
  _idx = idx;
  _size = size;
}

MyString::InsertException::InsertException(int idx, int size) : MyString::StringException(idx, size){}

const char* MyString::InsertException::what(){
  char* s = new char[30];
  sprintf(s, "Called insert(`%d`) on string of size `%d`", _idx, _size);
  return s;
}

MyString::AtException::AtException(int idx, int size) : MyString::StringException(idx, size){}

const char* MyString::AtException::what(){
  char* s = new char[30];
  sprintf(s, "Called at(`%d`) on string of size `%d`", _idx, _size);
  return s;
}

MyString::EraseException::EraseException(int size, int idx)
    : MyString::StringException(size, idx) {} 

const char* MyString::EraseException::what() const noexcept {
    char* s = new char[256];
    sprintf(s, "Called erase(`%d`) on string of size `%d`", _idx, _size);
    return s;
}