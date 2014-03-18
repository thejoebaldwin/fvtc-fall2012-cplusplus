#include <stdlib.h>

#include "glut.h"
#include "png.h"
#include "square.h"

#include <iostream>
//http://sourceforge.net/projects/libpng/files/libpng12/older-releases/1.2.44/


#define BUFSIZE 512

const int squareLength =50;
square* allSquares[squareLength];

const int treeLength =10;
square* allTrees[treeLength];

static int ww = 1280;
static int wh = 700;

GLubyte *textureImage;
float rotateX = 0;
float rotateY = 0;
GLuint texture_id[6];

//position of light
static GLfloat light_one[] = {1,    0.0, 20.0, 0.0};

int mouseX;
int mouseY;

bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
void reshape(int w, int h);
void initialize();
void init();
void mouseClick(int button, int state, int x, int y);
void selectionDetection(int button, int state, int x, int y);
void processHits (GLuint hits, GLuint buffer[], int button);

void gotClicked(int index, int button);

void mouseMove(int x, int y);

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 2.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'o':
		
		break;
	}
	glutPostRedisplay();
}


void initialize()
{
	for (int i = 0; i < squareLength; i++)
	{
		allSquares[i] = new square;
	    allSquares[i]->setLimits(10, -10, -15, 15);
		//set different z values so we dont get overlap
        allSquares[i]->z = i * 0.1;

		
		//allSquares[i]->textureIndex = i % 3;
		allSquares[i]->textureIndex = 0;
		
		//allSquares[i]->textureIndex = 1;
		allSquares[i]->setName((GLint) i);
		cout << *allSquares[i] << endl;
	}

	for (int i = 0; i < treeLength; i++)
	{
		allTrees[i] = new square;
	    allTrees[i]->setLimits(10, -10, -15, 15);
		//set different z values so we dont get overlap
        allTrees[i]->z = i * 0.1;

		
		//allSquares[i]->textureIndex = i % 3;
		allTrees[i]->textureIndex = 1;
		
		//allSquares[i]->textureIndex = 1;
		allTrees[i]->setName((GLint) i + squareLength);


		allTrees[i]->_velocity_x = 0;
			allTrees[i]->_velocity_y = 0;

			//allTrees[i]->x = -10 + (i * 2);
			allTrees[i]->move(-10 + (i * 2), -6);

			allTrees[i]->move(-10 + (i * 2), -6, i - 15);

			allTrees[i]->setWidth(8);

		cout << *allTrees[i] << endl;
	}
}


void initTexture(int textureIndex, char fileName[])
{
	glBindTexture ( GL_TEXTURE_2D, texture_id[textureIndex] );
	//free (textureImage);
	int height, width;
	bool hasAlpha;
    bool success = loadPngImage(fileName, width, height, hasAlpha, &textureImage);
    if (!success) {
        std::cout << "Unable to load png file" << std::endl;
        return;
    }
    std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
            height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
            textureImage);
	//free (textureImage);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 

	
	free (textureImage);

}

void init() {
    //glClearColor(0.1, 0.1, 0.4, 1.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    // The following two lines enable semi transparent
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_COLOR_MATERIAL);

	 glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    int width, height;
    bool hasAlpha;

	  glGenTextures (6, texture_id); 



	  glEnable ( GL_TEXTURE_2D );
	
	  initTexture(0, "snow1.png");
      initTexture(1, "tree.png");
      initTexture(2, "snowman.png");
	 glDisable ( GL_TEXTURE_2D );

	initialize();
}

static GLdouble viewer[] = {0.0, -2.0, 20.0}; 


void draw(GLenum mode)
{

		
	
		   
	for (int i = 0; i < squareLength; i++)
	{
		glBindTexture ( GL_TEXTURE_2D, texture_id[allSquares[i]->textureIndex] );
		   glEnable(GL_TEXTURE_2D);

		if (mode == GL_SELECT) glLoadName(allSquares[i]->getName());
		allSquares[i]->draw();
		  glDisable(GL_TEXTURE_2D);
	}



	for (int i = 0; i < treeLength; i++)
	{
		glBindTexture ( GL_TEXTURE_2D, texture_id[allTrees[i]->textureIndex] );
		   glEnable(GL_TEXTURE_2D);

		if (mode == GL_SELECT) glLoadName(allTrees[i]->getName());
		allTrees[i]->draw();
		  glDisable(GL_TEXTURE_2D);
	}
	 
}


void update()
{
   for (int i = 0; i < squareLength; i++)
   {
	    allSquares[i]->update();
   }
}

