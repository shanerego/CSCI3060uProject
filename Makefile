CXX=clang++ 
VER=-std=c++11
EXE=auction
OBJS=src/main.o src/fileout.o src/transaction.o src/item.o src/user.o src/parser.o


.cpp.o:
	$(CC) $(VER) -c -o $@ $<

all: $(EXE)
	@echo a

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(VER)

clean:
	rm $(EXE) $(OBJS)
