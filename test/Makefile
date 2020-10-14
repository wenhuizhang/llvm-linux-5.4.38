tests = $(patsubst %.c,%,$(wildcard *.c))

all: $(tests)

%: %.c
	gcc -o $@ $< -lm

clean:
	rm -f $(tests)
	rm -f alter
	rm -f tmp
	rm -f ./result/*
