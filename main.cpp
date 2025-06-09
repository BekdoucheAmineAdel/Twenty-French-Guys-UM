#include <stdio.h>
#include <GL/glut.h>

#include "loaders_src_files/imageloader.h"
#include "loaders_src_files/textureloader.h"
#include "square_src_files/square.h"
#include "audio_controller/audio_player.h"
#include "level_manager_src_files/level_manager.h"
#include "user_interactions_src_files/mouse_handler.h"
#include "game_settings.h"

AudioManager audioManager;

void handleKeypress(unsigned char key, int x, int y) {
	switch(G_gameState)
	{
		case MAIN_MENU:
			switch (key) {
				case 27: //Escape key
					audioManager.stopBackground();
					exit(0);
			}
			break;
		case GAME:
			switch (key) {
				case 27: //Escape key
					store_score();
					load_score();
					G_gameState = MAIN_MENU;
			}
			break;
		case GAME_WON:
			switch (key) {
				case 27: //Escape key
					store_score();
					load_score();
					G_gameState = MAIN_MENU;
			}
			break;
		case GAME_OVER:
			switch (key) {
				case 27: //Escape key
					store_score();
					load_score();
					G_gameState = MAIN_MENU;
			}
			break;
	}
}
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	load_square_images();
}
void handleResize(int w, int h) {
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
	glutReshapeWindow(WIDTH, HEIGHT);
}
void drawScene() {
	switch(G_gameState)
	{
		case MAIN_MENU:
			drawMenu();
			break;
		case GAME:
			drawGame();
			break;
		case GAME_WON:
			drawWin();
			break;
		case GAME_OVER:
			drawLose();
			break;
	}
	glutSwapBuffers();
}
void update(int value) {
	glutPostRedisplay();
	switch(G_gameState)
	{
		case MAIN_MENU:
			break;
		case GAME:
			level_timer();
			break;
		case GAME_WON:
			break;
		case GAME_OVER:
			break;
	}
    audioManager.update();
	Pa_Sleep(1000/FPS);
	glutTimerFunc(1000/FPS, update, 0);
}

void intialize_game()
{
    audioManager.loadAudioFile(1.0f, "background", "background.wav");
    audioManager.loadAudioFile(0.5f, "fusion", "fusion.wav");
    audioManager.playBackground("background");

	load_score();
	fill_winSquares();
	G_gameState = MAIN_MENU;
}
int main(int argc, char** argv) {
	intialize_game();

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutCreateWindow("20s");
	initRendering();
	srand(time(0));

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMotionFunc(motion_callback);
	glutMouseFunc(mouse_callback);
	glutTimerFunc(25, update, 0);
	glutMainLoop();

	audioManager.stopBackground();
	return 0;
}
