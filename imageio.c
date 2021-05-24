/*
 *  module  : imageio.c
 *  version : 1.2
 *  date    : 04/27/21
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joy.h"

#define MAXBUF		256

void read2EOL(FILE *fd)
{
    int c;

    while ((c = getc(fd)) != '\n')
	if (c == EOF)
	    return;
}

int __read_ascii_data(FILE *fd, char *r, char *g, char *b, int len)
{
    int i;

    for (i = 0; i < len; i++) {
	if (fscanf(fd, "%d", (int *)&r[i]) == 0)
	    return -1;
	if (fscanf(fd, "%d", (int *)&g[i]) == 0)
	    return -1;
	if (fscanf(fd, "%d", (int *)&b[i]) == 0)
	    return -1;
    }
    return (1);
}

int __read_raw_data(FILE *fd, char *r, char *g, char *b, int len)
{
    int i;
    char *buf, *ptr;

    ptr = buf = (char *)GC_malloc_atomic(3 * len);
    fread(buf, 1, 3 * len, fd);
    for (i = 0; i < len; i++) {
	r[i] = *ptr++;
	g[i] = *ptr++;
	b[i] = *ptr++;
    }
    return 1;
}

int __read_ppm(FILE *fd, char **r, char **g, char **b, int *w, int *h,
               int ascii)
{
    char tmpstr[MAXBUF];
    int maxc;

    /* header */
    fscanf(fd, "%s", tmpstr);
    while (tmpstr[0] == '#') {
	read2EOL(fd);
	fscanf(fd, "%s", tmpstr);
    }
    sscanf(tmpstr, "%d", w);
    fscanf(fd, "%s", tmpstr);
    while (tmpstr[0] == '#') {
	read2EOL(fd);
	fscanf(fd, "%s", tmpstr);
    }
    sscanf(tmpstr, "%d", h);
    fscanf(fd, "%s", tmpstr);
    while (tmpstr[0] == '#') {
	read2EOL(fd);
	fscanf(fd, "%s", tmpstr);
    }
    sscanf(tmpstr, "%d", &maxc);
    read2EOL(fd);

    /* bound checks */
    if (*w < 0)
	return -1;
    if (*h < 0)
	return -1;
    if (*w * *h > 1 << 24)
	return -1;
    if ((*r = GC_malloc_atomic(*w * *h)) == NULL)
	return -1;
    if ((*g = GC_malloc_atomic(*w * *h)) == NULL)
	return -1;
    if ((*b = GC_malloc_atomic(*w * *h)) == NULL)
	return -1;
    if (ascii) {
	if (__read_ascii_data(fd, *r, *g, *b, *w * *h) < 0)
	    return -1;
    } else {
	if (__read_raw_data(fd, *r, *g, *b, *w * *h) < 0)
	    return -1;
    }
    return 1;
}

int __read_bmp(FILE *fd, char **r, char **g, char **b, int *w, int *h)
{
    int i, k, len, filesize, offset, tmp, idx;
    int size, compression, sizeimage, xpels, ypels, clrused, cltimp;
    short planes, bitcount;
    char *color, *data, *ptr;

    fread(&filesize, sizeof(int), 1, fd);
    fread(&tmp, sizeof(int), 1, fd);
    fread(&offset, sizeof(int), 1, fd);
    fread(&size, sizeof(int), 1, fd);
    fread(w, sizeof(int), 1, fd);
    fread(h, sizeof(int), 1, fd);
    fread(&planes, sizeof(short), 1, fd);
    fread(&bitcount, sizeof(short), 1, fd);
    fread(&compression, sizeof(int), 1, fd);
    fread(&sizeimage, sizeof(int), 1, fd);
    fread(&xpels, sizeof(int), 1, fd);
    fread(&ypels, sizeof(int), 1, fd);
    fread(&clrused, sizeof(int), 1, fd);
    fread(&cltimp, sizeof(int), 1, fd);

    if ((*r = GC_malloc_atomic(*w * *h)) == NULL)
	return -1;
    if ((*g = GC_malloc_atomic(*w * *h)) == NULL)
	return -1;
    if ((*b = GC_malloc_atomic(*w * *h)) == NULL)
	return -1;

    if (bitcount == 24) {
	len = 3 * *w;
	while (len % 4)
	    len++;
	data = (char *)GC_malloc_atomic(len);
	for (k = *h - 1; k >= 0; k--) {
	    fread(data, 1, len, fd);
	    ptr = data;
	    for (i = 0; i < *w; i++) {
		(*b)[k * *w + i] = *ptr++;
		(*g)[k * *w + i] = *ptr++;
		(*r)[k * *w + i] = *ptr++;
	    }
	}
    }

    if (bitcount == 8) {
	if (clrused == 0)
	    clrused = 256;
	color = (char *)GC_malloc_atomic(4 * clrused);
	fread(color, 4, clrused, fd);
	len = *w;
	while (len % 4)
	    len++;
	data = (char *)GC_malloc_atomic(len * *h);
	fread(data, 1, len * *h, fd);
	for (k = *h - 1; k >= 0; k--)
	    for (i = 0; i < *w; i++) {
		(*r)[*w * k + i] = color[4 * data[(*h - k - 1) * len + i] + 2];
		(*g)[*w * k + i] = color[4 * data[(*h - k - 1) * len + i] + 1];
		(*b)[*w * k + i] = color[4 * data[(*h - k - 1) * len + i]];
	    }
    }

    if (bitcount == 4) {
	if (clrused == 0)
	    clrused = 16;
	color = (char *)GC_malloc_atomic(4 * clrused);
	fread(color, 4, clrused, fd);
	len = *w / 2;
	if (*w % 2)
	    len++;
	while (len % 4)
	    len++;
	data = (char *)GC_malloc_atomic(*h * len);
	fread(data, 1, *h * len, fd);
	for (k = *h - 1; k >= 0; k--)
	    for (i = 0; i < *w; i++) {
		idx = (data[(*h - k - 1) * len + i / 2] & 0xF0) / 16;
		if (i % 2)
		    idx = (data[(*h - k - 1) * len + i / 2] & 0x0F);
		(*r)[*w * k + i] = color[4 * idx + 2];
		(*g)[*w * k + i] = color[4 * idx + 1];
		(*b)[*w * k + i] = color[4 * idx];
	    }
    }
    return 1;
}

