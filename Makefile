APP      = veg

SRCS     = $(wildcard *.c)
OBJS     = $(SRCS:.c=.o)

LDFLAGS  =
LIBS     =-lncursesw

.PHONY: all clean

all: clean $(APP)

$(APP): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

clean:
	$(RM) $(OBJS) $(APP)

run:    ${APP}
	./${APP} ${ARGS}
