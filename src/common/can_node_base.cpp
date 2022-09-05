#include "can_node_base.h"

namespace drev_can {

can_node_base::can_node_base(uint16_t id) : m_id(id) {}

int can_node_base::read(can_message& message) {
    int ret = read_all(message);

    if (ret != DREV_CAN_OK) {
        return ret;
    }

    if (message.id != m_id) {
        return DREV_CAN_NOMSG;
    }

    return DREV_CAN_OK;
}

uint16_t can_node_base::id() {
    return m_id;
}

} // namespace drev_can
