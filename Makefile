all:
	gcc -Wall tk.c aluno.c main.c -o aluno -lncurses
clean:
	rm aluno
