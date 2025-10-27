/* nbe.h - v0.1 - public domain data structures - nickscha 2025

A C89 standard compliant, nostdlib (no C Standard Library) No Bloat Editor (NBE).

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#ifndef NBE_H
#define NBE_H

/* #############################################################################
 * # COMPILER SETTINGS
 * #############################################################################
 */
/* Check if using C99 or later (inline is supported) */
#if __STDC_VERSION__ >= 199901L
#define NBE_INLINE inline
#elif defined(__GNUC__) || defined(__clang__)
#define NBE_INLINE __inline__
#elif defined(_MSC_VER)
#define NBE_INLINE __inline
#else
#define NBE_INLINE
#endif

#define NBE_API static

typedef unsigned int u32;
typedef unsigned char u8;

#define NBE_COLOR_RGB(r, g, b) ((u32)(((r) << 16) | ((g) << 8) | (b)))
#define NBE_COLOR_DARKEN(color, percent)          \
  (NBE_COLOR_RGB(                                 \
      (((color >> 16) & 0xFF) * (percent) / 100), \
      (((color >> 8) & 0xFF) * (percent) / 100),  \
      ((color & 0xFF) * (percent) / 100)))
#define NBE_U32_MAX(a, b) ((u32)((a) > (b) ? (a) : (b)))
#define NBE_U32_MIN(a, b) ((u32)((a) < (b) ? (a) : (b)))
#define NBE_STATIC_ASSERT(c, m) typedef char nbe_assert_##m[(c) ? 1 : -1]

NBE_STATIC_ASSERT(sizeof(u8) == 1, u8_size_must_be_1);
NBE_STATIC_ASSERT(sizeof(u32) == 4, u32_size_must_be_4);

#define NBE_FONT_SIZE 8
static u8 nbe_font[96][NBE_FONT_SIZE] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* */
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, /* */
    {0x36, 0x36, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00}, /* */
    {0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00}, /* */
    {0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00}, /* */
    {0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00}, /* */
    {0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00}, /* */
    {0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}, /* */
    {0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00}, /* */
    {0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00}, /* */
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}, /* */
    {0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00}, /* */
    {0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06, 0x00}, /* */
    {0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, /* */
    {0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00}, /* */
    {0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00}, /* */
    {0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00}, /* */
    {0x0C, 0x0E, 0x0F, 0x0C, 0x0C, 0x0C, 0x3F, 0x00}, /* */
    {0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00}, /* */
    {0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00}, /* */
    {0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00}, /* */
    {0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00}, /* */
    {0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00}, /* */
    {0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00}, /* */
    {0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00}, /* */
    {0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00}, /* */
    {0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x00}, /* */
    {0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x06, 0x00}, /* */
    {0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00}, /* */
    {0x00, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x00, 0x00}, /* */
    {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00}, /* */
    {0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00}, /* */
    {0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00}, /* */
    {0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}, /* */
    {0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00}, /* */
    {0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00}, /* */
    {0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00}, /* */
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00}, /* */
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00}, /* */
    {0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00}, /* */
    {0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00}, /* */
    {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, /* */
    {0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00}, /* */
    {0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00}, /* */
    {0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00}, /* */
    {0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00}, /* */
    {0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00}, /* */
    {0x1E, 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x00}, /* */
    {0x3F, 0x66, 0x66, 0x3F, 0x06, 0x06, 0x0F, 0x00}, /* */
    {0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00}, /* */
    {0x3F, 0x66, 0x66, 0x3F, 0x36, 0x66, 0x67, 0x00}, /* */
    {0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00}, /* */
    {0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, /* */
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00}, /* */
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, /* */
    {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00}, /* */
    {0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00}, /* */
    {0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00}, /* */
    {0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00}, /* */
    {0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00}, /* */
    {0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00}, /* */
    {0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00}, /* */
    {0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00}, /* */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, /* */
    {0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, /* */
    {0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00}, /* */
    {0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00}, /* */
    {0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00}, /* */
    {0x38, 0x30, 0x30, 0x3E, 0x33, 0x33, 0x6E, 0x00}, /* */
    {0x00, 0x00, 0x1E, 0x33, 0x3F, 0x03, 0x1E, 0x00}, /* */
    {0x1C, 0x36, 0x06, 0x0F, 0x06, 0x06, 0x0F, 0x00}, /* */
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F}, /* */
    {0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00}, /* */
    {0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, /* */
    {0x30, 0x00, 0x38, 0x30, 0x30, 0x33, 0x33, 0x1E}, /* */
    {0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00}, /* */
    {0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, /* */
    {0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00}, /* */
    {0x00, 0x00, 0x1B, 0x37, 0x33, 0x33, 0x33, 0x00}, /* */
    {0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00}, /* */
    {0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F}, /* */
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78}, /* */
    {0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00}, /* */
    {0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00}, /* */
    {0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00}, /* */
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00}, /* */
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, /* */
    {0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00}, /* */
    {0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00}, /* */
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F}, /* */
    {0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00}, /* */
    {0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00}, /* */
    {0x0C, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x0C, 0x00}, /* */
    {0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00}, /* */
    {0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* */
    {0x1C, 0x36, 0x63, 0x63, 0x7F, 0x00, 0x00, 0x00}, /* */
};

