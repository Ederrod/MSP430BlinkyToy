# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

all: button.elf 

#additional rules for files
button.elf: ${COMMON_OBJECTS} wdInterruptHandler.o p2_interrupt_handler.o buzzer.o led.o led_dim_statemachine.o switches.o main.o statemachine.a ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

statemachine.a: statemachine.o
	$(AR) crs $@ $^

load: button.elf
	mspdebug rf2500 "prog button.elf"

clean:
	rm -f *.o *.elf

