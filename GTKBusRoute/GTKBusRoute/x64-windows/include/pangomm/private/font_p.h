// Generated by gmmproc 2.49.5 -- DO NOT MODIFY!
#ifndef _PANGOMM_FONT_P_H
#define _PANGOMM_FONT_P_H


#include <glibmm/private/object_p.h>

#include <glibmm/class.h>

namespace Pango
{

class Font_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = Font;
  using BaseObjectType = PangoFont;
  using BaseClassType = PangoFontClass;
  using CppClassParent = Glib::Object_Class;
  using BaseClassParent = GObjectClass;

  friend class Font;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();


  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.

  //Callbacks (virtual functions):
};


} // namespace Pango


#endif /* _PANGOMM_FONT_P_H */