typedef struct nbe_context
{
  int framebuffer_changed; /* Did the dimensions of the framebuffer changed */
  u32 *framebuffer;
  u32 framebuffer_width;
  u32 framebuffer_height;

  u8 *textbuffer;          /* The text loaded */
  u32 textbuffer_length;   /* The current length of the text */
  u32 textbuffer_capacity; /* The maximum size of the text */

  u32 font_scale;

  u32 cursor_textbuffer_index_current; /* To which textbuffer position is the current cursor pointing */

  u32 line_number_width;

} nbe_context;

NBE_API NBE_INLINE void nbe_cursor_position(nbe_context *ctx, u32 *x_out, u32 *y_out)
{
  u32 i;
  u32 x = 0;
  u32 y = 0;

  for (i = 0; i < ctx->cursor_textbuffer_index_current && i < ctx->textbuffer_length; ++i)
  {
    u8 c = ctx->textbuffer[i];

    if (c == '\r')
    {
      continue;
    }

    if (c == '\n')
    {
      x = 0;
      ++y;
    }
    else
    {
      ++x;
    }
  }

  *x_out = x;
  *y_out = y;
}

NBE_API NBE_INLINE void nbe_textbuffer_event_char_add(nbe_context *ctx, char c)
{
  u32 idx = ctx->cursor_textbuffer_index_current;
  u32 i;

  if (ctx->textbuffer_length >= ctx->textbuffer_capacity - 1)
  {
    return;
  }

  if ((c >= 32 && c < 127) || c == '\n')
  {
    /* Shift characters to the right to make space */
    for (i = ctx->textbuffer_length; i > idx; --i)
    {
      ctx->textbuffer[i] = ctx->textbuffer[i - 1];
    }

    /* Insert the new character */
    ctx->textbuffer[idx] = (u8)c;
    ctx->textbuffer_length++;
    ctx->cursor_textbuffer_index_current++;
    ctx->framebuffer_changed = 1;
  }
}

NBE_API NBE_INLINE void nbe_textbuffer_event_char_remove(nbe_context *ctx)
{
  u32 idx = ctx->cursor_textbuffer_index_current;
  u32 i;

  if (ctx->textbuffer_length == 0 || idx == 0)
  {
    return;
  }

  /* Move cursor back one position */
  idx--;

  /* Shift remaining characters left to remove the character */
  for (i = idx; i < ctx->textbuffer_length - 1; ++i)
  {
    ctx->textbuffer[i] = ctx->textbuffer[i + 1];
  }

  ctx->textbuffer_length--;
  ctx->cursor_textbuffer_index_current = idx;

  ctx->framebuffer_changed = 1;
}

NBE_API NBE_INLINE void nbe_textbuffer_event_char_delete(nbe_context *ctx)
{
  u32 idx = ctx->cursor_textbuffer_index_current;
  u32 i;

  /* Nothing to delete if cursor is at the end or buffer is empty */
  if (idx >= ctx->textbuffer_length || ctx->textbuffer_length == 0)
  {
    return;
  }

  /* Shift characters left to overwrite the deleted character */
  for (i = idx; i < ctx->textbuffer_length - 1; ++i)
  {
    ctx->textbuffer[i] = ctx->textbuffer[i + 1];
  }

  ctx->textbuffer_length--;
  ctx->framebuffer_changed = 1;
}

