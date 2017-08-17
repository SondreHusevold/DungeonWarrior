OPT=g++ -std=c++11
TEST= position.o visible.o clickable.o block.o

BINARY=test

all: test

# Skriv ut litt info om FLTK lokalt
info:
	@echo "==================== BIULDING TEST FOR GAME ============================"
	@echo "Compiling with: \t" $(OPT)
	@echo ""
	@echo "========================================================================"

test: info $(TEST)
	$(OPT) $(TEST) -o $(BINARY)
	@echo 
	@echo 'Done. Run with ./'$(BINARY)
	@echo 

# Bygg, med valgte opsjoner
%.o: %.cpp
	$(OPT) -c $< -o $@

clean:
	$(RM) $(BINARY) $(TEST)