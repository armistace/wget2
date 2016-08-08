/*
 * Copyright(c) 2013 Tim Ruehsen
 * Copyright(c) 2015-2016 Free Software Foundation, Inc.
 *
 * This file is part of libwget.
 *
 * Libwget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Libwget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libwget.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Testing Wget
 *
 * Changelog
 * 15.07.2013  Tim Ruehsen  created
 *
 */

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h> // exit()
#include "libtest.h"

int main(void)
{
	wget_test_url_t urls[]={
		{	.name = "/start.html",
			.code = "200 Dontcare",
			.body =
				"<meta name= \"roBoTS\" content=\"noFolLow ,  foo, bar \">" \
				"<a href=\"/bombshell.html\">Don't follow me!</a>",
			.headers = {
				"Content-Type: text/html",
			}
		},
		{	.name = "/mid.html",
			.code = "200 Dontcare",
			.body =
				"<meta name=\"rObOts\" content=\" foo  ,  NOfOllow ,  bar \">" \
				"<a href=\"/bombshell.html\">Don't follow me!</a>",
			.headers = {
				"Content-Type: text/html",
			}
		},
		{	.name = "/end.html",
			.code = "200 Dontcare",
			.body =
				"<meta name=\"RoBotS\" content=\"foo,BAr,   nofOLLOw    \">" \
				"<a href=\"/bombshell.html\">Don't follow me!</a>",
			.headers = {
				"Content-Type: text/html",
			}
		},
		{	.name = "/solo.html",
			.code = "200 Dontcare",
			.body =
				"<meta name=\"robots\" content=\"nofollow\">" \
				"<a href=\"/bombshell.html\">Don't follow me!</a>",
			.headers = {
				"Content-Type: text/html",
			}
		},
		{	.name = "/bombshell.html",
			.code = "200 Dontcare",
			.body = "What ever",
			.headers = {
				"Content-Type: text/html",
			}
		},
	};

	// functions won't come back if an error occurs
	wget_test_start_server(
		WGET_TEST_RESPONSE_URLS, &urls, countof(urls),
		0);

	// test-meta-robots
	wget_test(
		WGET_TEST_OPTIONS, "-r -e",
		WGET_TEST_REQUEST_URLS, "start.html", "mid.html", "end.html", "solo.html", NULL,
		WGET_TEST_EXPECTED_ERROR_CODE, 0,
		WGET_TEST_EXPECTED_FILES, &(wget_test_file_t []) {
			{ urls[0].name + 1, urls[0].body },
			{ urls[1].name + 1, urls[1].body },
			{ urls[2].name + 1, urls[2].body },
			{ urls[3].name + 1, urls[3].body },
			{	NULL } },
		0);

	exit(0);
}
