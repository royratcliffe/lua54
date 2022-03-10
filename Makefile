SOBJ = $(patsubst %, $(PACKSODIR)/lua5%.$(SOEXT), 4)
CORE54 = lapi lcode lctype ldebug ldo ldump lfunc lgc llex lmem lobject lopcodes lparser lstate lstring ltable ltm lundump lvm lzio
LIB54 = lauxlib lbaselib lcorolib ldblib liolib lmathlib loadlib loslib lstrlib ltablib lutf8lib linit
BASE54 = $(CORE54) $(LIB54)
OBJ54 = $(patsubst %, c/%.o, lua54) $(patsubst %, c/54/%.o, $(BASE54))
OBJ = $(OBJ54)

CFLAGS += -O2 -fomit-frame-pointer -Dlua_c

all: $(SOBJ)

$(PACKSODIR)/lua54.$(SOEXT): $(OBJ54)
	mkdir -p $(PACKSODIR)
	$(LD) $(LDSOFLAGS) -o $@ $< $(SWISOLIB)

check::
install::
clean:
	rm -f $(OBJ)
distclean: clean
	rm -f $(SOBJ)
