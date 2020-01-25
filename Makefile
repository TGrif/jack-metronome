CC=g++
LIBS=`pkg-config jack sndfile gtkmm-3.0 --cflags --libs`

MKDIR_P := mkdir -p
OUT_DIR := build

$(OUT_DIR)/metronome: main.cc
	$(MKDIR_P) $(@D)
	$(CC) -o $(@D)/metronome main.cc $(LIBS)

clean:
	rm -rf $(OUT_DIR)