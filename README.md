# CAN Example

This is an example project containing working CAN communication between and among Arduinos and Teensies.

## Disclaimers and TODOs

This code has not yet been cleaned up and still requires source changes. It is a very basic example requiring one device to be sending and one device to be receiving. It will go through several iterations before being a "complete" example. These changes include

* Restructuring the project to a more sensible structure
* Selecting one Arduino CAN library between the two examples
* Containing the libraries in one header/interface
* Moving that header and source to its own git submodule
* Making a more robust example which includes more than a proof of concept

## Circuit Description

TODO: replace with diagram

Much of the struggle of achieving CAN communication was in getting the circuit right. While researching CAN, I never knew if it was my circuit or the code which wasn't right. Starting with a clear description of the circuit is a wonderful start, so that you know it's just your code that's broken.

A CAN network at its most basic is simply two resistors, roughly 120 ohms, wired in parallel. On a breadboard, this could be wiring two resistors across the same two columns. One column is for CAN High, while the other is for CAN Low. Therefore, wire each CANH pin to the "high" column and each CANL pin to the "low" column.

