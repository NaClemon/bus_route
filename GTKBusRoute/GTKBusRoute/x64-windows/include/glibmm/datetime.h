// Generated by gmmproc 2.52.1 -- DO NOT MODIFY!
#ifndef _GLIBMM_DATETIME_H
#define _GLIBMM_DATETIME_H


/* Copyright (C) 2011 The glibmm Development Team
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


#include <glibmmconfig.h>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>
#include <glib.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GDateTime GDateTime;
#endif

namespace Glib
{

struct TimeVal;
class TimeZone;

/** A value representing an interval of time, in microseconds.  As GTimeSpan,
 * its underlying type is gint64.
 */
using TimeSpan = GTimeSpan;

/** DateTime - A structure representing Date and Time.
 * DateTime is a structure that combines a Gregorian date and time into a
 * single structure. It provides many conversion and methods to manipulate
 * dates and times. Time precision is provided down to microseconds and the
 * time can range (proleptically) from 0001-01-01 00:00:00 to 9999-12-31
 * 23:59:59.999999. DateTime follows POSIX time in the sense that it is
 * oblivious to leap seconds.
 *
 * DateTime is an immutable object; once it has been created it cannot be
 * modified further. All modifiers will create a new DateTime. Nearly all such
 * functions can fail due to the date or time going out of range, in which case
 * <tt>0</tt> will be returned.
 *
 * DateTime is reference counted.  When the reference count drops to 0, the
 * resources allocated by the DateTime structure are released.
 *
 * Many parts of the API may produce non-obvious results. As an example, adding
 * two months to January 31st will yield March 31st whereas adding one month
 * and then one month again will yield either March 28th or March 29th. Also
 * note that adding 24 hours is not always the same as adding one day (since
 * days containing daylight savings time transitions are either 23 or 25 hours
 * in length).
 * @newin{2,30}
 */
class DateTime
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = DateTime;
  using BaseObjectType = GDateTime;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  /** Constructs an invalid object.
   * E.g. for output arguments to methods. There is not much you can do with
   * the object before it has been assigned a valid value.
   */
  DateTime();

  // Use make_a_copy=true when getting it directly from a struct.
  explicit DateTime(GDateTime* castitem, bool make_a_copy = false);

  DateTime(const DateTime& src);
  DateTime& operator=(const DateTime& src);

  DateTime(DateTime&& other) noexcept;
  DateTime& operator=(DateTime&& other) noexcept;

  ~DateTime() noexcept;

  void swap(DateTime& other) noexcept;

  GDateTime*       gobj()       { return gobject_; }
  const GDateTime* gobj() const { return gobject_; }

  ///Provides access to the underlying C instance. The caller is responsible for freeing it. Use when directly setting fields in structs.
  GDateTime* gobj_copy() const;

protected:
  GDateTime* gobject_;

