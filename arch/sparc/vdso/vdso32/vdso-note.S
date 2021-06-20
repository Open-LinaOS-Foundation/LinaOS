/*
 * This supplies .note.* sections to go into the PT_NOTE inside the vDSO
 * text. Here we can supply some information useful to userland.
 */

#include <linaos/uts.h>
#include <linaos/version.h>
#include <linaos/elfnote.h>

ELFNOTE_START(LinaOS, 0, "a")
	.long	LINUX_VERSION_CODE
ELFNOTE_END
