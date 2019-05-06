// Generated by gmmproc 2.52.1 -- DO NOT MODIFY!
#ifndef _GIOMM_TLSCLIENTCONNECTION_H
#define _GIOMM_TLSCLIENTCONNECTION_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* Copyright (C) 2013 The giomm Development Team
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

#include <glibmm/interface.h>
#include <giomm/tlsconnection.h>
#include <giomm/enums.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GTlsClientConnectionInterface GTlsClientConnectionInterface;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GTlsClientConnection = struct _GTlsClientConnection;
using GTlsClientConnectionClass = struct _GTlsClientConnectionClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gio
{ class TlsClientConnection_Class; } // namespace Gio
#endif // DOXYGEN_SHOULD_SKIP_THIS

namespace Gio
{

class SocketConnectable;

/** TlsClientConnection - TLS client-side connection.
 * TlsClientConnection is the client-side subclass of TlsConnection,
 * representing a client-side TLS connection.
 * @newin{2,36}
 */

class TlsClientConnection
: public Glib::Interface,
  public TlsConnection
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  using CppObjectType = TlsClientConnection;
  using CppClassType = TlsClientConnection_Class;
  using BaseObjectType = GTlsClientConnection;
  using BaseClassType = GTlsClientConnectionInterface;

  // noncopyable
  TlsClientConnection(const TlsClientConnection&) = delete;
  TlsClientConnection& operator=(const TlsClientConnection&) = delete;

private:
  friend class TlsClientConnection_Class;
  static CppClassType tlsclientconnection_class_;

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
protected:
  /**
   * You should derive from this class to use it.
   */
  TlsClientConnection();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /** Called by constructors of derived classes. Provide the result of
   * the Class init() function to ensure that it is properly
   * initialized.
   *
   * @param interface_class The Class object for the derived type.
   */
  explicit TlsClientConnection(const Glib::Interface_Class& interface_class);

public:
  // This is public so that C++ wrapper instances can be
  // created for C instances of unwrapped types.
  // For instance, if an unexpected C type implements the C interface.
  explicit TlsClientConnection(GTlsClientConnection* castitem);

protected:
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  TlsClientConnection(TlsClientConnection&& src) noexcept;
  TlsClientConnection& operator=(TlsClientConnection&& src) noexcept;

  ~TlsClientConnection() noexcept override;

