DZCOMM

RSXNT-specific information.

See readme.txt for a more general overview.



=====================================
============ RSXNT notes ============
=====================================

   Who knows !!!



===========================================
============ Required software ============
===========================================

   - Allegro DLL, produced by MSVC.
   - djgpp compiler (djdev*.zip, gcc*b.zip, and bnu*b.zip).
   - RSXNTDJ package (rsxdj*.zip).
   - GNU make (mak*b.zip).
   - Optional: rm (fil*b.zip). Used by the clean and uninstall targets.
   - Optional: sed (sed*b.zip). Used by "make depend" and "fixdll".
   - Optional: sort (txt*b.zip). Used by "fixdll". Use Unix sort, not DOS!

   At the moment the only way to get an Allegro DLL is by using MSVC to 
   compile it yourself. Eventually we are planning to distribute precompiled 
   versions of this, but that doesn't make sense while the code is changing 
   so rapidly. The DLL should be in your allegro/lib/msvc/ directory.

   All of the other software can be downloaded from your nearest SimTel 
   mirror site, in the /pub/simtelnet/gnu/djgpp/ directory, or you can use 
   the zip picker on http://www.delorie.com/djgpp/. See the djgpp readme.1st 
   file for information about how to install djgpp, and the RSXNT help files 
   for RSXNT installation instructions.



============================================
============ Installing dzcomm =============
============================================

   Type "cd dzcomm", followed by "fixrsxnt.bat", followed by "make". Then go 
   do something interesting while everything compiles. When it finishes 
   compiling, type "make install" to set the library up ready for use.

   If you also want to install a debugging version of the library (highly 
   recommended), now type "make install DEBUGMODE=1". Case is important, so 
   it must be DEBUGMODE, not debugmode!

   If you also want to install a profiling version of the library, now type 
   "make install PROFILEMODE=1".

   If your copy of Allegro doesn't include the makefile.dep dependency files 
   (unlikely, unless you have run "make veryclean" at some point), you can 
   regenerate them by running "make depend".

   If your copy of Allegro doesn't include rsxdll.h (unlikely, unless you 
   have run "make veryclean" at some point), you can regenerate it by 
   running "fixdll.bat".



=======================================
============ Using dzcomm =============
=======================================

   All the dzcomm functions, variables, and data structures are defined in 
   dzcomm.h. You should include this in your programs, and link with either 
   the optimised library liball_i.a, the debugging library libald_i.a, or the 
   profiling library libalp_i.a.

   You will need to distribute the appropriate DLL along with your program: 
   these can be found in the allegro/lib/msvc/ directory.

