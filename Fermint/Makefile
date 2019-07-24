BOARD := "Intel:arc32:arduino_101"
PORT := "/dev/tty.wchusbserial1430"
CLI = /usr/local/bin/arduino-cli-0.3.7-alpha.preview-linux64

src=$(wildcard *.cpp)


.PHONY: compile

compile: Fermint.ino $(src)
	$(CLI) compile --fqbn $(BOARD) .

.PHONY: upload

upload:
	test -e $(PORT) || { echo "Port not found!"; exit 1; }
	$(MAKE) compile

	$(CLI) upload  --fqbn $(BOARD) -p $(PORT) .

.PHONY: clean

clean:
	rm -rf build/*
	rm -f *.hex *.elf
	rm *~
