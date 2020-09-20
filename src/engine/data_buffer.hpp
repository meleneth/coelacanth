#ifndef DATABUFFER_HPP
#define DATABUFFER_HPP

namespace Coelacanth {

class DataBuffer {
  public:
    DataBuffer(ssize_t length);
    ~DataBuffer();
    bool starts_with(std::string needle);

    void reset_position(void);
    void add_value(int32_t value);

    ssize_t buffer_length;
    ssize_t active_length;
    unsigned char *storage;
};

}
#endif
