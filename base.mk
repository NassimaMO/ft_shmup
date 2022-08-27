OBJS=		${SRCS:%=build/$(DIR)/%.o}
MULTIPROG+=$(NAME)
$(NAME):	CFLAGS+=-DPROG_NAME='"$(NAME)"'
$(NAME):  $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
-include	${OBJS:%.o=%.d}
build/%.o: %.c srcs/make.mk
	@mkdir -p ${@D}
	$(COMPILE.c) -MMD $(OUTPUT_OPTION) $<
build/%.o: %.cpp
	@mkdir -p ${@D}
	$(COMPILE.cpp) -MMD $(OUTPUT_OPTION) $<
