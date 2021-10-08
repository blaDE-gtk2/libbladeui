/*-
 * vi:set et ai sts=2 sw=2 cindent:
 *
 * Copyright (c) 2016 Eric Koegel <eric@xfce.org>
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
 * You should have received a copy of the GNU Library General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>

#include <gtk/gtk.h>
#include <glib.h>
#include <libbladeui/libbladeui.h>


static const gchar *APP_NAME = "libbladeui: Test";

static void
main_window_destroy (GtkWidget *window)
{
  gtk_main_quit ();
}

static void
show_xfce_message_dialog (GtkButton *button,
                          gpointer unused)
{
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size ("../icons/48x48/xfce4-logo.png", 24, 24, NULL);

#if GTK_CHECK_VERSION (3, 0, 0)
  xfce_message_dialog (NULL, "Question - Gtk3 version with no deprecated symbols",
                       "dialog-question",
                       "There are unsaved modifications",
                       "The menu has been modified, do you want to save it before quitting?",
                       XFCE_BUTTON_TYPE_MIXED, "document-save", "Save", GTK_RESPONSE_YES,
                       XFCE_BUTTON_TYPE_MIXED, "edit-delete", "Forget modifications", GTK_RESPONSE_APPLY,
                       XFCE_BUTTON_TYPE_PIXBUF, pixbuf, "Quit", GTK_RESPONSE_NO,
                       XFCE_BUTTON_TYPE_MIXED, "process-stop", "Cancel", GTK_RESPONSE_CANCEL,
                       NULL);
#endif

/* ignore those warnings so it's easy to see what the default Gtk2 version
 * looks like in Gtk3 with the stock icons */
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  xfce_message_dialog (NULL, "Question - Gtk2 version",
                       GTK_STOCK_DIALOG_QUESTION,
                       "There are unsaved modifications",
                       "The menu has been modified, do you want to save it before quitting?",
                       GTK_STOCK_SAVE, GTK_RESPONSE_YES,
                       XFCE_BUTTON_TYPE_MIXED, GTK_STOCK_DELETE, "Forget modifications", GTK_RESPONSE_APPLY,
                       XFCE_BUTTON_TYPE_PIXBUF, pixbuf, "Quit", GTK_RESPONSE_NO,
                       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                       NULL);
G_GNUC_END_IGNORE_DEPRECATIONS

  if (pixbuf != NULL)
    {
      g_object_unref (G_OBJECT (pixbuf));
    }
}

static void
show_xfce_dialog_show_help (GtkButton *button,
                            gpointer unused)
{
  xfce_dialog_show_help (NULL, "xfce4-session", "preferences", NULL);
}

static void
show_xfce_dialog_show_help_with_version (GtkButton *button,
                                         gpointer unused)
{
  xfce_dialog_show_help_with_version (NULL, "blade-pm", "start", NULL, "4.12");
}

static void
remove_auto_online (GtkButton *button,
                    gpointer unused)
{
  XfceRc   *rc;
  gboolean  response;

#if GTK_CHECK_VERSION (3, 0, 0)
  response = xfce_dialog_confirm (NULL, "system-run", "Execute",
                                  "Removing this will enable the show help "
                                  "dialogs to appear. Do you want to do this?",
                                  "Remove auto-online in rc file? (Gtk3)");
#endif

/* ignore those warnings so it's easy to see what the default Gtk2 version
 * looks like in Gtk3 with the stock icons */
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  response = xfce_dialog_confirm (NULL, GTK_STOCK_EXECUTE, "Execute",
                                  "Removing this will enable the show help "
                                  "dialogs to appear. Do you want to do this?",
                                  "Remove auto-online in rc file? (Gtk2)");
G_GNUC_END_IGNORE_DEPRECATIONS

  if (response == FALSE)
    return;

  rc = xfce_rc_config_open (XFCE_RESOURCE_CONFIG, "xfce4/help.rc", FALSE);
  if (rc != NULL)
    {
      xfce_rc_write_bool_entry (rc, "auto-online", FALSE);
      xfce_rc_close (rc);
    }
}

static void
show_xfce_dialog_show_info (GtkButton *button,
                            gpointer unused)
{
  xfce_dialog_show_info(NULL, NULL, "%s", "xfburn_transcoder_get_description (priv->trans)");
}

static void
show_xfce_dialog_show_warning (GtkButton *button,
                               gpointer unused)
{
  xfce_dialog_show_warning(NULL, NULL, _("A file named \"%s\" already exists in this directory, the file hasn't been added."), "name");
}

