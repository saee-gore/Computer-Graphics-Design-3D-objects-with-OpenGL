# Design 3D objects with OpenGL

A graphical view of interactions between the moon and a rocket in space.

## Components of this project 

- Different interactions between the moon and a rocket in space.
- Written in C++ 
- All objects have lighting and materials.
- Runs on Visual Studio

## Interactions of this project

- Mouse Interactions
- Keyboard Interactions
- Arrow Keys
- Number Keys
- Menu Interactions

  ### Mouse Interactions 

    - Right button and Left button: Rotation in a particular axis.
    - Middle button: The menu list will appear.

  ### Keyboard Interactions 

    - Alphabet q is used for exiting the program.

   ### Arrow Keys 
    - Right Key
      - Rotation in x-y axis in clockwise direction
    - Left Key
      - Rotation in x-y axis in counterclockwise direction
    - Up Key
      - Rotation in z axis in counterclockwise direction
    - Down Key
      - Rotation in z axis in clockwise direction

   ### Number Keys

     1.  Stops the idle animation
     2.  Starts the idle animation
     3.  Changes the red color with lighting and materials
     4.  Changes the white color with lighting and materials
     5.  Changes the brass yellow color with lighting and materials
     6.  Changes the lighting to white lighting
     7.  Changes the lighting to colored lighting

  ### Menu Interactions 
    - The menu interaction occurs when the middle mouse button is clicked.
    - It consists of a question stating 'What would you like the program to do?'.
    - Upon clicking it, 3 options will appear.

    - Option 1: Start the animation 
       - display2() is called.
       - A rocket starts to revolve around the moon.

    - Option 2: Stop the animation 
       - display1() is called.
       - The parts of rocket and moon are suspended in the space. 

    - Option 3: Exit 
       - Exits the application.
  
## How to run 
- Save the file called 'Project.cpp' and then click on Run and the output will be displayed.
- You can download the 'Project.exe' to view the output.

## How to exit the program 
- Click on 'q' on the keyboard.
- Click on the 'Exit' option in the menu.

**Programmer: Saee A. Gore**
