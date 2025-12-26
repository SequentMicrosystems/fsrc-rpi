# Modbus

The Solera SYSTEMS Controller can be accessed through the Modbus RTU protocol over the RS-485 port.
You can set-up the RS-485 port with **fsrc** command.

Example:
```bash
fsrc 0 cfg485wr 1 9600 1 0 1
```
Set Modbus RTU, Baudrate: 9600bps, 1 Stop Bit,  parity: None, slave address base: 1
```bash
fsrc -h cfg485wr
```
display the full set of options

## Slave Address
The three address jumpers have a dual purpose. 
When the card is accessed from a Raspberry Pi, the jumpers define the offset of the I2C address, permitting stacking of up to 8 cards.
When the card is accessed through the MODBUS protocol over the RS-485 port, the jumpers define the offset of the RS-485 base address set by the software.

## Modbus object types
All Modbus RTU object types with standard addresses are implemented: Coils, Discrete Inputs, Input registers, Holding registers.

### Coils

Access level Read/Write, Size 1 bit

| Device function | Register Address | Modbus Address | Description |
| --- | --- | --- | --- |
|   COIL_OD1 | 0001 | 0x00 | Open drain #1 control |
|	COIL_OD2|0002 | 0x01 |  Open drain #2 control |
|	COIL_OD3|0003 | 0x02 |  Open drain #3 control |
|	COIL_OD4|0004 | 0x03 |  Open drain #4 control |
|	COIL_OD5| 0005 | 0x04 | Open drain #5 control|
|	COIL_OD6|0006 | 0x05 | Open drain #6 control |
|	COIL_OD7|0007 | 0x06 | Open drain #7 control|
|	COIL_OD8|0008 | 0x07 | Open drain #8 control|
|	COIL_OPT_RISING1|0009 | 0x08 | Opto input #1 rising edges enable counting| 
|	COIL_OPT_RISING2|0010 | 0x09 | Opto input #2 rising edges enable counting|
|	COIL_OPT_RISING3|0011 | 0x0a | Opto input #3 rising edges enable counting|
|	COIL_OPT_RISING4|0012 | 0x0b | Opto input #4 rising edges enable counting|
|	COIL_OPT_FALLING1|0013 | 0x0c | Opto input #1 falling edges enable counting|
|	COIL_OPT_FALLING2|0014 | 0x0d |Opto input #2 falling edges enable counting|
|	COIL_OPT_FALLING3|0015 | 0x0e |Opto input #3 falling edges enable counting|
|	COIL_OPT_FALLING4|0016 | 0x0f |Opto input #4 falling edges enable counting|


### Discrete Inputs

Access level Read Only, Size 1 bit

| Device function | Register Address | Modbus Address | Description |
| --- | --- | --- | --- |
| DI_OPT1 | 10001 | 0x00 | input #1 state|
| DI_OPT2 | 10002 | 0x01 |input #2 state|
| DI_OPT3 | 10003 | 0x02 |input #3 state|
| DI_OPT4 | 10004 | 0x03 |input #4 state|


### Input registers

Access level Read Only, Size 16 bits

