TARGET = swiver
SRCDIR = source
INCDIR = include
LIBDIR = library
RESDIR = resource

CFILES = $(wildcard $(SRCDIR)/*.c)
OBJS = $(CFILES:.c=.o)

CFLAGS = -Ofast -Wall -Wextra -Wno-error

BUILD_PRX = 1
PSP_LARGE_MEMORY = 0
PSP_FW_VERSION = 550

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = swiver v1.0
PSP_EBOOT_ICON = $(RESDIR)/ICON0.png
PSP_EBOOT_PIC1 = $(RESDIR)/PIC1.png

PSPSDK = $(shell psp-config -p)
include $(PSPSDK)/lib/build.mak