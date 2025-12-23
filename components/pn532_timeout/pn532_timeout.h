#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/pn532/pn532.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace pn532_timeout {

class PN532Timeout : public Component {
 public:
  void set_pn532(pn532::PN532 *pn532) { this->pn532_ = pn532; }
  void set_timeout(uint32_t timeout_ms) { this->timeout_ms_ = timeout_ms; }

  void set_timeout_sensor(binary_sensor::BinarySensor *sensor) {
    this->timeout_sensor_ = sensor;
  }

  Trigger<> *get_timeout_trigger() { return &this->timeout_trigger_; }

  void loop() override;

 protected:
  void on_successful_poll_() override;
  uint32_t last_response_ms_{0};

  pn532::PN532 *pn532_{nullptr};
  binary_sensor::BinarySensor *timeout_sensor_{nullptr};

  uint32_t timeout_ms_{30000};
  bool timed_out_{false};

  Trigger<> timeout_trigger_;
};

}  // namespace pn532_timeout
}  // namespace esphome
