#pragma once

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.h>

#include "Core/Application.h"
#include "Core/Layer.h"

#include "Core/Timestep.h"
#include "Core/Input.h"

#include "Scene/Scene.h"

#include "Renderer/Renderer.h"
#include "Utils/Camera.h"
#include "Utils/Maths.h"

#include <imgui/imgui.h>

#define EVENT_F_POINTER(fn) [&](Event& event) { return fn(event); }