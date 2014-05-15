// the file where shit tends to go down

#include "Backend.h"

#define NUM_RESULTS 8

// Given a song title and artist, finds a link to a Youtube vid.
YOUTUBEVID GetYouTubeVidToSong(LPTSTR title, LPTSTR artist, SONGDATA data)
{
	/*
	 * Algorithm:
	 * - combine title and artist into one string
	 * - search for that string
	 * - find vid with a duration closest to duration of song (prioritize HD)
	 */

	LPTSTR searchPage = GetWebPage(SongNameToSearchURL(title, artist));
}

LPTSTR GetWebPage(LPTSTR url)
{

}

LPTSTR SongNameToSearchURL(LPTSTR title, LPTSTR artist)
{
	LPTSTR result = L"https://www.youtube.com/results?search_query=";

	LPTSTR search = (LPTSTR)malloc(256 * sizeof(TCHAR));
	wcscpy(search, artist);
	wcscat(search, L"+");
	wcscat(search, title);
	
	LPTSTR escsearch = (LPTSTR)malloc(256 * sizeof(TCHAR));
	DWORD searchsize = 256 * sizeof(TCHAR);
	UrlEscape(search, escsearch, &searchsize, )
}
