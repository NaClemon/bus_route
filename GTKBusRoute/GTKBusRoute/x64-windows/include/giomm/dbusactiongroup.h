// Generated by gmmproc 2.52.1 -- DO NOT MODIFY!
#ifndef _GIOMM_DBUSACTIONGROUP_H
#define _GIOMM_DBUSACTIONGROUP_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* Copyright (C) 2012 The giomm Development Team
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

#include <glibmm/object.h>
#include <giomm/actiongroup.h>
#include <giomm/remoteactiongroup.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GDBusActionGroup = struct _GDBusActionGroup;
using GDBusActionGroupClass = struct _GDBusActionGroupClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gio
{

namespace DBus
{ class ActionGroup_Class; } // namespace DBus

} // namespace Gio
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Gio
{

namespace DBus
{

class Connection;


/** ActionGroup - A D-Bus Gio::ActionGroup implementation.
 * ActionGroup is an implementation of the Gio::ActionGroup interface that can
 * be used as a proxy for an action group that is exported over D-Bus with
 * Gio::DBus::Connection::export_action_group().
 * @newin{2,32}
 */

class ActionGroup
: public Glib::Object, public ::Gio::ActionGroup, public RemoteActionGroup
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  using CppObjectType = ActionGroup;
  using CppClassType = ActionGroup_Class;
  using BaseObjectType = GDBusActionGroup;
  using BaseClassType = GDBusActionGroupClass;

  // noncopyable
  ActionGroup(const ActionGroup&) = delete;
  ActionGroup& operator=(const ActionGroup&) = delete;

private:  friend class ActionGroup_Class;
  static CppClassType actiongroup_class_;

protected:
  explicit ActionGroup(const Glib::ConstructParams& construct_params);
  explicit ActionGroup(GDBusActionGroup* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  ActionGroup(ActionGroup&& src) noexcept;
  ActionGroup& operator=(ActionGroup&& src) noexcept;

  ~ActionGroup() noexcept override;

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GDBusActionGroup*       gobj()       { return reinterpret_cast<GDBusActionGroup*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GDBusActionGroup* gobj() const { return reinterpret_cast<GDBusActionGroup*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GDBusActionGroup* gobj_copy();

private:

  
protected:
  ActionGroup();

public:
 

  /** Obtains a DBusActionGroup for the action group which is exported at
   * the given @a bus_name and @a object_path.
   * 
   * The thread default main context is taken at the time of this call.
   * All signals on the menu model (and any linked models) are reported
   * with respect to this context.  All calls on the returned menu model
   * (and linked models) must also originate from this same context, with
   * the thread default main context unchanged.
   * 
   * This call is non-blocking.  The returned action group may or may not
   * already be filled in.  The correct thing to do is connect the signals
   * for the action group to monitor for changes and then to call
   * g_action_group_list_actions() to get the initial list.
   * 
   * @newin{2,32}
   * 
   * @param connection A DBusConnection.
   * @param bus_name The bus name which exports the action group.
   * @param object_path The object path at which the action group is exported.
   * @return A DBusActionGroup.
   */
  static Glib::RefPtr<ActionGroup> get(const Glib::RefPtr<Connection>& connection, const Glib::ustring& bus_name, const Glib::ustring& object_path);


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


};

} // namespace DBus

} // namespace Gio


namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gio::DBus::ActionGroup
   */
  Glib::RefPtr<Gio::DBus::ActionGroup> wrap(GDBusActionGroup* object, bool take_copy = false);
}


#endif /* _GIOMM_DBUSACTIONGROUP_H */

