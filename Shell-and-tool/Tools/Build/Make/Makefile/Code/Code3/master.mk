PREFIX := ../..
SHELL := /bin/sh
RM := rm -rf
MV := mv
CC := gcc
CXX := g++
CFLAGS += -g -fPIC -O1
CFLAGS += -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wundef -Wredundant-decls -Wunused-parameter -Wparentheses -fno-strict-aliasing
#-Wfatal-errors����ͻ��˳������ܻᵼ����ش�����Ϣ��ȫ�������ڽ�����������Ҫ����������Լ����
#CFLAGS += -Wfatal-errors -Wunreachable-code

LDFLAGS += -L$(PREFIX)/lib -L$(PREFIX)/appcom -shared
MKDIR := mkdir -p
TAGGET_PATH := $(PREFIX)/appcom

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

$(TARGET):$(OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(OBJS) -o $@
	install -v $@ $(TAGGET_PATH)/$@
	
$(OBJS): %.o: %.cpp
	$(call make-depend,$<,$@,$(patsubst %.o,%.d,$@))
	$(CXX) $(CFLAGS) $(INC) -c $< -o $@

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
