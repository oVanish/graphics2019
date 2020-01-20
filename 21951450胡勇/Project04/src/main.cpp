#pragma comment(lib,"winmm.lib")
#include "../headers/base.h"
#include <string>
#include "../headers/gltexture.h"
#include "../headers/glDrawer.h"
#include "../headers/glcamera.h"
#include "../headers/planet.h"
#include "../headers/glSkybox.h"
//#include "../headers/filesystem.h"
#include "../headers/glexplosion.h"
#include "../headers/trail.h"

//ȫ�ֱ�������
bool lighting = true;
int frontViewOnOff;//���ر�����ǰ��ͼ������ͼת��
glTexture *boxtex;//��պ�������ͼ����������պ���Ҫ�����޷�������������ھ���һ��������պ��������ϣ���һ��
glTexture *parttex;
glExplosion * glexp = new glExplosion(1, vec3(0, 0, 0), 1.0f, 0);
bool isexp = true;
int numexp;
float px, py, pz;
glTrail* trail;

//����ϵͳ
planet *sun; //̫��
planet *sx;  //ˮ��
planet *jx;  //����
planet *hx;  //����
planet *mx;  //ľ��
planet *tx;  //����
planet *twx; //������
planet *hwx; //������

planet * earth; //����
planet * moon;  //����

glCamera camera(vec3(0.0f, 0.0f, 10.0f)); //�������ʼλ��,w/s�����������ǰ���ƶ���a/d��������������ƶ��������������϶������������pitch/yaw��ת

int angle = 0; //���ı������������ǵ��ƶ���ת�����ٶ�����angleΪ�����������ı�angle��ת�ٶȻ�Ӱ���������ǵ��˶��ٶȣ��������ٶȺ;��룬�������Ƕ��ǰ���angle��Ա��������˶�

void SetLight(bool b)
{
	float amb[4] = { 1.0, 0.8, 0.8, 1 };
	float dif[4] = { 1.0, 1.0, 1.0, 1 };
	float pos[4] = { 0, 10, 0, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, dif);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	if (b)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}

	glShadeModel(GL_SMOOTH);
}

void init()
{
	boxtex = new glTexture("resources/�ǿ�ͼ.png", true);

	sun = new planet("resources/̫��.png", 0.0f, 1.0f, 1.0f, vec3(0.0f, 0.0f, 0.0f));
	sx = new planet("resources/ˮ��.png", 0.5f, 0.5f, 0.2f, vec3(1.4f, 0.4f, 0.0f));
	jx = new planet("resources/����.png", 0.5f, 0.5f, 0.2f, vec3(3.0f, -0.4f, 0.0f));
	earth = new planet("resources/����.png", 1.0f, 2.0f, 0.5f, vec3(5.0f, 2.0f, 8.0f));
	moon = new planet("resources/����.png", 0.5f, 0.5f, 0.2f, vec3(1.5f, 0.0f, 0.0f));
	hx = new planet("resources/����.png", 0.2f, 0.3f, 0.3f, vec3(7.0f, 0.0f, 0.0f));
	mx = new planet("resources/ľ��.png", 0.4f, 1.0f, 0.5f, vec3(10.0f, 0.0f, 0.0f));
	tx = new planet("resources/����.png", -0.4f, 0.2f, 1.0f, vec3(15.0f, 1.0f, 0.0f));
	twx = new planet("resources/������.png", 0.8f, 0.5f, 0.3f, vec3(17.0f, 0.0f, 0.0f));
	hwx = new planet("resources/������.png", 0.6f, 0.5f, 0.4f, vec3(19.0f, 0.8f, 0.0f));

	parttex = new glTexture("resources/particle.png");

	trail = new glTrail("resources/spawnflash.png");
	trail->setPath(vec3(0, 0, 0));

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	//��ʼ�������������
	drawInit();
}

void deinit()
{
	delete boxtex;
	delete sun;
	delete sx;
	delete jx;
	delete earth;
	delete moon;
	delete hx;
	delete mx;
	delete tx;
	delete twx;
	delete hwx;
	delete parttex;
	delete trail;
	delete glexp;
	drawDeInit();
}


static void DrawEarthAndMoon(planet *earth, planet *moon)
{
	glPushMatrix();//����ת+��ת��Χ��̫����
	earth->texture->MakeCurrent();

	glRotatef(angle*earth->aroundRotatedSpeed, 0.0f, 1.0f, 0.0f);
	glTranslatef(earth->pos.x, earth->pos.y, earth->pos.z);
	glRotatef(angle*earth->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);
	drawSphere(earth->radius, 20, 20, true);

	glPushMatrix();//����ת+��ת��Χ�Ƶ���
	moon->texture->MakeCurrent();
	glRotatef(angle*moon->aroundRotatedSpeed, 0.0f, 1.0f, 0.0f);
	glTranslatef(moon->pos.x, moon->pos.y, moon->pos.z);
	glRotatef(angle*moon->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);
	drawSphere(moon->radius, 20, 20, true);
	glPopMatrix();

	glPopMatrix();
}
static void DrawOtherPlanet(planet * p)
{
	glPushMatrix();
	p->texture->MakeCurrent();
	glRotatef(angle*p->aroundRotatedSpeed, 0.0f, 1.0f, 0.0f);
	glTranslatef(p->pos.x, p->pos.y, p->pos.z);
	glRotatef(angle*p->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);
	drawSphere(p->radius, 20, 20, true);
	glPopMatrix();
}

