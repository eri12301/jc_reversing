# jc_reversing
Jade Cocoon 1 Reimplementation
## Jade Cocoon's file formats
The game uses multiple file formats, if you use [Meos Unpacker](https://github.com/Meos4/Jade-Cocoon-Unpacker-Repacker.git) you can get
the main archive DATA.001 unpacked and find a bunch of different files.
Some of them are described here:
### TIY files
Packed TIM files \
File structure:
| Offset    | Description |
| -------- | ------- |
| 0 to 4 byte   | Number of included TIM files := *n* |
| 4 to n+4 byte | Offset (int) of each TIM file       |
| n+4 to EOF    | TIM file data                       |
### SND files
Wrapped VAB audio files \
File structure:
| Offset    | Description |
| -------- | ------- |
| 0 to 32 byte | Header (additional playback infos) |
| 32 to EOF    | VAB file                           |
