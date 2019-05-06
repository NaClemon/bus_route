// Generated by gmmproc 2.49.5 -- DO NOT MODIFY!
#ifndef _PANGOMM_LAYOUT_H
#define _PANGOMM_LAYOUT_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* $Id: layout.hg,v 1.9 2006/06/08 20:39:39 murrayc Exp $ */

/* layout.h
 *
 * Copyright(C) 1998-1999 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or(at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include <glibmm/object.h>
#include <glibmm/slisthandle.h>
#include <pangomm/font.h>
#include <pangomm/fontdescription.h>
#include <pangomm/context.h>
#include <pangomm/attrlist.h>
#include <pangomm/tabarray.h>
#include <pangomm/layoutline.h>
#include <pangomm/layoutiter.h>
#include <pango/pango-layout.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using PangoLayout = struct _PangoLayout;
using PangoLayoutClass = struct _PangoLayoutClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Pango
{ class Layout_Class; } // namespace Pango
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Pango
{


/** @addtogroup pangommEnums pangomm Enums and Flags */

/** 
 *  @var Alignment ALIGN_LEFT
 * Put all available space on the right.
 * 
 *  @var Alignment ALIGN_CENTER
 * Center the line within the available space.
 * 
 *  @var Alignment ALIGN_RIGHT
 * Put all available space on the left.
 * 
 *  @enum Alignment
 * 
 * A Pango::Alignment describes how to align the lines of a Pango::Layout within the
 * available space. If the Pango::Layout is set to justify
 * using Pango::Layout::set_justify(), this only has effect for partial lines.
 *
 * @ingroup pangommEnums
 */
