COMMON_OBJECTS =
CPU            = msp430g2553
CFLAGS         = -mmcu=${CPU} -I../h
LDFLAGS = ../lib/libTimer.a -L/opt/ti/msp430_gcc/include


CC            = msp430-elf-gcc
AS            = msp430-elf-as


all: demo.elf

demo.elf: ${COMMON_OBJECTS} pmain.o led.o wdInterruptHandler.o ../lib/libTimer.a
	${CC} $(CFLAGS) $^ $(LDFLAGS) -o $@

load: demo.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf
pmain.o: led.h
led.o: led.h
wdInterruptHandler.o: led.h
