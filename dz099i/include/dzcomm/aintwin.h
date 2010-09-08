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
 *      Some definitions for internal use by the Windows library code.
 *
 *      By Stefan Schimanski.
 *
 *      See readme.txt for copyright information.
 */


#ifndef AINTWIN_H
#define AINTWIN_H

#ifndef ALLEGRO_H
   #error must include allegro.h first
#endif

#ifndef ALLEGRO_WINDOWS
   #error bad include
#endif

#ifdef __cplusplus
   extern "C" {
#endif


#include "winalleg.h"



/*******************************************/
/***************** general *****************/
/*******************************************/
AL_VAR(HINSTANCE, allegro_inst);
AL_VAR(HWND, allegro_wnd);
AL_VAR(HANDLE, allegro_thread);
AL_VAR(DWORD, wnd_back_color);
AL_VAR(BOOL, wnd_paint_back);

AL_FUNC(int, init_directx_window, (void));
AL_FUNC(void, exit_directx_window, (void));
AL_FUNC(int, wnd_call_proc, (void (*proc)(void)));
AL_FUNC(int, get_dx_ver, (void));
AL_FUNC(void, set_sync_timer_freq, (int freq));
AL_FUNC(void, handle_window_size, (int x, int y, int w, int h));
AL_FUNC(void, restore_window_style, (void));

/* focus switch routines */
AL_VAR(BOOL, app_foreground);

AL_FUNC(void, sys_directx_display_switch_init, (void));
AL_FUNC(void, sys_directx_display_switch_exit, (void));
AL_FUNC(int, sys_directx_set_display_switch_mode, (int mode));
AL_FUNC(int, sys_directx_set_display_switch_callback, (int dir, void (*cb)(void)));
AL_FUNC(void, sys_directx_remove_display_switch_callback, (void (*cb)(void)));

AL_FUNC(void, sys_switch_in, (void));
AL_FUNC(void, gfx_switch_in, (void));

AL_FUNC(void, sys_switch_out, (void));
AL_FUNC(void, gfx_switch_out, (void));
AL_FUNC(void, thread_switch_out, (void));
AL_FUNC(void, midi_switch_out, (void));
AL_FUNC(void, timer_switch_out, (void));

AL_FUNC(void, sys_directx_switch_out_callback, (void));
AL_FUNC(void, sys_directx_switch_in_callback, (void));



/*******************************************/
/************** mouse routines *************/
/*******************************************/
AL_FUNC(int, mouse_dinput_acquire, (void));
AL_FUNC(void, mouse_dinput_unacquire, (void));
AL_FUNC(void, wnd_acquire_mouse, (void));



/*******************************************/
/************* thread routines *************/
/*******************************************/
AL_FUNC(void, _enter_critical, (void));
AL_FUNC(void, _exit_critical, (void));
AL_FUNC(void, win_init_thread, (void));
AL_FUNC(void, win_exit_thread, (void));



/******************************************/
/************* sound routines *************/
/******************************************/
AL_FUNC(_DRIVER_INFO *, _get_digi_driver_list, (void));
AL_FUNC(_DRIVER_INFO *, _get_midi_driver_list, (void));



/*******************************************/
/************* error handling **************/
/*******************************************/
AL_FUNC(char* , win_err_str, (long err));
AL_FUNC(void, thread_safe_trace, (char *msg, ...));

#ifdef DEBUGMODE
   #define _TRACE                 thread_safe_trace
#else
   #define _TRACE                 1 ? (void) 0 : thread_safe_trace
#endif




#ifdef __cplusplus
   }
#endif

#endif          /* ifndef AINTWIN_H */

