#include <gtk/gtk.h>
#include <iostream>

class CleaningWindow : public Gtk::Window {
public:
    CleaningWindow();
    virtual ~CleaningWindow() {}

private:
    Gtk::Box box;
    Gtk::Label speedLabel, lengthLabel, resultLabel;
    Gtk::Entry speedEntry, lengthEntry;
    Gtk::Button calculateButton, resetButton;
    Gtk::ComboBoxText unitComboBox;

    void on_calculate_button_clicked();
    void on_reset_button_clicked();
};

CleaningWindow::CleaningWindow() {
    set_title("Conveyor Cleaning System");
    set_default_size(300, 200);

    // Add widgets
    box.set_orientation(Gtk::ORIENTATION_VERTICAL);
    add(box);

    speedLabel.set_text("Sprayer Speed (m/min):");
    box.pack_start(speedLabel);

    speedEntry.set_placeholder_text("Default: 30");
    box.pack_start(speedEntry);

    lengthLabel.set_text("Conveyor Length:");
    box.pack_start(lengthLabel);

    lengthEntry.set_placeholder_text("Enter in meters or feet");
    box.pack_start(lengthEntry);

    unitComboBox.append("Meters");
    unitComboBox.append("Feet");
    unitComboBox.set_active(0);
    box.pack_start(unitComboBox);

    calculateButton.set_label("Calculate");
    calculateButton.signal_clicked().connect(sigc::mem_fun(*this, &CleaningWindow::on_calculate_button_clicked));
    box.pack_start(calculateButton);

    resetButton.set_label("Reset");
    resetButton.signal_clicked().connect(sigc::mem_fun(*this, &CleaningWindow::on_reset_button_clicked));
    box.pack_start(resetButton);

    resultLabel.set_text("Result:");
    box.pack_start(resultLabel);

    show_all_children();
}

void CleaningWindow::on_calculate_button_clicked() {
    double speed = 30.0; // Default speed
    double length;
    std::string unit = unitComboBox.get_active_text();

    try {
        if (!speedEntry.get_text().empty())
            speed = std::stod(speedEntry.get_text());
        length = std::stod(lengthEntry.get_text());

        if (unit == "Feet") {
            length *= 0.3048; // Convert feet to meters
        }

        double time = length / speed; // Time in minutes
        resultLabel.set_text("Cleaning Time: " + std::to_string(time) + " minutes");
    } catch (...) {
        resultLabel.set_text("Error: Invalid input.");
    }
}

void CleaningWindow::on_reset_button_clicked() {
    speedEntry.set_text("");
    lengthEntry.set_text("");
    unitComboBox.set_active(0);
    resultLabel.set_text("Result:");
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    CleaningWindow window;
    return app->run(window);
}
