# ConcreteEditor2

Bugs to fix/things to work on:  
  1: Below the sliders and buttons I have an empty place holder widget that I want to display the Information about the texture chosen.
<br/> 2:  On start of application, If user selects a photo, then tries to select another one without doing anything else.  The program will crash.
<br/> 3:  When selecting a texture I should learn how to open and display the textures in the .qrc file.  It could be better to make a new dialog that opens an image viewer widget of all the textures.  
<br/> 4:  In the vertex shader I use the back squares position vertex's to limit the drawn squares size.  This did not account for the rotation which also brings up another problem.  To account for rotations, I should make the back square much bigger and farther back.  Farther back and bigger will account for rotating the square so far that the plane doesn't fully fit in the front square anymore (do some math to figure what I can get away with).  Then in the vertex shader, instead of using the positions of the square, use the squares position in world space (gl_positions xyz values to check there is no interference with the front square).


Improvements: <br />
  1:  Currently using raw pointers, QPointer class would be better.
<br/>  2:  When clipping out a region, current implementation only takes out selected area but it would be more realistic to allow continued cropping.  E.g. If someone has a pool, the first clip would keep the pool there and another clip would clip out the concrete around the pool.
<br/>  3:  Stairs are not considered at all so would be just a flat surface if edited.
<br/> 4: Improve sample photos.  I could find a better angle to take them.  Also for textures that have a pattern, create a sample that when edited will continue the pattern when repeated.
