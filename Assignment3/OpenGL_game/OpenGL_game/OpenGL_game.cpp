// OpenGL_Game.cpp
// Bare bones version of "Acorn Dodge"
// K.Doyle Apr 2019  
//credits to C. Markham code provided to us
// Images used found on google images

#include "stdafx.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>    // Required for sound only (consider OpenAL), 
#include <mmsystem.h>   // Again only required for sound only

#include <freeglut.h>   // GLUT OpenGL Utility Toolkit
#include "Sprite.h"     // Prototype Sprite class


// 3 Sprites are used in the "game"
Sprite player;
Sprite acorn;
bool acorn_moving=true;
Sprite background;

// Score data and method
int score=0;
char score_text[20];


// Callback function called each time screen is to be redrawn (called by OS not you directly)
static void display(void)                                 
{															// Keep game logic out of display()...
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f) ;
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and the Depth Buffer

		background.drawSprite();							// Draw background at X,Y in a given direction
		player.drawSprite();								// Draw player	
		acorn.drawSprite();								    // Draw ball 
	    
		sprintf(score_text,"Score: %d",score);              // Display text 
		Sprite::text(830,420,score_text);

		glutSwapBuffers();  // Display buffer just drawn and then switch to draw on the other buffer
}


// Callback function to allow dynamic resizing of runtime display
static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
	Sprite::spriteModeOn(0,0);  // (0,0) Causes orginal screen size to be reused
}

// Callback to manage standard keys on the keyboard
// In this case 'q' or 'Q' causes program to terminate
static void qwerty_keys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'Q':
    case 'q': glutLeaveMainLoop () ; break;  // (Stop!)
    default: break;
    }
}

// Callback for cursor keys on the keyboard
// <- and -> cursors keys cause player to move left and right
static void function_keys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
			player.advance_frame(0,4);
			player.sprite_x_position-=10;
			player.direction=false;
		break;


    case GLUT_KEY_RIGHT: 
		    player.advance_frame(0,4);
			player.sprite_x_position+=10;
			player.direction=true;
		break;

    default: break;
    }
}

// Game loop
// static void idle()    // if using  glutIdleFunc(idle); this line should replace the one below
static void idle(int v)  // Runs between frame updates in doublebuffer mode, game logic goes here
{
	if(acorn_moving)
	{
	  acorn.advance_projectile();      // Advance acorn
	  if(acorn.sprite_y_position<20)   // if it has landed
	  { 	   
		   score++;
		   acorn.sprite_y_position=1100;
		   acorn.sprite_y_velocity=0;
		   acorn.sprite_x_position=50+(rand()%850);
		   acorn.sprite_x_velocity=0;
		   acorn_moving=false;
	  }
	} 
	
	if (!acorn_moving) acorn_moving=true;

	acorn.advance_frame(0,0); 

	if(player.collision(acorn)) score=0; // If player collides with ball score is reset to zero

    glutPostRedisplay();      // Send message to ask for screen to be redrawn
	glutTimerFunc(10,idle,0); // Restart the timer (remove line if using the more common glutIdleFunc(idle) approach)
}

/* Program entry point - starts here */

int main(int argc, char *argv[])
{
	Sprite::spriteModeOn(1024,480);		// Create a screen 640x480 to contain game

	// Start playing background music (uses Windows calls, there are other ways incluing OpenAL)
	PlaySound(L"Music.wav",NULL, SND_LOOP| SND_ASYNC);  

	// load sprite files (24bit BMP), Frames (X,Y), position (X,Y), size (Width,Height), direction
	// Use sprites with Width and Height divisible by 4, ideally powers of two e.g. 256x128
	player.load("Walker.bmp",5,1,320,10,150,150,false);  
	acorn.load("Acorn.bmp",1,1,100,35,50,50,true);          
	background.load("Background.bmp",1,1,0,0,1024,480,true); 

    glutReshapeFunc(resize);			// Called when window is resized (not required)
	glutDisplayFunc(display);			// Callback function to redraw, an event created by glutPostRedisplay()
    glutKeyboardFunc(qwerty_keys);		// QWERTY Keys
    glutSpecialFunc(function_keys);		// Cursor keys etc 

	//glutIdleFunc(idle);			    // Called during idle time 
	glutTimerFunc(10,idle,0);           // Use timer callback for more consistent timing
	
	glutMainLoop();						// Start main loop running (go!)
    
	return EXIT_SUCCESS;
}

