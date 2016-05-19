_CFLAGS=-D__IDP__ -D__PLUGIN__ -ps
!include ..\..\allmake.mak

#----------------------------------------------------------------------------
WIN32_LOCAL_OBJ=$(F)nes_rstub$(O) $(F)tcpip$(O)
WIN32CLIENT=$(BIN_PATH)nes_stub$(PLUGIN)
win32_stub: $(WIN32CLIENT)

$(WIN32CLIENT): $(WIN32_LOCAL_OBJ) $(IDALIB) ..\plugin.def
	$(LINKER) @&&~
$(LINKOPTS) $(LDRSTUB) $(WIN32_LOCAL_OBJ)
$@

$(IDALIB) $(LIBS) $(IDPSLIB)
..\plugin.def
~
	$(PEUTIL) -d..\plugin.def $@

# MAKEDEP dependency list ------------------
$(F)tcpip$(O)   : $(I)area.hpp $(I)bytes.hpp $(I)err.h $(I)fpro.h           \
	          $(I)funcs.hpp $(I)help.h $(I)ida.hpp $(I)idd.hpp          \
	          $(I)idp.hpp $(I)kernwin.hpp $(I)lines.hpp $(I)llong.hpp   \
	          $(I)nalt.hpp $(I)netnode.hpp $(I)pro.h $(I)segment.hpp    \
	          $(I)ua.hpp $(I)xref.hpp idarpc.hpp tcpip.cpp
$(F)nes_rstub$(O): $(I)area.hpp $(I)bytes.hpp $(I)dbg.hpp $(I)diskio.hpp     \
	          $(I)err.h $(I)fpro.h $(I)funcs.hpp $(I)help.h             \
	          $(I)ida.hpp $(I)idd.hpp $(I)idp.hpp $(I)kernwin.hpp       \
	          $(I)lines.hpp $(I)llong.hpp $(I)loader.hpp $(I)nalt.hpp   \
	          $(I)name.hpp $(I)netnode.hpp $(I)pro.h $(I)segment.hpp    \
	          $(I)ua.hpp $(I)xref.hpp                                   \
	          common_local.cpp deb_nes.hpp idarpc.cpp idarpc.hpp         \
	          m6502_local.cpp nes_local.cpp nes_rstub.cpp
