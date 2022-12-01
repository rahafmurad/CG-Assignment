#include <gl/glew.h>  // A cross-platform open-source C/C++ extension loading library
#include <stdlib.h>
#include <gl/freeglut.h>   // Handle the window-managing operations
#include <iostream>
#include <conio.h>

using namespace std;

/*  Approximation of PI */
#define PI 3.1415926535898

/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

/*  Globals varibles*/

double dim = 4.0; /* Dimension of projection box */
const char* windowName = "Camera Movement";
int windowWidth = 500;
int windowHeight = 450;



/*  Various global state */
int th = -25;  /*theta is y-angle */
int ph = 15;   /*phi is  x-angle */
int fov = 50;   /* Field of view angle */
int asp = 1;  /* aspect ratio */

/*Aim of camera lens */
float ecX = -0.4;
float ecZ = -0.2;
float ecY = 0.0;


// buffers
GLuint myTexture1;
GLuint myTexture2;
GLuint myTexture3;
GLuint myTexture4;
GLuint myTexture5;
GLuint myTexture6;


char image1Path[] = "C:\\Users\\rahaf\\Downloads\\images1.bmp";
char image2Path[] = "C:\\Users\\rahaf\\Downloads\\back1.bmp";
char image3Path[] = "C:\\Users\\rahaf\\Downloads\\side1.bmp";
char image4Path[] = "C:\\Users\\rahaf\\Downloads\\back.bmp"; 
char image5Path[] = "C:\\Users\\rahaf\\Downloads\\top.bmp";
char image6Path[] = "C:\\Users\\rahaf\\Downloads\\bottom1.bmp";




////////////////
//  Functions //
////////////////


//http://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture
GLuint LoadTexture(const char* filename, int width, int height)
{
	GLuint texture;
	unsigned char* data;
	FILE* file;

	//The following code will read in our RAW file   
	file = fopen(filename, "rb");

	if (file == NULL)
	{
		cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
		exit(0);
		return 0;
	}

	data = (unsigned char*)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);

	fclose(file);


	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}


	/////////////////////////////////////////
	// All Exercises TODO: load another texture image
	//////
	glGenTextures(1, &texture);            //generate the texture with the loaded data 
	glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//GL_MODULATE ); //set texture environment parameters 
	//GL_MODULATE 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);// GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); //GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	/////////////////////////////////////////

	free(data); //free the texture array

	if (glGetError() != GL_NO_ERROR)
		printf("GLError in genTexture()\n");

	return texture; //return whether it was successfull  
}



////////////////
//  Functions //
////////////////








/*

* project()
* ------
* Sets the projection
*/
void project(double fov, double asp, double dim)

