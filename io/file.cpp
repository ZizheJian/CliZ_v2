#ifndef __FILE_CPP__
#define __FILE_CPP__

#include "io.hpp2"

namespace cliz
{
	void open_file(FILE *&f,const char *fname,const char *type,bool reuse_check=true)
	{
		if ((f!=NULL) && (reuse_check))
		{
			printf("Warning: Reusing file pointer.\n");
			return;
		}
		f=fopen(fname,type);
		if (f==NULL)
		{
			printf("Error: File \"%s\" open failed\n",fname);
			exit(0);
		}
	}

	void close_file(FILE *&f)
	{
		if (f!=NULL)
		{
			fclose(f);
			f=NULL;
		}
		else
			printf("Warning: Closing an invalid file pointer.\n");
	}
}

#endif