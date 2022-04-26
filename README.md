# neo6m-controller

This is a small wrapper around SoftwareSerial and TinyGPSPlus for Arduino to read various data from
a NEO 6M GPS. Requires C++17 (`-std=c++1z`).

## Setup

For this to work, one simply needs to connect the NEO 6M GPS to the specified RX and TX pins.
After setting up the basic code, you can then directly start reading data from the GPS with
various helper functions.

**IMPORTANT**: Remember that the TX pin from the GPS needs to be connected to the RX pin on the
Arduino, and the RX pin from the GPS needs to be connected to the TX pin on your board, as they
act like a sender/receiver pair.

## Usage

You can use Neo6M::GPS through software serial by using the `GPS(rxpin, txpin)`
constructors and the `GPS::begin()` function. Note that the the rxpin, as noted above, need to be wired
correctly and which pins are suitable for a connection is different between each Arduino board.

You can also use this wrapper with any other Stream, e.g. HardwareSerial. This can be useful, as
for example on an Arduino Mega the communication ports 14..19 do not work with SoftwareSerial.
To use custom streams, you can use the `GPS()` constructor and pass your Stream to the
`GPS::useStream(Stream*)` function. Note that the wrapper does not call `Stream::begin()` for you.
