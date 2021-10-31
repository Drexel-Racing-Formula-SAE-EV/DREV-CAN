# Drexel Racing Formula EV CAN Library

This is a CAN library for use of the Drexel EV team. It provides a layer of abstraction over the CAN tranceiver drivers so that the same interface is used for both Arduinos and Teensies. Furthermore, it provides a simpler interface and hides away the lower level handling.

# TODO

This code has not yet been cleaned up and still requires a lot of work. 

* Creating a single class structure to interface with the CAN libraries
	* Parent class for abstracted use with children classes for use of different drivers
* Making a more robust example which includes more than a proof of concept

## Installation

Currently, installation unfortunately requires the manual installation of the underlying CAN libraries. I wish to make those libraries a dependency of this one, but I currently do not know how to add a dependency pointing to the library's github repository for the libraries not in the library manager.

1. Install dependency libraries

		git clone https://github.com/Seeed-Studio/Seeed_Arduino_CAN.git

2. Install this library

		git clone https://github.com/Drexel-Racing-Formula-SAE-EV/DREV-CAN.git

## Circuit Description

TODO: replace with diagram

Much of the struggle of achieving CAN communication was in getting the circuit right. While researching CAN, I never knew if it was my circuit or the code which wasn't right. Starting with a clear description of the circuit is a wonderful start, so that you know it's just your code that's broken.

A CAN network at its most basic is simply two resistors, roughly 120 ohms, wired in parallel. On a breadboard, this could be wiring two resistors across the same two columns. One column is for CAN High, while the other is for CAN Low. Therefore, wire each CANH pin to the "high" column and each CANL pin to the "low" column.

