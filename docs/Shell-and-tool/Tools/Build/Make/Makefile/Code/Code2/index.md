# GNU/Linux智能Makefile模板（多目录，多文件）

参考：

http://www.voidcn.com/article/p-rkpadnqa-bkn.html



http://www.voidcn.com/article/p-mpuyxady-kg.html



http://bbs.chinaunix.net/thread-3553668-1-1.html



https://gist.github.com/mauriciopoppe/de8908f67923091982c8c8136a063ea6



```makefile
###############################################################################
#
# A smart Makefile template for GNU/LINUX programming
#
# Author: PRC (ijkxyz AT msn DOT com)
# Date:   2011/06/17
#
# Usage:
#   $ make           Compile and link (or archive)
#   $ make clean     Clean the objectives and target.
###############################################################################

CROSS_COMPILE =
OPTIMIZE := -O2 #其他选项:调试: -g
WARNINGS := -Wall -Wno-unused -Wno-format #其他选择: -Wno-deprecated -Wno-write-strings
#macro define
DEFS     := -DOS_COMMON_EXT -DNDEBUG -D_FILE_OFFSET_BITS=64
EXTRA_CFLAGS := -c -fvisibility=hidden -std=c++11
# 输出路径
OUT_DIR	  = ../lib/linux.x64
# 多个路径，使用 空格 隔开
INC_DIR   = . ../include ../../..
# 多个路径，使用 空格 隔开
SRC_DIR   = ./src1 . ./src2 ./src3
# 需要链接的动态库的路径
LIB_DIR   = -L../lib/linux.x64 -L../../../../lib/linux.x64
# 存放object file的路径
OBJ_DIR   = build
EXTRA_SRC =
EXCLUDE_FILES =
# 需要链接的动态库
EXTRA_LIBS	:= -llib1 -llib2 -Wl,--whole-archive -lssl -lcrypto -Wl,--no-whole-archive
SUFFIX       = c cpp cc cxx
TARGET       = $(OUT_DIR)/libTest.so
#TARGET_TYPE  := ar
#TARGET_TYPE  := app
TARGET_TYPE  := so

ifdef DEBUG
DEFS           += -D_DEBUG
else
OPTIMIZE       += -O2
endif

#for gcov version flags
ifdef GCOV 
EXTRA_CFLAGS   += -fprofile-arcs -ftest-coverage
EXTRA_LIBS     += -lgcov
endif


#####################################################################################
#  Do not change any part of them unless you have understood this script very well  #
#  This is a kind remind.                                                           #
#####################################################################################

#FUNC#  Add a new line to the input stream.
define add_newline
$1

endef

#FUNC# set the variable `src-x' according to the input $1
define set_src_x
src-$1 = $(filter-out $4,$(foreach d,$2,$(wildcard $d/*.$1)) $(filter %.$1,$3))

endef

#FUNC# set the variable `obj-x' according to the input $1
define set_obj_x
obj-$1 = $(patsubst %.$1,$3%.o,$(notdir $2))

endef

#VAR# Get the uniform representation of the object directory path name
ifneq ($(OBJ_DIR),)
prefix_objdir  = $(shell echo $(OBJ_DIR)|sed 's:\(\./*\)*::')
prefix_objdir := $(filter-out /,$(prefix_objdir)/)
endif

GCC      := $(CROSS_COMPILE)gcc
G++      := $(CROSS_COMPILE)g++
SRC_DIR := $(sort . $(SRC_DIR))
inc_dir = $(foreach d,$(sort $(INC_DIR) $(SRC_DIR)),-I$d)

#--# Do smart deduction automatically
$(eval $(foreach i,$(SUFFIX),$(call set_src_x,$i,$(SRC_DIR),$(EXTRA_SRC),$(EXCLUDE_FILES))))
$(eval $(foreach i,$(SUFFIX),$(call set_obj_x,$i,$(src-$i),$(prefix_objdir))))
$(eval $(foreach f,$(EXTRA_SRC),$(call add_newline,vpath $(notdir $f) $(dir $f))))
$(eval $(foreach d,$(SRC_DIR),$(foreach i,$(SUFFIX),$(call add_newline,vpath %.$i $d))))

all_objs = $(foreach i,$(SUFFIX),$(obj-$i))
all_srcs = $(foreach i,$(SUFFIX),$(src-$i))

CFLAGS       = $(EXTRA_CFLAGS) $(WARNINGS) $(OPTIMIZE) $(DEFS)
TARGET_TYPE := $(strip $(TARGET_TYPE))

ifeq ($(filter $(TARGET_TYPE),so ar app),)
$(error Unexpected TARGET_TYPE `$(TARGET_TYPE)')
endif

ifeq ($(TARGET_TYPE),so)
 CFLAGS  += -fpic -shared
 LDFLAGS += -shared
endif

PHONY = all .mkdir clean

all: .mkdir $(TARGET)

define cmd_o
$$(obj-$1): $2%.o: %.$1  $(MAKEFILE_LIST)
	$(GCC) $(inc_dir) -Wp,-MT,$$@ -Wp,-MMD,$$@.d $(CFLAGS) -c -o $$@ $$<

endef
$(eval $(foreach i,$(SUFFIX),$(call cmd_o,$i,$(prefix_objdir))))

ifeq ($(TARGET_TYPE),ar)
$(TARGET): AR := $(CROSS_COMPILE)ar
$(TARGET): $(all_objs)
        rm -f $@
        $(AR) rcvs $@ $(all_objs)
else
$(TARGET): LD = $(if $(strip $(src-cpp) $(src-cc) $(src-cxx)),$(G++),$(GCC))
$(TARGET): $(all_objs)
	$(LD) $(LDFLAGS) $(all_objs) $(LIB_DIR) $(EXTRA_LIBS) -o $@
endif

.mkdir:
        @if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi

clean:
	rm -f $(prefix_objdir)*.o $(TARGET)
	rm -f $(prefix_objdir)*.o.d

-include $(patsubst %.o,%.o.d,$(all_objs))

.PHONY: $(PHONY)
```