# ConcreteEditor2

Bugs to fix/things to work on:  
  1: Below the sliders and buttons I have an empty place holder widget that I want to display the Information about the texture chosen.
<br/> 2:  On start of application, If user selects a photo, then tries to select another one without doing anything else.  The program will crash.
<br/> 3:  When selecting a texture I should learn how to open and display the textures in the .qrc file.  It could be better to make a new dialog that opens an image viewer widget of all the textures.  
4:  In the vertex shader I use the back squares position vertex's to limit the drawn squares size.  This did not account for the rotation which also brings up another problem.  To account for rotations, I should make the back square much bigger and farther back.  Farther back and bigger will account for rotating the square so far that the plane doesn't fully fit in the front square anymore (do some math to figure what I can get away with).  Then in the vertex shader, instead of using the positions of the square, use the squares position in world space (gl_positions xyz values to check there is no interference with the front square).
<br/> 5:  Consider adding a slider for a z axis rotation.  Could be labeled "twist"


Improvements: <br />
  1:  Currently using raw pointers, QPointer class would be better.
<br/>  2:  When clipping out a region, current implementation only takes out selected area but it would be more realistic to allow continued cropping.  E.g. If someone has a pool, the first clip would keep the pool there and another clip would clip out the concrete around the pool.
<br/>  3:  Stairs are not considered at all so would be just a flat surface if edited.
<br/> 4: Improve sample photos.  I could find a better angle to take them.  Also for textures that have a pattern, create a sample that when edited will continue the pattern when repeated.  The difference in lighting spanning the images also really how increasing the size looks.  With a repeated texture, most of my images have a clear square where repeated because of the lighting.


Licenses:

/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
