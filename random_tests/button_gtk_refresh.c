#include <gtk/gtk.h>

static int counter = 0;
GtkWidget *text_view; // The GtkTextView widget

void clear_text() {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "", -1);
}

void append_text(const char *text) {
    clear_text();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter iter;

    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, text, -1);
}

void greet(GtkWidget *widget, gpointer data) {
    gchar message[100];
    g_snprintf(message, sizeof(message), "%s clicked %d times\n", (char *)data, ++counter);
    append_text(message);
}

void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *scrolled_window; // The scrolled window for the text view

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    button = gtk_button_new_with_label("Click Me!");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(greet), "button");

    // Create a GtkTextView widget and put it in a scrolled window
    text_view = gtk_text_view_new();
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // Set the text view as read-only
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

    // Add the button and the scrolled window to a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    // Add the vertical box to the main window
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
