# update

This is the Flagstaff Reasearch Controller board firmware update tool.

## Usage

```bash
~$ git clone https://github.com/SequentMicrosystems/fsrc-rpi.git
~$ cd fsrc-rpi/update/
~/fsrc-rpi/update$ ./update 0
```

If you clone the repository already, skip the first step. 
The command will download the newest firmware version from our server and write it  to the board.
The stack level of the board must be provided as a parameter. 
During firmware update we strongly recommend to disconnect all outputs from the board since they can change state unpredictably.
If the update stop until reach 100%, make sure nowan try to acces the I2C port and restart the process.
