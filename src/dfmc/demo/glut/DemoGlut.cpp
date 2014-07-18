#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
// ----------------------------------------------------------------------------
// Copyright 2013 DFMC Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#ifdef DFMC_HAS_GLUT
#include <dfmc/demo/glut/DemoGlut.hpp>
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Exceptions.hpp>
#include <dfmc/base/log/Log.hpp>
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

#if defined(WIN32)
#  define vsnprintf _vsnprintf
#  include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>

namespace dfmc
{
  namespace
  {
    DFMC::weak_ptr<DemoAppController> gAppController;
    Point2 gScreenResolution;

    void OnGlutIdle(void)
    {
      glutPostRedisplay();
    }


    void OnGlutReshape(int w, int h)
    {
      gScreenResolution.X = w;
      gScreenResolution.Y = h;

      DFMC::shared_ptr<DemoAppController> controller = gAppController.lock();
      if (controller)
      {
        controller->Render(gScreenResolution);
        // vgResizeSurfaceSH(w, h);
      }
    }

    void OnGlutDisplay(void)
    {
      bool bExit = true;
      DFMC::shared_ptr<DemoAppController> controller = gAppController.lock();
      bool bIsFrozen = false;
      if (controller)
      {
        if (controller->GetDemoState() == DemoState::Running)
          controller->Render(gScreenResolution);
        else
          bIsFrozen = true;

        bExit = controller->HasExitRequest();
      }
      if (! bIsFrozen)
      {
        // swap
        glutSwapBuffers();
      }
      if (controller)
      {
        controller->SequenceCompleted();
      }

      //if (bExit)
      //  glutExit();
    }

  }

  DemoGlut::DemoGlut(const DemoConfig& demoConfig, IDemoController& demoController)
    : mConfig(demoConfig.GetAppFactory()->GetConfig())
    , mAppController()
  {
    // FIX: this code doesn't obey the demoConfig.Render config
    const bool isFullscreen = (demoConfig.GetRenderConfig().GetWindowMode() == RenderWindowMode::Fullscreen);
    const Rectangle targetRect = demoConfig.GetRenderConfig().GetTargetRectangle();
    if (isFullscreen)
      std::cout << "WARNING: DemoGLut -> Fullscreen rendering not supported." << std::endl;
    if (targetRect.X() != 0 || targetRect.Y() != 0 )
      std::cout << "WARNING: DemoGLut -> Window location not supported." << std::endl;
    std::cout << "WARNING: DemoGLut -> Might not create a window of the desired size." << std::endl;

    const unsigned int preferredWidth = !isFullscreen ? targetRect.Width() : 1280;
    const unsigned int preferredHeight = !isFullscreen ? targetRect.Height() : 720;
    gScreenResolution = Point2(preferredWidth, preferredHeight);

    int argc = 1;
    char* argv[1] = { "dfmc.exe" };

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_STENCIL | GLUT_MULTISAMPLE);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(preferredWidth, preferredHeight);
    glutCreateWindow("Demo");
    glutReshapeWindow(preferredWidth, preferredHeight);

    glutReshapeFunc(OnGlutReshape);
    glutDisplayFunc(OnGlutDisplay);
    glutIdleFunc(OnGlutIdle);
    //glutKeyboardFunc(testKeyboard);
    //glutSpecialFunc(testSpecialKeyboard);
    //glutMouseFunc(testButton);
    //glutMotionFunc(testDrag);
    //glutPassiveMotionFunc(testMove);
    //atexit(testCleanup);

    const DemoEnvironment demoEnvironment(demoConfig.GetDemoDataProvider());
    mAppController.reset(new DemoAppController(demoConfig, demoController, demoEnvironment, false, mConfig.RestartOnResize));
    gAppController = mAppController;
  }


  DemoGlut::~DemoGlut()
  {
    Cleanup();
  }


  int DemoGlut::RunDemo()
  {
    glutMainLoop();
    return 0;
  }


  void DemoGlut::Cleanup()
  {
    // Release the app first, since it expects GL to be ready
    mAppController.reset();
  }

}
#endif