static void
show_xfce_dialog_show_error (GtkButton *button,
                             gpointer unused)
{
  GError *error = NULL;

  g_set_error (&error, G_FILE_ERROR, G_FILE_ERROR_NOENT, "This isn't a real error");

  xfce_dialog_show_error (NULL, error, _("Failed to migrate the old bar configuration"));

  g_clear_error (&error);
}

static void
show_xfce_dialog_confirm (GtkButton *button,
                          gpointer unused)
{
#if GTK_CHECK_VERSION (3, 0, 0)
  xfce_dialog_confirm (NULL, "system-run", "Execute",
                       "Do you want to start the bar? If you do, make sure "
                       "you save the session on logout, so the bar is "
                       "automatically started the next time you login.",
                       "No running instance of %s was found", G_LOG_DOMAIN);
#endif

/* ignore those warnings so it's easy to see what the default Gtk2 version
 * looks like in Gtk3 with the stock icons */
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  xfce_dialog_confirm (NULL, GTK_STOCK_EXECUTE, "Execute",
                       "Do you want to start the bar? If you do, make sure "
                       "you save the session on logout, so the bar is "
                       "automatically started the next time you login.",
                       "No running instance of %s was found", G_LOG_DOMAIN);
G_GNUC_END_IGNORE_DEPRECATIONS
}


static void
close_window (GtkDialog *dialog,
              gint       response_id,
              gpointer   user_data)
{
  gtk_widget_destroy (GTK_WIDGET (dialog));
}

static void
show_xfce_titled_dialog_new_with_buttons (GtkButton *button,
                                          gpointer unused)
{
  GtkWidget *dialog_gtk2;

#if GTK_CHECK_VERSION (3, 0, 0)
  GtkWidget *dialog_gtk3;

  dialog_gtk3 = xfce_titled_dialog_new_with_buttons ("Settings Editor (Gtk3)", NULL,
                                                GTK_DIALOG_DESTROY_WITH_PARENT,
                                                "gtk-help", GTK_RESPONSE_HELP,
                                                "gtk-close", GTK_RESPONSE_OK,
                                                NULL);

  xfce_titled_dialog_set_subtitle (XFCE_TITLED_DIALOG (dialog_gtk3),
                                   _("Customize settings stored by Blconf"));

  gtk_window_set_icon_name (GTK_WINDOW (dialog_gtk3), "preferences-system");
  gtk_window_set_type_hint (GTK_WINDOW (dialog_gtk3), GDK_WINDOW_TYPE_HINT_NORMAL);

  g_signal_connect (dialog_gtk3, "response", G_CALLBACK (close_window), NULL);

  gtk_widget_show_all (dialog_gtk3);
#endif

/* ignore those warnings so it's easy to see what the default Gtk2 version
 * looks like in Gtk3 with the stock icons */
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  dialog_gtk2 = xfce_titled_dialog_new_with_buttons ("Settings Editor (Gtk2)", NULL,
                                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                                     GTK_STOCK_HELP, GTK_RESPONSE_HELP,
                                                     GTK_STOCK_CLOSE, GTK_RESPONSE_OK,
                                                     NULL);

  xfce_titled_dialog_set_subtitle (XFCE_TITLED_DIALOG (dialog_gtk2),
                                   _("Customize settings stored by Blconf"));

  gtk_window_set_icon_name (GTK_WINDOW (dialog_gtk2), "preferences-system");
  gtk_window_set_type_hint (GTK_WINDOW (dialog_gtk2), GDK_WINDOW_TYPE_HINT_NORMAL);

  g_signal_connect (dialog_gtk2, "response", G_CALLBACK (close_window), NULL);

  gtk_widget_show_all (dialog_gtk2);
G_GNUC_END_IGNORE_DEPRECATIONS
}

