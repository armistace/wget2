// Just a test for static linking.
// We call one function from each object file in libwget.
// Unresolved references should come up on linking.

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <string.h> // CygWin strlcpy() declaration
#include <libwget.h>

int main(void)
{
	char *empty = (char *)"";

	wget_info_printf("%d\n", wget_base64_is_string("")); // base64.c
	wget_buffer_alloc(0); // buffer.c
	wget_buffer_printf((wget_buffer_t *)1, "%s", ""); // buffer_printf.c
	strlcpy((char *)"", "", 0); // strlcpy.c
	wget_css_parse_buffer((const char *)1, NULL, NULL, NULL); // css.c
	wget_decompress_close(NULL); // decompressor.c
	wget_hashmap_create(0, 0, NULL, NULL); // hashmap.c
	wget_fdgetline(&empty, (size_t *)1, 0); // io.c
	wget_iri_parse("", NULL); // iri.c
	wget_list_free((wget_list_t **)1); // list.c
	wget_debug_write("", 0); // log.c
	wget_logger_set_file(NULL, ""); // logger.c
	wget_tcp_set_connect_timeout(NULL, 0); // net.c
	wget_netrc_deinit(NULL); // netrc.c
	wget_strdup(""); // mem.c
//	wget_popenf("r", "%s", ""); // pipe.c
//	wget_bsprintf(NULL, NULL, "%s", ""); // printf.c
	wget_ssl_set_config_int(0, 0); // ssl_[gnutls].c
	wget_stringmap_create(0); // stringmap.c
	if (wget_strcmp("", "")) {}; // utils.c
	wget_vector_set_destructor(NULL, NULL); // vector.c
	wget_malloc(1); // xalloc.c
	wget_xml_parse_buffer("", NULL, NULL, 0); // xml.c
}
