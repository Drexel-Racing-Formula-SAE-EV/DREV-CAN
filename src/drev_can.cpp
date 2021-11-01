#include <drev_can.h>

DrevCan::DrevCan(uint32_t id): controller(SPI_PORT), id(id) {
    controller.begin(CAN_SPEED);
}

DrevCan::sendMessage(void *data, size_t length) {
	controller.sendMsgBuf((unsigned long) this->id, 0, (byte) length, (byte*) data);
}

int DrevCan::readMessage(void *data, size_t *length) {
	unsigned long id;

	if(controller.readMsgBufID(&id, (byte*) &length, (byte*) data) == CAN_NOMSG) {
		return DREV_CAN_NOMSG;
	}

	if(id != this->id) {
		return DREV_CAN_WRONGID;
	}

	return DREV_CAN_OK;
}

bool DrevCan::available() {
	return controller.checkReceive() == CAN_MSGAVAIL;
}

