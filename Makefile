APP = dsp_test

# Add any other object files to this list below
APP_OBJS = dsp_util.o dsp_main.o dsp_wave.o
CFLAGS = -DDEBUG

all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CC) -o $@ $(APP_OBJS) $(LDFLAGS) $(LDLIBS)
clean:
	rm -f $(APP) *.o

