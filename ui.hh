#ifndef UI_H
#define UI_H

#include <gtkmm.h>


class MainWindow: public Gtk::Window {
  
  public:
    
    MainWindow();
    virtual ~MainWindow();


  protected:

    void on_BPM_value_changed();
    void on_button_quit();


    Glib::RefPtr<Gtk::Adjustment> bpm_adjustment;


    Gtk::ScrolledWindow app_Window;
    
    Gtk::VBox m_VBox;
    Gtk::Box m_HBox_Digits;
    
    // Gtk::TextView m_TextView;

    Gtk::HScale bpm_Scale;
    
    Gtk::HButtonBox m_ButtonBox;
    Gtk::Button button_Quit;
  
};

#endif  // UI_H
