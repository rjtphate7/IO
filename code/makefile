CC = avr-gcc
MC = atmega8
F_CPU = 8000000UL


io.hex: io.elf
	avr-objcopy -O ihex -j .text -j .data io.elf io.hex
io.elf: adc.o ultrasonic.o uart.o PWM_motors.o motors_controller.o io.o
	$(CC) -Os -Werror -mmcu=$(MC) -Werror adc.o ultrasonic.o uart.o PWM_motors.o motors_controller.o io.o -o io.elf
adc.o: adc.h adc.c
	$(CC) -c -Os -Werror -D F_CPU=$(F_CPU) -mmcu=$(MC) adc.c -o adc.o
ultrasonic.o: ultrasonic.h ultrasonic.c
	$(CC) -c -Os -Werror -D F_CPU=$(F_CPU) -mmcu=$(MC) ultrasonic.c -o ultrasonic.o
uart.o: uart.h uart.c
	$(CC) -c -Os -Werror -D F_CPU=$(F_CPU) -mmcu=$(MC) uart.c -o uart.o
PWM_motors.o: PWM_motors.h PWM_motors.c
	$(CC) -c -Os -Werror -D F_CPU=$(F_CPU) -mmcu=$(MC) PWM_motors.c -o PWM_motors.o
motors_controller.o: motors_controller.h motors_controller.c
	$(CC) -c -Os -Werror -D F_CPU=$(F_CPU) -mmcu=$(MC) motors_controller.c -o motors_controller.o
io.o: io.c
	$(CC) -c -Os -Werror -D F_CPU=$(F_CPU) -mmcu=$(MC) io.c -o io.o
