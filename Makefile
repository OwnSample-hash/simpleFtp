CC = clang
CFLAGS = -ggdb -DGIT_COMMIT=\"$(shell git rev-parse --short HEAD)\"
LDFLAGS =

BIN = server client

_MAKE_DIR = make.dir
SRC_DIR = src
BUILD_DIR = ${_MAKE_DIR}/build

SERVER_CSRCS = $(shell find ${SRC_DIR} -type f -name "*.c" -not -name "client.c")
CLIENT_CSRCS = $(shell find ${SRC_DIR} -type f -name "*.c" -not -name "server.c")

SERVER_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SERVER_CSRCS))
CLIENT_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(CLIENT_CSRCS))

all: prolog ${BIN}
	@echo Done bulding

prolog:
	@echo CC=${CC}
	@echo CFLAGS=${CFLAGS}
	@echo BIN=${BIN}
	@echo BUILD_DIR=${BUILD_DIR}
	@echo FULL_BD=$(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(shell find $(SRC_DIR) -type d))
	@echo SERVER_CSRCS = $(SERVER_CSRCS)
	@echo SERVER_OBJS = $(SERVER_OBJS)
	@echo CLIENT_CSRCS = $(CLIENT_CSRCS)
	@echo CLIENT_OBJS = $(CLIENT_OBJS)
	@echo


$(BUILD_DIR):
	mkdir -p $(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(shell find $(SRC_DIR) -type d))


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


server: $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) $(LDFLAGS) -o server


client: $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) $(LDFLAGS) -o client

clean:
	rm ${BUILD_DIR} -rf
	rm simple -f
