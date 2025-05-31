# ESP-NOW Telegraph
A simple telegraph made with ESP-NOW protocol
This telegraph works using two buttons: one represents 0, the other 1. You send messages to the other device by typing a sequence in binary code of 4 bits.
With a total of 16 combinations, the software associates the number typed to a letter of the alphabet:
"a b k d e f h y l m o r s t v x" (a simplified alphabet with 16 letters). The letters are associated with the numbers in the following way:
- decimal --> binary --> letter
- 0 --> 0000 --> a
- 1 --> 0001 --> b/p
- 2 --> 0010 --> c/g/k/q
- 3 --> 0011 --> d
- 4 --> 0100 --> e
- 5 --> 0101 --> f
- 6 --> 0110 --> h
- 7 --> 0111 --> i/j/y
- 8 --> 1000 --> l
- 9 --> 1001 --> m/n
- 10 --> 1010 --> o
- 11 --> 1011 --> r
- 12 --> 1100 --> s
- 13 --> 1101 --> t
- 14 --> 1110 --> u/v/w
- 15 --> 1111 --> x/z

## Components Used
This is the list of components I used for this demo:
- two ESP32 wroom with integrated wifi
- two terminal adapters for the boards
- buttons
- jumper wires
- 1k Ohm resistors
- a breadboard

## Flashing the code into the ESP32
To get the ESP32 to run the code you have to use PlatformIO for VSCode. Install the extension and then import this project.