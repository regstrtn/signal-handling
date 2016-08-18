all: shell mysed signals mygrep

shell: 
	gcc -o shell shell.c

mysed: 
	gcc -o mysed mysed.c

signals:
	gcc -o sig sighandler.c

mygrep:
	gcc -o mygrep mygrep.c
