// SPDX-License-Identifier: GPL-2.0
/*
 * decompress.c
 *
 * Detect the decompression method based on magic number
 */

#include <linaos/decompress/generic.h>

#include <linaos/decompress/bunzip2.h>
#include <linaos/decompress/unlzma.h>
#include <linaos/decompress/unxz.h>
#include <linaos/decompress/inflate.h>
#include <linaos/decompress/unlzo.h>
#include <linaos/decompress/unlz4.h>
#include <linaos/decompress/unzstd.h>

#include <linaos/types.h>
#include <linaos/string.h>
#include <linaos/init.h>
#include <linaos/printk.h>

#ifndef CONFIG_DECOMPRESS_GZIP
# define gunzip NULL
#endif
#ifndef CONFIG_DECOMPRESS_BZIP2
# define bunzip2 NULL
#endif
#ifndef CONFIG_DECOMPRESS_LZMA
# define unlzma NULL
#endif
#ifndef CONFIG_DECOMPRESS_XZ
# define unxz NULL
#endif
#ifndef CONFIG_DECOMPRESS_LZO
# define unlzo NULL
#endif
#ifndef CONFIG_DECOMPRESS_LZ4
# define unlz4 NULL
#endif
#ifndef CONFIG_DECOMPRESS_ZSTD
# define unzstd NULL
#endif

struct compress_format {
	unsigned char magic[2];
	const char *name;
	decompress_fn decompressor;
};

static const struct compress_format compressed_formats[] __initconst = {
	{ {0x1f, 0x8b}, "gzip", gunzip },
	{ {0x1f, 0x9e}, "gzip", gunzip },
	{ {0x42, 0x5a}, "bzip2", bunzip2 },
	{ {0x5d, 0x00}, "lzma", unlzma },
	{ {0xfd, 0x37}, "xz", unxz },
	{ {0x89, 0x4c}, "lzo", unlzo },
	{ {0x02, 0x21}, "lz4", unlz4 },
	{ {0x28, 0xb5}, "zstd", unzstd },
	{ {0, 0}, NULL, NULL }
};

decompress_fn __init decompress_method(const unsigned char *inbuf, long len,
				const char **name)
{
	const struct compress_format *cf;

	if (len < 2) {
		if (name)
			*name = NULL;
		return NULL;	/* Need at least this much... */
	}

	pr_debug("Compressed data magic: %#.2x %#.2x\n", inbuf[0], inbuf[1]);

	for (cf = compressed_formats; cf->name; cf++) {
		if (!memcmp(inbuf, cf->magic, 2))
			break;

	}
	if (name)
		*name = cf->name;
	return cf->decompressor;
}
