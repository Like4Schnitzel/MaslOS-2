#include "components.hpp"

#include <libm/cstr.h>
#include <libm/cstrTools.h>
#include <libm/gui/guiInstance.h>
#include <libm/gui/guiStuff/components/button/buttonComponent.h>
#include <libm/heap/heap.h>
#include <libm/rendering/Cols.h>
#include <libm/syscallManager.h>
#include <libm/wmStuff/wmStuff.h>

using namespace GuiComponentStuff;

int main(int argc, char **argv) {

  initWindowManagerStuff();

  Window *window = requestWindow();
  if (window == NULL) {
    return -1;
  }
  window->Resizeable = false;

  _Free(window->Title);
  window->Title = StrCopy("calcRocc");

  window->Dimensions.width = 200;
  window->Dimensions.height = 250;

  setWindow(window);

  GuiInstance *guiInstance = new GuiInstance(window);
  guiInstance->Init();
  style(guiInstance);

  while (!CheckForWindowClosed(window)) {
    guiInstance->Update();
    guiInstance->Render(false);

    programWaitMsg();
  }

  return 0;
}
