/*         ______   ___    ___
 *        /\  _  \ /\_ \  /\_ \
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \_/__/
 *
 *      Inline functions (MSVC style 386 asm).
 *
 *      By Stefan Schimanski.
 *
 *      See readme.txt for copyright information.
 */


#if (!defined ALLEGRO_MSVC) || (!defined ALLEGRO_I386)
   #error bad include
#endif


#pragma warning (disable: 4035)



/* _default_ds:
 *  Return a copy of the current %ds selector.
 */
INLINE _AL_DLL int _default_ds(void)
{
   _asm {
      mov eax, 0
      mov ax, ds
   }
}

END_OF_INLINE(_default_ds);



/* bmp_write_line:
 *  Bank switch function.
 */
INLINE _AL_DLL unsigned long bmp_write_line(BITMAP *bmp, int line)
{ 
   _asm { 
      mov edx, bmp
      mov ecx, [edx]BITMAP.write_bank
      mov eax, line
      call ecx
   }
}

END_OF_INLINE(bmp_write_line);



/* bmp_read_line:
 *  Bank switch function.
 */
INLINE _AL_DLL unsigned long bmp_read_line(BITMAP *bmp, int line)
{
   _asm {
      mov edx, bmp
      mov ecx, [edx]BITMAP.read_bank
      mov eax, line
      call ecx
   }
}

END_OF_INLINE(bmp_read_line);



/* bmp_unwrite_line:
 *  Terminate bank switch function.
 */
INLINE _AL_DLL void bmp_unwrite_line(BITMAP *bmp)
{
   _asm {
      mov edx, bmp
      mov ecx, [edx]BITMAP.vtable
      mov ecx, [ecx]GFX_VTABLE.unwrite_bank
      call ecx
   }
}

END_OF_INLINE(bmp_unwrite_line);



/* fadd:
 *  Fixed point (16.16) addition.
 */
INLINE _AL_DLL fixed fadd(fixed x, fixed y)
{
   _asm {
      mov eax, x
      add eax, y
      jno Out1
      mov eax, [allegro_errno]
      mov dword ptr [eax], ERANGE
      mov eax, 0x7FFFFFFF
      cmp y, 0
      jg Out1
      neg eax
   Out1:
   }
}

END_OF_INLINE(fadd);



/* fsub:
 *  Fixed point (16.16) subtraction.
 */
INLINE _AL_DLL fixed fsub(fixed x, fixed y)
{
   _asm {
      mov eax, x
      sub eax, y
      jno Out1
      mov eax, [allegro_errno]
      mov dword ptr [eax], ERANGE
      mov eax, 0x7FFFFFFF
      cmp y, 0
      jl Out1
      neg eax
   Out1:
   }
}

END_OF_INLINE(fsub);



/* fmul:
 *  Fixed point (16.16) multiplication.
 */
INLINE _AL_DLL fixed fmul(fixed x, fixed y)
{
   _asm {
      mov eax, x
      imul y
      shrd eax, edx, 16
      sar edx, 15
      jz Out2
      cmp edx, -1
      jz Out2
      mov eax, [allegro_errno]
      mov dword ptr [eax], ERANGE
      mov eax, 0x7FFFFFFF
      cmp x, 0
      jge Out1
      neg eax
   Out1:
      cmp y, 0
      jge Out2
      neg eax
   Out2:
   }
}

END_OF_INLINE(fmul);



/* fdiv:
 *  Fixed point (16.16) division.
 */
INLINE _AL_DLL fixed fdiv(fixed x, fixed y)
{
   _asm {
      mov ecx, y
      xor ebx, ebx
      mov eax, x
      or eax, eax
      jns Out1
      neg eax
      inc ebx
   Out1:
      or ecx, ecx
      jns Out2
      neg ecx
      inc ebx
   Out2:
      mov edx, eax
      shr edx, 0x10
      shl eax, 0x10
      cmp edx, ecx
      jae Out3
      div ecx
      or eax, eax
      jns Out4
   Out3:
      mov eax, [allegro_errno]
      mov dword ptr [eax], ERANGE
      mov eax, 0x7FFFFFFF
   Out4:
      test ebx, 1
      je Out5
      neg eax
   Out5:
   }
}

END_OF_INLINE(fdiv);



#pragma warning (default: 4035)

