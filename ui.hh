#ifndef UI_H
#define UI_H

#include <gtkmm.h>


class MainWindow: public Gtk::Window, Metronome {
  
  public:
    
    MainWindow(const Glib::RefPtr<Gtk::Application>& app);
    virtual ~MainWindow();


  private:
    
    Gdk::RGBA *light_pink_bg = new Gdk::RGBA("#CEB7B3");

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    void draw_aiguille(const Cairo::RefPtr<Cairo::Context>& cr);

    void on_BPM_value_changed();
    void on_combo_changed();
    void on_button_quit();
    // bool on_eventbox_button_press(GdkEventButton* button_event);
    bool on_eventbox_clicked(GdkEventButton* e);
    
    Glib::RefPtr<Gdk::Pixbuf> background_image;
    
    
    Gtk::ScrolledWindow app_Window;
    
    Gtk::VBox m_VBox;
    Gtk::EventBox m_EventBox;
    // Gtk::Image m_Led;
    // Gtk::DrawingArea area;
    
    Gtk::Label bpm_Label;
    
    Glib::RefPtr<Gtk::Adjustment> bpm_adjustment;  // WARNING Keep this line before bpm_Scale
    Gtk::HScale bpm_Scale;
    
    Gtk::ComboBoxText m_Combo;
    
    Gtk::HButtonBox m_ButtonBox;
    Gtk::Button button_Quit;
  
};

#endif  // UI_H
