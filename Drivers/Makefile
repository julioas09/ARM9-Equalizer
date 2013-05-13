
ifndef TOOLCHAIN

ifdef CROSS_TS7400 
#TOOLCHAIN = CODESOURCERY_201109
TOOLCHAIN = CROSSTOOL_334
endif

endif

ifeq ($(TOOLCHAIN),CODESOURCERY_201109)
ARCH = arm
PREFIX = ts
CROSS_COMPILE = arm-none-linux-gnueabi-
CC_PATH = /usr/local/opt/crosstool/arm-linux/gcc-3.3.4-glibc-2.3.2/bin
MOD_HPATH = /home/lsed02/linux24/include
MODFLAGS = -DMODULE -D__KERNEL__ -I$(MOD_HPATH)
CFLAGS = -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common -fomit-frame-pointer -mcpu=arm920t
LDFLAGS =
endif

ifeq ($(TOOLCHAIN),CROSSTOOL_334)
ARCH = arm
PREFIX = ts
CROSS_COMPILE = arm-linux-
CC_PATH = /usr/local/opt/crosstool/arm-linux/gcc-3.3.4-glibc-2.3.2/bin
MOD_HPATH = /home/lsed02/linux24/include
MODFLAGS = -DMODULE -D__KERNEL__ -I$(MOD_HPATH)
CFLAGS = -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common -fomit-frame-pointer -mcpu=arm920t
LDFLAGS =
endif

MODPREFIX = $(PREFIX)md

all: $(MODPREFIX)Inter.o

$(MODPREFIX)%.o: %.c
	$(CC_PATH)/$(CROSS_COMPILE)gcc $(MODFLAGS) $(CFLAGS) -c $^ -o $@

$(PREFIX)%.o: %.c
	$(CC_PATH)/$(CROSS_COMPILE)gcc $(CFLAGS) -c $^ -o $@

%: %.o
	$(CC_PATH)/$(CROSS_COMPILE)gcc $(LDFLAGS) $^ -o $@
