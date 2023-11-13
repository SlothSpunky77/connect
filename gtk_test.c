#include <gtk/gtk.h>

void clear_text(GtkTextView *text_view)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    gtk_text_buffer_set_text(buffer, "", -1);
}

void display_ascii_art(GtkContainer *container) {
    // ASCII art
    const char *ascii_art =
        "                _                                      _     \n"
        "               | |                                    | |    \n"
        " __      ____ _| |_ __ _   _ ___   _ __ ___  _   _ ___| |__  \n"
        " \\ \\ /\\ / / _` | | '__| | | / __| | '_ ` _ \\| | | / __| '_ \\ \n"
        "  \\ V  V / (_| | | |  | |_| \\__ \\ | | | | | | |_| \\__ \\ | | |\n"
        "   \\_/\\_/ \\__,_|_|_|   \\__,_|___/ |_| |_| |_|\\__,_|___/_| |_|\n";

    GtkWidget *label = gtk_label_new(ascii_art);
    gtk_container_add(container, label);
}

void on_button_clicked(GtkWidget *widget, gpointer data)
{
    GtkEntry *entry1 = GTK_ENTRY(data);
    const char *text1 = gtk_entry_get_text(entry1);
    double num1 = atof(text1);

    GtkEntry *entry2 = GTK_ENTRY(g_object_get_data(G_OBJECT(widget), "entry2"));
    const char *text2 = gtk_entry_get_text(entry2);
    double num2 = atof(text2);

    double sum = num1 + num2;
    GtkTextView *text_view = GTK_TEXT_VIEW(g_object_get_data(G_OBJECT(widget), "text_view"));
    clear_text(text_view);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    char result_text[50];
    snprintf(result_text, sizeof(result_text), "The sum is: %.2f", sum);
    gtk_text_buffer_set_text(buffer, result_text, -1);

    // Open a new window
    GtkWidget *new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window), "New Window");
    gtk_window_set_default_size(GTK_WINDOW(new_window), 200, 100);

    // Create a label for the new window
    //GtkWidget *label = gtk_label_new("This is a new window!");
    // Add the label to the new window
    //gtk_container_add(GTK_CONTAINER(new_window), label);

    display_ascii_art(GTK_CONTAINER(new_window));

    // Show all widgets in the new window
    gtk_widget_show_all(new_window);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Connect!");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 300, 200);

    GtkWidget *entry1 = gtk_entry_new();
    GtkWidget *entry2 = gtk_entry_new();
    GtkWidget *entry3 = gtk_entry_new();
    GtkWidget *important = gtk_label_new("Important information:\nRow and column values must be above '6'.\nNumber of players 'x' must adhere to (1<x<6).");
    GtkWidget *label1 = gtk_label_new("Enter the number of rows:");
    GtkWidget *label2 = gtk_label_new("Enter the number of columns:");
    GtkWidget *label3 = gtk_label_new("Enter the number of players:");
    GtkWidget *button = gtk_button_new_with_label("accept");

    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    gtk_grid_attach(GTK_GRID(grid), important, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label3, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry3, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), text_view, 0, 5, 1, 1);

    g_object_set_data(G_OBJECT(button), "entry2", entry2);
    g_object_set_data(G_OBJECT(button), "text_view", text_view);

    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry1);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
