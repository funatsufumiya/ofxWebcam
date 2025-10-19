// Modified from: https://github.com/lukehugh/cv2_enumerate_cameras/blob/8b262be1ecfc4ff4fd5c6eee06ab878a342443dc/cv2_enumerate_cameras/_windows_backend.cpp
//
// MIT License
//
// Copyright (c) 2024 Yu He
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <vector>
#include <string>

namespace enumerate_cameras_windows {

struct CameraInfo
{
    std::wstring name;
    std::wstring path;
};

bool MSMF_enumerate_cameras(std::vector<CameraInfo>& camera_info);
bool DSHOW_enumerate_cameras(std::vector<CameraInfo>& camera_info);

} // namespace enumerate_cameras_windows