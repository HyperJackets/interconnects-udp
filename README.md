# interconnects-udp

This project contains files for the definitions, encoding, decoding, validation, and printing of UDP packets
used by the HyperJackets 2018 Pod design.

`main.c` contains many examples and POSIX specific code. All other source files and headers are intended to be
cross-platform and compiled for both the host controller (most likely x86_64) and the Pod's on-board Nucleo 144
microcontrollers.
