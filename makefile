MULTIPROG:=
BASEMK:=$(realpath base.mk)

include srcs/make.mk

all: $(MULTIPROG)
clean:
	@$(RM) -r build
fclean: clean
	@$(RM) $(MULTIPROG)
re: fclean
	$(MAKE) all
.PHONY: all clean fclean re
.DEFAULT_GOAL:=all
