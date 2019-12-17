#ifndef UI_H
#define UI_H

#include <gtkmm.h>


class MainWindow: public Gtk::Window {
  
  public:
    
    MainWindow();
    virtual ~MainWindow();


  protected:

    // void fill_buffers();
    
    //Signal handlers:
    void on_button_quit();
    // void on_button_buffer1();
    // void on_button_buffer2();

    //Child widgets:
    Gtk::VBox m_VBox;

    Gtk::ScrolledWindow m_ScrolledWindow;
    // Gtk::TextView m_TextView;
    
    // Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer1, m_refTextBuffer2;

    Gtk::HButtonBox m_ButtonBox;
    Gtk::Button m_Button_Quit;//, m_Button_Buffer1, m_Button_Buffer2;
  
};

#endif  // UI_H
