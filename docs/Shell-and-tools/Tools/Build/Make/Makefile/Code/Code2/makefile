# 切换到指定目录，然后就进行编译
define cd_and_compile
	make -C $(1) || exit "$$?"
endef

# 切换到指定目录，然后就进行清空
define cd_and_clean
	make -C $(1) clean || exit "$$?"
endef

# 所有需要编译的模块，已经按照依赖关系排序
MOD:= frame biz bizcore ust_opt

# 先全部清空，然后进行全编
all: clean $(MOD)

# 单编 ust_opt
ust_opt:
	$(call cd_and_compile, $@)

# 单编frame，输出libust_bizframe.a
frame:
	$(call cd_and_compile, $@)

# 单编biz，输出libust_biz.a
biz: 
	$(call cd_and_compile, $@)

# 单编bizcore，输出libust_biztrade.a
bizcore: 
	$(call cd_and_compile, $@)

# 清空ust_opt
clean_ust_opt:
	$(call cd_and_clean, ust_opt)
# 清空frame
clean_frame:
	$(call cd_and_clean, frame)
# 清空biz
clean_biz:
	$(call cd_and_clean, biz)
# 清空bizcore
clean_bizcore:
	$(call cd_and_clean, bizcore)


# 清空
clean:
	@for dir in $(MOD); do	\
		$(call cd_and_clean, $$dir);	\
	done

.PHONY:all $(MOD) clean clean_ust_opt clean_frame clean_biz clean_bizcore