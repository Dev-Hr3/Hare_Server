CXX = clang++
CPPFLAGS=-g -std=c++20

INCLUDEDIR =
LIBDIR =

## LIST OF CONSTANTS BEGIN
ENABLE_LUA_5_VERSION = 0
ENABLE_STATIC = 1
## LIST OF CONSTANTS END

ifeq ($(ENABLE_STATIC), 1)
CPPFLAGS+= -static
endif

ifeq ($(ENABLE_LUA_5_VERSION), 2)
INCLUDEDIR += -I../../../liblua/5.2/install/include
INCLUDEDIR += -I../../../liblua/5.2/src/lib
# LIBDIR += -L../../../liblua/5.2/install/lib
LIBS += ../../../liblua/5.2/install/lib/liblua.a
else
INCLUDEDIR += -I../../../liblua/5.0/include
INCLUDEDIR += -I../../../liblua/5.0/src
# LIBDIR += -L../../../liblua/5.0/lib
LIBS += ../../../liblua/5.0/lib/liblua.a ../../../liblua/5.0/lib/liblualib.a
endif

all: qc create_conversion

qc: qc.cc qc.o crc32.o
	$(CXX) $(CPPFLAGS) -o ./qc $(INCLUDEDIR) $(LIBDIR) qc.o crc32.o $(LIBS)

crc32.o: crc32.cc
	$(CXX) $(CPPFLAGS) -c $< $(INCLUDEDIR) $(LIBDIR)

qc.o: qc.cc
	$(CXX) $(CPPFLAGS) -c $< $(INCLUDEDIR) $(LIBDIR)

create_conversion.o: create_conversion.cc
	$(CXX) $(CPPFLAGS) -c $< $(INCLUDEDIR) $(LIBDIR)

create_conversion: crc32.o create_conversion.o
	$(CXX) -g -o ./create_conversion $(INCLUDEDIR) $(LIBDIR) create_conversion.o crc32.o $(LIBS)

clean:
	rm -f qc cc qc.o crc32.o cc.o create_conversion.o
