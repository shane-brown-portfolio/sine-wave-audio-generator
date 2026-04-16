CC = g++
DEBUG = -g

FLAGS = ${DEBUG} -Wall -Wextra -Wshadow -Wunreachable-code -Wredundant-decls \
        -Wuninitialized -Werror -std=c++17

LIBS = -lsndfile -lportaudio

PROG1 = audio
PROGS = ${PROG1}

SRCS = main.cpp wav_utils.cpp
OBJS = main.o wav_utils.o

all: ${PROG1}

${PROG1}: ${OBJS}
	$(CC) $(FLAGS) -o $@ $^ $(LIBS)

main.o: main.cpp wav_utils.h
	$(CC) $(FLAGS) -c $< -o $@

wav_utils.o: wav_utils.cpp wav_utils.h
	$(CC) $(FLAGS) -c $< -o $@

clean cls:
	rm -f ${PROGS} *.o *~ \#*

TAR_FILE = ${LOGNAME}_sine-wave-audio-generator.tar.gz

tar: clean
	rm -f $(TAR_FILE)
	tar cvfa $(TAR_FILE) *.cpp *.h [mM]akefile README.md wavs/