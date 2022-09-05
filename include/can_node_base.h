#ifndef DREV_CAN_H
#define DREV_CAN_H

#include <mcp2515_can.h>

#define SPI_PORT 10
#define CAN_SPEED CAN_500KBPS

/* return values */
#define DREV_CAN_OK (0)
#define DREV_CAN_NOMSG (1)
#define DREV_CAN_SENDFAIL (2)

namespace drev_can {

struct message {
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
};

class node {
public:
    /**
     * @brief create a node on the CAN bus
     */
    node(uint16_t id);

    /**
     * @brief check for if a message is available
     * @return true if message is available, false if not
     */
    bool available();

    /**
     * @breif read a can message for any id
     *
     * @param message the received message
     * @return OK for success, NOMSG for no message
     */
    int read_all(message& message);

    /**
     * @brief read a can message only for this node's id
     *
     * @param message the received message
     * @return OK for success, NOMSG for no message
     */
    int read(message& message);

    /**
     * @brief send a message
     *
     * @param message the message
     * @return OK for success, SENDFAIL for failure
     */
    int send(const message& message);

    /**
     * @brief get the id of the node
     * @return the id of the node
     */
    uint16_t id();

private:
    uint16_t m_id;
    mcp2515_can m_controller;
};

} // namespace drev_can

#endif /* DREV_CAN_H */
