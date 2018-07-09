# Gesture-Based-Quadcopter
Concept:

Quadcopter working on hand gestures.
Data recieved from accelerometer and gyroscope is sent to Arduino Mega, using I2C protocol. This data is analyzed and then sent to Xbee which is in coordinator mode and the data is transmitted wirelessly to the other xbee which acts as reciever/router. Router Xbee sends this data to Arduino Nano which in turn analyzes the data for any bugs. if the bugs are present, the quadcopter will remain stationary, that data will be discarded and it will wait for further instructions.

Components:

Quadcopter consists of following components:
1.  Quadcopter
    a.  Frame.
    b.  ESC (electronic speed controller) (x4)
    c.  3-phase brushless dc motors (x4)
    d.  11.1 V battery 2200 Mah 25C
2.  Reciever
    a.  Xbee module
    b.  Arduino Nano
3.  Transmitter
    a.  Xbee
    b.  Arduino Mega
    c.  MPU6050 (accelerometer & gyroscope)

