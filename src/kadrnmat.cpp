//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2002/01/03
 * \brief	   Main class for running this flying simulator.
 *
 *  Main file that takes care of everything.
 *
*/
//----------------------------------------------------------------------------------------

#include <cmath>
#include <iostream>
#include <string>

#include "pgr.h"
#include "SceneObject.h"
#include "Scene.h"
#include "PitchAnimation.h"
#include "CurveMovementAnimation.h"
#include "CurveMovementAnimation2.h"
#include "SkyBox.h"
#include "FollowObjectAnimation.h"
#include "Cube.h"
#include "ChangeTexAnimation.h"
#include "StalkingAnimation.h"

#include <GL/GL.h>
#include <GL/freeglut.h>


using namespace glm;

void passiveMotionFunc(int x, int y);


// ***** OKNO ********
int WIDTH = 600;
int HEIGHT = 300;
char *TITLE = "Kadrnmat";

NewCamera *nc;
NewModel *newModel, *newModel2, *newModel3, *terrain;
SceneObject *activeModel = NULL;
Scene *sc;
Light *l, *spotLight;

float time;

void printVector(glm::vec3);
void printMatrix(glm::mat4);

void keyboardFunc(unsigned char key, int x, int y) {
	float speed = 0.3f;
	switch(key){
	case 27:
		glutLeaveMainLoop();
		break;


	case 'e':
		activeModel->roll(speed*-5);
		break;
	case 'q':
		activeModel->roll(speed*5);
		break;
	case 'w':
		activeModel->moveForward(speed);
		break;
	case 's':
		activeModel->moveBackward(speed);
		break;
	case 'a':
		activeModel->strafeLeft(speed);
		break;
	case 'd':
		activeModel->strafeRight(speed);
		break;
	case 'r':
		activeModel->reset();
		activeModel->animations.clear();
		break;
	case 'c':
		l->flyUp(speed);
		break;
	case 'C':
		l->flyDown(speed);
		break;
	case 'f':
		glutWarpPointer(WIDTH/2, HEIGHT/2);
		glutPassiveMotionFunc(passiveMotionFunc);
		break;
	case 'g':
		glutPassiveMotionFunc(NULL);
		break;
	case 'o':
		if(activeModel != nc)
			activeModel->lookAt(nc->position);
		break;
	case 'p':
		newModel->pitch(90.0f);
		break;
	case 'B':
		printf("%s - %p ", newModel->dataFile, newModel);
		printVector(newModel->position);

		printf("%s - %p ", newModel2->dataFile, newModel2);
		printVector(newModel2->position);

		printf("%s - %p ", newModel3->dataFile, newModel3);
		printVector(newModel3->position);
		break;
	case 'b':
		printf("Camera\n");
		printf("upVector ");printVector(nc->getUpVector());
		printf("lookingAt ");printVector(nc->getLookingAt());
		printf("position ");printVector(nc->position);
		printf("angle: %f\n", acos(glm::dot(nc->getDirection(), nc->getUpVector())));
		printf("0: %s, 2: %s, 3: %s\n", newModel->dataFile, newModel2->dataFile, newModel3->dataFile);
		break;
	case 'v':
		printf("Model\n");
		printf("upVector ");printVector(activeModel->getUpVector());
		printf("lookingAt ");printVector(activeModel->getLookingAt());
		printf("position ");printVector(activeModel->position);
		printf("angle: %f\n", acos(glm::dot(activeModel->getDirection(), activeModel->getUpVector())));
		break;
	case '1':
		nc->addAnimation(new FollowObjectAnimation(nc, newModel2, -3.0f));
		break;
	case '2':
		nc->addAnimation(new CurveMovementAnimation(glm::vec3(0.0f, 10.0f, 0.0f)));
		break;
	case '3':
		activeModel->addAnimation(new PitchAnimation());
		break;
	case '4':
		printf("change tex animation\n");
		newModel2->addAnimation(new ChangeTexAnimation("data\\ship\\raider.bmp", "data\\ship\\raider2.bmp"));
		break;
	case '7':
		nc->translateTo(glm::vec3(5.0f, 6.0f, 0.0f));
		nc->lookAt(glm::vec3(1.0f));
		break;
	case '8':
		nc->translateTo(glm::vec3(15.0f, 8.0f, 13.0f));
		nc->lookAt(glm::vec3(0.0f));
		break;
	case '9':
		nc->animations.clear();
		nc->addAnimation(new CurveMovementAnimation2(glm::vec3(0.0f, 5.0f, 0.0f)));
		break;
	case 'i':
		newModel2->lookAt(nc->position);
		break;
	case 'j':
		nc->lookAt(newModel2->position);
		break;
	case 'l':
		activeModel->animations.clear();
		break;
	}

}

