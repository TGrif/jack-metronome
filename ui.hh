#ifndef UI_H
#define UI_H

#include <gtkmm.h>


class MainWindow: public Gtk::Window, Metronome {
  
  public:
    
    MainWindow(const Glib::RefPtr<Gtk::Application>& app);
    virtual ~MainWindow();


  protected:

    void on_BPM_value_changed();
    void change_BPM_value(double val);
    void on_button_quit();


    Glib::RefPtr<Gtk::Adjustment> bpm_adjustment;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;  // https://developer.gnome.org/gtkmm-tutorial/stable/combobox-example-full.html.en
    

    Gtk::ScrolledWindow app_Window;
    
    Gtk::VBox m_VBox;
    // Gtk::Box m_HBox_Digits;
    
    // Gtk::TextView m_TextView;
    Gtk::Label bpm_Label;
    Gtk::HScale bpm_Scale;
    
    Gtk::ComboBox m_Combo;
    
    Gtk::HButtonBox m_ButtonBox;
    Gtk::Button button_Quit;
  
};

#endif  // UI_H