  static void add_interface(GType gtype_implementer);

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GTlsClientConnection*       gobj()       { return reinterpret_cast<GTlsClientConnection*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GTlsClientConnection* gobj() const { return reinterpret_cast<GTlsClientConnection*>(gobject_); }

private:

  
public:
  //TODO: It's not possible to use _WRAP_CTOR/_WRAP_CREATE to wrap the new
  //function because this is an interface.
 

  /** Creates a new TlsClientConnection wrapping @a base_io_stream (which
   * must have pollable input and output streams) which is assumed to
   * communicate with the server identified by @a server_identity.
   * 
   * See the documentation for TlsConnection::property_base_io_stream() for restrictions
   * on when application code can run operations on the @a base_io_stream after
   * this function has returned.
   * 
   * @newin{2,28}
   * 
   * @param base_io_stream The IOStream to wrap.
   * @param server_identity The expected identity of the server.
   * @return The new
   * TlsClientConnection, or <tt>nullptr</tt> on error.
   */
  static Glib::RefPtr<TlsClientConnection> create(const Glib::RefPtr<IOStream>& base_io_stream, const Glib::RefPtr<const SocketConnectable>& server_identity);

  /// A create() convenience overload.
  static Glib::RefPtr<TlsClientConnection> create(const Glib::RefPtr<IOStream>& base_io_stream);

  
  /** Sets @a conn's expected server identity, which is used both to tell
   * servers on virtual hosts which certificate to present, and also
   * to let @a conn know what name to look for in the certificate when
   * performing TLS_CERTIFICATE_BAD_IDENTITY validation, if enabled.
   * 
   * @newin{2,28}
   * 
   * @param identity A SocketConnectable describing the expected server identity.
   */
  void set_server_identity(const Glib::RefPtr<SocketConnectable>& identity);

  
  /** Gets @a conn's expected server identity
   * 
   * @newin{2,28}
   * 
   * @return A SocketConnectable describing the
   * expected server identity, or <tt>nullptr</tt> if the expected identity is not
   * known.
   */
  Glib::RefPtr<SocketConnectable> get_server_identity();
  
  /** Gets @a conn's expected server identity
   * 
   * @newin{2,28}
   * 
   * @return A SocketConnectable describing the
   * expected server identity, or <tt>nullptr</tt> if the expected identity is not
   * known.
   */
  Glib::RefPtr<const SocketConnectable> get_server_identity() const;

  
  /** Sets @a conn's validation flags, to override the default set of
   * checks performed when validating a server certificate. By default,
   * TLS_CERTIFICATE_VALIDATE_ALL is used.
   * 
   * @newin{2,28}
   * 
   * @param flags The TlsCertificateFlags to use.
   */
  void set_validation_flags(TlsCertificateFlags flags);
  
  /** Gets @a conn's validation flags
   * 
   * @newin{2,28}
   * 
   * @return The validation flags.
   */
  TlsCertificateFlags get_validation_flags() const;

  
  /** If @a use_ssl3 is <tt>true</tt>, this forces @a conn to use SSL 3.0 rather than
   * trying to properly negotiate the right version of TLS or SSL to use.
   * This can be used when talking to servers that do not implement the
   * fallbacks correctly and which will therefore fail to handshake with
   * a "modern" TLS handshake attempt.
   * 
   * @newin{2,28}
   * 
   * @param use_ssl3 Whether to use SSL 3.0.
   */
  void set_use_ssl3(bool use_ssl3 =  true);
  
  /** Gets whether @a conn will use SSL 3.0 rather than the
   * highest-supported version of TLS; see
   * g_tls_client_connection_set_use_ssl3().
   * 
   * @newin{2,28}
   * 
   * @return Whether @a conn will use SSL 3.0.
   */
  bool get_use_ssl3() const;

 
  /** Gets the list of distinguished names of the Certificate Authorities
   * that the server will accept certificates from. This will be set
   * during the TLS handshake if the server requests a certificate.
   * Otherwise, it will be <tt>nullptr</tt>.
   * 
   * Each item in the list is a ByteArray which contains the complete
   * subject DN of the certificate authority.
   * 
   * @newin{2,28}
   * 
   * @return The list of
   * CA DNs.
   */
  std::vector< Glib::RefPtr<Glib::ByteArray> > get_accepted_cas();

 
  /** Gets the list of distinguished names of the Certificate Authorities
   * that the server will accept certificates from. This will be set
   * during the TLS handshake if the server requests a certificate.
   * Otherwise, it will be <tt>nullptr</tt>.
   * 
   * Each item in the list is a ByteArray which contains the complete
   * subject DN of the certificate authority.
   * 
   * @newin{2,28}
   * 
   * @return The list of
   * CA DNs.
   */
  std::vector< Glib::RefPtr<const Glib::ByteArray> > get_accepted_cas() const;


  /** Copies session state from one connection to another. This is
   * not normally needed, but may be used when the same session
   * needs to be used between different endpoints as is required
   * by some protocols such as FTP over TLS. @a source should have
   * already completed a handshake, and @a conn should not have
   * completed a handshake.
   * 
   * @newin{2,46}
   * 
   * @param source A TlsClientConnection.
   */
  void copy_session_state(const Glib::RefPtr<TlsClientConnection>& source);

  /** A list of the distinguished names of the Certificate Authorities
   * that the server will accept client certificates signed by. If the
   * server requests a client certificate during the handshake, then
   * this property will be set after the handshake completes.
   * 
   * Each item in the list is a ByteArray which contains the complete
   * subject DN of the certificate authority.
   * 
   * @newin{2,28}
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< std::vector< Glib::RefPtr<Glib::ByteArray> > > property_accepted_cas() const;


  /** A SocketConnectable describing the identity of the server that
   * is expected on the other end of the connection.
   * 
   * If the TLS_CERTIFICATE_BAD_IDENTITY flag is set in
   * TlsClientConnection::property_validation_flags(), this object will be used
   * to determine the expected identify of the remote end of the
   * connection; if TlsClientConnection::property_server_identity() is not set,
   * or does not match the identity presented by the server, then the
   * TLS_CERTIFICATE_BAD_IDENTITY validation will fail.
   * 
   * In addition to its use in verifying the server certificate,
   * this is also used to give a hint to the server about what
   * certificate we expect, which is useful for servers that serve
   * virtual hosts.
   * 
   * @newin{2,28}
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Glib::RefPtr<SocketConnectable> > property_server_identity() ;

/** A SocketConnectable describing the identity of the server that
   * is expected on the other end of the connection.
   * 
   * If the TLS_CERTIFICATE_BAD_IDENTITY flag is set in
   * TlsClientConnection::property_validation_flags(), this object will be used
   * to determine the expected identify of the remote end of the
   * connection; if TlsClientConnection::property_server_identity() is not set,
   * or does not match the identity presented by the server, then the
   * TLS_CERTIFICATE_BAD_IDENTITY validation will fail.
   * 
   * In addition to its use in verifying the server certificate,
   * this is also used to give a hint to the server about what
   * certificate we expect, which is useful for servers that serve
   * virtual hosts.
   * 
   * @newin{2,28}
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::RefPtr<SocketConnectable> > property_server_identity() const;

  /** If <tt>true</tt>, tells the connection to use a fallback version of TLS
   * or SSL, rather than trying to negotiate the best version of TLS
   * to use. This can be used when talking to servers that don't
   * implement version negotiation correctly and therefore refuse to
   * handshake at all with a "modern" TLS handshake.
   * 
   * Despite the property name, the fallback version is not
   * necessarily SSL 3.0; if SSL 3.0 has been disabled, the
   * TlsClientConnection will use the next highest available version
   * (normally TLS 1.0) as the fallback version.
   * 
   * @newin{2,28}
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< bool > property_use_ssl3() ;

/** If <tt>true</tt>, tells the connection to use a fallback version of TLS
   * or SSL, rather than trying to negotiate the best version of TLS
   * to use. This can be used when talking to servers that don't
   * implement version negotiation correctly and therefore refuse to
   * handshake at all with a "modern" TLS handshake.
   * 
   * Despite the property name, the fallback version is not
   * necessarily SSL 3.0; if SSL 3.0 has been disabled, the
   * TlsClientConnection will use the next highest available version
   * (normally TLS 1.0) as the fallback version.
   * 
   * @newin{2,28}
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< bool > property_use_ssl3() const;

  /** What steps to perform when validating a certificate received from
   * a server. Server certificates that fail to validate in all of the
   * ways indicated here will be rejected unless the application
   * overrides the default via TlsConnection::signal_accept_certificate().
   * 
   * @newin{2,28}
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< TlsCertificateFlags > property_validation_flags() ;

/** What steps to perform when validating a certificate received from
   * a server. Server certificates that fail to validate in all of the
   * ways indicated here will be rejected unless the application
   * overrides the default via TlsConnection::signal_accept_certificate().
   * 
   * @newin{2,28}
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< TlsCertificateFlags > property_validation_flags() const;


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
   * @relates Gio::TlsClientConnection
   */
  Glib::RefPtr<Gio::TlsClientConnection> wrap(GTlsClientConnection* object, bool take_copy = false);

} // namespace Glib


#endif /* _GIOMM_TLSCLIENTCONNECTION_H */

