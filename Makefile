outputName = compiler

all: compiler.cpp
	g++ -o ${outputName} compiler.cpp

clean:
	rm -rf ./test compiler