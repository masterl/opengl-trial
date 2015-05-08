# The MIT License (MIT)

# Copyright (c) 2015 Leonardo de Oliveira Lourenço

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#   =======================
#  ||    ROOT MAKEFILE    ||
#   =======================
#

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Compiler:
#--------------------------------------------------------------------------
CC = g++

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Directories for linking
#--------------------------------------------------------------------------
# ======== GERAL ========
LIBDIR = -L/usr/lib
LOCALLIBDIR =  -L/usr/local/lib
VIDYAPREFIXLIBDIR = -L/usr/local/vidya/libs

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Compilation flags
#--------------------------------------------------------------------------
#PGFLAG = -lpq
#ALLBOOSTFLAGS = -lboost_locale -lpthread -lboost_thread -lboost_filesystem -lboost_system -lboost_regex -lboost_serialization -lboost_random
#ALLENDFLAGS = -lssl -lcrypto -lz -ldl -lmhash -lcurl
GENERALSTARTFLAGS = -Wall -std=c++14
#STACKTRACEFLAGS = -rdynamic
#ALLCOMPFLAGS = $(GENERALSTARTFLAGS) `pkg-config gtkmm-3.0 --cflags`
ALLCOMPFLAGS = $(GENERALSTARTFLAGS)

#LINKFLAGS = `pkg-config gtkmm-3.0 --libs` -lboost_system -lboost_filesystem
LINKFLAGS = -lglfw -lglut -lGLEW -lGL -lboost_filesystem -lboost_system

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Sources directories
#--------------------------------------------------------------------------
# ======== main ========
MAINDIR = src

UTILSDIR = utils

_ALLSRCDIRLIST = $(MAINDIR) $(UTILSDIR)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	Dependencies and object directories
#--------------------------------------------------------------------------
DEPDIR = deps

DEPDIRLIST = $(addsuffix /$(DEPDIR),$(_ALLSRCDIRLIST))

DEPSUFFIX = _dep

#----====----====----====----====----
OBJDIR = objs

OBJDIRLIST = $(addsuffix /$(OBJDIR),$(_ALLSRCDIRLIST))

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Sources list
#--------------------------------------------------------------------------
#ALLSRCFILES := $(wildcard $(_ALLSRCDIRLIST)/*.cpp)
ALLSRCFILES = $(foreach dir,$(_ALLSRCDIRLIST),$(wildcard $(dir)/*.cpp))

MAINFILES = $(wildcard $(MAINDIR)/*.cpp)
UTILSFILES = $(wildcard $(UTILSDIR)/*.cpp)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Dependencies Lists
#--------------------------------------------------------------------------
#   Dependencias dos .o
MAINDEPS := $(addprefix $(MAINDIR)/$(DEPDIR)/,$(patsubst %.cpp,%.d,$(notdir $(MAINFILES))))
UTILSDEPS := $(addprefix $(UTILSDIR)/$(DEPDIR)/,$(patsubst %.cpp,%.d,$(notdir $(UTILSFILES))))

#   Dependencias dos .d
MAINDEPDEPS := $(subst .d,$(DEPSUFFIX).d,$(MAINDEPS))
UTILSDEPDEPS := $(subst .d,$(DEPSUFFIX).d,$(UTILSDEPS))


ALLDEPDEPS :=	$(MAINDEPDEPS) $(UTILSDEPDEPS)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Object Lists
#--------------------------------------------------------------------------
MAINOBJS := $(addprefix $(MAINDIR)/$(OBJDIR)/,$(patsubst %.cpp,%.o,$(notdir $(MAINFILES))))
UTILSOBJS := $(addprefix $(UTILSDIR)/$(OBJDIR)/,$(patsubst %.cpp,%.o,$(notdir $(UTILSFILES))))


ALLOBJS :=	$(MAINOBJS) $(UTILSOBJS)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Executable
#--------------------------------------------------------------------------
EXEC := opengl

BINDIR := bin

export CC
export ALLCOMPFLAGS
export LOCALLIBDIR
export DEPDIR
export OBJDIR
export DEPSUFFIX
export ALLDEPDEPS
export ALLOBJS

all:
	@echo -e '\n\n==================== ERROR ===================='
	@echo -e '   --------------------------------------------'
	@echo "   |        There's no default rule!           |"
	@echo -e '   --------------------------------------------'
	@echo -e '   Choose an option:\n'
	@echo -e '\texec\t    [compiles main executable]'
	@echo -e '\tclean\t\t    [erases all files]'
	@echo -e '===============================================\n\n'

exec: rmexec allobjs FORCE | $(BINDIR)
	$(CC) $(ALLOBJS) $(ALLCOMPFLAGS) -o $(BINDIR)/$(EXEC) $(LINKFLAGS)
	@echo -e '=----------------------------------------------------='
	@echo -e '=           $(EXEC) generated/updated                ='
	@echo -e '=           Executable: $(BINDIR)/$(EXEC)  \t\t     ='
	@echo -e '=----------------------------------------------------=\n\n'

allobjs: objdirs alldeps
	@set -e; $(MAKE) --no-print-directory -f makeobjs allobjs

#aobjsdebian: objdirs adeps
#	@set -e; $(MAKE) --no-print-directory -f makeobjs allobjs PGINCDIR=$(PGDEBIANINCDIR) PGLIBDIR=$(PGDEBIANLIBDIR)

#aobjscentos: objdirs adeps
#	@set -e; $(MAKE) --no-print-directory -f makeobjs allobjs PGINCDIR=$(PGCENTOSINCDIR) PGLIBDIR=$(PGCENTOSLIBDIR)

alldeps: depdirs
	@set -e; $(MAKE) --no-print-directory -f makedeps alldeps

depdirs: | $(DEPDIRLIST)
	@echo -e '------------------------------------------------------'
	@echo -e '\tDependencies directories created/checked!\n'

objdirs: | $(OBJDIRLIST)
	@echo -e '------------------------------------------------------'
	@echo -e '\tObjects directories created/checked!\n'

$(DEPDIRLIST) $(OBJDIRLIST) $(BINDIR):
	mkdir $@

#trash rule for tests
test: FORCE
	@echo -e '\n--------------------------------------------------'
	@echo -e '\tOption disabled!\nExecute make without parameters to see the menu'
	@echo -e '--------------------------------------------------\n'
#	@echo -e 'Tests:'
#	@echo -e '$(_ALLSRCDIRLIST)\n'
#	@echo -e '$(ALLSRCFILES)'

clean: rmdeps rmobjs rmexec FORCE
	rm -rf $(BINDIR)
	@echo -e '------------------------------------------------------'
	@echo -e '\tAll files removed!\n\n'

rmexec:
	rm -f $(BINDIR)/$(EXEC)
	@echo -e '------------------------------------------------------'
	@echo -e '\tExecutables removed!'

rmdeps: FORCE
	rm -rf $(MAINDIR)/$(DEPDIR)
	rm -rf $(UTILSDIR)/$(DEPDIR)

rmobjs: FORCE
	rm -rf $(MAINDIR)/$(OBJDIR)
	rm -rf $(UTILSDIR)/$(OBJDIR)
	
FORCE:

#  ===================================
#  ||    VIDYA MAKE FILE >FIM<      ||
#  ===================================
