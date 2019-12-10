# ArduinoIRcontrol
Use IR sensor to contor motors
In arduino, we have stepper.h, servo and Infrared Light remote control libraries.
In this example, I use L298 to control servo and Stepper at the same time, but I would recommend using A4988 intead of L298. 
The reason is L298 is easily to get overheated (The remaining currents change its energy to heat loss)
