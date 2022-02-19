#!/bin/sh -xe

set -e

#arduino-cli lib install PinChangeInterrupt
arduino-cli compile --fqbn arduino:avr:uno antswhirly
# arduino-cli upload -p /dev/ttyUSB0 --fqbn aceduino:avr:m168xt4m AceGrid
arduino-cli upload --verbose  -p /dev/ttyUSB0 --fqbn arduino:avr:uno antswhirly
