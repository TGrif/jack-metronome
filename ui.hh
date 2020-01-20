#ifndef UI_H
#define UI_H

#include <gtkmm.h>


class MainWindow: public Gtk::Window, Metronome {
  
  public:
    
    MainWindow(const Glib::RefPtr<Gtk::Application>& app);
    virtual ~MainWindow();


  private:

    void on_BPM_value_changed();
    void on_combo_changed();
    void on_button_quit();


    Glib::RefPtr<Gtk::Adjustment> bpm_adjustment;
    

    Gtk::ScrolledWindow app_Window;
    
    Gtk::VBox m_VBox;

    Gtk::Label bpm_Label;
    Gtk::HScale bpm_Scale;
    
    Gtk::ComboBoxText m_Combo;
    
    Gtk::HButtonBox m_ButtonBox;
    Gtk::Button button_Quit;
  
};

#endif  // UI_H
