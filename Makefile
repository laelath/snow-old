PREFIX ?= /usr/local
DESTDIR ?= # root dir

all: snow

snow: snow.c
	$(CC) -o snow snow.c -l ncurses

clean:
	$(RM) snow

installdirs:
	install -d $(DESTDIR)$(PREFIX)/bin

install: snow installdirs
	install -m 0755 snow $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/bin/snow