glm::vec3 computeCameraDirection(int yaw, int pitch){
	glm::vec3 cameraViewDirection;
	cameraViewDirection.x = std::cos(pitch) * std::sin(yaw);
	cameraViewDirection.y = std::sin(pitch);
	cameraViewDirection.z = std::cos(pitch) * std::cos(yaw); 
	return cameraViewDirection;
}

void passiveMotionFunc(int x, int y){

	if(x != WIDTH/2 || y != HEIGHT/2){


		activeModel->pitch(0.2*(y - HEIGHT/2));
		activeModel->yaw(-0.2*(x - WIDTH/2));

		glutWarpPointer(WIDTH/2, HEIGHT/2);
		glutPostRedisplay();

	}
}

void displayFunc(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	sc->drawScene();
	spotLight->rotationQuaternion = nc->rotationQuaternion;
	spotLight->position = nc->position;
}

void timerFunc(int){

	time += 0.05;
	if(time >= 10000.0f)
		time -= 10000.f;

	sc->updateAnimations(time);

	glutTimerFunc(33, timerFunc, 0);

	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y){

	if(button == 3 || button == 4){  // mouse wheel event
		if(state == GLUT_UP){
			return;
		}

		if(button == 3){
			activeModel->roll(5.0f);
		}
		else{
			activeModel->roll(-5.0f);
		}
	}

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		int modelID = 5;

		glReadPixels(x, HEIGHT - y - 1, 1, 1, GL_STENCIL_INDEX, GL_INT, &modelID);

		NewModel *m = sc->getModelById(modelID);

		if(m != NULL){

			printf("Kliknuto na model s cislem %d - %s - %p\n", modelID, m->dataFile, m);

			if(activeModel != NULL){
				activeModel->color = glm::vec3(0.0f, 0.0f, 0.0f);
				activeModel->animations.clear();
			}
			activeModel = m;
			activeModel->color = glm::vec3(0.0f, 1.0f, 0.0f);
			//activeModel->addAnimation(new PitchAnimation());
		}

		if(modelID == 0){
			printf("Kliknuto na pozadi\n");
			activeModel = nc;// Pozadi
		}

		printf("[%d,%d]\n",x,y);


	}
}


void specialFunc(int key, int mouseX, int mouseY) {

	switch(key){
	case GLUT_KEY_F1:
		nc->translateTo(glm::vec3(-5.0f, -7.0f, 0.0f));
	}

}

