CC          := g++
SRC         := ./src
BUILD       := ./build
BIN         := ./bin
HEADERS     := ./include
CFLAGS      := -std=c++11 -I$(HEADERS)
LDFLAGS     := -lm
EXEC        := $(BIN)/prog

# List of all expected $(BUILD)/*.o
ALL         := $(wildcard $(SRC)/*.cpp)
ALL         := $(ALL:$(SRC)/%.cpp=$(BUILD)/%.o)


all: $(EXEC)

compile: clean all

run: all
	./$(EXEC)

clean:
	rm -f $(EXEC) $(BUILD)/*.o

$(EXEC): $(ALL)
	$(CC) -o $(EXEC) $(BUILD)/*.o $(LDFLAGS)

$(BUILD)/%.o: $(SRC)/%.cpp $(BUILD)
	$(CC) -o $@ -c $< -I $(HEADERS) $(CFLAGS) 

$(BUILD):
	mkdir -p $(BUILD)
	mkdir -p $(BIN)