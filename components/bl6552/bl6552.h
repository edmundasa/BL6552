#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace bl6552 {

class BL6552 : public Component, public uart::UARTDevice {
 public:
  void set_phase_a_voltage_sensor(sensor::Sensor *voltage_sensor) { phase_a_voltage_sensor_ = voltage_sensor; }

  void setup() override {
    // Reset state
    this->rx_buffer_.clear();
    // Add initialization commands if needed
  }

  void loop() override {
    // Read data if available
    while (available()) {
      this->read_byte(&this->rx_buffer_);
      if (this->parse_data_()) {
        // Process the data
        this->update_sensors_();
      }
    }
  }

 protected:
  bool parse_data_() {
    // TODO: Implement actual parsing logic
    // For now, just return true for testing
    return true;
  }

  void update_sensors_() {
    // TODO: Implement actual sensor updates
    // For testing, publish a dummy value
    if (this->phase_a_voltage_sensor_ != nullptr) {
      this->phase_a_voltage_sensor_->publish_state(230.0);
    }
  }

  std::vector<uint8_t> rx_buffer_;
  sensor::Sensor *phase_a_voltage_sensor_{nullptr};
};

}  // namespace bl6552
}  // namespace esphome