int __read_image(FILE *fd, char **r, char **g, char **b, int *w, int *h)
{
    char type[3];

    /* check for ppm or bmp */
    fread(type, 1, 2, fd);
    type[2] = '\0';

    if (strstr("P3", type) != NULL) {
	if (__read_ppm(fd, r, g, b, w, h, 1) < 0)
	    return -1;
    } else if (strstr("P6", type) != NULL) {
	if (__read_ppm(fd, r, g, b, w, h, 0) < 0)
	    return -1;
    } else if (strstr("BM", type) != NULL) {
	if (__read_bmp(fd, r, g, b, w, h) < 0)
	    return -1;
    } else
	return -1;
    return 1;
}

int __write_raw_data(FILE *fd, char *r, char *g, char *b, int len)
{
    int i;
    char *buf, *ptr;

    ptr = buf = (char *)GC_malloc_atomic(3 * len);
    for (i = 0; i < len; i++) {
	*ptr++ = r[i];
	*ptr++ = g[i];
	*ptr++ = b[i];
    }
    fwrite(buf, 1, 3 * len, fd);
    return 1;
}

int __write_ppm_image(FILE *fd, char *r, char *g, char *b, int w, int h)
{
    if (fprintf(fd, "P6\n") == 0)
	return -1;
    if (fprintf(fd, "%d %d\n", w, h) == 0)
	return -1;
    if (fprintf(fd, "255\n") == 0)
	return -1;
    if (__write_raw_data(fd, r, g, b, w * h) < 0)
	return -1;
    return 1;
}

int __write_bmp_image(FILE *fd, char *r, char *g, char *b, int w, int h)
{
    char type[] = {'B', 'M'};
    int i, k, len;
    short s;
    char *buf, *ptr;

    /* file header */
    fwrite(type, 2, 1, fd); /* BM                */
    i = 54 + w * h * 3;
    fwrite(&i, 4, 1, fd); /* file size           */
    i = 0;
    fwrite(&i, 4, 1, fd); /* reserved = 0        */
    i = 54;
    fwrite(&i, 4, 1, fd); /* headers length      */

    /* info header */
    i = 40;
    fwrite(&i, 4, 1, fd); /* header info length  */
    fwrite(&w, 4, 1, fd); /* image width         */
    fwrite(&h, 4, 1, fd); /* image height        */
    s = 1;
    fwrite(&s, 2, 1, fd); /* planes              */
    s = 24;
    fwrite(&s, 2, 1, fd); /* depth               */
    i = 0;
    fwrite(&i, 4, 1, fd); /* compression         */
    i = w * h * 3;
    fwrite(&i, 4, 1, fd); /* data length         */
    i = 0;
    fwrite(&i, 4, 1, fd); /* xPels               */
    i = 0;
    fwrite(&i, 4, 1, fd); /* yPels               */
    i = 0;
    fwrite(&i, 4, 1, fd); /* color used          */
    i = 0;
    fwrite(&i, 4, 1, fd); /* color important     */

    /* Dummy bytes */
    len = 3 * w;
    while (len % 4) {
	fwrite(&i, 1, 1, fd);
	len++;
    }

    buf = (char *)GC_malloc_atomic(len);
    for (k = h - 1; k >= 0; k--) {
	ptr = buf;
	for (i = 0; i < w; i++) {
	    *ptr++ = b[k * w + i];
	    *ptr++ = g[k * w + i];
	    *ptr++ = r[k * w + i];
	}
	fwrite(buf, 1, len, fd);
    }
    return 1;
}

int __write_image(FILE *fd, char *r, char *g, char *b, int w, int h, int type)
{
    if (type == J_PPM) {
	if (__write_ppm_image(fd, r, g, b, w, h) < 0)
	    return -1;
    } else if (type == J_BMP) {
	if (__write_bmp_image(fd, r, g, b, w, h) < 0)
	    return -1;
    }
    return 1;
}
