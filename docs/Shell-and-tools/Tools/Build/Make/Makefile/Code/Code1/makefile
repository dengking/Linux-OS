# 整个工程由多个源代码目录组成，每个目录有自己独立的一个makefile，这个makefile是一个大的、整体的Makefile来构建整个工程，
# 默认情况是全编，也提供单编某个模块的指令，比如工程proj由mod1、mod2、mod3这几个编译单元组成，它们之间还存在着依赖关系。我写了一个这样的Makefile：
# make # 全编
# make mod1 # 单编mod1目录
# make mod2 # 单编mod2目录
# ...
# make clean # 清除已经编译的

# 切换到指定目录，然后就进行编译
define cd_and_compile
	make -C $(1) || exit "$$?"
endef

# 切换到指定目录，然后就进行清空
define cd_and_clean
	make -C $(1) clean || exit "$$?"
endef

# 所有需要编译的模块，已经按照依赖关系排序
MOD:= mod1 mod2 mod3 

# 先全部清空，然后进行全编
all: clean $(MOD)


# 单编mod3，输出libmod3.so
mod3:
	$(call cd_and_compile, $@)

# 单编mod1，输出libmod1.a
mod1: 
	$(call cd_and_compile, $@)

# 单编mod2，输出libmod2.a
mod2: 
	$(call cd_and_compile, $@)


# 清空mod3
clean_mod3:
	$(call cd_and_clean, mod3)
# 清空mod1
clean_mod1:
	$(call cd_and_clean, mod1)
# 清空mod2
clean_mod2:
	$(call cd_and_clean, mod2)


# 清空
clean:
	@for dir in $(MOD); do	\
		$(call cd_and_clean, $$dir);	\
	done

.PHONY:all $(MOD) clean clean_mod3 clean_mod2 clean_mod1