{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* perspective */
	// TODO1: gluPerspective() /
		gluPerspective(fov, asp, dim, 50);//*


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init() {



	//------- Texture ---------
	myTexture1 = LoadTexture(image1Path, 224, 225);

	if (myTexture1 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture1 << endl;


	myTexture2 = LoadTexture(image2Path,1024, 768 );

	if (myTexture2 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture2 << endl;

	myTexture3 = LoadTexture(image3Path, 256, 169);

	if (myTexture3 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture3 << endl;
	myTexture4 = LoadTexture(image4Path, 256, 248);

	if (myTexture4 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture4 << endl;
	myTexture5 = LoadTexture(image5Path, 256, 170);

	if (myTexture5 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture5 << endl;
	myTexture6 = LoadTexture(image6Path, 256, 192);

	if (myTexture6 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture6 << endl;

	//----------------------





}


/*
*  drawShape()
*/
void drawShape()
{
	/* Cube */
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float size = 1.0f;

	float A[3] = { size,  size,  size };
	float B[3] = { size,  size, -size };
	float C[3] = { size, -size, -size };
	float D[3] = { size, -size,  size };
	float E[3] = { -size,  size,  size };
	float F[3] = { -size,  size, -size };
	float G[3] = { -size, -size, -size };
	float H[3] = { -size, -size,  size };
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture1);
	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3fv(D);
	glTexCoord2f(1, 1);
	glVertex3fv(C);
	glTexCoord2f(1, 0);
	glVertex3fv(B);
	glTexCoord2f(0, 0);
	glVertex3fv(A);
	glDisable(GL_TEXTURE_2D);
	glEnd();

	//--------------------\\

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture2);
	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3fv(G);
	glTexCoord2f(1, 1);
	glVertex3fv(H);
	glTexCoord2f(1, 0);
	glVertex3fv(E);
	glTexCoord2f(0, 0);
	glVertex3fv(F);
	glDisable(GL_TEXTURE_2D);
	glEnd();

	//--------------------\\
     
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture3);
	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3fv(C);
	glTexCoord2f(1, 1);
	glVertex3fv(G);
	glTexCoord2f(1, 0);
	glVertex3fv(F);
	glTexCoord2f(0, 0);
	glVertex3fv(B);
	glDisable(GL_TEXTURE_2D);
	glEnd();

	//--------------------\\
         
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture4);
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3fv(H);
	glTexCoord2f(1, 1);
	glVertex3fv(D);
	glTexCoord2f(1, 0);
	glVertex3fv(A);
	glTexCoord2f(0, 0);
	glVertex3fv(E);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	//--------------------\\
    
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture5);
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3fv(E);
	glTexCoord2f(1, 1);
	glVertex3fv(A);
	glTexCoord2f(1, 0);
	glVertex3fv(B);
	glTexCoord2f(0, 0);
	glVertex3fv(F);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	//--------------------\\
      
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture6);
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3fv(G);
	glTexCoord2f(1, 1);
	glVertex3fv(C);
	glTexCoord2f(1, 0);
	glVertex3fv(D);
	glTexCoord2f(0, 0);
	glVertex3fv(H);
	glDisable(GL_TEXTURE_2D);
	glEnd();


}

/*
*  display()
*  ------
*  Display the scene
*/

void display()

{
	/* Initializes display */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/*  Clear the image */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	/*  Enable Z-buffering in OpenGL */
	glEnable(GL_DEPTH_TEST);
	/*  Reset previous transforms */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*
	* TODO2: set eye postions for the camera
	* check the referace that was provided in the assignement sheet
	*/

	/* TODO3 : camera/eye position, aim of camera lens, up-vector,  gluLookAt() */
	//gluLookAt(sin(PI * th / 180) * 7, sin(PI * ph / 180) * 7, cos(PI * th / 180) * 7, ecX, ecY, ecZ, 0, 1, 0);
	gluLookAt(Sin(th) * Cos(ph) * 7, Sin(ph) * 7, Cos(th) * Cos(ph) * 7, ecX, ecY, ecZ, 0, 1, 0);
	/*  Draw  */
	glPushMatrix();

	glEnable(GL_DEPTH_TEST);
	drawShape();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();

}

/*

*  reshape()
*  ------
*  GLUT calls this routine when the window is resized
*/

void reshape(int width, int height)
{
	asp = (height > 0) ? (double)width / height : 1;
	glViewport(0, 0, width, height);
	project(fov, asp, dim);
}

/*
*  windowKey()
*  ------
*  GLUT calls this routine when a non-special key is pressed
*/

/**TODO4: Follow the assignment sheet instructions to functional the following keys**/

void windowKey(unsigned char key, int x, int y)
{
	//  Exit on ESC /  
	if (key == 27 || key == 'Esc') exit(0);


	/// Change field of view angle */
	else if (key == '-' && key > 1) {
		fov = fov - 2;
		cout << "The fov :" << fov << endl;
	}
	else if (key == '+' && key < 179) {
		fov = fov + 2;
		cout << "The fov :" << fov << endl;
	}
	/*  Change dimensions */
	else if (key == 'D') {
		dim = dim + 0.1;
		cout << "The dim:" << dim << endl;
	}
	else if (key == 'd' && dim > 1) {
		dim = dim - 0.1;
		cout << "The dim:" << dim << endl;
	}

	reshape(windowWidth, windowHeight);
	glutPostRedisplay();
}

/*
 *  windowSpecial()
 *  ------
 *  GLUT calls this routine when an arrow key is pressed
 */
 /**TODO5: Follow the assignment sheet instruction to functional the following keys**/

void windowSpecial(int key, int x, int y)
{
	int modifiers = glutGetModifiers();
	/*  If holding shift, then rotate/elevate */
	if (modifiers == GLUT_ACTIVE_SHIFT) {
		/*  Right/Left - rotate */
		if (key == GLUT_KEY_RIGHT) {
			th = th + 2;
			cout << "The th:" << th << endl;
		}
		else if (key == GLUT_KEY_LEFT) {
			th = th - 2;
			cout << "The th:" << th << endl;
		}
		/*  Up/Down - elevation */
		else if (key == GLUT_KEY_UP) {
			ph = ph + 2;
			cout << "The ph:" << ph << endl;
		}
		else if (key == GLUT_KEY_DOWN) {
			ph = ph - 2;
			cout << "The ph:" << ph << endl;
		}
	}
	/*  Otherwise, just shift the camera */
	else {
		/*  Shift */
		if (key == GLUT_KEY_RIGHT) {
			ecX = ecX + 0.5;
			cout << "The ecX:" << ecX << endl;
		}
		else if (key == GLUT_KEY_LEFT) {
			ecX = ecX - 0.5;
			cout << "The ecX:" << ecX << endl;
		}
		else if (key == GLUT_KEY_DOWN) {
			ecZ = ecZ - 0.5;
			cout << "The ecZ:" << ecZ << endl;
		}
		else if (key == GLUT_KEY_UP) {
			ecZ = ecZ + 0.5;
			cout << "The ecZ:" << ecZ << endl;
		}
	}

	/*  Keep angles to +/-360 degrees */
	th %= 360;
	ph %= 360;

	reshape(windowWidth, windowHeight);
	glutPostRedisplay();
}


/*
*  main()
*/
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(windowKey);
	glutSpecialFunc(windowSpecial);

	glutMainLoop();
	return 0;
}