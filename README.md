# CAN Example

This is an example project containing working CAN communication between and among Arduinos and Teensies.

## Disclaimers and TODOs

This code has not yet been cleaned up and still requires source changes. It is a very basic example requiring one device to be sending and one device to be receiving. It will go through several iterations before being a "complete" example. These changes include:

* ~~Restructuring the project to a more sensible structure~~
* ~~Selecting one Arduino CAN library between the two examples~~
	* Both have been tested
	* The SparkFun library is the driver made for this specific arduino shield, but the Seeed one seems to have a more active github repository
	* Furthermore, it is specified to work with the MCP2551, which is the tranceiver on the SparkFun shield
	* For these reasons, it will be selected over the SparkFun library
* Creating a single class structure to interface with the CAN libraries
* ~~Moving that header and source to its own git submodule~~
	* Instead, the examples have been moved to `./examples` and the library will be contained in `./src`
* Making a more robust example which includes more than a proof of concept

## Installation

Currently, installation unfortunately requires the manual installation of the underlying CAN libraries. I wish to make those libraries a dependency of this one, but I currently do not know how to add a dependency pointing to the library's github repository for the libraries not in the library manager.

1. Install dependency libraries

		git clone https://github.com/Seeed-Studio/Seeed_Arduino_CAN.git

2. Install this library

		git clone https://github.com/Drexel-Racing-Formula-SAE-EV/can-example.git

## Circuit Description

TODO: replace with diagram

Much of the struggle of achieving CAN communication was in getting the circuit right. While researching CAN, I never knew if it was my circuit or the code which wasn't right. Starting with a clear description of the circuit is a wonderful start, so that you know it's just your code that's broken.

A CAN network at its most basic is simply two resistors, roughly 120 ohms, wired in parallel. On a breadboard, this could be wiring two resistors across the same two columns. One column is for CAN High, while the other is for CAN Low. Therefore, wire each CANH pin to the "high" column and each CANL pin to the "low" column.

