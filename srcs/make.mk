NAME=		ft_shmup

SRCS=		main init game/init game/free game/move game/colision game/kill game/draw game/bullets

DIR=		srcs
$(NAME):	CFLAGS=-Wall -Wextra -I include -g3 \
#	-Wno-unused-variable -Weverything -Wno-poison-system-directories -Wno-unused-parameter -Wno-padded -Wno-gnu-compound-literal-initializer -Wno-zero-length-array -Wno-date-time
$(NAME):	LDFLAGS=-lncurses
include		$(BASEMK)
