// the file where shit tends to go down

#include "stdafx.h"
#include "Backend.h"

#define NUM_RESULTS 8
#define HD_VALUE 5

// Given a song title and artist, finds a link to a Youtube vid.
YOUTUBEVID * FindAndChooseVidForSong(LPTSTR title, LPTSTR artist, SONGDATA * data)
{
	/*
	 * Algorithm:
	 * - combine title and artist into one string
	 * - search for that string
	 * - find vid with a duration closest to duration of song (prioritize HD)
	 */

	// Get video results for the search.
	unsigned int num_results = NUM_RESULTS;
	YOUTUBEVID ** results = VidResultsForSongSearch(title, artist, &num_results);

	// Find the best result.
	long best = MAXDWORD;
	unsigned int best_i = 0;
	for (unsigned int i = 0; i < num_results; i++)
	{
		// Score determined by duration and HD.
		long score = abs(data->duration - results[i]->duration) - (results[i]->hd ? 5 : 0);
		if (score < best)
		{
			best = score;
			best_i = i;
		}
	}

	return results[best_i];
}

YOUTUBEVID ** VidResultsForSongSearch(LPTSTR title, LPTSTR artist, unsigned int * num_results)
{
	YOUTUBEVID ** results = (YOUTUBEVID **)malloc((*num_results + 1) + sizeof(YOUTUBEVID *));
	LPTSTR searchPage = GetWebPage(SongNameToSearchURL(title, artist));

	char * location;
	unsigned int i;

	// Find results.
	for (i = 0; i < *num_results; i++)
	{
		YOUTUBEVID * result = (YOUTUBEVID *)malloc(sizeof(YOUTUBEVID));

		// Find URL.
		location = strstr(searchPage, "/watch?v=");
		if (!location)
			break;

		result->url = SpanToChar(location, "\"");

		// Filter out playlists.
		if (strstr(result->url, "&amp;"))
		{
			do
			{
				location = location + sizeof(TCHAR);
				location = strstr(location, "/watch?v=");
			} while (strstr(SpanToChar(location, "\""), "&amp;"));

			continue;
		}

		// Find duration and convert to seconds.
		location = strstr(location, "video-time");
		location = location + 12 * sizeof(TCHAR);
		LPTSTR duration_string = SpanToChar(location, "<"); 

		int hours = atoi(strtok(duration_string, ":"));
		int minutes = atoi(strtok(NULL, ":"));
		LPTSTR secs = strtok(NULL, ":");
		if (secs)
			result->duration = hours * 3600 + minutes * 60 + atoi(secs);
		else
			result->duration = hours * 60 + minutes;

		// Find title.
		location = strstr(location, result->url);
		location = strstr(location, ">");
		location = location + sizeof(TCHAR);
		result->title = SpanToChar(location, "<");

		// HD?
		LPTSTR hd_string = strstr(location, ">HD</span>");
		if (!hd_string)
		{
			result->hd = false;
		}
		else
		{
			hd_string = strstr(hd_string, "/watch?v=");
			LPTSTR comp_string = strstr(location, "/watch?v=");
			result->hd = hd_string == comp_string;
		}

		results[i] = result;
	}

	*num_results = i;
	results[i] = NULL;
	return results;
}

LPTSTR GetWebPage(LPTSTR url)
{
	LPTSTR command = (LPTSTR)malloc(256 * sizeof(TCHAR));
	strcpy(command, "curl ");
	strcat(command, url);
	strcat(command, " > TEMP.dat");

	//size_t num_converted = strlen(command);
	//char * actual_command = (char *)malloc(256 * sizeof(char));
	//strtombs_s(&num_converted, actual_command, 256, command, strlen(command));

	system(command);
	return FileToString("TEMP.dat");
}

LPTSTR SongNameToSearchURL(LPTSTR title, LPTSTR artist)
{
	LPTSTR result = (LPTSTR)malloc(256 * sizeof(TCHAR)); 
	strcpy(result, "https://www.youtube.com/results?search_query=");

	LPTSTR search = (LPTSTR)malloc(256 * sizeof(TCHAR));
	strcpy(search, artist);
	strcat(search, "+");
	strcat(search, title);
	
	for (unsigned int i = 0; i < strlen(search); i++)
	{
		if (search[i] == ' ')
			search[i] = '+';
	}

	strcat(result, search);

	LPTSTR escsearch = (LPTSTR)malloc(256 * sizeof(TCHAR));
	DWORD searchsize = 256 * sizeof(TCHAR);
	UrlEscape(result, escsearch, &searchsize, 0);

	return escsearch;
}

char * FileToString(char * file)
{
	// Open file.
	FILE * fp = fopen(file, "rb");
	if (!fp) return NULL;

	// Get size of file.
	fseek(fp, 0, SEEK_END);
	long filesize = ftell(fp);
	rewind(fp);

	// Allocate memory for the file.
	char * output = (char *)malloc(sizeof(char)* filesize);
	if (!output) return NULL;

	// Read file into output.
	fread(output, 1, filesize, fp);
	fclose(fp);

	return output;
}

LPTSTR SpanToChar(LPTSTR start, LPTSTR charString)
{
	size_t str_length = strcspn(start, charString);
	LPTSTR output = (LPTSTR)malloc((str_length + 1) * sizeof(TCHAR));
	strncpy(output, start, str_length);
	output[str_length] = '\0';
	return output;
}