#include "stdafx.h"

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

YOUTUBEVID GetYouTubeVidToSong(LPTSTR title, LPTSTR artist, SONGDATA data);
LPTSTR GetWebPage(LPTSTR url);
LPTSTR SongNameToSearchURL(LPTSTR title, LPTSTR artist);
