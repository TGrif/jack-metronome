#include "ui.hh"


void buildUI (int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);
  MainWindow window;
  Gtk::Main::run(window);
  // std::cout << "ui" << std::endl;
}


MainWindow::MainWindow():
 // m_HBox_Digits(Gtk::ORIENTATION_HORIZONTAL, 10),
 bpm_adjustment(Gtk::Adjustment::create(0.0, 0.0, 101.0, 0.1, 1.0, 1.0) ),
 bpm_Scale(bpm_adjustment),
 button_Quit(Gtk::Stock::QUIT)/*,
  m_Button_Buffer1("Use buffer 1"),
  m_Button_Buffer2("Use buffer 2")*/
{
  
  set_title("Jack Métronome");
  set_border_width(5);
  set_default_size(400, 200);

  add(m_VBox);

  app_Window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_VBox.pack_start(app_Window);
  
  // m_HBox_Digits.pack_start(*Gtk::make_managed<Gtk::Label>("Scale Digits:", 0), Gtk::PACK_SHRINK);
  // m_Scale_Digits.set_digits(0);
  // m_adjustment_digits->signal_value_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_adjustment1_value_changed));
  // m_HBox_Digits.pack_start(m_Scale_Digits);
  
  
  bpm_Scale.set_digits(1);
  bpm_Scale.set_value_pos(Gtk::POS_TOP);
  bpm_Scale.set_draw_value();
  bpm_Scale.set_size_request(200, 30);
  m_VBox.pack_start(bpm_Scale);

  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_spacing(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_ButtonBox.pack_start(button_Quit, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);


  button_Quit.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_quit));


  show_all_children();
  
}

void MainWindow::on_BPM_value_changed() {
  std::cout << bpm_adjustment->get_value() << std::endl;
  // const double val = m_adjustment_digits->get_value();
  const double val = 5;
  bpm_Scale.set_digits((int)val);
}

MainWindow::~MainWindow() {
  std::cout << "Bye." << std::endl;
}

void MainWindow::on_button_quit() {
  hide();
}

