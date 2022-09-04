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
    node(uint16_t id);

    bool available();

    int read_all(message& message);

    int read(message& message);
    int send(const message& message);

    uint16_t id();

private:
    uint16_t m_id;
    mcp2515_can m_controller;
};

} // namespace drev_can

#endif /* DREV_CAN_H */
