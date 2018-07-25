# PaintLike

The goal of this project is to create a program similar to Paint / a very simplified Photoshop.
This project is going to be **fully developed in C++**, that is, I'm not going to use OpenGL nor other graphics libraries in order to generate the effects or filters to be drawn.

However, the use of some libreries is nedeed. I use GLFW to open a window and for input detection, and OpenGL 3.1 to draw into the window. I use this version of OpenGL because is the last one featuring glDrawPixels. This rather old and slow way of drawing pixels to the screen allows me to easily write pixels onto the screen, directly from the info stored in an array. Further than that, **no more OpenGL nor GLFW nor any other library is going to be used**.

The aim of this project is, therefore, to create an **image edition program from scratch, only using C++ and its standard library**. Consequently, routines for drawing and creating shapes, handling images, filtering, layers, etc are to be created from scratch.
