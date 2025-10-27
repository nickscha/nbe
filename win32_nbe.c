/* win32_nbe.c - v0.1 - public domain data structures - nickscha 2025

A C89 standard compliant, nostdlib (no C Standard Library) No Bloat Editor (NBE).

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#include "nbe.h" /* The platform independant text editor part */

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

static nbe_context *g_ctx = 0; /* global pointer to our context for simplicity */

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_SIZE:
    {
        if (g_ctx)
        {
            RECT rc;
            GetClientRect(hwnd, &rc);
            u32 new_width = (u32)(rc.right - rc.left);
            u32 new_height = (u32)(rc.bottom - rc.top);

            if (new_width == 0 || new_height == 0)
                break;

            /* Free previous framebuffer if any */
            if (g_ctx->framebuffer)
            {
                VirtualFree(g_ctx->framebuffer, 0, MEM_RELEASE);
                g_ctx->framebuffer = 0;
            }

            /* Allocate new framebuffer */
            g_ctx->framebuffer = (u32 *)VirtualAlloc(
                0,
                new_width * new_height * sizeof(u32),
                MEM_COMMIT | MEM_RESERVE,
                PAGE_READWRITE);

            if (g_ctx->framebuffer)
            {
                g_ctx->framebuffer_width = new_width;
                g_ctx->framebuffer_height = new_height;
                g_ctx->framebuffer_changed = 1;
            }
        }
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

#define FB_WIDTH 640
#define FB_HEIGHT 480
#define TB_CAPACITY 4096

static u8 textbuffer[TB_CAPACITY];

/* ############################################################################
 * # C-Like main function
 * ############################################################################
 *
 * The "mainCRTStartup" will read the command line arguments parsed and call
 * this function.
 */
int start(int argc, char **argv)
{
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WinProc;
    wc.hInstance = GetModuleHandleA(0);
    wc.lpszClassName = "NBE";
    RegisterClassA(&wc);

    (void)argc;
    (void)argv;

    HWND hwnd = CreateWindowExA(
        0, wc.lpszClassName, wc.lpszClassName,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        FB_WIDTH, FB_HEIGHT,
        0, 0, wc.hInstance, 0);

    MSG msg;
    HDC hdc = GetDC(hwnd);

    nbe_context ctx = {0};
    ctx.framebuffer_changed = 1;
    ctx.framebuffer = (u32 *)VirtualAlloc(0, FB_WIDTH * FB_HEIGHT * sizeof(u32), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    ctx.framebuffer_width = FB_WIDTH;
    ctx.framebuffer_height = FB_HEIGHT;
    ctx.textbuffer = textbuffer;
    ctx.textbuffer_capacity = TB_CAPACITY;
    ctx.textbuffer_length = 0;
    ctx.font_scale = 2;

    g_ctx = &ctx;

    nbe_textbuffer_append(
        &ctx,
        "This is a test of a very long line that has a very long text which exceeds 80 characters\n"
        "And this is the second row\n"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab\n");

    for (;;)
    {
        while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return 0;

            if (msg.message == WM_CHAR)
            {
                char c = (char)msg.wParam;

                /* Add char */
                if (c >= 32 && c < 127 && ctx.textbuffer_length < ctx.textbuffer_capacity)
                {
                    ctx.textbuffer[ctx.textbuffer_length++] = (u8)c;
                    ctx.cursor_textbuffer_index++;
                    ctx.framebuffer_changed = 1;
                }
            }
            else if (msg.message == WM_KEYDOWN)
            {
                switch (msg.wParam)
                {
                case VK_UP:
                    if (ctx.cursor_scroll_y > 0)
                    {
                        ctx.cursor_scroll_y--;
                        ctx.framebuffer_changed = 1;
                    }
                    break;
                case VK_DOWN:
                    ctx.cursor_scroll_y++;
                    ctx.framebuffer_changed = 1;
                    break;
                case VK_LEFT:
                    if (ctx.cursor_scroll_x > 0)
                    {
                        ctx.cursor_scroll_x--;
                        ctx.framebuffer_changed = 1;
                    }
                    break;
                case VK_RIGHT:
                    ctx.cursor_scroll_x++;
                    ctx.framebuffer_changed = 1;
                    break;
                case VK_ESCAPE:
                    return 0;
                case VK_TAB:
                    if (ctx.textbuffer_length + 1 < ctx.textbuffer_capacity)
                    {
                        ctx.textbuffer[ctx.textbuffer_length++] = ' ';
                        ctx.textbuffer[ctx.textbuffer_length++] = ' ';
                        ctx.cursor_textbuffer_index += 2;
                        ctx.framebuffer_changed = 1;
                    }
                    break;

                case VK_BACK:
                    /* Remove */
                    if (ctx.textbuffer_length > 0)
                    {
                        ctx.textbuffer_length--;
                        ctx.framebuffer_changed = 1;
                        ctx.cursor_textbuffer_index--;
                        ctx.framebuffer_changed = 1;
                    }
                    break;

                case VK_RETURN:
                    /* New Line */
                    if (ctx.textbuffer_length < ctx.textbuffer_capacity)
                    {
                        ctx.textbuffer[ctx.textbuffer_length++] = '\n';
                        ctx.cursor_textbuffer_index++;
                        ctx.framebuffer_changed = 1;
                    }
                    break;

                case VK_OEM_PLUS:
                case VK_ADD:
                    if (GetKeyState(VK_CONTROL) & 0x8000 && ((ctx.font_scale + 1) * NBE_FONT_SIZE) <= ctx.framebuffer_height)
                    {
                        ctx.font_scale++;
                        ctx.framebuffer_changed = 1;
                    }
                    break;

                case VK_OEM_MINUS:
                case VK_SUBTRACT:
                    if (GetKeyState(VK_CONTROL) & 0x8000 && ctx.font_scale > 1)
                    {
                        ctx.font_scale--;
                        ctx.framebuffer_changed = 1;
                    }
                    break;
                }
            }

            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        nbe_draw(&ctx);

        BITMAPINFO fb_bmi;
        fb_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        fb_bmi.bmiHeader.biWidth = (long)ctx.framebuffer_width;
        fb_bmi.bmiHeader.biHeight = (long)(-(int)ctx.framebuffer_height); /* top-down */
        fb_bmi.bmiHeader.biPlanes = 1;
        fb_bmi.bmiHeader.biBitCount = 32;
        fb_bmi.bmiHeader.biCompression = BI_RGB;

        StretchDIBits(
            hdc,
            0, 0, (int)ctx.framebuffer_width, (int)ctx.framebuffer_height,
            0, 0, (int)ctx.framebuffer_width, (int)ctx.framebuffer_height,
            ctx.framebuffer,
            &fb_bmi,
            DIB_RGB_COLORS,
            SRCCOPY);

        Sleep(1);
    }

    return 0;
}

/* ############################################################################
 * # Command line parsing
 * ############################################################################
 *
 * Basic (non-quoted) command line parser
 * Converts "program.exe arg1 arg2" -> argc=3, argv={"program.exe","arg1","arg2",NULL}
 * In-place: modifies the command line buffer.
 */
static int win32_parse_command_line(char *cmdline, char ***argv_out)
{
    static char *argv_local[64]; /* up to 63 args */
    int argc = 0;

    while (*cmdline)
    {
        /* skip whitespace */
        while (*cmdline == ' ' || *cmdline == '\t')
        {
            cmdline++;
        }

        if (!*cmdline)
        {
            break;
        }

        if (argc < 63)
        {
            argv_local[argc++] = cmdline;
        }

        /* parse token (basic, no quote handling) */
        while (*cmdline && *cmdline != ' ' && *cmdline != '\t')
        {
            cmdline++;
        }

        if (*cmdline)
        {
            *cmdline++ = '\0';
        }
    }

    argv_local[argc] = (char *)0;
    *argv_out = argv_local;

    return argc;
}

/* ############################################################################
 * # Main entry point
 * ############################################################################
 */
#ifdef __clang__
#elif __GNUC__
__attribute((externally_visible))
#endif
#ifdef __i686__
__attribute((force_align_arg_pointer))
#endif
int nostdlib_main(void)
{
    char *cmdline = GetCommandLineA();

    char **argv;
    int argc = win32_parse_command_line(cmdline, &argv);

    return start(argc, argv);
}

/*
   ------------------------------------------------------------------------------
   This software is available under 2 licenses -- choose whichever you prefer.
   ------------------------------------------------------------------------------
   ALTERNATIVE A - MIT License
   Copyright (c) 2025 nickscha
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   ------------------------------------------------------------------------------
   ALTERNATIVE B - Public Domain (www.unlicense.org)
   This is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
   software, either in source code form or as a compiled binary, for any purpose,
   commercial or non-commercial, and by any means.
   In jurisdictions that recognize copyright laws, the author or authors of this
   software dedicate any and all copyright interest in the software to the public
   domain. We make this dedication for the benefit of the public at large and to
   the detriment of our heirs and successors. We intend this dedication to be an
   overt act of relinquishment in perpetuity of all present and future rights to
   this software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   ------------------------------------------------------------------------------
*/