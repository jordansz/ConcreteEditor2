# ConcreteEditor2

Bugs to fix:  
  1: On start of application, If user selects a photo, then tries to select another one without doing anything else.  The program will crash.


Improvements: 
  1:  Currently using raw pointers, QPointer class would be better.
  2:  When clipping out a region, current implementation only takes out selected area but it would be more realistic to allow continued cropping.  E.g. If someone has a pool, the first clip would keep the pool there and another clip would clip out the concrete around the pool
