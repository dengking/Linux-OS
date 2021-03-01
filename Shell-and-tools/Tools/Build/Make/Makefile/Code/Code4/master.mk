PREFIX := ../..
SHELL := /bin/sh
RM := rm -rf
MV := mv
CC := gcc
CXX := g++ --std=c++11
CFLAGS += -g -O1
CFLAGS += -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wundef -Wredundant-decls -Wunused-parameter -Wparentheses -fno-strict-aliasing
#-Wfatal-errors报错就会退出，可能会导致相关错误信息不全，不利于解决编译错误，需要这个参数的自己添加
CFLAGS += -Wfatal-errors -Wunreachable-code
LDFLAGS += -L$(PREFIX)/lib -L$(PREFIX)/appcom 
MKDIR := mkdir -p
TAGGET_PATH := ./

define make-depend
	$(CXX) -MM	\
		   -MF $3	\
		   -MP	\
		   -MT $2	\
		   $(CFLAGS)	\
		   $(INC)	\
		   $(CPPFLAGS)	\
		   $1
endef

$(TARGET):$(OBJS) $(C_OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(C_OBJS) $(OBJS) -o $@
	
$(OBJS): %.o: %.cpp
	$(call make-depend,$<,$@,$(patsubst %.o,%.d,$@))
	$(CXX) $(CFLAGS) $(INC) -c $< -o $@

$(C_OBJS): %.o: %.c
	$(call make-depend,$<,$@,$(patsubst %.o,%.d,$@))
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ 
	
sinclude $(SRCS:.cpp=.d)

.PHONY: clean
clean:
	$(RM) *.o *.so *.d

tags:
	rm -rf .clang_complete
	touch .clang_complete
	echo $(CFLAGS) >> .clang_complete
	echo $(INC) >> .clang_complete
	cp .clang_complete .syntastic_cpp_config
