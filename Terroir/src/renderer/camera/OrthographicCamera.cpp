////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Christopher J. Pohl 2023 to Present  All Rights Reserved.
//
// This file is part of TERROIR ENGINE:
// This is free software as described by the Apache 2.0 License
//
// The above copyright notice shall be included in all portions of this software
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "OrthographicCamera.h"
#include "Tpch.h"
#include "math/Math.h"

namespace Terroir
{
using namespace Math;
OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top)
    : m_ProjectionMatrix(Transform::Ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f),
      m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix)

{
}

void OrthographicCamera::SetProjection(f32 left, f32 right, f32 bottom, f32 top)
{
    m_ProjectionMatrix = Transform::Ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    Mat4 transform{Transform::Translate(Mat4(1.0f), m_Position) *
                   Transform::Rotate(Mat4(1.0f), Conversion::ToRadians(m_Rotation), Vec3(0, 0, 1))};

    m_ViewMatrix = Transform::Inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

} // namespace Terroir
