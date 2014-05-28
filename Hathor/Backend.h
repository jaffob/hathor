#include <cstdlib>
#include <cstdio>

typedef struct _SONGDATA
{
	LPTSTR title;
	LPTSTR artist;
	LPTSTR album;
	long year;
	long duration;
} SONGDATA;

typedef struct _YOUTUBEVID
{
	LPTSTR url;
	LPTSTR title;
	long duration;
	bool hd;
} YOUTUBEVID;

YOUTUBEVID * FindAndChooseVidForSong(LPTSTR title, LPTSTR artist, SONGDATA * data);
YOUTUBEVID ** VidResultsForSongSearch(LPTSTR title, LPTSTR artist, unsigned int * num_results);
LPTSTR GetWebPage(LPTSTR url);
LPTSTR SongNameToSearchURL(LPTSTR title, LPTSTR artist);
char * FileToString(char * file);
LPTSTR SpanToChar(LPTSTR start, LPTSTR charString);