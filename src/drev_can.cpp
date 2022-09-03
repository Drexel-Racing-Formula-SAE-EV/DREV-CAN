#include <drev_can.h>

namespace drev_can {

bus::bus(uint16_t id) : m_controller(SPI_PORT), m_id(id) {
    m_controller.begin(CAN_SPEED);
}

int bus::send(void* data, size_t length) {
    if (m_controller.sendMsgBuf((unsigned long) m_id, 0, (byte) length,
                                (byte*) data) == CAN_FAILTX) {
        return DREV_CAN_SENDFAIL;
    }

    return DREV_CAN_OK;
}

int bus::read(void* data, size_t* length) {
    unsigned long id;

    if (m_controller.readMsgBufID(&id, (byte*) &length, (byte*) data) ==
        CAN_NOMSG) {
        return DREV_CAN_NOMSG;
    }

    if (id != m_id) {
        return DREV_CAN_WRONGID;
    }

    return DREV_CAN_OK;
}

bool bus::available() {
    return m_controller.checkReceive() == CAN_MSGAVAIL;
}

} // namespace drev_can
