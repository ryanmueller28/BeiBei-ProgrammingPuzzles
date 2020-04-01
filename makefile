bei-bei-puzzles:
	g++ -I/usr/include/python3.8 -lpython3.8 -lsfml-graphics -lsfml-window -lsfml-system  Main.cpp -o bei-bei-puzzles 

clean:
	rm -f bei-bei-puzzles

run: $(OUT)
	./bei-bei-puzzles
