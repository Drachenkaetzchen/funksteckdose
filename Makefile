PRG            = funksteckdose
OBJ            = src/funksteckdose.o src/rfm12.o
DEFS		   = -D__PLATFORM_LINUX__

# these are set by config in parent dir
#MCU_TARGET     = atmega32
#DEFS           = -DF_CPU=16000000



OPTIMIZE       = -Os

LIBS           =

# You should not have to change anything below here.

CC             = gcc
SRC = $(OBJ:%.o=%.c)
DEPENDFILE = .depend

# Override is only needed by avr-lib build system.

override CFLAGS        =  -g -Wall $(OPTIMIZE) -fno-jump-tables $(DEFS)
override LDFLAGS       = -Wl,-Map,$(PRG).map

all: dep $(PRG) 

$(PRG): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o $(PRG) $(UART_LIB_DIR)/*.o
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

dep: $(SRC)
	$(CC) $(DEFS) -MM $(SRC) > $(DEPENDFILE)

-include $(DEPENDFILE)
