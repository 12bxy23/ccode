LDFLAGS+=-pthread
TARGET=server
SRC=main.c media_lib.c ./thread_pool/pool.c ./thread_pool/queue.c

$(TARGET):$(SRC)
	gcc -o $@ $^ $(LDFLAGS)