void display(void) {


	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	 glLightfv(GL_LIGHT0, GL_POSITION, light_one);
	
	 const GLfloat specular[]= {1.0f,1.0f,1.0f,1.0f};
      glLightfv(GL_LIGHT0, GL_SPECULAR, specular );

 // GL_SPECULAR
	draw(GL_RENDER);
	
	update();
	glutPostRedisplay();
    glutSwapBuffers();
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0 * (GLfloat) w / (GLfloat) h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void mousePassive(int x, int y){
    mouseX = x;
    mouseY = y;
}

void mouseMotion(int x, int y){
    const float SPEED = 2;

    rotateX += (mouseX-x)/SPEED;
    rotateY += (mouseY-y)/SPEED;
    mousePassive(x, y);
    glutPostRedisplay();
}



void mouseMove(int x, int y)
{
	//cout << "x:" << x << "||y:" << y << endl;
	//if (leftMouseDown)
	//{
	//	if (last_x_pos > x )
	//	{
	//		//isMovingLeft = true;
	//		s.move(-0.1f, 0);
	//	}
	//	else if (last_x_pos < x)
	//	{
	//		s.move(0.1f, 0);
	//	}
	//	//s.move((last_x_pos - x) / 10.0f, 0);
	//	last_x_pos = x;
	//}
}



void gotClicked(int index, int button)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		GLfloat newColor[4] = {1, 0, 0, 1};
		allSquares[index]->setColor(newColor);
		allSquares[index]->grow();
	}
	//toggle rotation
	if (button == GLUT_RIGHT_BUTTON)
	{
		allSquares[index]->isRotating = !allSquares[index]->isRotating;
	}
}



void processHits (GLuint hits, GLuint buffer[], int button)
{
 GLuint *ptr =(GLuint *) buffer;
 GLuint names = *ptr;
 ptr++;
 ptr++;
 ptr++;
  //loop through hits if you want to process ALL objects that were selected
 //for (int i=0; i < hits; i++) 
  //{
 if (names < squareLength)
 {
	 for (int j = 0; j < names; j++)
	 {
		cout<< "Selected Name:" << *ptr << endl;
    	for (int k = 0; k < squareLength; k++)
	    {
			//if true then object received a mouse click (others might have also)
			if (allSquares[k]->getName() == *ptr)
			{
				//this object was click on
				gotClicked(k, button);
			}
		}
   	  ptr++;
	 }
 }
 //}
}


void selectionDetection(int button, int state, int x, int y)
{
 GLuint selectBuf[ BUFSIZE ] ;
 GLint viewport[4];
 if (state !=GLUT_DOWN)
	 return;
 glGetIntegerv(GL_VIEWPORT, viewport);
 glSelectBuffer(BUFSIZE, selectBuf);
 (void) glRenderMode(GL_SELECT);
 glInitNames();
 glPushName(0);
 glMatrixMode(GL_PROJECTION);
 glPushMatrix();
   glLoadIdentity();
   gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y), 5.0, 5.0, viewport);
   gluPerspective(45.0, (GLfloat) ww/(GLfloat) wh, 1.0, 50.0);
   glMatrixMode(GL_MODELVIEW); 
   glPushMatrix();
     draw(GL_SELECT);
   glPopMatrix();
   glMatrixMode(GL_PROJECTION);
 glPopMatrix();
 glFlush();
 glMatrixMode(GL_MODELVIEW); 
 processHits( glRenderMode(GL_RENDER),selectBuf, button);
}

void mouseClick(int button, int state, int x, int y)
{

	selectionDetection(button, state, x, y);


	//if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
	//{
	//	//cout << "left button clicked at " << x << "," << y << endl;
	//	leftMouseDown = false;
 //   	isMovingLeft = false;
	//}
	//else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP))
	//{
	//	//cout << "right button clicked at " << x << "," << y << endl;
	//}
	//else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	//{
	//	leftMouseDown = true;
	//	//cout << "last_x_pos:" << last_x_pos << "||x:" << x << endl;
	//}
}



int main(int argc, char** argv) {
    /*glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	  glutInitWindowSize(400, 300); 
    glutCreateWindow("PNG texture");
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mousePassive);
    init();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    std::cout << "Use mouse drag to rotate." << std::endl;
    glutMainLoop();*/



   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(ww, wh); 
   glutInitWindowPosition(50, 50);
   glutCreateWindow(argv[0]);

     glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   init();
   //pass display delegate
  
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouseClick); 
   glutMotionFunc(mouseMove);



   glutMainLoop();

    return 0;
}


bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;

    if ((fp = fopen(name, "rb")) == NULL)
        return false;

    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);

    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }

    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
        return false;
    }

    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return false;
    }

    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);

    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);

    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);

    outWidth = info_ptr->width;
    outHeight = info_ptr->height;

    switch (info_ptr->color_type) {
        case PNG_COLOR_TYPE_RGBA:
            outHasAlpha = true;
            break;
        case PNG_COLOR_TYPE_RGB:
            outHasAlpha = false;
            break;
        default:
            std::cout << "Color type " << info_ptr->color_type << " not supported" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
            return false;
    }
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    *outData = (unsigned char*) malloc(row_bytes * outHeight);

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }

    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

    /* Close the file */
    fclose(fp);

    /* That's it */
    return true;
}