# MagicSerialChunk - Send magic-sequence-wrapped data (ex. for serial comm)

Tiny low-overhead library, coupled with MagicSerialDechunk, for inter-device
communications.  The initial version uses magic sequences before and after
a user-provided length of data (a chunk).  It presently doesn't do a
checksum nor variable length.

## Usage:
```c
...Some magic code goes here...
```
