%.o : $.c
	gcc -fPIC ${CFLAGS} -c $< -o $@

%.o : %.cpp
	g++ -fPIC ${CPPFLAGS} -c $< -o  $@


${EXE} : ${OBJS}
	g++ ${OBJS} ${LDFLAGS} -o -lboost_python -lboost_system -lpython2\.7$@

${LIBSO} : ${LIBSO_OBJS}
	gcc -o $@ -shared ${LDFLAGS} $^ ${LIBS}