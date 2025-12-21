#include "pn532_timeout.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pn532_timeout {

static const char *TAG = "pn532_timeout";

void PN532Timeout::loop() {
  if (this->pn532_ == nullptr || this->timeout_sensor_ == nullptr)
    return;

  uint32_t last = this->pn532_->get_last_response_ms();  // accessor required
  if (last == 0)
    return;

  uint32_t now = millis();
  bool timeout = (now - last) > this->timeout_ms_;

  if (timeout != this->timed_out_) {
    this->timed_out_ = timeout;

    // Publish HA state
    this->timeout_sensor_->publish_state(timeout);

    if (timeout) {
      ESP_LOGW(TAG, "PN532 timed out");
      this->timeout_trigger_.trigger();
    } else {
      ESP_LOGI(TAG, "PN532 recovered");
    }
  }
}

}  // namespace pn532_timeout
}  // namespace esphome
