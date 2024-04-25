// ============================================================================
// Layout (Codeloader UI) Program
// Programmed by Francois Lamini
// ============================================================================

#include "Layout.h"

Codeloader::cPage_Manager* page_manager;

bool Layout_Process();
bool Process_Keys();

// **************************************************************************
// Program Entry Point
// **************************************************************************

int main(int argc, char** argv) {
  if (argc == 2) {
    std::string layout_name = argv[1];
    try {
      Codeloader::cConfig config("Config");
      int width = config.Get_Property("width");
      int height = config.Get_Property("height");
      Codeloader::cAllegro_IO allegro(layout_name, width, height, 1, "Game");
      allegro.Load_Resources_From_Files();
      page_manager = new Codeloader::cPage_Manager();
      page_manager->Add_Page(new Codeloader::cPage("Config", &allegro), "Layout_Screen");
      page_manager->Add_Page(new Codeloader::cPage("Config", &allegro), "Layout_Screen_2");
      allegro.Process_Messages(Layout_Process, Process_Keys);
    }
    catch (Codeloader::cError error) {
      error.Print();
    }
    if (page_manager) {
      delete page_manager;
    }
  }
  else {
    std::cout << "Usage: " << argv[0] << " <layout>" << std::endl;
  }
  std::cout << "Done." << std::endl;
  return 0;
}

// ****************************************************************************
// Layout Processor
// ****************************************************************************

/**
 * Called when command needs to be processed.
 * @return True if the app needs to exit, false otherwise.
 */
bool Layout_Process() {
  bool quit = false;
  try {
    page_manager->Render();
  }
  catch (Codeloader::cError error) {
    error.Print();
    quit = true;
  }
  return quit;
}

/**
 * Called when keys are processed.
 * @return True if the app needs to exit, false otherwise.
 */
bool Process_Keys() {
  return false;
}