void reshapeFunc(int newWidth, int newHeight){
	WIDTH = newWidth;
	HEIGHT = newHeight;

	glViewport(0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
}

void loadAndPlaceRocks(){

	GLuint texture;

	Cube* c = new Cube();
	c->reset();
	c->materialAmbient = glm::vec3(0.25f);
	c->materialSpecular = glm::vec3(0.774f);
	c->materialDiffuse = glm::vec3(0.4f);
	c->materialShininess = 76.8f;
	c->addTexture("data\\rock.jpg");
	sc->addModel(c);
	c->translateTo(glm::vec3(-6.45f, -7.2f, -15.1f));

	texture = c->texture;

	c = new Cube();
	c->reset();
	c->materialAmbient = glm::vec3(0.25f);
	c->materialSpecular = glm::vec3(0.774f);
	c->materialDiffuse = glm::vec3(0.4f);
	c->materialShininess = 76.8f;
	sc->addModel(c);
	c->texture = texture;
	c->useTexture = true;
	c->translateTo(glm::vec3(-44.7f, 5.0f, 11.48f));

	c = new Cube();
	c->reset();
	c->materialAmbient = glm::vec3(0.25f);
	c->materialSpecular = glm::vec3(0.774f);
	c->materialDiffuse = glm::vec3(0.4f);
	c->materialShininess = 76.8f;
	sc->addModel(c);
	c->texture = texture;
	c->useTexture = true;
	c->translateTo(glm::vec3(-8.2f, -7.9f, 7.6f));


}

int main(int argc, char** argv) {

	time = 0;

	GLuint programID;

	glutInit(&argc, argv);

	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow(TITLE);

	glutDisplayFunc(displayFunc);
	glutKeyboardFunc(keyboardFunc);
	glutMouseFunc(mouseFunc);
	glutTimerFunc(33, timerFunc, 0);
	glutSpecialFunc(specialFunc);
	glutReshapeFunc(reshapeFunc);


	// initialize GL, devil etc.
	if(!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);

	//**************************************************************
	sc = new Scene();
	loadAndPlaceRocks();

	l = new Light();
	l->position = glm::vec3(1.0f, 0.0f, 0.0f);
	l->ambient = glm::vec3(0.1f);
	l->diffuse = glm::vec3(2.0f);
	l->specular = glm::vec3(2.0f);
	l->intensity = 8.0f;
	sc->addPointLight(l);

	Light* directionalLight = new Light();
	directionalLight->position = vec3(10.0, 10.0, 0.0);
	directionalLight->ambient = glm::vec3(0.2f);
	directionalLight->diffuse = glm::vec3(1.0f);
	directionalLight->specular = glm::vec3(1.0f);
	directionalLight->intensity = 5.0f;
	sc->addDirectionalLight(directionalLight);

	spotLight = new Light();
	spotLight->reset();
	spotLight->spotLightAngle = 0.86f;
	spotLight->ambient = glm::vec3(0.2f);
	spotLight->diffuse = glm::vec3(1.0f);
	spotLight->specular = glm::vec3(1.0f);
	spotLight->intensity = 2.0;
	sc->addSpotLight(spotLight);

	newModel = new NewModel("data\\evo1.obj");
	newModel->reset();
	newModel->addTexture("data\\ship\\raider.bmp");
	newModel->addAnimation(new CurveMovementAnimation2(glm::vec3(0.0f, 15.0f, 0.0f)));
	sc->addModel(newModel);
	newModel->scale(5.0f);

	newModel->materialAmbient = glm::vec3(0.41f);
	newModel->materialSpecular = glm::vec3(0.64f);
	newModel->materialDiffuse = glm::vec3(0.8f);
	newModel->materialShininess = 120.8f;

	newModel2 = new NewModel("data\\ship\\raider.obj");
	newModel2->reset();
	newModel2->addTexture("data\\ship\\raider.bmp");
	sc->addModel(newModel2);

	newModel2->materialAmbient = glm::vec3(0.25f);
	newModel2->materialSpecular = glm::vec3(0.774f);
	newModel2->materialDiffuse = glm::vec3(0.4f);
	newModel2->materialShininess = 76.8f;

	//********** SKYBOX *********
	
	SkyBox* skybox = new SkyBox();
	sc->skybox = skybox;
	

	//****** TERRAIN ************
	
	terrain = new NewModel("data\\terrain\\terrain.obj");
	terrain->reset();
	terrain->addTexture("data\\terrain\\terraintex.jpg");
	terrain->translateTo(glm::vec3(0.0f, 1.0f, 0.0f));
	terrain->scale(50.0f);
	terrain->roll(180.0f);
	sc->terrain = terrain;

	terrain->materialAmbient = glm::vec3(0.25f);
	terrain->materialSpecular = glm::vec3(0.774f);
	terrain->materialDiffuse = glm::vec3(0.4f);
	terrain->materialShininess = 76.8f;

	nc = new NewCamera();
	nc->reset();
	nc->translateTo(glm::vec3(12.0f, 9.0f, -24.0f));
	sc->setActiveCamera(nc);

	//spotLight->addAnimation(new FollowObjectAnimation(spotLight, activeModel, 0.1f));
	newModel2->addAnimation(new CurveMovementAnimation(glm::vec3(1.0f)));
	//nc->addAnimation(new FollowObjectAnimation(nc, newModel, -4.0f));
	//nc->addAnimation(new StalkingAnimation(nc, newModel));

	activeModel = nc;
	printf("GLUT MAIN LOOP\n");
	glutMainLoop();

	return 0;
}


void printVector(glm::vec3 vector){
	printf("(%f, %f, %f)\n", vector.x, vector.y, vector.z);
}

void printMatrix(glm::mat4 matrix){
	int ii;
	for(ii = 0; ii < 16; ii++){
		if(ii % 4 == 0)
			printf("\n");
		printf("%+.1f ", glm::value_ptr(matrix)[ii]);
	}

	printf("\n");
}