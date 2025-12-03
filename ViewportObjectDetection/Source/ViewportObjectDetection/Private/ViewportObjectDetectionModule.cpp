
#include "Modules/ModuleManager.h"

class FViewportObjectDetectionModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
    }

    virtual void ShutdownModule() override
    {
    }
};

IMPLEMENT_MODULE(FViewportObjectDetectionModule, ViewportObjectDetection);
