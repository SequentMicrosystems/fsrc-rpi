# fsrc 
Command line interface for Flagstaff Research Controller

## Setup

Enable Raspberry Pi I2C communication by opening a terminal and typing:
```bash
~$ sudo raspi-config
```
Go to the *Interface Options* menu then *I2C* and enable the port.

## Usage

```bash
~$ git clone https://github.com/SequentMicrosystems/fsrc-rpi.git
~$ cd fsrc-rpi/
~/fsrc-rpi$ sudo make install
```

Now you can access all the functions of the relays board through the command "fsrc". Use -h option for help:
```bash
~$ fsrc -h
```

If you clone the repository any update can be made with the following commands:

```bash
~$ cd fsrc-rpi/  
~/fsrc-rpi$ git pull
~/fsrc-rpi$ sudo make install
``` 
## [FIRMWARE UPDATE](https://github.com/SequentMicrosystems/fsrc-rpi/tree/master/update)
