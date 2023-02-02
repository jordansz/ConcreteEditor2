# ConcreteEditor2

Bugs to fix/things to work on:  
  1: Below the sliders and buttons I have an empty place holder widget that I want to display the Information about the texture chosen.
<br/> 2:  On start of application, If user selects a photo, then tries to select another one without doing anything else.  The program will crash.
<br/> 3:  When selecting a texture I should learn how to open and display the textures in the .qrc file.  It could be better to make a new dialog that opens an image viewer widget of all the textures.  


Improvements: <br />
  1:  Currently using raw pointers, QPointer class would be better.
<br/>  2:  When clipping out a region, current implementation only takes out selected area but it would be more realistic to allow continued cropping.  E.g. If someone has a pool, the first clip would keep the pool there and another clip would clip out the concrete around the pool.
<br/>  3:  Stairs are not considered at all so would be just a flat surface if edited.
<br/> 4: Improve sample photos.  I could find a better angle to take them.  Also for textures that have a pattern, create a sample that when edited will continue the pattern when repeated.
