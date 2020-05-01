%.o : $.c
	gcc -fPIC ${CFLAGS} -c $< -o $@

%.o : %.cpp
	#g++ -fPIC ${CPPFLAGS} $< ${CRYPTOLIB}.c ${CRYPTOLIB}.h -o $@
	#g++ -fPIC ${CPPFLAGS} ${CRYPTOLIB}.c ${CRYPTOLIB}.h -c $< -o $@
	g++ -fPIC ${CPPFLAGS} -c $< -o $@


${EXE} : ${OBJS}
	g++ ${OBJS} ${LDFLAGS} -o $@

${LIBSO} : ${LIBSO_OBJS}
	gcc -o $@ -shared ${LDFLAGS} $^ ${LIBS}