static void
show_xfce_titled_dialog_new_with_mixed_buttons (GtkButton *button,
                                                gpointer unused)
{
  GtkWidget *dialog_gtk2;

#if GTK_CHECK_VERSION (3, 0, 0)
  GtkWidget *dialog_gtk3;

  dialog_gtk3 = xfce_titled_dialog_new_with_mixed_buttons ("Settings Editor (Gtk3)", NULL,
                                                           GTK_DIALOG_DESTROY_WITH_PARENT,
                                                           "help-browser", "Help", GTK_RESPONSE_HELP,
                                                           "window-close", "Close", GTK_RESPONSE_OK,
                                                           "weather-snow", "Snow!", GTK_RESPONSE_APPLY,
                                                           "", "no icon", GTK_RESPONSE_CANCEL,
                                                           NULL);

  xfce_titled_dialog_set_subtitle (XFCE_TITLED_DIALOG (dialog_gtk3),
                                   _("Customize settings stored by Blconf"));

  gtk_window_set_icon_name (GTK_WINDOW (dialog_gtk3), "preferences-system");
  gtk_window_set_type_hint (GTK_WINDOW (dialog_gtk3), GDK_WINDOW_TYPE_HINT_NORMAL);

  g_signal_connect (dialog_gtk3, "response", G_CALLBACK (close_window), NULL);

  gtk_widget_show_all (dialog_gtk3);
#endif

/* ignore those warnings so it's easy to see what the default Gtk2 version
 * looks like in Gtk3 with the stock icons */
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  dialog_gtk2 = xfce_titled_dialog_new_with_mixed_buttons ("Settings Editor (Gtk2)", NULL,
                                                           GTK_DIALOG_DESTROY_WITH_PARENT,
                                                           GTK_STOCK_HELP, "Help", GTK_RESPONSE_HELP,
                                                           GTK_STOCK_CLOSE, "Close", GTK_RESPONSE_OK,
                                                           "weather-snow", "Snow?", GTK_RESPONSE_APPLY,
                                                           "", "no icon", GTK_RESPONSE_CANCEL,
                                                           NULL);

  xfce_titled_dialog_set_subtitle (XFCE_TITLED_DIALOG (dialog_gtk2),
                                   _("Customize settings stored by Blconf"));

  gtk_window_set_icon_name (GTK_WINDOW (dialog_gtk2), "preferences-system");
  gtk_window_set_type_hint (GTK_WINDOW (dialog_gtk2), GDK_WINDOW_TYPE_HINT_NORMAL);

  g_signal_connect (dialog_gtk2, "response", G_CALLBACK (close_window), NULL);

  gtk_widget_show_all (dialog_gtk2);
G_GNUC_END_IGNORE_DEPRECATIONS
}

static void
show_xfce_gdk_screen_get_active (GtkButton *button,
                                 gpointer unused)
{
  gint       monitor_num;
  GdkScreen *screen;

  screen = xfce_gdk_screen_get_active (&monitor_num);

  xfce_dialog_show_info(NULL, NULL, "monitor num: %d of %d",
                        monitor_num, gdk_screen_get_n_monitors (screen));
}



static void
create_main_window (void)
{
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *button;

  /* Create main window */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), APP_NAME);
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (window), 12);
  gtk_widget_show (window);

  /* Exit main loop when when the window is closed */
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (main_window_destroy), NULL);

  /* Create the box to hold all the stuff */
#if GTK_CHECK_VERSION (3, 0, 0)
  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
#else
  box = gtk_vbox_new (FALSE, 0);
#endif
  gtk_container_add (GTK_CONTAINER (window), box);
  gtk_widget_show (box);

  /* Create buttons */

  /* xfce_message_dialog */
  button = gtk_button_new_with_label ("show xfce_message_dialog");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_message_dialog), NULL);

  /* xfce_dialog_show_help */
  button = gtk_button_new_with_label ("show xfce_dialog_show_help");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_help), NULL);

  /* xfce_dialog_show_help_with_version */
  button = gtk_button_new_with_label ("show xfce_dialog_show_help_with_version");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_help_with_version), NULL);

  /* remove auto-online check from rc file */
  button = gtk_button_new_with_label ("remove auto-online check from rc file");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (remove_auto_online), NULL);

  /* xfce_dialog_show_info */
  button = gtk_button_new_with_label ("show xfce_dialog_show_info");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_info), NULL);

  /* xfce_dialog_show_warning */
  button = gtk_button_new_with_label ("show xfce_dialog_show_warning");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_warning), NULL);

  /* xfce_dialog_show_error */
  button = gtk_button_new_with_label ("show xfce_dialog_show_error");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_error), NULL);

  /* xfce_dialog_confirm */
  button = gtk_button_new_with_label ("show xfce_dialog_confirm");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_confirm), NULL);

  /* xfce_titled_dialog_new_with_buttons */
  button = gtk_button_new_with_label ("show xfce_titled_dialog_new_with_buttons");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_titled_dialog_new_with_buttons), NULL);

  /* xfce_titled_dialog_new_with_mixed_buttons */
  button = gtk_button_new_with_label ("show xfce_titled_dialog_new_with_mixed_buttons");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_titled_dialog_new_with_mixed_buttons), NULL);

  /* xfce_gdk_screen_get_active */
  button = gtk_button_new_with_label ("show xfce_gdk_screen_get_active");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_gdk_screen_get_active), NULL);
}



gint
main (gint    argc,
      gchar **argv)
{
  gint    exit_code = EXIT_SUCCESS;

  /* Initialize GTK+ */
  gtk_init (&argc, &argv);

  /* create the main window */
  create_main_window ();

  /* Enter main loop */
  gtk_main ();

  return exit_code;
}