private:

  
public:
 
  /** Creates a DateTime corresponding to this exact instant in the given
   * time zone @a tz.  The time is as accurate as the system allows, to a
   * maximum accuracy of 1 microsecond.
   * 
   * This function will always succeed unless the system clock is set to
   * truly insane values (or unless GLib is still being used after the
   * year 9999).
   * 
   * You should release the return value by calling g_date_time_unref()
   * when you are done with it.
   * 
   * @newin{2,26}
   * 
   * @param tz A TimeZone.
   * @return A new DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create_now(const TimeZone& tz);
  
  /** Creates a DateTime corresponding to this exact instant in the local
   * time zone.
   * 
   * This is equivalent to calling g_date_time_new_now() with the time
   * zone returned by g_time_zone_new_local().
   * 
   * @newin{2,26}
   * 
   * @return A new DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create_now_local();
  
  /** Creates a DateTime corresponding to this exact instant in UTC.
   * 
   * This is equivalent to calling g_date_time_new_now() with the time
   * zone returned by g_time_zone_new_utc().
   * 
   * @newin{2,26}
   * 
   * @return A new DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create_now_utc();

  
  /** Creates a DateTime corresponding to the given Unix time @a t in the
   * local time zone.
   * 
   * Unix time is the number of seconds that have elapsed since 1970-01-01
   * 00:00:00 UTC, regardless of the local time offset.
   * 
   * This call can fail (returning <tt>nullptr</tt>) if @a t represents a time outside
   * of the supported range of DateTime.
   * 
   * You should release the return value by calling g_date_time_unref()
   * when you are done with it.
   * 
   * @newin{2,26}
   * 
   * @param t The Unix time.
   * @return A new DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create_now_local(gint64 t);
  
  /** Creates a DateTime corresponding to the given Unix time @a t in UTC.
   * 
   * Unix time is the number of seconds that have elapsed since 1970-01-01
   * 00:00:00 UTC.
   * 
   * This call can fail (returning <tt>nullptr</tt>) if @a t represents a time outside
   * of the supported range of DateTime.
   * 
   * You should release the return value by calling g_date_time_unref()
   * when you are done with it.
   * 
   * @newin{2,26}
   * 
   * @param t The Unix time.
   * @return A new DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create_now_utc(gint64 t);

  
  /** Creates a DateTime corresponding to the given TimeVal @a tv in the
   * local time zone.
   * 
   * The time contained in a TimeVal is always stored in the form of
   * seconds elapsed since 1970-01-01 00:00:00 UTC, regardless of the
   * local time offset.
   * 
   * This call can fail (returning <tt>nullptr</tt>) if @a tv represents a time outside
   * of the supported range of DateTime.
   * 
   * You should release the return value by calling g_date_time_unref()
   * when you are done with it.
   * 
   * @newin{2,26}
   * 
   * @param tv A TimeVal.
   * @return A new DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create_now_local(const TimeVal& tv);
  
  /** Creates a DateTime corresponding to the given TimeVal @a tv in UTC.
   * 
   * The time contained in a TimeVal is always stored in the form of
   * seconds elapsed since 1970-01-01 00:00:00 UTC.
   * 
   * This call can fail (returning <tt>nullptr</tt>) if @a tv represents a time outside
   * of the supported range of DateTime.
   * 
   * You should release the return value by calling g_date_time_unref()
   * when you are done with it.
   * 
   * @newin{2,26}
   * 
   * @param tv A TimeVal.
   * @return A new DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create_now_utc(const TimeVal& tv);

  
  /** Creates a new DateTime corresponding to the given date and time in
   * the time zone @a tz.
   * 
   * The @a year must be between 1 and 9999, @a month between 1 and 12 and @a day
   * between 1 and 28, 29, 30 or 31 depending on the month and the year.
   * 
   *  @a hour must be between 0 and 23 and @a minute must be between 0 and 59.
   * 
   *  @a seconds must be at least 0.0 and must be strictly less than 60.0.
   * It will be rounded down to the nearest microsecond.
   * 
   * If the given time is not representable in the given time zone (for
   * example, 02:30 on March 14th 2010 in Toronto, due to daylight savings
   * time) then the time will be rounded up to the nearest existing time
   * (in this case, 03:00).  If this matters to you then you should verify
   * the return value for containing the same as the numbers you gave.
   * 
   * In the case that the given time is ambiguous in the given time zone
   * (for example, 01:30 on November 7th 2010 in Toronto, due to daylight
   * savings time) then the time falling within standard (ie:
   * non-daylight) time is taken.
   * 
   * It not considered a programmer error for the values to this function
   * to be out of range, but in the case that they are, the function will
   * return <tt>nullptr</tt>.
   * 
   * You should release the return value by calling g_date_time_unref()
   * when you are done with it.
   * 
   * @newin{2,26}
   * 
   * @param tz A TimeZone.
   * @param year The year component of the date.
   * @param month The month component of the date.
   * @param day The day component of the date.
   * @param hour The hour component of the date.
   * @param minute The minute component of the date.
   * @param seconds The number of seconds past the minute.
   * @return A new DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create(const TimeZone& tz, int year, int month, int day, int hour, int minute, double seconds);
  
  /** Creates a new DateTime corresponding to the given date and time in
   * the local time zone.
   * 
   * This call is equivalent to calling g_date_time_new() with the time
   * zone returned by g_time_zone_new_local().
   * 
   * @newin{2,26}
   * 
   * @param year The year component of the date.
   * @param month The month component of the date.
   * @param day The day component of the date.
   * @param hour The hour component of the date.
   * @param minute The minute component of the date.
   * @param seconds The number of seconds past the minute.
   * @return A DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create_local(int year, int month, int day, int hour, int minute, double seconds);
  
  /** Creates a new DateTime corresponding to the given date and time in
   * UTC.
   * 
   * This call is equivalent to calling g_date_time_new() with the time
   * zone returned by g_time_zone_new_utc().
   * 
   * @newin{2,26}
   * 
   * @param year The year component of the date.
   * @param month The month component of the date.
   * @param day The day component of the date.
   * @param hour The hour component of the date.
   * @param minute The minute component of the date.
   * @param seconds The number of seconds past the minute.
   * @return A DateTime, or <tt>nullptr</tt>.
   */
  static DateTime create_utc(int year, int month, int day, int hour, int minute, double seconds);

  
  /** Creates a copy of @a datetime and adds the specified timespan to the copy.
   * 
   * @newin{2,26}
   * 
   * @param timespan A TimeSpan.
   * @return The newly created DateTime which should be freed with
   * g_date_time_unref().
   */
  DateTime add(TimeSpan timespan) const;
  
  /** Creates a copy of @a datetime and adds the specified number of years to the
   * copy. Add negative values to subtract years.
   * 
   * @newin{2,26}
   * 
   * @param years The number of years.
   * @return The newly created DateTime which should be freed with
   * g_date_time_unref().
   */
  DateTime add_years(int years) const;
  
  /** Creates a copy of @a datetime and adds the specified number of months to the
   * copy. Add negative values to subtract months.
   * 
   * @newin{2,26}
   * 
   * @param months The number of months.
   * @return The newly created DateTime which should be freed with
   * g_date_time_unref().
   */
  DateTime add_months(int months) const;
  
  /** Creates a copy of @a datetime and adds the specified number of weeks to the
   * copy. Add negative values to subtract weeks.
   * 
   * @newin{2,26}
   * 
   * @param weeks The number of weeks.
   * @return The newly created DateTime which should be freed with
   * g_date_time_unref().
   */
  DateTime add_weeks(int weeks) const;
  
  /** Creates a copy of @a datetime and adds the specified number of days to the
   * copy. Add negative values to subtract days.
   * 
   * @newin{2,26}
   * 
   * @param days The number of days.
   * @return The newly created DateTime which should be freed with
   * g_date_time_unref().
   */
  DateTime add_days(int days) const;
  
  /** Creates a copy of @a datetime and adds the specified number of hours.
   * Add negative values to subtract hours.
   * 
   * @newin{2,26}
   * 
   * @param hours The number of hours to add.
   * @return The newly created DateTime which should be freed with
   * g_date_time_unref().
   */
  DateTime add_hours(int hours) const;
  
  /** Creates a copy of @a datetime adding the specified number of minutes.
   * Add negative values to subtract minutes.
   * 
   * @newin{2,26}
   * 
   * @param minutes The number of minutes to add.
   * @return The newly created DateTime which should be freed with
   * g_date_time_unref().
   */
  DateTime add_minutes(int minutes) const;
  
  /** Creates a copy of @a datetime and adds the specified number of seconds.
   * Add negative values to subtract seconds.
   * 
   * @newin{2,26}
   * 
   * @param seconds The number of seconds to add.
   * @return The newly created DateTime which should be freed with
   * g_date_time_unref().
   */
  DateTime add_seconds(double seconds) const;
  
  /** Creates a new DateTime adding the specified values to the current date and
   * time in @a datetime. Add negative values to subtract.
   * 
   * @newin{2,26}
   * 
   * @param years The number of years to add.
   * @param months The number of months to add.
   * @param days The number of days to add.
   * @param hours The number of hours to add.
   * @param minutes The number of minutes to add.
   * @param seconds The number of seconds to add.
   * @return The newly created DateTime that should be freed with
   * g_date_time_unref().
   */
  DateTime add_full(int years, int months, int days, int hours, int minutes, double seconds) const;

  
  /** Calculates the difference in time between @a *this and @a other.  The
   * TimeSpan that is returned is effectively @a *this - @a other.
   *
   * @newin{2,26}
   *
   * @param other The other DateTime.
   * @return The difference between the two DateTime, as a time
   * span expressed in microseconds.
   */
  TimeSpan difference(const DateTime& other) const;

 
  /** A comparison function for DateTimes that is suitable
   * as a CompareFunc.
   *
   * @newin{2,26}
   *
   * @param other The DateTime to compare with.
   * @return -1, 0 or 1 if @a *this is less than, equal to or greater
   * than @a other.
   */
  int compare(const DateTime& other) const;

  
  /** Hashes @a datetime into a <tt>unsigned int</tt>, suitable for use within HashTable.
   * 
   * @newin{2,26}
   * 
   * @return A <tt>unsigned int</tt> containing the hash.
   */
  guint hash() const;

  
  /** Checks to see if @a *this and @a other are equal.
   *
   * Equal here means that they represent the same moment after converting
   * them to the same time zone.
   *
   * @newin{2,26}
   *
   * @param other The DateTime to compare with.
   * @return <tt>true</tt> if @a *this and @a other are equal.
   */
  bool equal(const DateTime& other) const;

  
  /** Retrieves the Gregorian day, month, and year of a given DateTime.
   * 
   * @newin{2,26}
   * 
   * @param year The return location for the gregorian year, or <tt>nullptr</tt>.
   * @param month The return location for the month of the year, or <tt>nullptr</tt>.
   * @param day The return location for the day of the month, or <tt>nullptr</tt>.
   */
  void get_ymd(int& year, int& month, int& day) const;
  
  /** Retrieves the year represented by @a datetime in the Gregorian calendar.
   * 
   * @newin{2,26}
   * 
   * @return The year represented by @a datetime.
   */
  int get_year() const;
  
  /** Retrieves the month of the year represented by @a datetime in the Gregorian
   * calendar.
   * 
   * @newin{2,26}
   * 
   * @return The month represented by @a datetime.
   */
  int get_month() const;
  
  /** Retrieves the day of the month represented by @a datetime in the gregorian
   * calendar.
   * 
   * @newin{2,26}
   * 
   * @return The day of the month.
   */
  int get_day_of_month() const;
  
  /** Returns the ISO 8601 week-numbering year in which the week containing
   *  @a datetime falls.
   * 
   * This function, taken together with g_date_time_get_week_of_year() and
   * g_date_time_get_day_of_week() can be used to determine the full ISO
   * week date on which @a datetime falls.
   * 
   * This is usually equal to the normal Gregorian year (as returned by
   * g_date_time_get_year()), except as detailed below:
   * 
   * For Thursday, the week-numbering year is always equal to the usual
   * calendar year.  For other days, the number is such that every day
   * within a complete week (Monday to Sunday) is contained within the
   * same week-numbering year.
   * 
   * For Monday, Tuesday and Wednesday occurring near the end of the year,
   * this may mean that the week-numbering year is one greater than the
   * calendar year (so that these days have the same week-numbering year
   * as the Thursday occurring early in the next year).
   * 
   * For Friday, Saturday and Sunday occurring near the start of the year,
   * this may mean that the week-numbering year is one less than the
   * calendar year (so that these days have the same week-numbering year
   * as the Thursday occurring late in the previous year).
   * 
   * An equivalent description is that the week-numbering year is equal to
   * the calendar year containing the majority of the days in the current
   * week (Monday to Sunday).
   * 
   * Note that January 1 0001 in the proleptic Gregorian calendar is a
   * Monday, so this function never returns 0.
   * 
   * @newin{2,26}
   * 
   * @return The ISO 8601 week-numbering year for @a datetime.
   */
  int get_week_numbering_year() const;
  
  /** Returns the ISO 8601 week number for the week containing @a datetime.
   * The ISO 8601 week number is the same for every day of the week (from
   * Moday through Sunday).  That can produce some unusual results
   * (described below).
   * 
   * The first week of the year is week 1.  This is the week that contains
   * the first Thursday of the year.  Equivalently, this is the first week
   * that has more than 4 of its days falling within the calendar year.
   * 
   * The value 0 is never returned by this function.  Days contained
   * within a year but occurring before the first ISO 8601 week of that
   * year are considered as being contained in the last week of the
   * previous year.  Similarly, the final days of a calendar year may be
   * considered as being part of the first ISO 8601 week of the next year
   * if 4 or more days of that week are contained within the new year.
   * 
   * @newin{2,26}
   * 
   * @return The ISO 8601 week number for @a datetime.
   */
  int get_week_of_year() const;
  
  /** Retrieves the ISO 8601 day of the week on which @a datetime falls (1 is
   * Monday, 2 is Tuesday... 7 is Sunday).
   * 
   * @newin{2,26}
   * 
   * @return The day of the week.
   */
  int get_day_of_week() const;
  
  /** Retrieves the day of the year represented by @a datetime in the Gregorian
   * calendar.
   * 
   * @newin{2,26}
   * 
   * @return The day of the year.
   */
  int get_day_of_year() const;
  
  /** Retrieves the hour of the day represented by @a datetime
   * 
   * @newin{2,26}
   * 
   * @return The hour of the day.
   */
  int get_hour() const;
  
  /** Retrieves the minute of the hour represented by @a datetime
   * 
   * @newin{2,26}
   * 
   * @return The minute of the hour.
   */
  int get_minute() const;
  
  /** Retrieves the second of the minute represented by @a datetime
   * 
   * @newin{2,26}
   * 
   * @return The second represented by @a datetime.
   */
  int get_second() const;
  
  /** Retrieves the microsecond of the date represented by @a datetime
   * 
   * @newin{2,26}
   * 
   * @return The microsecond of the second.
   */
  int get_microsecond() const;
  
  /** Retrieves the number of seconds since the start of the last minute,
   * including the fractional part.
   * 
   * @newin{2,26}
   * 
   * @return The number of seconds.
   */
  double get_seconds() const;
  
  /** Gives the Unix time corresponding to @a datetime, rounding down to the
   * nearest second.
   * 
   * Unix time is the number of seconds that have elapsed since 1970-01-01
   * 00:00:00 UTC, regardless of the time zone associated with @a datetime.
   * 
   * @newin{2,26}
   * 
   * @return The Unix time corresponding to @a datetime.
   */
  gint64 to_unix() const;
  
  /** Stores the instant in time that @a datetime represents into @a tv.
   * 
   * The time contained in a TimeVal is always stored in the form of
   * seconds elapsed since 1970-01-01 00:00:00 UTC, regardless of the time
   * zone associated with @a datetime.
   * 
   * On systems where 'long' is 32bit (ie: all 32bit systems and all
   * Windows systems), a TimeVal is incapable of storing the entire
   * range of values that DateTime is capable of expressing.  On those
   * systems, this function returns <tt>false</tt> to indicate that the time is
   * out of range.
   * 
   * On systems where 'long' is 64bit, this function never fails.
   * 
   * @newin{2,26}
   * 
   * @param tv A TimeVal to modify.
   * @return <tt>true</tt> if successful, else <tt>false</tt>.
   */
  bool to_timeval(TimeVal& tv) const;
  
  /** Determines the offset to UTC in effect at the time and in the time
   * zone of @a datetime.
   * 
   * The offset is the number of microseconds that you add to UTC time to
   * arrive at local time for the time zone (ie: negative numbers for time
   * zones west of GMT, positive numbers for east).
   * 
   * If @a datetime represents UTC time, then the offset is always zero.
   * 
   * @newin{2,26}
   * 
   * @return The number of microseconds that should be added to UTC to
   * get the local time.
   */
  TimeSpan get_utc_offset() const;
  
  /** Determines the time zone abbreviation to be used at the time and in
   * the time zone of @a datetime.
   * 
   * For example, in Toronto this is currently "EST" during the winter
   * months and "EDT" during the summer months when daylight savings
   * time is in effect.
   * 
   * @newin{2,26}
   * 
   * @return The time zone abbreviation. The returned
   * string is owned by the DateTime and it should not be
   * modified or freed.
   */
  Glib::ustring get_timezone_abbreviation() const;
  
  /** Determines if daylight savings time is in effect at the time and in
   * the time zone of @a datetime.
   * 
   * @newin{2,26}
   * 
   * @return <tt>true</tt> if daylight savings time is in effect.
   */
  bool is_daylight_savings() const;
  
  /** Create a new DateTime corresponding to the same instant in time as
   *  @a datetime, but in the time zone @a tz.
   * 
   * This call can fail in the case that the time goes out of bounds.  For
   * example, converting 0001-01-01 00:00:00 UTC to a time zone west of
   * Greenwich will fail (due to the year 0 being out of range).
   * 
   * You should release the return value by calling g_date_time_unref()
   * when you are done with it.
   * 
   * @newin{2,26}
   * 
   * @param tz The new TimeZone.
   * @return A new DateTime, or <tt>nullptr</tt>.
   */
  DateTime to_timezone(const TimeZone& tz) const;
  
  /** Creates a new DateTime corresponding to the same instant in time as
   *  @a datetime, but in the local time zone.
   * 
   * This call is equivalent to calling g_date_time_to_timezone() with the
   * time zone returned by g_time_zone_new_local().
   * 
   * @newin{2,26}
   * 
   * @return The newly created DateTime.
   */
  DateTime to_local() const;
  
  /** Creates a new DateTime corresponding to the same instant in time as
   *  @a datetime, but in UTC.
   * 
   * This call is equivalent to calling g_date_time_to_timezone() with the
   * time zone returned by g_time_zone_new_utc().
   * 
   * @newin{2,26}
   * 
   * @return The newly created DateTime.
   */
  DateTime to_utc() const;
  
  /** Creates a newly allocated string representing the requested @a format_str.
   * 
   * The format strings understood by this function are a subset of the
   * strftime() format language as specified by C99.  The \\%D, \\%U and \\%W
   * conversions are not supported, nor is the 'E' modifier.  The GNU
   * extensions \\%k, \\%l, \\%s and \\%P are supported, however, as are the
   * '0', '_' and '-' modifiers.
   * 
   * In contrast to strftime(), this function always produces a UTF-8
   * string, regardless of the current locale.  Note that the rendering of
   * many formats is locale-dependent and may not match the strftime()
   * output exactly.
   * 
   * The following format specifiers are supported:
   * 
   * - \\%a: the abbreviated weekday name according to the current locale
   * - \\%A: the full weekday name according to the current locale
   * - \\%b: the abbreviated month name according to the current locale
   * - \\%B: the full month name according to the current locale
   * - \\%c: the preferred date and time representation for the current locale
   * - \\%C: the century number (year/100) as a 2-digit integer (00-99)
   * - \\%d: the day of the month as a decimal number (range 01 to 31)
   * - \\%e: the day of the month as a decimal number (range  1 to 31)
   * - \\%F: equivalent to `%Y-%m-%d` (the ISO 8601 date format)
   * - \\%g: the last two digits of the ISO 8601 week-based year as a
   * decimal number (00-99). This works well with \\%V and \\%u.
   * - \\%G: the ISO 8601 week-based year as a decimal number. This works
   * well with \\%V and \\%u.
   * - \\%h: equivalent to \\%b
   * - \\%H: the hour as a decimal number using a 24-hour clock (range 00 to 23)
   * - \\%I: the hour as a decimal number using a 12-hour clock (range 01 to 12)
   * - \\%j: the day of the year as a decimal number (range 001 to 366)
   * - \\%k: the hour (24-hour clock) as a decimal number (range 0 to 23);
   * single digits are preceded by a blank
   * - \\%l: the hour (12-hour clock) as a decimal number (range 1 to 12);
   * single digits are preceded by a blank
   * - \\%m: the month as a decimal number (range 01 to 12)
   * - \\%M: the minute as a decimal number (range 00 to 59)
   * - \\%p: either "AM" or "PM" according to the given time value, or the
   * corresponding  strings for the current locale.  Noon is treated as
   * "PM" and midnight as "AM".
   * - \\%P: like \\%p but lowercase: "am" or "pm" or a corresponding string for
   * the current locale
   * - \\%r: the time in a.m. or p.m. notation
   * - \\%R: the time in 24-hour notation (\\%H:\\%M)
   * - \\%s: the number of seconds since the Epoch, that is, since 1970-01-01
   * 00:00:00 UTC
   * - \\%S: the second as a decimal number (range 00 to 60)
   * - \\%t: a tab character
   * - \\%T: the time in 24-hour notation with seconds (\\%H:\\%M:\\%S)
   * - \\%u: the ISO 8601 standard day of the week as a decimal, range 1 to 7,
   * Monday being 1. This works well with \\%G and \\%V.
   * - \\%V: the ISO 8601 standard week number of the current year as a decimal
   * number, range 01 to 53, where week 1 is the first week that has at
   * least 4 days in the new year. See g_date_time_get_week_of_year().
   * This works well with \\%G and \\%u.
   * - \\%w: the day of the week as a decimal, range 0 to 6, Sunday being 0.
   * This is not the ISO 8601 standard format -- use \\%u instead.
   * - \\%x: the preferred date representation for the current locale without
   * the time
   * - \\%X: the preferred time representation for the current locale without
   * the date
   * - \\%y: the year as a decimal number without the century
   * - \\%Y: the year as a decimal number including the century
   * - \\%z: the time zone as an offset from UTC (+hhmm)
   * - \\%:z: the time zone as an offset from UTC (+hh:mm).
   * This is a gnulib strftime() extension. Since: 2.38
   * - \\%::z: the time zone as an offset from UTC (+hh:mm:ss). This is a
   * gnulib strftime() extension. Since: 2.38
   * - \\%:::z: the time zone as an offset from UTC, with : to necessary
   * precision (e.g., -04, +05:30). This is a gnulib strftime() extension. Since: 2.38
   * - \\%Z: the time zone or name or abbreviation
   * - \\%\\%: a literal \\% character
   * 
   * Some conversion specifications can be modified by preceding the
   * conversion specifier by one or more modifier characters. The
   * following modifiers are supported for many of the numeric
   * conversions:
   * 
   * - O: Use alternative numeric symbols, if the current locale supports those.
   * - _: Pad a numeric result with spaces. This overrides the default padding
   * for the specifier.
   * - -: Do not pad a numeric result. This overrides the default padding
   * for the specifier.
   * - 0: Pad a numeric result with zeros. This overrides the default padding
   * for the specifier.
   * 
   * @newin{2,26}
   * 
   * @param format_str A valid UTF-8 string, containing the format for the
   * DateTime.
   * @return A newly allocated string formatted to the requested format
   * or <tt>nullptr</tt> in the case that there was an error.
   */
  Glib::ustring format(const Glib::ustring& format_str) const;


};

} // namespace Glib


namespace Glib
{

/** @relates Glib::DateTime
 * @param lhs The left-hand side
 * @param rhs The right-hand side
 */
inline void swap(DateTime& lhs, DateTime& rhs) noexcept
  { lhs.swap(rhs); }

} // namespace Glib

namespace Glib
{

  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Glib::DateTime
   */
Glib::DateTime wrap(GDateTime* object, bool take_copy = false);

} // namespace Glib


#endif /* _GLIBMM_DATETIME_H */

