CFLAGS = -Wall -Wextra
LIBFLAGS = -I ./include -L ./src -l #penser à ajouter le nom de la lib en utilisant ce flag (sans mentionner 'lib', ni l'extension '.h')
LIBS = objects gestion-de-fichiers


all: $(LIBS) gpt


#-----CREATION LIB
objects:
	gcc -c src/libgestion-de-fichiers.c
gestion-de-fichiers: libgestion-de-fichiers.o
	ar -rsc src/libgestion-de-fichiers.a libgestion-de-fichiers.o
	rm *.o
#-----FIN CREATION LIB



gpt: solver-by-chat-gpt.c
	gcc $(CFLAGS) solver-by-chat-gpt.c $(LIBFLAGS) gestion-de-fichiers -o gpt


clean:
	rm src/libgestion-de-fichiers.a
	rm gpt