/**
 * Jack Metronome
 * TGrif (of-pop) 2020 - direct-shoot.com
 * License GPL3
 */
#include <iostream>

#include "metronome.cc"
#include "ui.cc"


int main(int argc, char *argv[]) {

  auto app = Gtk::Application::create(argc, argv, "org.of_pop.jack_metronome");

  MainWindow window(app);

  window.set_title("Jack Metronome");
  window.set_icon_from_file("assets/icon.png");

  return app->run(window);

}