enum Alignment
{
  ALIGN_LEFT,
  ALIGN_CENTER,
  ALIGN_RIGHT
};

} // namespace Pango

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value<Pango::Alignment> : public Glib::Value_Enum<Pango::Alignment>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace Pango
{

/** 
 *  @var WrapMode WRAP_WORD
 * Wrap lines at word boundaries.
 * 
 *  @var WrapMode WRAP_CHAR
 * Wrap lines at character boundaries.
 * 
 *  @var WrapMode WRAP_WORD_CHAR
 * Wrap lines at word boundaries, but fall back to character boundaries if there is not
 * enough space for a full word.
 * 
 *  @enum WrapMode
 * 
 * A Pango::WrapMode describes how to wrap the lines of a Pango::Layout to the desired width.
 *
 * @ingroup pangommEnums
 */
enum WrapMode
{
  WRAP_WORD,
  WRAP_CHAR,
  WRAP_WORD_CHAR
};

} // namespace Pango

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value<Pango::WrapMode> : public Glib::Value_Enum<Pango::WrapMode>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace Pango
{

/** 
 *  @var EllipsizeMode ELLIPSIZE_NONE
 * No ellipsization.
 * 
 *  @var EllipsizeMode ELLIPSIZE_START
 * Omit characters at the start of the text.
 * 
 *  @var EllipsizeMode ELLIPSIZE_MIDDLE
 * Omit characters in the middle of the text.
 * 
 *  @var EllipsizeMode ELLIPSIZE_END
 * Omit characters at the end of the text.
 * 
 *  @enum EllipsizeMode
 * 
 * The Pango::EllipsizeMode type describes what sort of (if any)
 * ellipsization should be applied to a line of text. In
 * the ellipsization process characters are removed from the
 * text in order to make it fit to a given width and replaced
 * with an ellipsis.
 *
 * @ingroup pangommEnums
 */
enum EllipsizeMode
{
  ELLIPSIZE_NONE,
  ELLIPSIZE_START,
  ELLIPSIZE_MIDDLE,
  ELLIPSIZE_END
};

} // namespace Pango

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value<Pango::EllipsizeMode> : public Glib::Value_Enum<Pango::EllipsizeMode>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace Pango
{


/** A Pango::Layout represents an entire paragraph of text.
 * It is initialized with a Pango::Context, UTF-8 string and set of attributes for that string.
 * Once that is done, the set of formatted lines can be extracted from the object,
 * the layout can be rendered, and conversion between logical character positions
 * within the layout's text, and the physical position of the resulting glyphs can be made.
 */

class Layout : public Glib::Object
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  using CppObjectType = Layout;
  using CppClassType = Layout_Class;
  using BaseObjectType = PangoLayout;
  using BaseClassType = PangoLayoutClass;

  // noncopyable
  Layout(const Layout&) = delete;
  Layout& operator=(const Layout&) = delete;

private:  friend class Layout_Class;
  static CppClassType layout_class_;

protected:
  explicit Layout(const Glib::ConstructParams& construct_params);
  explicit Layout(PangoLayout* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  Layout(Layout&& src) noexcept;
  Layout& operator=(Layout&& src) noexcept;

  ~Layout() noexcept override;

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  PangoLayout*       gobj()       { return reinterpret_cast<PangoLayout*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const PangoLayout* gobj() const { return reinterpret_cast<PangoLayout*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  PangoLayout* gobj_copy();

private:

  
protected:
  explicit Layout(const Glib::RefPtr<Context>& context);

public:
  
  static Glib::RefPtr<Layout> create(const Glib::RefPtr<Context>& context);


 /** Creates a layout object set up to match the current transformation
  * and target surface of the Cairo context.  This layout can then be
  * used for text measurement with functions like
  * get_size() or drawing with methods like show_in_cairo_contet(). 
  * If you change the transformation or target surface for @a context, 
  * you need to call update_from_cairo_context()
  *
  * This is the most convenient way to use Cairo with Pango. 
  * However it is slightly inefficient since it creates a separate
  * Pango Context object for each layout. This might matter in an
  * application that is laying out large amounts of text.
  * 
  * @param context A Cairo context.
  * @result The newly created Pango Layout.
  */
  static Glib::RefPtr<Layout> create(const Cairo::RefPtr<Cairo::Context>& context);

  /** Updates the private Pango Context of a Pango Layout created with
   * create(const Cairo::RefPtr<Cairo::Context>&) to match the current transformation
   * and target surface of a Cairo Context.
   *
   * @param context A Cairo context.
   */
  void update_from_cairo_context(const Cairo::RefPtr<Cairo::Context>& context);


  /** Does a deep copy-by-value of the @a src layout. The attribute list,
   * tab array, and text from the original layout are all copied by
   * value.
   * 
   * @return The newly allocated Pango::Layout,
   * with a reference count of one, which should be freed
   * with Glib::object_unref().
   */
  Glib::RefPtr<Layout> copy();
  
  /** Retrieves the Pango::Context used for this layout.
   * 
   * @return The Pango::Context for the layout.
   * This does not have an additional refcount added, so if you want to
   * keep a copy of this around, you must reference it yourself.
   */
  Glib::RefPtr<Context> get_context() const;
  
  /** Sets the text attributes for a layout object.
   * References @a attrs, so the caller can unref its reference.
   * 
   * @param attrs A Pango::AttrList, can be <tt>nullptr</tt>.
   */
  void set_attributes(AttrList& attrs);
  
  /** Gets the attribute list for the layout, if any.
   * 
   * @return A Pango::AttrList.
   */
  AttrList get_attributes() const;

  /** Set the text of the layout.
   * @param text The text for the layout.
   */
  void set_text(const Glib::ustring& text);

  
  /** Gets the text in the layout. The returned text should not
   * be freed or modified.
   * 
   * @return The text in the @a layout.
   */
  Glib::ustring get_text() const;

  
  /** Returns the number of Unicode characters in the
   * the text of @a layout.
   * 
   * @newin{1,30}
   * 
   * @return The number of Unicode characters
   * in the text of @a layout.
   */
  int get_character_count() const;

  /** Sets the layout text and attribute list from marked-up text (see markup format).
   * Replaces the current text and attribute list.
   * @param markup Some marked-up text.
   */
  void set_markup(const Glib::ustring& markup);

  /** Sets the layout text and attribute list from marked-up text (see markup format).
   * Replaces the current text and attribute list.
   *
   * If @a accel_marker is nonzero, the given character will mark the character following
   * it as an accelerator. For example, the accel marker might be an ampersand or
   * underscore. All characters marked as an accelerator will receive a
   * Pango::UNDERLINE_LOW attribute, and the first character so marked will be returned
   * in @a accel_char. Two @a accel_marker characters following each other produce a
   * single literal @a accel_marker character.
   * @param markup Some marked-up text.
   * @param accel_marker Marker for accelerators in the text.
   * @param accel_char Return location for any located accelerators.
   */
  void set_markup(const Glib::ustring& markup, gunichar accel_marker, gunichar& accel_char);

  
  /** Set the default font description for the layout. If no font
   * description is set on the layout, the font description from
   * the layout's context is used.
   * 
   * @param desc The new pango font description.
   */
  void set_font_description(const FontDescription& desc);
  void unset_font_description();

  
  /** Gets the font description for the layout, if any.
   * 
   * @newin{1,8}
   * 
   * @return A pointer to the layout's font
   * description, or <tt>nullptr</tt> if the font description from the layout's
   * context is inherited. This value is owned by the layout and must
   * not be modified or freed.
   */
  FontDescription get_font_description() const;

  
  /** Sets the width to which the lines of the Pango::Layout should wrap or
   * ellipsized.  The default value is -1: no width set.
   * 
   * @param width The desired width in Pango units, or -1 to indicate that no
   * wrapping or ellipsization should be performed.
   */
  void set_width(int width);
  
  /** Gets the width to which the lines of the Pango::Layout should wrap.
   * 
   * @return The width in Pango units, or -1 if no width set.
   */
  int get_width() const;
  
  /** Sets the height to which the Pango::Layout should be ellipsized at.  There
   * are two different behaviors, based on whether @a height is positive or
   * negative.
   * 
   * If @a height is positive, it will be the maximum height of the layout.  Only
   * lines would be shown that would fit, and if there is any text omitted,
   * an ellipsis added.  At least one line is included in each paragraph regardless
   * of how small the height value is.  A value of zero will render exactly one
   * line for the entire layout.
   * 
   * If @a height is negative, it will be the (negative of) maximum number of lines per
   * paragraph.  That is, the total number of lines shown may well be more than
   * this value if the layout contains multiple paragraphs of text.
   * The default value of -1 means that first line of each paragraph is ellipsized.
   * This behvaior may be changed in the future to act per layout instead of per
   * paragraph.  File a bug against pango at http://bugzilla.gnome.org/ if your
   * code relies on this behavior.
   * 
   * Height setting only has effect if a positive width is set on
   *  @a layout and ellipsization mode of @a layout is not Pango::ELLIPSIZE_NONE.
   * The behavior is undefined if a height other than -1 is set and
   * ellipsization mode is set to Pango::ELLIPSIZE_NONE, and may change in the
   * future.
   * 
   * @newin{1,20}
   * 
   * @param height The desired height of the layout in Pango units if positive,
   * or desired number of lines if negative.
   */
  void set_height(int height);
  
  /** Gets the height of layout used for ellipsization.  See
   * set_height() for details.
   * 
   * @newin{1,20}
   * 
   * @return The height, in Pango units if positive, or
   * number of lines if negative.
   */
  int get_height() const;
  
  /** Sets the wrap mode; the wrap mode only has effect if a width
   * is set on the layout with set_width().
   * To turn off wrapping, set the width to -1.
   * 
   * @param wrap The wrap mode.
   */
  void set_wrap(WrapMode wrap);
  
  /** Gets the wrap mode for the layout.
   * 
   * Use is_wrapped() to query whether any paragraphs
   * were actually wrapped.
   * 
   * @return Active wrap mode.
   */
  WrapMode get_wrap() const;
  
  /** Queries whether the layout had to wrap any paragraphs.
   * 
   * This returns <tt>true</tt> if a positive width is set on @a layout,
   * ellipsization mode of @a layout is set to Pango::ELLIPSIZE_NONE,
   * and there are paragraphs exceeding the layout width that have
   * to be wrapped.
   * 
   * @newin{1,16}
   * 
   * @return <tt>true</tt> if any paragraphs had to be wrapped, <tt>false</tt>
   * otherwise.
   */
  bool is_wrapped() const;
  
  /** Sets the width in Pango units to indent each paragraph. A negative value
   * of @a indent will produce a hanging indentation. That is, the first line will
   * have the full width, and subsequent lines will be indented by the
   * absolute value of @a indent.
   * 
   * The indent setting is ignored if layout alignment is set to
   * Pango::ALIGN_CENTER.
   * 
   * @param indent The amount by which to indent.
   */
  void set_indent(int indent);
  
  /** Gets the paragraph indent width in Pango units. A negative value
   * indicates a hanging indentation.
   * 
   * @return The indent in Pango units.
   */
  int get_indent() const;
  
  /** Sets the amount of spacing in Pango unit between the lines of the
   * layout.
   * 
   * @param spacing The amount of spacing.
   */
  void set_spacing(int spacing);
  
  /** Gets the amount of spacing between the lines of the layout.
   * 
   * @return The spacing in Pango units.
   */
  int get_spacing() const;
  
  /** Sets whether each complete line should be stretched to
   * fill the entire width of the layout. This stretching is typically
   * done by adding whitespace, but for some scripts (such as Arabic),
   * the justification may be done in more complex ways, like extending
   * the characters.
   * 
   * Note that this setting is not implemented and so is ignored in Pango
   * older than 1.18.
   * 
   * @param justify Whether the lines in the layout should be justified.
   */
  void set_justify(bool justify =  true);
  
  /** Gets whether each complete line should be stretched to fill the entire
   * width of the layout.
   * 
   * @return The justify.
   */
  bool get_justify() const;

  
  /** Gets whether to calculate the bidirectional base direction
   * for the layout according to the contents of the layout.
   * See set_auto_dir().
   * 
   * @newin{1,4}
   * 
   * @return <tt>true</tt> if the bidirectional base direction
   * is computed from the layout's contents, <tt>false</tt> otherwise.
   */
  bool get_auto_dir() const;
  
  /** Sets whether to calculate the bidirectional base direction
   * for the layout according to the contents of the layout;
   * when this flag is on (the default), then paragraphs in
   *    @a layout that begin with strong right-to-left characters
   * (Arabic and Hebrew principally), will have right-to-left
   * layout, paragraphs with letters from other scripts will
   * have left-to-right layout. Paragraphs with only neutral
   * characters get their direction from the surrounding paragraphs.
   * 
   * When <tt>false</tt>, the choice between left-to-right and
   * right-to-left layout is done according to the base direction
   * of the layout's Pango::Context. (See Pango::Context::set_base_dir()).
   * 
   * When the auto-computed direction of a paragraph differs from the
   * base direction of the context, the interpretation of
   * Pango::ALIGN_LEFT and Pango::ALIGN_RIGHT are swapped.
   * 
   * @newin{1,4}
   * 
   * @param auto_dir If <tt>true</tt>, compute the bidirectional base direction
   * from the layout's contents.
   */
  void set_auto_dir(bool auto_dir =  true);
  
  
  /** Sets the alignment for the layout: how partial lines are
   * positioned within the horizontal space available.
   * 
   * @param alignment The alignment.
   */
  void set_alignment(Alignment alignment);
  
  /** Gets the alignment for the layout: how partial lines are
   * positioned within the horizontal space available.
   * 
   * @return The alignment.
   */
  Alignment get_alignment() const;

  
  /** Sets the tabs to use for @a layout, overriding the default tabs
   * (by default, tabs are every 8 spaces). If @a tabs is <tt>nullptr</tt>, the default
   * tabs are reinstated. @a tabs is copied into the layout; you must
   * free your copy of @a tabs yourself.
   * 
   * @param tabs A Pango::TabArray, or <tt>nullptr</tt>.
   */
  void set_tabs(TabArray& tabs);
  
  /** Get the current Pango::TabArray used by this layout. If no
   * Pango::TabArray has been set, then the default tabs are in use
   * and an invalid instance is returned. Default tabs are every 8 spaces.
   * 
   * @return A copy of the tabs for this layout.
   */
  TabArray get_tabs() const;

  
  /** If @a setting is <tt>true</tt>, do not treat newlines and similar characters
   * as paragraph separators; instead, keep all text in a single paragraph,
   * and display a glyph for paragraph separator characters. Used when
   * you want to allow editing of newlines on a single text line.
   * 
   * @param setting New setting.
   */
  void set_single_paragraph_mode(bool setting =  true);
  
  /** Obtains the value set by set_single_paragraph_mode().
   * 
   * @return <tt>true</tt> if the layout does not break paragraphs at
   * paragraph separator characters, <tt>false</tt> otherwise.
   */
  bool get_single_paragraph_mode() const;

  
  /** Sets the type of ellipsization being performed for @a layout.
   * Depending on the ellipsization mode @a ellipsize text is
   * removed from the start, middle, or end of text so they
   * fit within the width and height of layout set with
   * set_width() and set_height().
   * 
   * If the layout contains characters such as newlines that
   * force it to be layed out in multiple paragraphs, then whether
   * each paragraph is ellipsized separately or the entire layout
   * is ellipsized as a whole depends on the set height of the layout.
   * See set_height() for details.
   * 
   * @newin{1,6}
   * 
   * @param ellipsize The new ellipsization mode for @a layout.
   */
  void set_ellipsize(EllipsizeMode ellipsize);
  
  /** Gets the type of ellipsization being performed for @a layout.
   * See set_ellipsize()
   * 
   * @newin{1,6}
   * 
   * @return The current ellipsization mode for @a layout.
   * 
   * Use is_ellipsized() to query whether any paragraphs
   * were actually ellipsized.
   */
  EllipsizeMode get_ellipsize() const;

  
  /** Queries whether the layout had to ellipsize any paragraphs.
   * 
   * This returns <tt>true</tt> if the ellipsization mode for @a layout
   * is not Pango::ELLIPSIZE_NONE, a positive width is set on @a layout,
   * and there are paragraphs exceeding that width that have to be
   * ellipsized.
   * 
   * @newin{1,16}
   * 
   * @return <tt>true</tt> if any paragraphs had to be ellipsized, <tt>false</tt>
   * otherwise.
   */
  bool is_ellipsized() const;
  
  /** Counts the number unknown glyphs in @a layout.  That is, zero if
   * glyphs for all characters in the layout text were found, or more
   * than zero otherwise.
   * 
   * This function can be used to determine if there are any fonts
   * available to render all characters in a certain string, or when
   * used in combination with Pango::ATTR_FALLBACK, to check if a
   * certain font supports all the characters in the string.
   * 
   * @newin{1,16}
   * 
   * @return The number of unknown glyphs in @a layout.
   */
  int get_unknown_glyphs_count() const;

  
  /** Forces recomputation of any state in the Pango::Layout that
   * might depend on the layout's context. This function should
   * be called if you make changes to the context subsequent
   * to creating the layout.
   */
  void context_changed();

  
  /** Returns the current serial number of @a layout.  The serial number is
   * initialized to an small number  larger than zero when a new layout
   * is created and is increased whenever the layout is changed using any
   * of the setter functions, or the Pango::Context it uses has changed.
   * The serial may wrap, but will never have the value 0. Since it
   * can wrap, never compare it with "less than", always use "not equals".
   * 
   * This can be used to automatically detect changes to a Pango::Layout, and
   * is useful for example to decide whether a layout needs redrawing.
   * To force the serial to be increased, use context_changed().
   * 
   * @newin{1,32,4}
   * 
   * @return The current serial number of @a layout.
   */
  guint get_serial() const;

  /** Retrieve an array of logical attributes for each character in the layout.
   * @return An array of logical attributes.
   */
  Glib::ArrayHandle<LogAttr> get_log_attrs() const;

  /** Convert from an index within the layout to the onscreen position corresponding to the grapheme at that index, which is represented as rectangle.
   * Note that @a x in the returned rectangle is always the leading edge of the grapheme
   * and @a x + @a width the trailing edge of the grapheme.
   * If the directionality of the grapheme is right-to-left, then @a width will be negative.
   * @param index Byte index within layout.
   * @return The position of the grapheme.
   */
  Rectangle index_to_pos(int index) const;
  

  /** Converts from byte @a index within the @a layout to line and X position.
   * (X position is measured from the left edge of the line)
   * 
   * @param index The byte index of a grapheme within the layout.
   * @param trailing An integer indicating the edge of the grapheme to retrieve the
   * position of. If > 0, the trailing edge of the grapheme, if 0,
   * the leading of the grapheme.
   * @param line Location to store resulting line index. (which will
   * between 0 and pango_layout_get_line_count(layout) - 1), or <tt>nullptr</tt>.
   * @param x_pos Location to store resulting position within line
   * (Pango::SCALE units per device unit), or <tt>nullptr</tt>.
   */
  void index_to_line_x(int index_, bool trailing, int& line, int& x_pos) const;

  
  /** Given an index within a layout, determines the positions that of the
   * strong and weak cursors if the insertion point is at that
   * index. The position of each cursor is stored as a zero-width
   * rectangle. The strong cursor location is the location where
   * characters of the directionality equal to the base direction of the
   * layout are inserted.  The weak cursor location is the location
   * where characters of the directionality opposite to the base
   * direction of the layout are inserted.
   * 
   * @param index The byte index of the cursor.
   * @param strong_pos Location to store the strong cursor position
   * (may be <tt>nullptr</tt>).
   * @param weak_pos Location to store the weak cursor position (may be <tt>nullptr</tt>).
   */
  void get_cursor_pos(int index, Rectangle& strong_pos, Rectangle& weak_pos) const;

  /** Given an index within the layout, determine the positions that of the strong cursors if the insertion point is at that index.
   * @param index The byte index of the cursor.
   * @return The strong cursor position.
   */
  Rectangle get_cursor_strong_pos(int index) const;

  /** Given an index within the layout, determine the positions that of the weak cursors if the insertion point is at that index.
   * @param index The byte index of the cursor.
   * @return The weak cursor position.
   */
  Rectangle get_cursor_weak_pos(int index) const;

  
  /** Computes a new cursor position from an old position and
   * a count of positions to move visually. If @a direction is positive,
   * then the new strong cursor position will be one position
   * to the right of the old cursor position. If @a direction is negative,
   * then the new strong cursor position will be one position
   * to the left of the old cursor position.
   * 
   * In the presence of bidirectional text, the correspondence
   * between logical and visual order will depend on the direction
   * of the current run, and there may be jumps when the cursor
   * is moved off of the end of a run.
   * 
   * Motion here is in cursor positions, not in characters, so a
   * single call to move_cursor_visually() may move the
   * cursor over multiple characters when multiple characters combine
   * to form a single grapheme.
   * 
   * @param strong Whether the moving cursor is the strong cursor or the
   * weak cursor. The strong cursor is the cursor corresponding
   * to text insertion in the base direction for the layout.
   * @param old_index The byte index of the grapheme for the old index.
   * @param old_trailing If 0, the cursor was at the leading edge of the
   * grapheme indicated by @a old_index, if > 0, the cursor
   * was at the trailing edge.
   * @param direction Direction to move cursor. A negative
   * value indicates motion to the left.
   * @param new_index Location to store the new cursor byte index. A value of -1
   * indicates that the cursor has been moved off the beginning
   * of the layout. A value of MAXINT indicates that
   * the cursor has been moved off the end of the layout.
   * @param new_trailing Number of characters to move forward from the
   * location returned for @a new_index to get the position
   * where the cursor should be displayed. This allows
   * distinguishing the position at the beginning of one
   * line from the position at the end of the preceding
   * line. @a new_index is always on the line where the
   * cursor should be displayed.
   */
  void move_cursor_visually(bool strong, int old_index, int old_trailing, int direction, int& new_index, int& new_trailing) const;

  
  /** Converts from X and Y position within a layout to the byte
   * index to the character at that logical position. If the
   * Y position is not inside the layout, the closest position is chosen
   * (the position will be clamped inside the layout). If the
   * X position is not within the layout, then the start or the
   * end of the line is chosen as described for Pango::LayoutLine::x_to_index().
   * If either the X or Y positions were not inside the layout, then the
   * function returns <tt>false</tt>; on an exact hit, it returns <tt>true</tt>.
   * 
   * @param x The X offset (in Pango units)
   * from the left edge of the layout.
   * @param y The Y offset (in Pango units)
   * from the top edge of the layout.
   * @param index Location to store calculated byte index.
   * @param trailing Location to store a integer indicating where
   * in the grapheme the user clicked. It will either
   * be zero, or the number of characters in the
   * grapheme. 0 represents the leading edge of the grapheme.
   * @return <tt>true</tt> if the coordinates were inside text, <tt>false</tt> otherwise.
   */
  bool xy_to_index(int x, int y, int& index, int& trailing) const;

  
  /** Compute the logical and ink extents of @a layout. Logical extents
   * are usually what you want for positioning things. The extents
   * are given in layout coordinates; layout coordinates begin at the
   * top left corner of the layout.
   * 
   * @param ink_rect Rectangle used to store the extents of the layout as drawn.
   * @param logical_rect Rectangle used to store the logical extents of the layout.
   */
  void get_extents(Rectangle& ink_rect, Rectangle& logical_rect) const;

  /** Compute the ink extents of layout.
   * @return The extents of the layout as drawn.
   */
  Rectangle get_ink_extents() const;

  /** Compute the logical extents of layout.
   * @return The logical extents of the layout.
   */
  Rectangle get_logical_extents() const;

  
  /** Compute the logical and ink extents of @a layout in device units.
   * See get_extents(); this function just calls
   * get_extents() and then converts the extents to
   * pixels using the Pango::SCALE factor.
   * 
   * @param ink_rect Rectangle used to store the extents of the layout as drawn.
   * @param logical_rect Rectangle used to store the logical extents of the
   * layout.
   */
  void get_pixel_extents(Rectangle& ink_rect, Rectangle& logical_rect) const;

  /** Compute the ink extents of the layout in device units.
   * @return The extents of the layout as drawn.
   */
  Rectangle get_pixel_ink_extents() const;

  /** Compute the logical extents of the layout in device units.
   * @return The logical extents of the layout.
   */
  Rectangle get_pixel_logical_extents() const;

  
  /** Determines the logical width and height of a Pango::Layout
   * in Pango units (device units scaled by Pango::SCALE). This
   * is simply a convenience function around get_extents().
   * 
   * @param width Location to store the logical width, or <tt>nullptr</tt>.
   * @param height Location to store the logical height, or <tt>nullptr</tt>.
   */
  void get_size(int& width, int& height) const;
  
  /** Determines the logical width and height of a Pango::Layout
   * in device units. (get_size() returns the width
   * and height scaled by Pango::SCALE.) This
   * is simply a convenience function around
   * get_pixel_extents().
   * 
   * @param width Location to store the logical width, or <tt>nullptr</tt>.
   * @param height Location to store the logical height, or <tt>nullptr</tt>.
   */
  void get_pixel_size(int& width, int& height) const;

  
  /** Gets the Y position of baseline of the first line in @a layout.
   * 
   * @newin{1,22}
   * 
   * @return Baseline of first line, from top of @a layout.
   */
  int get_baseline() const;

  
  /** Retrieves the count of lines for the @a layout.
   * 
   * @return The line count.
   */
  int get_line_count() const;
  
  //Note that the const version uses a different (faster) C function:
  
  /** Retrieves a particular line from a Pango::Layout.
   * 
   * Use the faster get_line_readonly() if you do not plan
   * to modify the contents of the line (glyphs, glyph widths, etc.).
   * 
   * @param line The index of a line, which must be between 0 and
   * <tt>pango_layout_get_line_count(layout) - 1</tt>, inclusive.
   * @return The requested
   * Pango::LayoutLine, or <tt>nullptr</tt> if the index is out of
   * range. This layout line can be ref'ed and retained,
   * but will become invalid if changes are made to the
   * Pango::Layout.
   */
  Glib::RefPtr<LayoutLine> get_line(int line);
  
  /** Retrieves a particular line from a Pango::Layout.
   * 
   * This is a faster alternative to get_line(),
   * but the user is not expected
   * to modify the contents of the line (glyphs, glyph widths, etc.).
   * 
   * @newin{1,16}
   * 
   * @param line The index of a line, which must be between 0 and
   * <tt>pango_layout_get_line_count(layout) - 1</tt>, inclusive.
   * @return The requested
   * Pango::LayoutLine, or <tt>nullptr</tt> if the index is out of
   * range. This layout line can be ref'ed and retained,
   * but will become invalid if changes are made to the
   * Pango::Layout.  No changes should be made to the line.
   */
  Glib::RefPtr<const LayoutLine> get_line(int line) const; 

  //Note that the const version uses a different (faster) C function:
  
  /** Returns the lines of the @a layout as a list.
   * 
   * Use the faster get_lines_readonly() if you do not plan
   * to modify the contents of the lines (glyphs, glyph widths, etc.).
   * 
   * @return A SList containing
   * the lines in the layout. This points to internal data of the Pango::Layout
   * and must be used with care. It will become invalid on any change to the layout's
   * text or properties.
   */
  SListHandle_LayoutLine get_lines();
  
  /** Returns the lines of the @a layout as a list.
   * 
   * This is a faster alternative to get_lines(),
   * but the user is not expected
   * to modify the contents of the lines (glyphs, glyph widths, etc.).
   * 
   * @newin{1,16}
   * 
   * @return A SList containing
   * the lines in the layout. This points to internal data of the Pango::Layout and
   * must be used with care. It will become invalid on any change to the layout's
   * text or properties.  No changes should be made to the lines.
   */
  SListHandle_ConstLayoutLine get_lines() const;
  
#ifndef PANGOMM_DISABLE_DEPRECATED

  /** Gets an iterator to iterate over the visual extents of the layout.
   * @param iter Location to store the iterator.
   *
   * @deprecated Use the get_iter() that returns the LayoutIter instead of 
   * using an output parameter.
   */
  void get_iter(LayoutIter& iter);
#endif // PANGOMM_DISABLE_DEPRECATED

  
  /** Gets an iterator to iterate over the visual extents of the layout.
   * @result The iterator.
   *
   * @newin{2,28}
   */
  LayoutIter get_iter();


  /** Adds the text in this LayoutLine to the current path in the
   * specified Cairo @a context. The origin of the glyphs (the left edge
   * of the line) will be at the current point of the cairo context.
   *
   * @param context A Cairo context.
   */
  void add_to_cairo_context(const Cairo::RefPtr<Cairo::Context>& context);

  /** Draws a Layout in the specified Cairo @a context. The top-left
   *  corner of the Layout will be drawn at the current point of the
   *  cairo context.
   *
   * @param context A Cairo context.
   *
   * @newin{2,16}
   */
  void show_in_cairo_context(const Cairo::RefPtr<Cairo::Context>& context);


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


};

} /* namespace Pango */


namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Pango::Layout
   */
  Glib::RefPtr<Pango::Layout> wrap(PangoLayout* object, bool take_copy = false);
}


#endif /* _PANGOMM_LAYOUT_H */

