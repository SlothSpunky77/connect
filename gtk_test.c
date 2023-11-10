#include <gtk/gtk.h>

void clear_text(GtkTextView *text_view) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    gtk_text_buffer_set_text(buffer, "", -1);
}

void on_button_clicked(GtkWidget *widget, gpointer data) {
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

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "The sum is: %.2f", sum);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Add Numbers");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 300, 200);

    GtkWidget *entry1 = gtk_entry_new();
    GtkWidget *entry2 = gtk_entry_new();

    GtkWidget *label1 = gtk_label_new("Number 1:");
    GtkWidget *label2 = gtk_label_new("Number 2:");

    GtkWidget *button = gtk_button_new_with_label("Add");

    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), text_view, 0, 3, 1, 1);

    g_object_set_data(G_OBJECT(button), "entry2", entry2);
    g_object_set_data(G_OBJECT(button), "text_view", text_view);

    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry1);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