| Device function | Register Address | Modbus Address | Measurement Unit | Description |
| --- | --- | --- | --- | --- |
| IR_0_5IN1| 30001 | 0x00 | mV | 0-5V input value for ch #1| 
| IR_0_5IN1| 30002 | 0x01 | mV | 0-5V input value for ch #2| 
| IR_0_5IN1| 30003 | 0x02 | mV | 0-5V input value for ch #3| 
| IR_0_5IN1| 30004 | 0x03 | mV | 0-5V input value for ch #4| 
| IR_0_5IN1| 30005 | 0x04 | mV | 0-5V input value for ch #5| 
| IR_0_5IN1| 30006 | 0x05 | mV | 0-5V input value for ch #6| 
| IR_0_5IN1| 30007 | 0x06 | mV | 0-5V input value for ch #7| 
| IR_0_5IN1| 30008 | 0x07 | mV | 0-5V input value for ch #8| 
| IR_0_5IN1| 30009 | 0x08 | mV | 0-5V input value for ch #9| 
| IR_0_5IN1| 300010 | 0x09 | mV | 0-5V input value for ch #10| 
| IR_0_5IN1| 300011 | 0x0a | mV | 0-5V input value for ch #11| 
| IR_0_5IN1| 300012 | 0x0b | mV | 0-5V input value for ch #12| 
| IR_OPT_CNT1| 30013 | 0x0c |  | Opto input channel #1 counter value| 
| IR_OPT_CNT2| 30014 | 0x0d |  | Opto input channel #2 counter value| 
| IR_OPT_CNT3| 30015 | 0x0e |  | Opto input channel #3 counter value| 
| IR_OPT_CNT4| 30016 | 0x0f |  | Opto input channel #4 counter value| 
| IR_OWB_TEMP1| 30017 | 0x10 | &deg;C x 100 | OWB sensor #1 temperature| 
| IR_OWB_TEMP2| 30018 | 0x10 | &deg;C x 100 | OWB sensor #2 temperature| 
| IR_OWB_TEMP3| 30019 | 0x10 | &deg;C x 100 | OWB sensor #3 temperature| 
| IR_OWB_TEMP4| 30020 | 0x10 | &deg;C x 100 | OWB sensor #4 temperature| 
| IR_OWB_TEMP5| 30021 | 0x10 | &deg;C x 100 | OWB sensor #5 temperature| 
| IR_OWB_TEMP6| 30022 | 0x10 | &deg;C x 100 | OWB sensor #6 temperature| 
| IR_OWB_TEMP7| 30023 | 0x10 | &deg;C x 100 |OWB sensor #7 temperature| 
| IR_OWB_TEMP8| 30024 | 0x10 | &deg;C x 100 | OWB sensor #8 temperature| 
| IR_OWB_TEMP9| 30025 | 0x10 | &deg;C x 100 | OWB sensor #9 temperature| 
| IR_OWB_TEMP10| 30026 | 0x10 | &deg;C x 100 |OWB sensor #10 temperature| 
| IR_OWB_TEMP11| 30027 | 0x10 | &deg;C x 100 |OWB sensor #11 temperature| 
| IR_OWB_TEMP12| 30028 | 0x10 | &deg;C x 100 |OWB sensor #12 temperature| 
| IR_OWB_TEMP13| 30029 | 0x10 | &deg;C x 100 |OWB sensor #13 temperature| 
| IR_OWB_TEMP14| 30030 | 0x10 | &deg;C x 100 |OWB sensor #14 temperature| 
| IR_OWB_TEMP15| 30031 | 0x10 | &deg;C x 100 |OWB sensor #15 temperature| 
| IR_OWB_TEMP16| 30032 | 0x10 | &deg;C x 100 |OWB sensor #16 temperature| 


### Holding registers

Access level Read/Write, Size 16 bits

| Device function | Register Address | Modbus Address | Measurement Unit | Range | Description |
| --- | --- | --- | --- | --- | --- |
| HR_0_10V_OUT1 | 40001 | 0x00 | mV | 0..10000 | 0-10V Output Channel #1 value|
| HR_0_10V_OUT2 | 40002 | 0x01 | mV | 0..10000 | 0-10V Output Channel #2 value|
| HR_PWM_OD_OUT1 | 40003 | 0x02 | % x 100 | 0..10000 | PWM OD #1 fill factor|
| HR_PWM_OD_OUT2 | 40004 | 0x03 | % x 100 | 0..10000 | PWM OD #2 fill factor|
| HR_PWM_OD_OUT3 | 40005 | 0x04 | % x 100 | 0..10000 | PWM OD #3 fill factor|
| HR_PWM_OD_OUT4 | 40006 | 0x05 | % x 100 | 0..10000 | PWM OD #4 fill factor|


## Function codes implemented

* Read Coils (0x01)
* Read Discrete Inputs (0x02)
* Read Holding Registers (0x03)
* Read Input Registers (0x04)
* Write Single Coil (0x05)
* Write Single Register (0x06)
* Write Multiple Coils (0x0f)
* Write Multiple registers (0x10)
