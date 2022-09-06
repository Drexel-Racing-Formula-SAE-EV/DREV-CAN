#include "can_node_teensy.h"

namespace drev_can {
can_node_teensy::can_node_teensy(uint16_t id)
    : can_node_base{id}, m_controller{500000, 0, 1, 1} {
    m_controller.begin();
}

bool can_node_teensy::available() {
    return m_controller.available();
}

int can_node_teensy::read_all(can_message& message) {
    CAN_message_t flex_can_message;
    int ret = m_controller.read(flex_can_message);

    if (!ret) {
        return DREV_CAN_NOMSG;
    }

    static_assert(sizeof(message.data) == sizeof(flex_can_message.buf),
                  "Message buffers are different sizes");
    memcpy(message.data, flex_can_message.buf, sizeof(flex_can_message.buf));

    message.id = flex_can_message.id;
    message.length = flex_can_message.len;

    return DREV_CAN_OK;
}

int can_node_teensy::send(const can_message& message) {
    CAN_message_t flex_can_message = {
        .id = message.id,
        .ext = 1,
        .len = message.length,
        .timeout = 0,
    };

    static_assert(sizeof(message.data) == sizeof(flex_can_message.buf),
                  "Message buffers are different sizes");
    memcpy(flex_can_message.buf, message.data, sizeof(flex_can_message.buf));

    int ret = m_controller.write(flex_can_message);

    if (!ret) {
        return DREV_CAN_SENDFAIL;
    }

    return DREV_CAN_OK;
}

} // namespace drev_can