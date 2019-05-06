// Generated by gmmproc 2.52.1 -- DO NOT MODIFY!
#ifndef _GIOMM_UNIXSOCKETADDRESS_H
#define _GIOMM_UNIXSOCKETADDRESS_H

#include <giommconfig.h>


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* Copyright (C) 2010 The giomm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <giomm/socketaddress.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GUnixSocketAddress = struct _GUnixSocketAddress;
using GUnixSocketAddressClass = struct _GUnixSocketAddressClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gio
{ class UnixSocketAddress_Class; } // namespace Gio
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Gio
{

/** @addtogroup giommEnums giomm Enums and Flags */

/** 
 *  @var UnixSocketAddressType UNIX_SOCKET_ADDRESS_INVALID
 * Invalid.
 * 
 *  @var UnixSocketAddressType UNIX_SOCKET_ADDRESS_ANONYMOUS
 * Anonymous.
 * 
 *  @var UnixSocketAddressType UNIX_SOCKET_ADDRESS_PATH
 * A filesystem path.
 * 
 *  @var UnixSocketAddressType UNIX_SOCKET_ADDRESS_ABSTRACT
 * An abstract name.
 * 
 *  @var UnixSocketAddressType UNIX_SOCKET_ADDRESS_ABSTRACT_PADDED
 * An abstract name, 0-padded
 * to the full length of a unix socket name.
 * 
 *  @enum UnixSocketAddressType
 * 
 * The type of name used by a UnixSocketAddress.
 * UNIX_SOCKET_ADDRESS_PATH indicates a traditional unix domain
 * socket bound to a filesystem path. UNIX_SOCKET_ADDRESS_ANONYMOUS
 * indicates a socket not bound to any name (eg, a client-side socket,
 * or a socket created with socketpair()).
 * 
 * For abstract sockets, there are two incompatible ways of naming
 * them; the man pages suggest using the entire `struct sockaddr_un`
 * as the name, padding the unused parts of the %sun_path field with
 * zeroes; this corresponds to UNIX_SOCKET_ADDRESS_ABSTRACT_PADDED.
 * However, many programs instead just use a portion of %sun_path, and
 * pass an appropriate smaller length to bind() or connect(). This is
 * UNIX_SOCKET_ADDRESS_ABSTRACT.
 * 
 * @newin{2,26}
 *
 * @ingroup giommEnums
 */
enum UnixSocketAddressType
{
  UNIX_SOCKET_ADDRESS_INVALID,
  UNIX_SOCKET_ADDRESS_ANONYMOUS,
  UNIX_SOCKET_ADDRESS_PATH,
  UNIX_SOCKET_ADDRESS_ABSTRACT,
  UNIX_SOCKET_ADDRESS_ABSTRACT_PADDED
};

} // namespace Gio

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value<Gio::UnixSocketAddressType> : public Glib::Value_Enum<Gio::UnixSocketAddressType>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace Gio
{


class ByteArray;

/** UnixSocketAddress - UNIX SocketAddress.
 * Support for UNIX-domain (also known as local) sockets.
 *
 * UNIX domain sockets are generally visible in the filesystem. However, some
 * systems support abstract socket names which are not visible in the
 * filesystem and not affected by the filesystem permissions, visibility, etc.
 * Currently this is only supported under Linux. If you attempt to use
 * abstract sockets on other systems, function calls may return
 * Gio::IO_ERROR_NOT_SUPPORTED errors. You can use
 * Gio::UnixSocketAddress::abstract_names_supported() to see if abstract names
 * are supported.
 *
 * Note that @c <giomm/unixsocketaddress.h> belongs to the UNIX-specific GIO
 * interfaces.
 * @newin{2,28}
 * @ingroup NetworkIO
 */

class UnixSocketAddress
: public SocketAddress
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  using CppObjectType = UnixSocketAddress;
  using CppClassType = UnixSocketAddress_Class;
  using BaseObjectType = GUnixSocketAddress;
  using BaseClassType = GUnixSocketAddressClass;

  // noncopyable
  UnixSocketAddress(const UnixSocketAddress&) = delete;
  UnixSocketAddress& operator=(const UnixSocketAddress&) = delete;

private:  friend class UnixSocketAddress_Class;
  static CppClassType unixsocketaddress_class_;

protected:
  explicit UnixSocketAddress(const Glib::ConstructParams& construct_params);
  explicit UnixSocketAddress(GUnixSocketAddress* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  UnixSocketAddress(UnixSocketAddress&& src) noexcept;
  UnixSocketAddress& operator=(UnixSocketAddress&& src) noexcept;

  ~UnixSocketAddress() noexcept override;

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GUnixSocketAddress*       gobj()       { return reinterpret_cast<GUnixSocketAddress*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GUnixSocketAddress* gobj() const { return reinterpret_cast<GUnixSocketAddress*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GUnixSocketAddress* gobj_copy();

private:

  //This is not available on Win32.
//This source file will not be compiled on Win32,
//and no class defined in it will be registered by wrap_init().


protected:
   explicit UnixSocketAddress(const std::string& path);


 //TODO: Possibly add when g_unix_socket_address_new_with_type() does not do
 //more than call g_object_new() (maybe file a bug).
 //_WRAP_CTOR(UnixSocketAddress(const std::string& path, int path_len = -1, UnixSocketAddressType type = Gio::UNIX_SOCKET_ADDRESS_PATH), g_unix_socket_address_new_with_type)

public:
 
  /** Creates a new UnixSocketAddress for @a path.
   * 
   * To create abstract socket addresses, on systems that support that,
   * use g_unix_socket_address_new_abstract().
   * 
   * @newin{2,22}
   * 
   * @param path The socket path.
   * @return A new UnixSocketAddress.
   */

 
  static Glib::RefPtr<UnixSocketAddress> create(const std::string& path);


 //TODO: Add when the above constructor is included, removing the handwritten
 //create() method for it below.
 //_WRAP_METHOD_DOCS_ONLY(g_unix_socket_address_new_with_type)
 //_WRAP_CREATE(const std::string& path, int path_len = -1, UnixSocketAddressType type = Gio::UNIX_SOCKET_ADDRESS_PATH)

 
  /** Creates a new UnixSocketAddress of type @a type with name @a path.
   * 
   * If @a type is UNIX_SOCKET_ADDRESS_PATH, this is equivalent to
   * calling g_unix_socket_address_new().
   * 
   * If @a type is UNIX_SOCKET_ADDRESS_ANONYMOUS, @a path and @a path_len will be
   * ignored.
   * 
   * If @a path_type is UNIX_SOCKET_ADDRESS_ABSTRACT, then @a path_len
   * bytes of @a path will be copied to the socket's path, and only those
   * bytes will be considered part of the name. (If @a path_len is -1,
   * then @a path is assumed to be NUL-terminated.) For example, if @a path
   * was "test", then calling g_socket_address_get_native_size() on the
   * returned socket would return 7 (2 bytes of overhead, 1 byte for the
   * abstract-socket indicator byte, and 4 bytes for the name "test").
   * 
   * If @a path_type is UNIX_SOCKET_ADDRESS_ABSTRACT_PADDED, then
   *  @a path_len bytes of @a path will be copied to the socket's path, the
   * rest of the path will be padded with 0 bytes, and the entire
   * zero-padded buffer will be considered the name. (As above, if
   *  @a path_len is -1, then @a path is assumed to be NUL-terminated.) In
   * this case, g_socket_address_get_native_size() will always return
   * the full size of a `struct sockaddr_un`, although
   * g_unix_socket_address_get_path_len() will still return just the
   * length of @a path.
   * 
   * UNIX_SOCKET_ADDRESS_ABSTRACT is preferred over
   * UNIX_SOCKET_ADDRESS_ABSTRACT_PADDED for new programs. Of course,
   * when connecting to a server created by another process, you must
   * use the appropriate type corresponding to how that process created
   * its listening socket.
   * 
   * @newin{2,26}
   * 
   * @param path The name.
   * @param path_len The length of @a path, or -1.
   * @param type A UnixSocketAddressType.
   * @return A new UnixSocketAddress.
   */

 static Glib::RefPtr<UnixSocketAddress> create(const std::string& path,
   UnixSocketAddressType type, int path_len = -1);

 // Deprecated.
 

  /** Gets @a address's type.
   * 
   * @newin{2,26}
   * 
   * @return A UnixSocketAddressType.
   */
  UnixSocketAddressType get_address_type() const;
 
  /** Gets @a address's path, or for abstract sockets the "name".
   * 
   * Guaranteed to be zero-terminated, but an abstract socket
   * may contain embedded zeros, and thus you should use
   * g_unix_socket_address_get_path_len() to get the true length
   * of this string.
   * 
   * @newin{2,22}
   * 
   * @return The path for @a address.
   */
  std::string get_path() const;
 

  /** Checks if abstract UNIX domain socket names are supported.
   * 
   * @newin{2,22}
   * 
   * @return <tt>true</tt> if supported, <tt>false</tt> otherwise.
   */
  static bool abstract_names_supported();

  
#ifndef GIOMM_DISABLE_DEPRECATED

/** Whether or not this is an abstract address
   * 
   * Deprecated: Use UnixSocketAddress::property_address_type(), which
   * distinguishes between zero-padded and non-zero-padded
   * abstract addresses.
   * 
   * @deprecated Use property_address_type() instead, which distinguishes between zero-padded and non-zero-padded abstract addresses.
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< bool > property_abstract() const;


#endif // GIOMM_DISABLE_DEPRECATED

  /** The type of UNIX socket address.
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< UnixSocketAddressType > property_address_type() const;


  /** UNIX socket path.
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< std::string > property_path() const;


  /** UNIX socket path, as byte array.
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::RefPtr<ByteArray> > property_path_as_array() const;


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


};

} // namespace Gio


namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gio::UnixSocketAddress
   */
  Glib::RefPtr<Gio::UnixSocketAddress> wrap(GUnixSocketAddress* object, bool take_copy = false);
}


#endif /* _GIOMM_UNIXSOCKETADDRESS_H */

