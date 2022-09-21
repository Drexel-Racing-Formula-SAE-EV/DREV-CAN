#ifndef DREV_CAN_NODE_ARDUINO_H
#define DREV_CAN_NODE_ARDUINO_H

#include "can_node_base.h"

#include <mcp2515_can.h>

namespace drev_can {
class can_node_arduino final : public can_node_base {
public:
    can_node_arduino(uint16_t id);

    bool available();
    int read_all(can_message& message);
    int send(const can_message& message);

private:
    mcp2515_can m_controller;
};
} // namespace drev_can

#endif /* DREV_CAN_NODE_ARDUINO_H */
