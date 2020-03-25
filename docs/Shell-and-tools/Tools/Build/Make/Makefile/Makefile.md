# Makefile

本文记录我学习makefile的过程。

## Makefile funciton

### Define your own function in a Makefile

[Define your own function in a Makefile](https://coderwall.com/p/cezf6g/define-your-own-function-in-a-makefile)

[Defining custom GNU make functions](https://stackoverflow.com/questions/6520914/defining-custom-gnu-make-functions)

实例如下：

```makefile
# 切换到指定目录，然后就进行编译
define cd_and_compile
	make -C $(1) || exit "$$?"
endef

# 切换到指定目录，然后就进行清空
define cd_and_clean
	make -C $(1) clean || exit "$$?"
endef

# 所有需要编译的模块，已经按照依赖关系排序
MOD:= mod1 mod1 mod1 mod1

# 先全部清空，然后进行全编
all: clean $(MOD)

# 单编 mod1
mod1:
	$(call cd_and_compile, $@)
```



### 官方文档[8 Functions for Transforming Text](https://www.gnu.org/software/make/manual/html_node/Functions.html#Functions)



## Invoke shell command in makefile

如何在makefile中执行shell命令？

下面给出了例子：

```makefile
$(shell mkdir -p ../appcom)
```



## make install

最好使用`install`命令

```makefile
	$(shell mkdir -p ../appcom)
	install -v ./lib/* ../appcom
```

## 源代码分布在多个目录

有的时候，一个target的source code文件分布在多个目录，这种情况下如何来处理呢？

下面给出了例子

```makefile
VPATH = .:../core:../core/celery:../core/data_model:../core/datetime:../core/feature



INC = -I. -I.. -I../hundsun -I../third_party
SRCS := $(wildcard *.cpp)
#SRCS += $(wildcard ../core/celery/*.cpp)
SRCS += $(wildcard ../core/datetime/*.cpp)
SRCS += $(wildcard ../core/data_model/*.cpp)
SRCS += $(wildcard ../core/feature/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
TARGET := libfsc_quote_predict.so
LIBS = -lalgo_public -lh5api -lhiredis -lredis++ -ltensorflow

include ../make/master.mk         
```

