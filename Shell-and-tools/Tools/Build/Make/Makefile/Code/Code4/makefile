#VPATH = .:../core:../core/celery:../core/data_model:../core/datetime:../core/feature



INC = -I. -I../include -I../../../../include/api
SRCS := $(wildcard *.cpp)
#SRCS += $(wildcard ../core/celery/*.cpp)
#SRCS += $(wildcard ../core/datetime/*.cpp)
#SRCS += $(wildcard ../core/data_model/*.cpp)
#SRCS += $(wildcard ../core/feature/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
TARGET := DemoMain
LDFLAGS := -L../lib/linux.x64
LIBS = -lt2sdk -lHSInsTradeApi -lpthread

include ./master.mk         