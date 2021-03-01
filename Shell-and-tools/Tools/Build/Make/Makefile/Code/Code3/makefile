INC = -I. -I.. -I$(PREFIX) -I../algo_include
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
TARGET = libalgo_vwap_plus.so
LIBS = -lstrategy_public -lalgo_twap_plus

include ./master.mk