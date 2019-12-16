
#include <gtkmm.h>


void buildUI(int argc, char *argv[]) {
  
  Gtk::Main kit(argc, argv);
  Gtk::Window mainWindow;
  mainWindow.set_default_size(400, 400);
  Gtk::Main::run(mainWindow);
  
}