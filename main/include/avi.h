#ifndef _AVI_H_
#define _AVI_H_

#include <stdio.h>

#define FRAME_WIDTH 320
#define FRAME_HEIGHT 240
#define FRAME_RATE 30

void write_avi_header(FILE* f);

void write_frame(FILE* f, uint8_t* frame, size_t frame_size);

#endif // _AVI_H_