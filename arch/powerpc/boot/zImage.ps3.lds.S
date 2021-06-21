/* SPDX-License-Identifier: GPL-2.0 */
OUTPUT_ARCH(powerpc:common)
ENTRY(_zimage_start)
EXTERN(_zimage_start)
SECTIONS
{
  _vmlinaos_start =  .;
  .kernel:vmlinaos.bin : { *(.kernel:vmlinaos.bin) }
  _vmlinaos_end =  .;

  . = ALIGN(4096);
  _dtb_start = .;
  .kernel:dtb : { *(.kernel:dtb) }
  _dtb_end = .;

  . = ALIGN(4096);
  _initrd_start =  .;
  .kernel:initrd : { *(.kernel:initrd) }
  _initrd_end =  .;

  _start = .;
  .text      :
  {
    *(.text)
    *(.fixup)
  }
  _etext = .;
  . = ALIGN(4096);
  .data    :
  {
    *(.rodata*)
    *(.data*)
    *(.sdata*)
    __got2_start = .;
    *(.got2)
    __got2_end = .;
  }

  . = ALIGN(4096);
  _edata  =  .;

  . = ALIGN(4096);
  __bss_start = .;
  .bss       :
  {
   *(.sbss)
   *(.bss)
  }
  . = ALIGN(4096);
  _end = . ;
}
