// Generated by gmmproc 2.52.1 -- DO NOT MODIFY!
#ifndef _GIOMM_UNIXSOCKETADDRESS_P_H
#define _GIOMM_UNIXSOCKETADDRESS_P_H


#include <giomm/private/socketaddress_p.h>

#include <glibmm/class.h>

namespace Gio
{

class UnixSocketAddress_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = UnixSocketAddress;
  using BaseObjectType = GUnixSocketAddress;
  using BaseClassType = GUnixSocketAddressClass;
  using CppClassParent = SocketAddress_Class;
  using BaseClassParent = GSocketAddressClass;

  friend class UnixSocketAddress;
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


} // namespace Gio


#endif /* _GIOMM_UNIXSOCKETADDRESS_P_H */

