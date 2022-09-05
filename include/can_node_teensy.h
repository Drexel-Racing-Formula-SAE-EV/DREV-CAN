#ifndef DREV_CAN_NODE_TEENSY_H
#define DREV_CAN_NODE_TEENSY_H

#include "can_node_base.h"

#include <FlexCAN.h>

namespace drev_can {
class can_node_teensy final : can_node_base {
public:
    can_node_teensy(uint16_t id);

    bool available();
    int read_all(can_message& message);
    int send(const can_message& message);

private:
    FlexCAN m_controller;
};
} // namespace drev_can

#endif /* DREV_CAN_NODE_TEENSY_H */