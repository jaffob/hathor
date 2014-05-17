// the file where shit tends to go down

#include "stdafx.h"
#include "Backend.h"
#include <cstdlib.h>

#define NUM_RESULTS 8

// Given a song title and artist, finds a link to a Youtube vid.
YOUTUBEVID * FindAndChooseVidFromSong(LPTSTR title, LPTSTR artist, SONGDATA data)
{
	/*
	 * Algorithm:
	 * - combine title and artist into one string
	 * - search for that string
	 * - find vid with a duration closest to duration of song (prioritize HD)
	 */

	return NULL;
}

YOUTUBEVID ** VidResultsForSongSearch(LPTSTR title, LPTSTR artist, unsigned int num_results)
{
	LPTSTR searchPage = GetWebPage(SongNameToSearchURL(title, artist));
	return NULL;
}

LPTSTR GetWebPage(LPTSTR url)
{
	LPTSTR command = (LPTSTR)malloc(256 * sizeof(TCHAR));
	wcscpy(command, L"curl ");
	wcscat(command, url);
	wcscat(command, L" > TEMP.dat");

	char * actual_command = (char *)malloc(256 * sizeof(char));
	wcstombs_s()
	system()
	return NULL;
}

LPTSTR SongNameToSearchURL(LPTSTR title, LPTSTR artist)
{
	LPTSTR result = (LPTSTR)malloc(256 * sizeof(TCHAR)); 
	wcscpy(result, L"https://www.youtube.com/results?search_query=");

	LPTSTR search = (LPTSTR)malloc(256 * sizeof(TCHAR));
	wcscpy(search, artist);
	wcscat(search, L"+");
	wcscat(search, title);
	
	for (unsigned int i = 0; i < wcslen(search); i++)
	{
		if (search[i] == ' ')
			search[i] = '+';
	}

	wcscat(result, search);

	LPTSTR escsearch = (LPTSTR)malloc(256 * sizeof(TCHAR));
	DWORD searchsize = 256 * sizeof(TCHAR);
	UrlEscape(result, escsearch, &searchsize, 0);

	return escsearch;
}
