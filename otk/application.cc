#include "application.hh"
#include "eventhandler.hh"

namespace otk {

OtkApplication::OtkApplication(int argc, char **argv)
  : OtkEventDispatcher(), _dockable(false)
{
  argc = argc;
  argv = argv;

  OBDisplay::initialize(0);
  const ScreenInfo *s_info = OBDisplay::screenInfo(DefaultScreen(OBDisplay::display));

  _timer_manager = new OBTimerQueueManager();
  _img_ctrl = new BImageControl(_timer_manager, s_info, True, 4, 5, 200);
  _style_conf = new Configuration(False);
  _style = new Style(_img_ctrl);

  loadStyle();
}

OtkApplication::~OtkApplication()
{
  delete _style_conf;
  delete _img_ctrl;
  delete _timer_manager;
  delete _style;
  
  OBDisplay::destroy();
}

void OtkApplication::loadStyle(void)
{
  // find the style name as a property
  _style_conf->setFile("/usr/local/share/openbox/styles/artwiz");
  _style_conf->load();
  _style->load(_style_conf);
}

void OtkApplication::exec(void)
{
  dispatchEvents();
}

}
