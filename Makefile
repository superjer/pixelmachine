EXE_NAME = pixelmachine
OBJS = main.o pixelmachine.o font.o collision.o sjui.o
CC = g++
FLAGS = -Wall -O3 -s
LIBS = -lSDL -lm
LIBSWIN = -lmingw32 -lSDLmain -lSDL -lm


.C.o:
	$(CC) $< -c $(FLAGS) $(INC)

$(EXE_NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(FLAGS) $(LIBS)

win: $(OBJS)
	$(CC) -o $(EXE_NAME).exe $(OBJS) $(FLAGS) -mwindows $(LIBSWIN)

clean:
	rm *.o
	del *.o

