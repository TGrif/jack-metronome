#include "ui.hh"
#include "tempo.hh"


MainWindow::MainWindow (const Glib::RefPtr<Gtk::Application>& app):
 bpm_adjustment(Gtk::Adjustment::create(BPM, BPM_min, BPM_max, 1, 100, 0)),
 bpm_Label("BPM"),
 bpm_Scale(bpm_adjustment),
 button_Quit(Gtk::Stock::QUIT) {
  
  // set_border_width(0);
  // set_default_size(400, 200);

  add(m_VBox);
  
  m_VBox.add(m_EventBox);
  m_EventBox.set_size_request(500, 500);
  m_EventBox.override_background_color(*light_pink_bg);
  
  // GtkWidget *drawing_area;
  // drawing_area->set_size_request(400, 400);

  // g_signal_connect(m_EventBox, "button-press-event", G_CALLBACK(clicked), NULL);
  // m_EventBox.add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
  m_EventBox.signal_button_release_event()
            .connect(sigc::mem_fun(*this, &MainWindow::on_eventbox_clicked));
  
  // area.set_size_request(400, 400);
  // area.set_line_width(10.0);
  // m_image = Gdk::Pixbuf::create_from_resource("assets/led_red.png");
  
  // m_EventBox.add(*drawing_area);
  
  
  // m_Led = gtk_image_new_from_icon_name ("gtk-yes", 128, 0);
  
  // new_from_icon_name  'gtk-yes'  'gtk-no'
  // Gtk.Image.new_from_icon_name("document-open", Gtk.IconSize.LARGE_TOOLBAR)   //TODO utiliser les icones et supprimer les images led
  

  // m_VBox.add(m_Led);

  app_Window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_VBox.pack_start(app_Window);
  m_VBox.set_spacing(18);
  
  for (auto const& t : tempo) {
    m_Combo.append(t.second);
  }
  m_Combo.set_active(3);
  m_Combo.signal_changed()
         .connect(sigc::mem_fun(*this, &MainWindow::on_combo_changed));
  m_VBox.pack_start(m_Combo);
  
  m_VBox.add(bpm_Label);
  
  bpm_Scale.set_digits(0);
  bpm_Scale.set_value_pos(Gtk::POS_TOP);
  bpm_Scale.signal_value_changed()
           .connect(sigc::mem_fun(*this, &MainWindow::on_BPM_value_changed));
  m_VBox.pack_start(bpm_Scale);

  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_spacing(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
  
  button_Quit.signal_clicked()
             .connect(sigc::mem_fun(*this, &MainWindow::on_button_quit));
  m_ButtonBox.pack_start(button_Quit, Gtk::PACK_SHRINK);
  
  show_all_children();

}

MainWindow::~MainWindow() {
  std::cout << "Bye." << std::endl;
}

bool MainWindow::on_draw (const Cairo::RefPtr<Cairo::Context>& cr) {
  try {
    background_image = Gdk::Pixbuf::create_from_file("assets/metronome.png");
  } catch (const Gio::ResourceError& ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError& ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }
  
  Gdk::Cairo::set_source_pixbuf(cr, background_image, 100, 80);
  cr->rectangle(110, 90, background_image->get_width(), background_image->get_height());
  cr->fill();
  
  draw_aiguille(cr);
  
  return true;
}

void MainWindow::draw_aiguille (const Cairo::RefPtr<Cairo::Context>& cr) {
  
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  cr->set_line_width(3.0);
  cr->set_source_rgb(0.0, 0.0, 0.0);

  cr->move_to(xc, yc);
  cr->line_to(xc-150, 150);

  cr->stroke();
}

bool MainWindow::on_eventbox_clicked (GdkEventButton* ev) {
  std::cout << "Clicked! \n" << std::endl;
  std::cout << ev->x << " " << ev->y << std::endl;
  return true;
}

void MainWindow::on_BPM_value_changed() {
  int bpm_value = bpm_adjustment->get_value();
  Metronome::change_BPM(bpm_value);
  int combo_index = get_index(bpm_value);
  m_Combo.set_active(combo_index);
}

void MainWindow::on_combo_changed() {
  Glib::ustring text = m_Combo.get_active_text();
  bpm_Scale.set_value(get_bpm(text));
  Metronome::change_BPM(bpm_adjustment->get_value());
}

void MainWindow::on_button_quit() {
  hide();
}
