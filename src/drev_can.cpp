#include "drev_can.h"

namespace drev_can {

node::node(uint16_t id) : m_id(id), m_controller(SPI_PORT) {
    m_controller.begin(CAN_SPEED);
}

bool node::available() {
    return m_controller.checkReceive() == CAN_MSGAVAIL;
}

int node::read_all(message& message) {
    if (m_controller.readMsgBufID(reinterpret_cast<unsigned long*>(&message.id),
                                  &message.length, message.data) == CAN_NOMSG) {
        return DREV_CAN_NOMSG;
    }

    return DREV_CAN_OK;
}

int node::read(message& message) {
    int ret = read(message);

    if (ret != DREV_CAN_OK) {
        return ret;
    }

    if (message.id != m_id) {
        return DREV_CAN_NOMSG;
    }

    return DREV_CAN_OK;
}

int node::send(const message& message) {
    if (m_controller.sendMsgBuf(m_id, 0, 0,
                                reinterpret_cast<byte>(message.length),
                                message.data) == CAN_FAILTX) {
        return DREV_CAN_SENDFAIL;
    }

    return DREV_CAN_OK;
}

uint16_t node::id() {
    return m_id;
}

} // namespace drev_can
