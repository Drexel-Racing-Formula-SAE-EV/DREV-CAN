#ifndef DREV_CAN_H

#if defined(ARDUINO_AVR_UNO)
#include "can_node_arduino.h"
namespace drev_can {
using can_node = can_node_arduino;
}
#elif defined(CORE_TEENSY)
#include "can_node_teensy.h"
namespace drev_can {
using can_node = can_node_teensy;
}
#else
#error unsupported board
#endif

#endif /* DREV_CAN_H */
