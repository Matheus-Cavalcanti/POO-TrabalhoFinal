CC          := g++
SRC         := ./src
BUILD       := ./build
BIN         := ./bin
HEADERS     := ./include
CFLAGS      := -std=c++17 -I$(HEADERS)
LDFLAGS     := -lm -lsfml-graphics -lsfml-window -lsfml-system
EXEC        := $(BIN)/prog
ZIP         := compactado.zip
FONTS		:= ./assets/fonts
IMAGES		:= ./assets/images

# List of all expected $(BUILD)/*.o
ALL         := $(wildcard $(SRC)/*.cpp)
ALL         := $(ALL:$(SRC)/%.cpp=$(BUILD)/%.o)

all: $(EXEC)

compile: clean all

run: all
	./$(EXEC)

clean:
	rm -f $(EXEC) $(BUILD)/*.o

zip:
	rm -f $(ZIP)
	mkdir TrabalhoFinalPOO/
	cp -R Makefile TrabalhoFinalPOO/
	cp -R ./include TrabalhoFinalPOO/
	cp -R ./src TrabalhoFinalPOO/
	cp -R ./assets TrabalhoFinalPOO/
	zip -r $(ZIP) TrabalhoFinalPOO/
	rm -rd TrabalhoFinalPOO/

$(EXEC): $(ALL)
	$(CC) -o $(EXEC) $(BUILD)/*.o $(LDFLAGS)

$(BUILD)/%.o: $(SRC)/%.cpp $(BUILD)
	$(CC) -o $@ -c $< -I $(HEADERS) $(CFLAGS) 

$(BUILD):
	mkdir -p $(BUILD)
	mkdir -p $(BIN)