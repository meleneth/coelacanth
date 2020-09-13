#include "coelacanth_types.hpp"

#include "data_buffer.hpp"

using namespace Coelacanth;

DataBuffer::DataBuffer(ssize_t length)
{
  this->buffer_length = length;
  this->active_length = 0;

  this->storage = new unsigned char[length];
}

DataBuffer::~DataBuffer()
{
  delete this->storage;
}

bool DataBuffer::starts_with(std::string needle) {
  if((int) this->active_length < (int)needle.length()) {
    return false;
  }
  for(unsigned int i = 0; i < needle.length(); ++i) {
    if(this->storage[i] != needle[i] ) {
      return false;
    }
  }
  return true;
}
