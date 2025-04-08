#include <stdio.h>

void WriteVersion()
{
#ifndef __WIN32__
	FILE* fp = fopen("VERSION.txt", "w");

	if (fp)
	{
		fprintf(fp, "__GAME_VERSION__: %s\n", __GAME_VERSION__);
		fprintf(fp, "%s@%s:%s\n", "dmFuYXRvcg==", __HOSTNAME__, __PWD__);
		fclose(fp);
	}
#endif
}
//martysama0134's a288e6779da68f768431f9975e780da3
