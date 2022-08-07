all:
	@echo 'try "make vi" to edit.'

vi:
	vim \
		Makefile \
		library.properties \
		src/MagicSerialChunk.c \
		src/MagicSerialChunk.h

