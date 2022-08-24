all:
	@echo 'try "make vi" to edit.'

vi:
	vim \
		Makefile \
		library.properties \
		src/MagicSerialChunk.cpp \
		src/MagicSerialChunk.h

