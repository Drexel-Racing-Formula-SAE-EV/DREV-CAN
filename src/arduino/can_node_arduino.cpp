#include "can_node_arduino.h"

namespace drev_can {
can_node_arduino::can_node_arduino(uint16_t id)
    : can_node_base{id}, m_controller{SPI_PORT} {
    m_controller.begin(CAN_SPEED);
}

bool can_node_arduino::available() {
    return m_controller.checkReceive() == CAN_MSGAVAIL;
}

int can_node_arduino::read_all(can_message& message) {
    if (m_controller.readMsgBufID(reinterpret_cast<unsigned long*>(&message.id),
                                  &message.length, message.data) == CAN_NOMSG) {
        return DREV_CAN_NOMSG;
    }

    return DREV_CAN_OK;
}

int can_node_arduino::send(const can_message& message) {
    if (m_controller.sendMsgBuf(id(), 0, 0,
                                reinterpret_cast<byte>(message.length),
                                message.data) == CAN_FAILTX) {
        return DREV_CAN_SENDFAIL;
    }

    return DREV_CAN_OK;
}

} // namespace drev_can