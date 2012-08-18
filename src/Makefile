include ../Makefile.common

OBJS+=startup.o
OBJS+=main.o
OBJS+=lcd_control.o

all: src

src: app.a

app.a: $(OBJS)
	$(AR) cr app.a $(OBJS)

.PHONY:src clean

clean:
	rm -f app.a $(OBJS)