static void DrawTrail(planet * p)
{
	glPushMatrix();
	glRotatef(angle*p->aroundRotatedSpeed*2.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(p->pos.x + 0.4f, p->pos.y + 0.3, p->pos.z);
	glPushMatrix();
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	trail->draw(camera.pos);
	glPopMatrix();
	glRotatef(angle*p->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);
	drawSphere(p->radius, 20, 20, true);
	glPopMatrix();
}

static void DrawOtherPlanet2(planet * p)
{
	glPushMatrix();
	p->texture->MakeCurrent();

	glRotatef(angle*p->aroundRotatedSpeed, 0.0f, 1.0f, 0.0f);

	glTranslatef(p->pos.x, p->pos.y, p->pos.z);


	glRotatef(angle*p->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);

	drawSphere(p->radius, 20, 20, true);

	glPushMatrix();
	glRotatef(85, 1.0f, 0.0f, 0.0f);

	drawDisk(1.5, 3, 20);

	glPopMatrix();
	glPopMatrix();

}
void DrawJX()
{
	glPushMatrix();
	jx->texture->MakeCurrent();

	glRotatef(angle*jx->aroundRotatedSpeed * 2, 1.0, 1.0, 1.0);

	glTranslatef(5.0f, 0.0, 0.0f);
	glRotatef(angle*jx->aroundRotatedSpeed * 2, 0.0f, 0.0f, 1.0f);

	drawSphere(jx->radius, 20, 20, true);
	glPopMatrix();
}
void DrawHX()
{
	glPushMatrix();
	hx->texture->MakeCurrent();

	glRotatef(angle*hx->aroundRotatedSpeed * 2, -1.0, -1.0, 0.0);

	glTranslatef(5.0f, 0.0, 0.0f);

	glRotatef(angle*hx->aroundRotatedSpeed * 2, 0.0f, 0.0f, 1.0f);

	drawSphere(hx->radius, 20, 20, true);

	glPopMatrix();

}
void testdraw1(planet *p)
{
	glPushMatrix();
	p->texture->MakeCurrent();

	glRotatef(45, 1.0, 0.0, 0.0);
	glRotatef(angle*p->aroundRotatedSpeed * 2, 0.0f, 1.0f, 0.0f);

	glTranslatef(5.0f, 0, 0.0f);
	glRotatef(angle*p->aroundRotatedSpeed * 2, 0.0f, 0.0f, 1.0f);

	drawSphere(p->radius, 20, 20, true);
	glPopMatrix();
}

void DrawSolarSystem(planet *sun)
{
	sun->texture->MakeCurrent();

	SetLight(lighting);
	glTranslatef(sun->pos.x, sun->pos.y, sun->pos.z);
	glRotatef(angle*sun->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);
	drawSphere(sun->radius, 50, 50, true);
	DrawEarthAndMoon(earth, moon);//���»���
	DrawOtherPlanet(sx);
	DrawOtherPlanet(jx);
	DrawOtherPlanet(twx);
	DrawOtherPlanet(hwx);
	//����Ȧ����
	DrawOtherPlanet2(mx);
	DrawOtherPlanet2(tx);
	DrawTrail(jx);
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:		//ESC
		exit(0);	//�˳�ϵͳ
		break;
	case 'w'://�������ǰ�˶�

		camera.pos -= camera.forward*0.5;
		glutPostRedisplay();
		break;
	case 's'://���������˶�
		camera.pos += camera.forward*0.5;

		glutPostRedisplay();
		break;
	case 'a'://����������˶�

		camera.pos -= camera.right *0.5;
		glutPostRedisplay();
		break;
	case 'd'://����������˶�

		camera.pos += camera.right*0.5;
		glutPostRedisplay();
		break;
	case 'f'://����ͼ�Ͷ���ͼ�л�

		frontViewOnOff ^= 1;
		glutPostRedisplay();
		break;
	case 'l'://��Դ����
		lighting = !lighting;
		glutPostRedisplay();
		break;
	}
}


void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, GLfloat(w) / h, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
}

void creatExplosion(float x, float y, float z, int num, float spread)
{
	if (glexp != NULL) { delete glexp; glexp = NULL; }
	glexp = new glExplosion(num, vec3(0, 0, 0), spread, parttex->m_tex);
	px = x, pz = z, py = y;
	isexp = false;
	numexp = 0;
}

void  drawExplosion()
{
	glPushMatrix();
	glTranslatef(px, py, pz);
	if (isexp == false)
	{
		glexp->Render();
		isexp = true;
	}
	if (isexp)
	{
		glexp->Update(0.03f);
		isexp = false;
	}
	glPopMatrix();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.update();

	//�������ͼ�Ļ�������x����ת90��
	glRotatef(frontViewOnOff*90.0f, 1.0f, 0.0f, 0.0f);

	//������պ�
	glDrawSkyBox(boxtex, 0.0f, 0.0f, 0.0f, 1000.0f, 1000.0f, 1000.0f);

	DrawJX();
	DrawHX();
	DrawSolarSystem(sun);

	if (numexp > 100)
	{
		creatExplosion(1.0f, 1.0f, 1.0f, 100, 1.5f);
	}

	drawExplosion();

	angle += 2;
	numexp++;

	glutSwapBuffers();
}

void myTimerFunc(int val)
{
	myDisplay();
	glutTimerFunc(25, myTimerFunc, 0);
}

int  main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("SolarSystem");
	init();
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(&myKeyboardFunc);
	glutTimerFunc(25, myTimerFunc, 0);
	glutMainLoop();
	deinit();
	return 0;
}