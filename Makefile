all:
	g++ oset.cc -o oset
run: all
	./oset
clean:
	rm oset
