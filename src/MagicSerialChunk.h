#include <Arduino.h>
#ifndef _MAGICSERIALCHUNK_H
#define _MAGICSERIALCHUNK_H

#ifdef ARDUINO
	#include <Arduino.h>
	#ifdef MAGICCHUNK_DEBUG
		#define DSP(v) Serial.print(v)
		#define DSPL(v) Serial.println(v)
	#else
		#define DSP(v)
		#define DSPL(v)
	#endif
#else
	#ifdef MAGICCHUNK_DEBUG
		#include <iostream>
		#define DSP(v)  do { std::cout << v; } while (0)
		#define DSPL(v) do { std::cout << v << std::endl; } while (0)
	#else
		#define DSP(v)
		#define DSPL(v)
	#endif
#endif

#if (!defined(SER_STSEQ1) || !defined(SER_STSEQ2) \
		|| !defined(SER_ENSEQ1) || !defined(SER_ENSEQ2))
	#define SER_STSEQ1 0x02
	#define SER_STSEQ2 0xFE
	#define SER_ENSEQ1 0x03
	#define SER_ENSEQ2 0xFD
#endif

#define SERMAG_DEBUG

#ifdef SERMAG_DEBUG
	#include <stdint.h>
	#include <stdio.h>
	#define MDPRINTF(...) printf(__VA_ARGS__)
#else
	#define MDPRINTF(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct SerialChunk;
struct SerialChunk {
	uint16_t chunksize;
	uint16_t _ctr;
	uint8_t _stseq1, _stseq2, _enseq1, _enseq2;
	void (*_send_startseq)(struct SerialChunk *sp);
	void (*_send_endseq)(struct SerialChunk *sp);
	void (*_write_cb)(struct SerialChunk *sp, uint8_t c);
	void (*add)(struct SerialChunk *sp, uint8_t c);
	void (*addbuf)(struct SerialChunk *sp, uint8_t *b, uint16_t len);
};

void serial_chunk_init(struct SerialChunk *sp,
	                   uint16_t chunksize,
	                   void (*write_cb)(struct SerialChunk *sp, uint8_t c));
void _send_startseq(struct SerialChunk *sp);
void _send_endseq(struct SerialChunk *sp);
void _serial_chunk_add(struct SerialChunk *sp, uint8_t c);
void _serial_chunk_addbuf(struct SerialChunk *sp, uint8_t *b, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif  /* _MAGICSERIALCHUNK_H */
