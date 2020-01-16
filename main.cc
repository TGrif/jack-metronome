/**
 * Jack Metronome
 * TGrif (of-pop) 2020 - direct-shoot.com
 * License GPL3
 *
 */
#include <iostream>

#include <gtkmm.h>

#include "metronome.cc"
#include "ui.cc"


int main(int argc, char *argv[]) {
  
  auto app = Gtk::Application::create(argc, argv, "org.of_pop.jack_metronome");
  
  MainWindow window(app);
  return app->run(window);
  
}