NBE_API NBE_INLINE void nbe_textbuffer_event_indent(nbe_context *ctx)
{
  nbe_textbuffer_event_char_add(ctx, ' ');
  nbe_textbuffer_event_char_add(ctx, ' ');
}

NBE_API NBE_INLINE void nbe_textbuffer_event_font_scale_increase(nbe_context *ctx)
{
  if ((ctx->font_scale + 1) * NBE_FONT_SIZE <= ctx->framebuffer_height)
  {
    ctx->font_scale++;
    ctx->framebuffer_changed = 1;
  }
}

NBE_API NBE_INLINE void nbe_textbuffer_event_font_scale_decrease(nbe_context *ctx)
{
  if (ctx->font_scale > 1)
  {
    ctx->font_scale--;
    ctx->framebuffer_changed = 1;
  }
}

NBE_API NBE_INLINE void nbe_textbuffer_event_toggle_line_numbers(nbe_context *ctx)
{
  ctx->line_number_width = ctx->line_number_width == 5 ? 0 : 5;
  ctx->framebuffer_changed = 1;
}

NBE_API NBE_INLINE void nbe_textbuffer_event_line_new(nbe_context *ctx)
{
  nbe_textbuffer_event_char_add(ctx, '\n');
}

NBE_API NBE_INLINE void nbe_textbuffer_event_cursor_move_left(nbe_context *ctx)
{
  if (ctx->cursor_textbuffer_index_current > 0)
  {
    ctx->cursor_textbuffer_index_current--;
    ctx->framebuffer_changed = 1;
  }
}

NBE_API NBE_INLINE void nbe_textbuffer_event_cursor_move_right(nbe_context *ctx)
{
  if (ctx->cursor_textbuffer_index_current < ctx->textbuffer_length)
  {
    ctx->cursor_textbuffer_index_current++;
    ctx->framebuffer_changed = 1;
  }
}

NBE_API NBE_INLINE void nbe_textbuffer_append(nbe_context *ctx, char *src)
{
  u32 i = 0;

  while (src[i] && ctx->textbuffer_length < (ctx->textbuffer_capacity - 1))
  {
    ctx->textbuffer[ctx->textbuffer_length++] = (u8)src[i++];
  }

  ctx->textbuffer[ctx->textbuffer_length] = 0; /* always keep null-terminated */
  ctx->cursor_textbuffer_index_current = ctx->textbuffer_length;
}

NBE_API NBE_INLINE void nbe_framebuffer_clear(nbe_context *ctx, u32 color)
{
  u32 *p = ctx->framebuffer;
  u32 *end = p + (ctx->framebuffer_width * ctx->framebuffer_height);

  while (p < end)
  {
    *p++ = color;
  }
}

NBE_API NBE_INLINE void nbe_framebuffer_draw_pixel(nbe_context *ctx, u32 x, u32 y, u32 color)
{
  if (x < ctx->framebuffer_width && y < ctx->framebuffer_height)
  {
    ctx->framebuffer[y * ctx->framebuffer_width + x] = color;
  }
}

NBE_API NBE_INLINE void nbe_framebuffer_draw_character(nbe_context *ctx, u32 x, u32 y, u8 c, u32 color_fg, u32 color_bg)
{
  u32 uc = c;
  u8 *glyph;
  u32 i, j;

  if (uc < 32 || uc > 127)
  {
    return;
  }

  glyph = nbe_font[uc - 32];

  for (i = 0; i < NBE_FONT_SIZE; ++i)
  {
    u8 row = glyph[i];

    for (j = 0; j < NBE_FONT_SIZE; ++j)
    {

      u32 xx, yy;

      for (yy = 0; yy < ctx->font_scale; ++yy)
      {
        for (xx = 0; xx < ctx->font_scale; ++xx)
        {
          nbe_framebuffer_draw_pixel(
              ctx,
              x + j * ctx->font_scale + xx,
              y + i * ctx->font_scale + yy,
              row & (1 << j) ? color_fg : color_bg);
        }
      }
    }
  }
}

