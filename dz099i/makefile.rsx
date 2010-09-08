#
#  Rules for building the Allegro library with RSXNT. This file is included
#  by the primary makefile, and should not be used directly.
#
#  This is not a full makefile: it uses the MSVC DLL, so it only has to
#  build an import library and the test/example programs. You must have
#  compiled the MSVC library before using this makefile.



# -------- define some variables that the primary makefile will use --------

PLATFORM = RSXNT
OBJ_DIR = obj/rsxnt/$(VERSION)
LIB_BASENAME = lib$(SHORT_VERSION)_i.a
LIB_NAME = lib/rsxnt/$(LIB_BASENAME)
EXE = .exe
OBJ = .o



# -------- check that the RSXNTDJ environment variable is set --------

ifndef RSXNTDJ
baddjgpp:
	@echo Your RSXNTDJ environment variable is not set correctly!
endif

RSXNTDJ_U = $(subst \,/,$(RSXNTDJ))
RSXNTDJ_D = $(subst /,\,$(RSXNTDJ))



# -------- give a sensible default target for make without any args --------

.PHONY: _default

_default: default



# -------- decide what compiler options to use --------

ifdef WARNMODE
WFLAGS = -Wall -W -Werror -Wno-unused
else
WFLAGS = -Wall -Wno-unused
endif

ifdef PGCC
OFLAGS = -mpentium -O6 -ffast-math
else
OFLAGS = -m486 -O3 -ffast-math
endif

ifdef DEBUGMODE

# -------- debugging build --------
CFLAGS =  -DDEBUGMODE=$(DEBUGMODE) $(WFLAGS) -g
LFLAGS =  -g

else
ifdef PROFILEMODE

# -------- profiling build --------
CFLAGS =  $(WFLAGS) $(OFLAGS) -pg
LFLAGS =  -pg

else

# -------- optimised build --------
CFLAGS =  $(WFLAGS) $(OFLAGS) -fomit-frame-pointer
LFLAGS = 

endif
endif



# -------- this code checks for gccw32 or RSXNT 1.5 --------

ifneq ($(wildcard $(RSXNTDJ_U)/bin/gccw32.exe),)
   RSXGCC = gccw32 
else
   RSXGCC = gcc -Zwin32
endif



# -------- list platform specific programs --------

VPATH = wintests

LIBRARIES = -lcomdlg32

PROGRAMS = dibgrab dibhello scrsave

dibgrab: wintests/dibgrab.exe
dibhello: wintests/dibhello.exe
scrsave: wintests/scrsave.scr



# -------- rules for installing and removing the library files --------

$(RSXNTDJ_U)/lib/$(LIB_BASENAME): $(LIB_NAME)
	copy lib\rsxnt\$(LIB_BASENAME) $(RSXNTDJ_D)\lib
	@echo You should also run fixdjgpp and then make install that,
	@echo to get the documentation and headers copied across.

install: $(RSXNTDJ_U)/lib/$(LIB_BASENAME)
	@echo The $(DESCRIPTION) RSXNT library has been installed.

uninstall:
	-rm -fv $(RSXNTDJ_U)/lib/liball_i.a $(RSXNTDJ_U)/lib/libald_i.a $(RSXNTDJ_U)/lib/libalp_i.a
	@echo All gone!



# -------- finally, we get to the fun part... --------

$(LIB_NAME): lib/msvc/$(SHORT_VERSION)$(LIBRARY_VERSION).dll

define MAKE_LIB
makelib lib/msvc/$(SHORT_VERSION)$(LIBRARY_VERSION).dll -o $(LIB_NAME)
endef

$(OBJ_DIR)/%.o: %.c
	$(RSXGCC) $(CFLAGS) -I. -I./include -o $@ -c $<

*/%.exe: $(OBJ_DIR)/%.o $(LIB_NAME)
	$(RSXGCC) $(LFLAGS) -o $@ $< $(LIB_NAME) $(LIBRARIES)

wintests/scrsave.scr: $(OBJ_DIR)/scrsave.o $(OBJ_DIR)/scrsave.res $(LIB_NAME)
	$(RSXGCC) $(LFLAGS) -o wintests/scrsave.exe $(OBJ_DIR)/scrsave.o $(LIB_NAME) $(LIBRARIES)
	rsrc $(OBJ_DIR)/scrsave.res wintests/scrsave.exe
	rename wintests\scrsave.exe scrsave.scr

$(OBJ_DIR)/scrsave.res: wintests/scrsave.rc
	grc -o $(OBJ_DIR)/scrsave.res wintests/scrsave.rc

PLUGIN_LIB = lib/rsxnt/lib$(VERY_SHORT_VERSION)dat.a
PLUGINS_H = obj/rsxnt/plugins.h
PLUGIN_DEPS = $(LIB_NAME) $(PLUGIN_LIB)
PLUGIN_SCR = scx

define GENERATE_PLUGINS_H
copy tools\plugins\*.inc obj\rsxnt\plugins.h
endef

define MAKE_PLUGIN_LIB
ar rs $(PLUGIN_LIB) $(PLUGIN_OBJS)
endef

define LINK_WITH_PLUGINS
$(RSXGCC) $(LFLAGS) -o $@ $< $(strip $(PLUGIN_LIB) $(addprefix @,$(PLUGIN_SCRIPTS)) $(LIB_NAME) $(LIBRARIES))
endef



# -------- generate automatic dependencies --------

depend:
	$(RSXGCC) -MM -MG -I. -I./include demo/*.c examples/*.c setup/*.c tests/*.c tools/*.c tools/plugins/*.c wintests/*.c > _depend.tmp
	sed -e "s/^[a-zA-Z0-9_\/]*\///" _depend.tmp > _depend2.tmp
	sed -e "s/^\([a-zA-Z0-9_]*\)\.o:/obj\/rsxnt\/alleg\/\1\.o:/" _depend2.tmp > obj/rsxnt/alleg/makefile.dep
	sed -e "s/^\([a-zA-Z0-9_]*\)\.o:/obj\/rsxnt\/alld\/\1\.o:/" _depend2.tmp > obj/rsxnt/alld/makefile.dep
	sed -e "s/^\([a-zA-Z0-9_]*\)\.o:/obj\/rsxnt\/allp\/\1\.o:/" _depend2.tmp > obj/rsxnt/allp/makefile.dep
	rm _depend.tmp _depend2.tmp
