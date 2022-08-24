#include <Arduino.h>
#ifdef ARDUINO
	#include <Arduino.h>
#else
	/* #include <stdio.h> */
	/* #include <stdint.h> */
	/* #include <string.h> */
	/* #include <stdlib.h> */
#endif
/* #define MAGICCHUNK_DEBUG */
#include "MagicSerialChunk.h"

void serial_chunk_init(struct SerialChunk *sp,
	                   uint16_t chunksize,
	                   void (*write_cb)(struct SerialChunk *sp, uint8_t c)) {
	memset(sp, 0, sizeof *sp);
	sp->chunksize = chunksize;
	/* sp->_ctr = 0; already 0 */
	sp->_stseq1 = SER_STSEQ1;
	sp->_stseq2 = SER_STSEQ2;
	sp->_enseq1 = SER_ENSEQ1;
	sp->_enseq2 = SER_ENSEQ2;
	sp->_write_cb = write_cb;
	sp->_send_startseq = _send_startseq;
	sp->_send_endseq = _send_endseq;
	sp->add = _serial_chunk_add;
	sp->addbuf = _serial_chunk_addbuf;
}

void _send_startseq(struct SerialChunk *sp) {
	DSP("Sending Start Sequence:\n");
	(*sp->_write_cb)(sp, sp->_stseq1);
	(*sp->_write_cb)(sp, sp->_stseq2);
}
void _send_endseq(struct SerialChunk *sp) {
	DSP("Sending End Sequence:\n");
	(*sp->_write_cb)(sp, sp->_enseq1);
	(*sp->_write_cb)(sp, sp->_enseq2);
}

void _serial_chunk_add(struct SerialChunk *sp, uint8_t c) {
	if (!sp->_ctr) _send_startseq(sp);
	sp->_ctr++;
	DSP("Sending a char [");
	DSP(sp->_ctr);
	DSP('] = ');
	Serial.println(c);
	(*sp->_write_cb)(sp, c);
	if (sp->_ctr >= sp->chunksize) {
		sp->_send_endseq(sp);
		sp->_ctr=0;
	}
}
void _serial_chunk_addbuf(struct SerialChunk *sp, uint8_t *b, uint16_t len) {
	for (uint16_t i=0; i<len; i++) sp->add(sp, b[i]);
}

