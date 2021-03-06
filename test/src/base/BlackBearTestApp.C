/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/*                       BlackBear                              */
/*                                                              */
/*           (c) 2017 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "BlackBearTestApp.h"
#include "BlackBearApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<BlackBearTestApp>()
{
  InputParameters params = validParams<BlackBearApp>();
  return params;
}

BlackBearTestApp::BlackBearTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  BlackBearApp::registerObjectDepends(_factory);
  BlackBearApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  BlackBearApp::associateSyntaxDepends(_syntax, _action_factory);
  BlackBearApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  BlackBearApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    BlackBearTestApp::registerObjects(_factory);
    BlackBearTestApp::associateSyntax(_syntax, _action_factory);
    BlackBearTestApp::registerExecFlags(_factory);
  }
}

BlackBearTestApp::~BlackBearTestApp() {}

// External entry point for dynamic application loading
extern "C" void
BlackBearTestApp__registerApps()
{
  BlackBearTestApp::registerApps();
}
void
BlackBearTestApp::registerApps()
{
  registerApp(BlackBearApp);
  registerApp(BlackBearTestApp);
}

// External entry point for dynamic object registration
extern "C" void
BlackBearTestApp__registerObjects(Factory & factory)
{
  BlackBearTestApp::registerObjects(factory);
}
void
BlackBearTestApp::registerObjects(Factory & factory)
{
  Registry::registerObjectsTo(factory, {"BlackBearTestApp"});
}

// External entry point for dynamic syntax association
extern "C" void
BlackBearTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  BlackBearTestApp::associateSyntax(syntax, action_factory);
}
void
BlackBearTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"BlackBearTestApp"});
}

// External entry point for dynamic execute flag registration
extern "C" void
BlackBearTestApp__registerExecFlags(Factory & factory)
{
  BlackBearTestApp::registerExecFlags(factory);
}
void
BlackBearTestApp::registerExecFlags(Factory & /*factory*/)
{
}
