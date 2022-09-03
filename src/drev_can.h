#ifndef DREV_CAN_H
#define DREV_CAN_H

#include <mcp2515_can.h>

#define SPI_PORT 10
#define CAN_SPEED CAN_500KBPS

/* return values */
#define DREV_CAN_OK (0)
#define DREV_CAN_NOMSG (1)
#define DREV_CAN_WRONGID (2)
#define DREV_CAN_SENDFAIL (3)

namespace drev_can {

struct message {
    uint8_t data[8];
    uint8_t length;
};

class bus {
public:
    bus(uint16_t id);

    int read(message& message);
    int send(const message& message);

    bool available();
    uint16_t id() { return m_id; }

private:
    mcp2515_can m_controller;
    uint16_t m_id;
};

} // namespace drev_can

#endif /* DREV_CAN_H */
