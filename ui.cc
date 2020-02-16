#include "ui.hh"

#include "tempo.hh"
#include "dial.hh"


MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application>& app):
 bpm_adjustment(Gtk::Adjustment::create(BPM, BPM_min, BPM_max, 1, 100, 0)),
 bpm_Label("BPM"),
 bpm_Scale(bpm_adjustment),
 button_Quit(Gtk::Stock::QUIT) {
  
  // set_border_width(0);
  // set_default_size(400, 200);

  add(m_VBox);
  
  app_Window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  
  m_EventBox.set_size_request(400, 400);
  m_EventBox.override_background_color(*light_pink_bg);
  m_EventBox.signal_button_release_event()
            .connect(sigc::mem_fun(*this, &MainWindow::on_eventbox_clicked));
  m_VBox.add(m_EventBox);
  
  m_VBox.pack_start(app_Window);
  m_VBox.set_spacing(18);
  
  for (auto const& t: tempo) {
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

bool MainWindow::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  try {
    background_image = Gdk::Pixbuf::create_from_file("assets/metronome.png");
  } catch (const Gio::ResourceError& ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError& ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }
  
  // m_Led = Gdk::Pixbuf::create_from_file("assets/led_red.png");
  // m_Led->copy_area(0,0,200,200,background_image,50,50);
  
  Gdk::Cairo::set_source_pixbuf(cr, background_image, 0.0, 0.0);
  cr->rectangle(0.0, 0.0, background_image->get_width(), background_image->get_height());
  
  cr->fill();
  
  draw_needle(cr, get_coordinate(BPM).first, get_coordinate(BPM).second);
  queue_draw();
  
  return true;
}

void MainWindow::draw_needle(const Cairo::RefPtr<Cairo::Context>& cr, int x, int y) {
  
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  
  int xc, yc;
  xc = width / 2;
  yc = height / 2 - 110;

  cr->set_line_width(3.0);
  cr->set_source_rgb(0.0, 0.0, 0.0);

  cr->move_to(xc, yc);
  cr->line_to(/*xc - */x, y);

  cr->stroke();
}

bool MainWindow::on_eventbox_clicked(GdkEventButton* ev) {
  std::cout << "Clicked! \n" << std::endl;
  std::cout << ev->x << " " << ev->y << std::endl;
  
  // draw_needle(cr, 246, 346);  // 208   // TODO
  
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
  int val = get_bpm(text);
  bpm_Scale.set_value(val);
  BPM = val;  // INFO -> draw in on_draw
  std::cout << BPM << std::endl;
  
  Metronome::change_BPM(bpm_adjustment->get_value());
}

void MainWindow::on_button_quit() {
  hide();
}
