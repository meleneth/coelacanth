#include <stdexcept>

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
  if((int32_t) this->active_length < (int32_t)needle.length()) {
    return false;
  }
  for(unsigned int i = 0; i < needle.length(); ++i) {
    if(this->storage[i] != needle[i] ) {
      return false;
    }
  }
  return true;
}

void DataBuffer::add_value(int32_t value) {
  if((ssize_t)(active_length + sizeof(value)) > buffer_length) {
    throw std::runtime_error("attempted to store too much in a databuffer");
  }
  int32_t* location = (int32_t *)(storage + active_length);
  *location = value;
  active_length += sizeof(value);
}
