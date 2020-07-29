# Baseconv

Translating number between base 10, base 16 and base 2

![Alt text](https://i.imgur.com/PExb4MJ.png "Converting numbers")

## User manual

### Converting a number in many bases.

When starting this program with no arguments, you are presented a prompt. After it you should enter either:
* A string of ASII characters
* A negative number in base 10
* A 'd' followed by a positive or negative number in base 10
* A 'h' or a 'x' followed by a number in base 16
* A 'b' followed by a number in base 2
The program will then print th number you entered in base 10, 16 and 2 and the ASCII equivalent of the 8 LSB of your number.

### Exiting

To quit the program, simply enter `exit` after the prompt.

### Getting help

To print a help message, enter `help` after the prompt or start the program with any argument.

### Instalation

To install, this program simply do

```bash
make && make install.
```

