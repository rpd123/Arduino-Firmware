config.h is set up for GUI+Bluetooth version, cartesian robot arm and stepper gripper.

For mini servo gripper change line

#define GRIPPER 0 //GRIPPER MOTOR IN USE

to

#define GRIPPER 1 //GRIPPER MOTOR IN USE

For SCARA version change line

#define SCARA false

to

#define SCARA true

For RPi (etc) USB version (version2) change

#define SERIALX Serial2

to

#define SERIALX Serial
