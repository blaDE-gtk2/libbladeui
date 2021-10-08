/*
 * Copyright (c) 2007 The Xfce Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

/**
 * SECTION:libbladeui-config
 * @title: libbladeui config
 * @short_description: libbladeui config macros
 * @stability: Stable
 * @include: libbladeui/libbladeui.h
 *
 * Variables and functions to check the Libbladeui version.
 **/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libbladeui/libbladeui-config.h>
#include <libbladeui/libbladeui-alias.h>


/**
 * libbladeui_major_version:
 *
 * A constat that evaluates to the major version of libbladeui.
 *
 */
const guint libbladeui_major_version = LIBBLADEUI_MAJOR_VERSION;

/**
 * libbladeui_minor_version:
 *
 * A constat that evaluates to the minor version of libbladeui.
 *
 */
const guint libbladeui_minor_version = LIBBLADEUI_MINOR_VERSION;

/**
 * libbladeui_micro_version:
 *
 * A constat that evaluates to the micro version of libbladeui.
 *
 */
const guint libbladeui_micro_version = LIBBLADEUI_MICRO_VERSION;



/**
 * libbladeui_check_version:
 * @required_major: the required major version.
 * @required_minor: the required minor version.
 * @required_micro: the required micro version.
 *
 * Checks that the <systemitem class="library">libbladeui</systemitem> library
 * in use is compatible with the given version. Generally you would pass in
 * the constants #LIBBLADEUI_MAJOR_VERSION, #LIBBLADEUI_MINOR_VERSION and
 * #LIBBLADEUI_MICRO_VERSION as the three arguments to this function; that produces
 * a check that the library in use is compatible with the version of
 * <systemitem class="library">libbladeui</systemitem> the extension was
 * compiled against.
 *
 * <example>
 * <title>Checking the runtime version of the Libbladeui library</title>
 * <programlisting>
 * const gchar *mismatch;
 * mismatch = libbladeui_check_version (LIBBLADEUI_MAJOR_VERSION,
 *                                      LIBBLADEUI_MINOR_VERSION,
 *                                      LIBBLADEUI_MICRO_VERSION);
 * if (G_UNLIKELY (mismatch != NULL))
 *   g_error ("Version mismatch: %<!---->s", mismatch);
 * </programlisting>
 * </example>
 *
 * Return value: %NULL if the library is compatible with the given version,
 *               or a string describing the version mismatch. The returned
 *               string is owned by the library and must not be freed or
 *               modified by the caller.
 **/
const gchar *
libbladeui_check_version (guint required_major,
                          guint required_minor,
                          guint required_micro)
{
  if (required_major > LIBBLADEUI_MAJOR_VERSION)
    return "Libbladeui version too old (major mismatch)";
  if (required_major < LIBBLADEUI_MAJOR_VERSION)
    return "Libbladeui version too new (major mismatch)";
  if (required_minor > LIBBLADEUI_MINOR_VERSION)
    return "Libbladeui version too old (minor mismatch)";
  if (required_minor == LIBBLADEUI_MINOR_VERSION && required_micro > LIBBLADEUI_MICRO_VERSION)
    return "Libbladeui version too old (micro mismatch)";
  return NULL;
}



#define __LIBBLADEUI_CONFIG_C__
#include <libbladeui/libbladeui-aliasdef.c>
