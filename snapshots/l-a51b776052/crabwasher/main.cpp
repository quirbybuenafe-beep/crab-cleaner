#include <gtkmm.h>
#include <iostream>

class MyWindow : public Gtk::Window {
public:
    MyWindow() {
        set_title("GTKmm Example");
        set_default_size(300, 200);

        // Set up button and connect signal
        m_button.set_label("Click Me");
        m_button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));

        // Add button to the window
        add(m_button);

        // Show all widgets
        show_all_children();
    }

    virtual ~MyWindow() {}

protected:
    // Signal handler for button click
    void on_button_clicked() {
        std::cout << "Button clicked!" << std::endl;
    }

private:
    Gtk::Button m_button;
};

int main(int argc, char *argv[]) {
    // Initialize GTKmm
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    // Create and run the window
    MyWindow window;

    // Run the application
    return app->run(window);
}
