
// #include <iostream>


void help() {
  std::cout << "Test Jack <option>" << std::endl;
  std::cout << "--help    show this help" << std::endl;
  exit(0);
}

void parseArguments(int argc, char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]).substr(0, std::string("--help").length()) == "--help") {
      help();
    }
  }
}
