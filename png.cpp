#ifndef __PNG_CPP__
#define __PNG_CPP__

#include "globalvar.hpp"

namespace png{
	#define SVPNG_PUT(u)\
		fputc(u,fp)
	#define SVPNG_U8A(ua,l)\
		for (i=0;i<l;i++)\
			SVPNG_PUT((ua)[i]);
	#define SVPNG_U32(u)\
		SVPNG_PUT((u)>>24);\
		SVPNG_PUT(((u)>>16)&255);\
		SVPNG_PUT(((u)>>8)&255);\
		SVPNG_PUT((u)&255);
	#define SVPNG_U8C(u)\
	{\
		SVPNG_PUT(u);\
		c^=(u);\
		c=(c>>4)^t[c&15];\
		c=(c>>4)^t[c&15];\
	}
	#define SVPNG_U8AC(ua,l)\
		for (i=0;i<l;i++)\
			SVPNG_U8C((ua)[i])
	#define SVPNG_U16LC(u)\
		SVPNG_U8C((u)&255);\
		SVPNG_U8C(((u)>>8)&255);
	#define SVPNG_U32C(u)\
		SVPNG_U8C((u)>>24);\
		SVPNG_U8C(((u)>>16)&255);\
		SVPNG_U8C(((u)>>8)&255);\
		SVPNG_U8C((u)&255);
	#define SVPNG_U8ADLER(u)\
	{\
		SVPNG_U8C(u);\
		a=(a+(u))%65521;\
		b=(b+a)%65521;\
	}
	#define SVPNG_BEGIN(s,l)\
		SVPNG_U32(l);\
		c=~0U;\
		SVPNG_U8AC(s,4);
	#define SVPNG_END()\
		SVPNG_U32(~c)

	void output_png(FILE *fp,unsigned int w,unsigned int h,unsigned char *img)
	{
		unsigned t[]={0,0x1db71064,0x3b6e20c8,0x26d930ac,0x76dc4190,0x6b6b51f4,0x4db26158,0x5005713c,
			 0xedb88320,0xf00f9344,0xd6d6a3e8,0xcb61b38c,0x9b64c2b0,0x86d3d2d4,0xa00ae278,0xbdbdf21c};
		unsigned int a=1;
		unsigned int b=0;
		unsigned int p=w*3+1;
		unsigned int c,i;
	
		SVPNG_U8A("\x89PNG\r\n\32\n",8);
		SVPNG_BEGIN("IHDR",13);
		SVPNG_U32C(w);
		SVPNG_U32C(h);
		SVPNG_U8C(8);
		SVPNG_U8C(2);
		SVPNG_U8AC("\0\0\0",3);
		SVPNG_END();
		SVPNG_BEGIN("IDAT",2+h*(5+p)+4);
		SVPNG_U8AC("\x78\1",2);
		for (unsigned int y=0;y<h;y++)
		{
			SVPNG_U8C(y==h-1);
			SVPNG_U16LC(p);
			SVPNG_U16LC(~p);
			SVPNG_U8ADLER(0);
			for (unsigned int x=0;x<p-1;x++)
				SVPNG_U8ADLER(img[y*(p-1)+x]);
		}
		SVPNG_U32C((b<<16)|a);
		SVPNG_END();
		SVPNG_BEGIN("IEND",0);
		SVPNG_END();
	}
}

#endif