NBE_API NBE_INLINE void nbe_framebuffer_draw_text(nbe_context *ctx, u32 color)
{
  u32 font_size = (NBE_FONT_SIZE * ctx->font_scale);

  /* How many cells (i.e. characters) fit horizontally / vertically */
  u32 cell_columns = (ctx->framebuffer_width / font_size);
  u32 cell_rows = ctx->framebuffer_height / font_size;

  /* Pointer to the text starting at the current cursor position */
  u8 *text = ctx->textbuffer;

  /* remaining characters in the buffer */
  u32 remaining = ctx->textbuffer_length;

  u32 i = 0;
  u32 col_start_index = ctx->line_number_width; /* Test */
  u32 col_index = col_start_index;
  u32 row_index = 0;

  /* Get the current cursor position */
  u32 cursor_col_index, cursor_row_index;
  nbe_cursor_position(ctx, &cursor_col_index, &cursor_row_index);
  cursor_col_index += ctx->line_number_width;

  /* Iterate until we consumed all remaining chars OR until the visible rows are filled */
  while (i < remaining && row_index < cell_rows)
  {
    u8 c = text[i++];

    /* ignore CR from CRLF pairs */
    if (c == '\r')
    {
      continue;
    }

    /* Newline: move to start of next row */
    if (c == '\n')
    {
      /* Draw cursor background if cursor is at this position */
      if (col_index == cursor_col_index && row_index == cursor_row_index)
      {
        u32 yy, xx;
        for (yy = 0; yy < font_size; ++yy)
        {
          for (xx = 0; xx < font_size; ++xx)
          {
            nbe_framebuffer_draw_pixel(
                ctx,
                col_index * font_size + xx,
                row_index * font_size + yy,
                NBE_COLOR_DARKEN(color, 60));
          }
        }
      }

      col_index = ctx->line_number_width;
      ++row_index;
      continue;
    }

    /* Stop drawing if we fill the row area */
    if (col_index >= cell_columns)
    {
      /* ignore overflow chars until next newline */
      while (i < remaining && text[i] != '\n')
      {
        ++i;
      }
      continue;
    }

    /* Draw the visible character */
    nbe_framebuffer_draw_character(
        ctx,
        col_index * font_size,
        row_index * font_size,
        c,
        color,
        (col_index == cursor_col_index && row_index == cursor_row_index)
            ? NBE_COLOR_DARKEN(color, 60)
            : NBE_COLOR_RGB(40, 40, 40));

    ++col_index;
  }

  /* Draw cursor background if it's at end of line / end of buffer */
  if (ctx->cursor_textbuffer_index_current == ctx->textbuffer_length)
  {
    u32 x = cursor_col_index * font_size;
    u32 y = cursor_row_index * font_size;
    u32 yy, xx;

    /* fill a full cell with cursor color */
    for (yy = 0; yy < font_size; ++yy)
    {
      for (xx = 0; xx < font_size; ++xx)
      {
        nbe_framebuffer_draw_pixel(ctx, x + xx, y + yy, NBE_COLOR_DARKEN(color, 60));
      }
    }
  }
}

NBE_API NBE_INLINE void nbe_framebuffer_draw_line_numbers(nbe_context *ctx, u32 color)
{
  u32 font_size = (NBE_FONT_SIZE * ctx->font_scale);
  u32 cell_rows = ctx->framebuffer_height / font_size;

  u32 x, y;

  if (ctx->line_number_width < 2)
  {
    return;
  }

  for (y = 0; y < cell_rows; ++y)
  {
    for (x = 0; x < ctx->line_number_width - 1; ++x)
    {
      nbe_framebuffer_draw_character(ctx, x * font_size, y * font_size, '0', color, NBE_COLOR_RGB(40, 40, 40));
    }
  }
}

NBE_API NBE_INLINE void nbe_draw(nbe_context *ctx)
{
  if (ctx->framebuffer_changed)
  {
    /* Clear Framebuffer */
    nbe_framebuffer_clear(ctx, NBE_COLOR_RGB(40, 40, 40));

    ctx->framebuffer_changed = 0;
  }

  nbe_framebuffer_draw_line_numbers(ctx, NBE_COLOR_RGB(252, 186, 3));
  nbe_framebuffer_draw_text(ctx, NBE_COLOR_RGB(252, 186, 3));
}

#endif /* NBE_H */

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
