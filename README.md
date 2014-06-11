AR_Drone_RC
===========

AR Drone RC 

Steuerung der AR Drone über eine 4/6/8 Kanal 2.4 Ghz Funksteuerung.
Kommunikation : Empfänger -> Arduino -> i2c -> ARDrone

Staus : 
Arduino Micro Bord <-> Empfänger - OK
RC_to_i2c - OK - First Version
Testboard Raspberry <-> i2c <-> Arduino Micro Bord - OK
i2c_RPi - OK - First Version
AR Drone <-> i2c <-> Arduino Micro Bord - TODO
i2c_ARDone - TODO


RC Empfänger - Arduino
Ports A0 bis A7
Ports SDA, SDL

RC Empfänger : Spektrum AR610 DSMX 6-Channel
Testsender : Spektrum DX8



