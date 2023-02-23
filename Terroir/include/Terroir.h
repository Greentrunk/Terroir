//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_TERROIR_H
#define TERROIR_TERROIR_H

/// ---- INTERFACE FOR CLIENT APPLICATIONS ---- ///

// To be used in applications with Terroir Engine
#include "Terroir/src/core/application/Application.h"

// Timestep
#include "Terroir/src/core/Timestep.h"

// Client entry-point
#include "Terroir/src/core/AppEntry.h"

// Logging logging
#include "Terroir/src/log/Log.h"

// Asserts
#include "Terroir/src/core/Assert.h"

// Math
#include "Terroir/src/math/Math.h"

// Events
#include "Terroir/src/core/event/ApplicationEvent.h"
#include "Terroir/src/core/event/Event.h"
#include "Terroir/src/core/event/KeyEvent.h"
#include "Terroir/src/core/event/MouseEvent.h"
#include "Terroir/src/core/event/WindowEvent.h"

// Input
#include "Terroir/src/core/KeyCodes.h"
#include "Terroir/src/core/MouseButtonCodes.h"
#include "Terroir/src/platform/Input.h"

// Layers
#include "Terroir/src/core/layer/Layer.h"

// Dear IMGUi layer
#include "Terroir/src/dear-imgui/DearImGuiLayer.h"

// Rendering
#include "Terroir/src/renderer/RenderCommand.h"
#include "Terroir/src/renderer/Renderer.h"
#include "Terroir/src/renderer/VertexArray.h"
#include "Terroir/src/renderer/buffer/IndexBuffer.h"
#include "Terroir/src/renderer/buffer/VertexBuffer.h"
#include "Terroir/src/renderer/camera/OrthographicCamera.h"
#include "Terroir/src/renderer/camera/OrthographicCameraController.h"
#include "Terroir/src/renderer/shader/Shader.h"
#include "Terroir/src/renderer/texture/Texture2D.h"
// TEMP
#include "Terroir/src/renderer/opengl/OpenGLShader.h"
#include "Terroir/src/renderer/shader/ShaderLibrary.h"

#endif // TERROIR_TERROIR_H
