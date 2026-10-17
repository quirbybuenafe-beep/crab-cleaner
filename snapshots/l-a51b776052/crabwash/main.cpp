#include <gtk.h>  // GTKmm header

class MyWindow : public Gtk::Window {
public:
    MyWindow() {
        // Set window title and size
        set_title("Simple GTKmm Example");
        set_default_size(400, 200);

        // Create and set up the label
        m_label.set_text("Hello, GTKmm!");
        m_box.pack_start(m_label);

        // Create and set up the button
        m_button.set_label("Click Me");
        m_button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));
        m_box.pack_start(m_button);

        // Add the box to the window
        add(m_box);

        // Show all widgets inside the window
        show_all_children();
    }

    virtual ~MyWindow() {}

protected:
    void on_button_clicked() {
        // Change the label text when the button is clicked
        m_label.set_text("Button Clicked!");
    }

private:
    Gtk::Box m_box{Gtk::ORIENTATION_VERTICAL};  // A container for the label and button
    Gtk::Label m_label;                         // A label widget
    Gtk::Button m_button;                       // A button widget
};

int main(int argc, char *argv[]) {
    // Initialize the GTKmm application
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    // Create an instance of the window
    MyWindow window;

    // Run the GTKmm application
    return app->run(window);
}
