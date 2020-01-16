#include "ui.hh"


MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application>& app):
 bpm_adjustment(Gtk::Adjustment::create(80, 0, 100, 1, 100, 0)),
 bpm_Label("BPM"),
 bpm_Scale(bpm_adjustment),
 button_Quit(Gtk::Stock::QUIT) {
  
  set_title("Jack Métronome");
  set_border_width(5);
  set_default_size(400, 200);

  add(m_VBox);

  app_Window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_VBox.pack_start(app_Window);
  m_VBox.set_spacing(18);
  
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

// change_BPM_value(50);
}

MainWindow::~MainWindow() {
  std::cout << "Bye." << std::endl;
}

void MainWindow::on_BPM_value_changed() {
  std::cout << bpm_adjustment->get_value() << std::endl;
  // const double val = m_adjustment_digits->get_value();
}

void MainWindow::change_BPM_value(double val) {
  bpm_Scale.set_value((int)val);
}

void MainWindow::on_button_quit() {
  hide();
}

