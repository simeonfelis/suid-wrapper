
SCRIPT_DIR   = /usr/sbin/
SCRIPT_NAME  = ejabberdctl
SCRIPT_PATH  = ${SCRIPT_DIR}${SCRIPT_NAME}

NAME = ${SCRIPT_NAME}-wrapper

WRAPPER_DIR  = ${SCRIPT_DIR}
WRAPPER_PATH = ${WRAPPER_DIR}${NAME}


all:
	${CC} -Wall -DSCRIPT_PATH=${SCRIPT_PATH} -DSCRIPT_NAME=${SCRIPT_NAME} -o ${NAME} main.c

clean:
	rm -f ${NAME}

install: clean all
	cp ${NAME} ${WRAPPER_PATH}
	chmod ug+s ${WRAPPER_PATH}

uninstall:
	rm -f ${WRAPPER_PATH}
