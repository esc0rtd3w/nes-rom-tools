Spartan X 2 -- bitstring compression\crypto utility package

---

Coded by Parasyte
An Abstract Crouton Production

---

  The developers of this game were not too keen on compression. I'm guessing
they figured that summing all the data would help their compression routine.
Instead, some of the compressed data is actually larger than the original. This
package was created in order to help hack and translate the game. It was quite
a challenge and learning experience. I hope someone else will be able to make
use of these!

  Data is compressed into bitstrings, where bytes will not appear on 8-bit
boundaries. It may sound like a good idea at first, but it's really a bad
compression method. Control bits are placed between uncompressed bytes,
eventually making the data much larger (this is called 'bloating').

  The control bits have two purposes: control bit 1 pastes a cached byte to
output. Control bit 2 is an LZ-copy from a 64-byte look-back buffer. Multiple
cache control bits can be placed in sequence to output many cache bytes. Each
control bit 1 takes only 1 bit, which is a quite good compression ratio - 8:1.
  Control bit 2 requires that control bit 1 be set to '0', followed by
control bit 2 (set to '1'), and finally a 6-bit 'source' and 6-bit 'length'. In
total, control bit 2 uses 14 bits. 14 cache bytes = 1 LZ copy. Each control bit
2 has a minimum length of '2' and maximum of '66'. For a compression ratio in
the range of 10:7 to 33:7.
  An uncompressed byte has both control bits set to '0' as well as the 8-bit
byte itself, for a total of 10 bits per uncompressed byte. Here we have
an example of bloating.

  To my knowledge, the repacker will compress data EXACTLY as the official
compressor program would have. This means that the compression ratio's will be
no better or worse when repacking the original data. Edited data will likely
have a different size. Be sure that the repacked data is not large enough to
overflow into pre-existing data! If it can't be avoided, you will be able to
change the pointers with relative ease. (see below)

  OK, enough on the theory! The source code and executables are included. These
should be run from the command line. Run each program with no parameters to
display the respective program's usage.

  For reference, here are a list of all [known] compressed bitstrings in the
game, along with a short description of each, if available.


address - size
0xC210  - 0x0127
0xC390  - 0x00BA [palettes]
0xC490  - 0x00B0
0xC590  - 0x00AB [tile maps for boss and HQ screens]
0xC710  - 0x049F
0xCC10  - 0x0271 [title screen and level intro screen tile maps]
0xCF10  - 0x0310
0xD310  - 0x0B28 [main script]


  If you haven't noticed, the script bitstring's size seems too short. However,
the data DIRECTLY after the bitstring is used by the game while booting. It is
not a part of the bitstring it proceeds.

  Pointers to these bitstrings can be found at address 0x1CDD7. They are
arranged in an odd fashion, where the high byte of each pointer is placed in
succession, followed by the low bytes of each pointer. Arrange the data into
two rows and read each pointer vertically, like so:

82 83 84 85 87 8C 8F 93
00 80 80 80 00 00 00 00

"8200" corresponds to 0xC210, "8380" corresponds to 0xC390, etc.

Enjoy!

---

Dragon Eye Studios: http://dragoneye.cg-games.net/
Abstract Crouton: http://www.freewebs.com/abstractcrouton/