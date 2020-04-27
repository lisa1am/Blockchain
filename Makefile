#CFLAGS := -fPIC -O3 -g -Wall -Werror
#CC := gcc
#MAJOR := 0
#MINOR := 1
#NAME := uECC
#VERSION := $(MAJOR).$(MINOR)

#lib: lib$(NAME).so.$(VERSION)

#test: $(NAME)_test
#	LD_LIBRARY_PATH=. ./$(NAME)_test

#$(NAME)_test: lib$(NAME).so
#	$(CC) $(NAME)_test.c -o $@ -L. -l$(NAME)

#lib$(NAME).so: lib$(NAME).so.$(VERSION)
#	ldconfig -v -n .
#	ln -s lib$(NAME).so.$(MAJOR) lib$(NAME).so

#lib$(NAME).so.$(VERSION): $(NAME).o
#	$(CC) -shared -Wl,-soname,lib$(NAME).so.$(MAJOR) $^ -o $@

#clean:
#	$(RM) $(NAME)_test *.o *.so*

CPPFLAGS=-I /usr/include/python3.6m
LIBS=-lpython3.6m -lboost_python3-py36

COMPOSANT = signature

LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o
CRYPTOLIB = uECC

include gcc.mk


all: $(LIBSO)
clean:
	rm -f ${LIBSO}  ${LIBSO_OBJS}


${DESTINATION_LIBSO}: ${LIBSO}
	cp $< $@


