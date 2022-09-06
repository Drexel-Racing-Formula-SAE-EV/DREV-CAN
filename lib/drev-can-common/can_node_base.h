#ifndef DREV_CAN_NODE_BASE_H
#define DREV_CAN_NODE_BASE_H

#include <stdint.h>

#define SPI_PORT 10
#define CAN_SPEED CAN_500KBPS

/* return values */
#define DREV_CAN_OK (0)
#define DREV_CAN_NOMSG (1)
#define DREV_CAN_SENDFAIL (2)

namespace drev_can {

struct can_message {
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
};

class can_node_base {
public:
    /**
     * @brief create a node on the CAN bus
     */
    can_node_base(uint16_t id);

    /**
     * @brief check for if a message is available
     * @return true if message is available, false if not
     */
    virtual bool available() = 0;

    /**
     * @breif read a can message for any id
     *
     * @param message the received message
     * @return OK for success, NOMSG for no message
     */
    virtual int read_all(can_message& message) = 0;

    /**
     * @brief send a message
     *
     * @param message the message
     * @return OK for success, SENDFAIL for failure
     */
    virtual int send(const can_message& message) = 0;

    /**
     * @brief read a can message only for this node's id
     *
     * @param message the received message
     * @return OK for success, NOMSG for no message
     */
    int read(can_message& message);

    /**
     * @brief get the id of the node
     * @return the id of the node
     */
    uint16_t id();

private:
    uint16_t m_id;
};

} // namespace drev_can

#endif /* DREV_CAN_NODE_BASE_H */
