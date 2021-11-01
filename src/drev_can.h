#ifndef __CAN_H__
#define __CAN_H__

#include <mcp2515_can.h>

#define SPI_PORT 10
#define CAN_SPEED CAN_500KBPS

/* return values */
#define DREV_CAN_OK (0)
#define DREV_CAN_NOMSG (1)
#define DREV_CAN_WRONGID (2)

class DrevCan {
public:
	DrevCan(uint32_t id);

	int sendMessage(void *data, size_t length);

	bool available();
	int readMessage(void *data, size_t *length);

	uint32_t getId() { return id; }
private:
	mcp2515_can controller;
	uint32_t id;
};

#endif /* __CAN_H__ */
