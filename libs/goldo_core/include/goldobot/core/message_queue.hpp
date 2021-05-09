#pragma once
#include "goldobot/platform/lockers.hpp"

#include <cstddef>

namespace goldobot {
enum class CommMessageType : uint16_t;

class MessageQueue {
 public:
  MessageQueue(unsigned char* buffer, size_t size);

  bool message_ready() const;
  CommMessageType message_type() const;
  size_t message_size() const;

  bool push_message(CommMessageType message_type, const unsigned char* buffer, size_t size);
  size_t pop_message(unsigned char* buffer, size_t size);

  size_t available_capacity() const;

 private:
  void push_data(const unsigned char* buffer, size_t size);
  void read_data(size_t start_index, unsigned char* buffer, size_t size);
  void pop_data(size_t size);

  unsigned char* m_buffer;
  size_t m_buffer_size;
  size_t m_begin_index;
  size_t m_end_index;
  bool m_message_ready;
  uint16_t m_message_size;
  CommMessageType m_message_type;

  detail::LockerMutex m_mutex;
};
}  // namespace goldobot
