#pragma once
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <functional>
#include "SDKsound.h"
#include "SDKwavefile.h"

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "dsound.lib")

#define g_Device DXUTGetD3D9Device()

using Vec2 = D3DXVECTOR2;
using Matrix = D3DXMATRIX;

#include "Math.h"

using namespace Math;
using namespace std;

#include "cImageManager.h"
#include "cObjectManager.h"
#include "cCameraManager.h"
#include "cSceneManager.h"
#include "cSoundManager.h"
#include "cInputManager.h"
#include "cParticleManager.h"
#include "cSystemManager.h"

#include "cCollider.h"
#include "cRenderer.h"
#include "cPath.h"
#include "cTimeLine.h"