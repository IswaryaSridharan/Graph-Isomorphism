CC = gcc
RM = rm

CFLAGS = -fopenmp -lpthread -o3

TARGET = graph_v4

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean: $(RM) $(TARGET)
