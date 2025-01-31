#include "bl6552.h"
#include "esphome/core/log.h"

namespace esphome {
namespace bl6552 {

static const char *const TAG = "bl6552";

void BL6552::setup() {
  ESP_LOGD(TAG, "Setting up BL6552...");
  this->rx_buffer_.clear();
}

void BL6552::loop() {
  while (available()) {
    uint8_t byte;
    if (!read_byte(&byte)) {
      continue;
    }
    ESP_LOGV(TAG, "Received byte: 0x%02X", byte);
    this->rx_buffer_.push_back(byte);
    
    if (this->parse_data_()) {
      this->update_sensors_();
    }
  }
}

}  // namespace bl6552
}  // namespace esphome
