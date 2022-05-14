/*
- This is a simple Ping Pong game that was developed by Marwan Esam
- The game simply consists of 2 players playing against each other. The player who scores 11 goals wins, simple.
- The controls: for the player on the left press 'w' to go up and 's' to go down (case insensitive),
and for the player on the right press "the arrow pointing to the top" to go up and "the arrow pointing to the bottom" to do down.
- while you are playing, the game gets more difficult as the ball starts to move faster if non of you is winningXD
- press the "esc" button if you want to exit the game.
this is pretty much the game, enjoy:)
*/
#include <gl/glut.h>
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <math.h>
using namespace std;
float theta;
int player1Score, player2Score, finalScore = 11;
float ballPosx, ballPosy, ballSpeedx = 0.00089, ballSpeedy = 0.00079;
float speedxtemp = ballSpeedx, speedytemp = ballSpeedy;
bool p1, p2, gameStart = true, duringGame, gameEnd;
int speedInc;
class playerLine {
public:
    float x1;
    float y1;
    float x2;
    float y2;
    float speed;
    float width;
    playerLine(float x1, float y1, float x2, float y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        speed = 0.11;
        width = 4;
    }
    void show() {
        glLineWidth(width);
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
    void update(unsigned char key) {
        if (key == 'w' || key == 'W' || key == GLUT_KEY_UP) {
            if (y1 < 0.95) {
                y1 += speed;
                y2 += speed;
            }
        }
        else if (key == 's' || key == 'S' || key == GLUT_KEY_DOWN) {
            if (y2 > -0.95) {
                y1 -= speed;
                y2 -= speed;
            }
        }
    }
};
playerLine player1 = playerLine(-0.9, 0.2, -0.9, -0.2);
playerLine player2 = playerLine(0.9, 0.2, 0.9, -0.2);
void ball() {
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        theta = i * 3.145 / 180;
        glVertex2f(cos(theta) * 0.105 / 2.5 + ballPosx, sin(theta) * 0.18 / 2.5 + ballPosy);
    }
    glEnd();
}
bool detectCollision() {
    float bx = ballPosx;
    if (bx < (player1.x1 + 0.05) && ballPosy < player1.y1 && ballPosy > player1.y2)
    {
        p1 = true;
        speedInc++;
        return true;
    }
    if (bx > (player2.x1 - 0.05) && ballPosy < player2.y1 && ballPosy > player2.y2)
    {
        p2 = true;
        speedInc++;
        return true;
    }
    return false;
}
void startGame() {
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();
    //show press enter to play
    glColor3f(0, 1, 0);
    glRasterPos2f(-0.14, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');
    glRasterPos2f(-0.12, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
    glRasterPos2f(-0.10, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(-0.08, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'S');
    glRasterPos2f(-0.06, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'S');
    glRasterPos2f(-0.02, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(0.00, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'N');
    glRasterPos2f(0.02, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'T');
    glRasterPos2f(0.04, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(0.06, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
}
void viewScore() {
    //player1 score
    glColor3f(1, 1, 1);
    glRasterPos2f(-0.9, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');
    glRasterPos2f(-0.88, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
    glRasterPos2f(-0.84, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'S');
    glRasterPos2f(-0.82, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'C');
    glRasterPos2f(-0.80, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
    glRasterPos2f(-0.78, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
    glRasterPos2f(-0.76, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(-0.74, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ':');
    string p1score = to_string(player1Score);
    glRasterPos2f(-0.72, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p1score.c_str()[0]);
    glRasterPos2f(-0.70, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p1score.c_str()[1]);
    // out of 11
    glColor3f(1, 1, 1);
    glRasterPos2f(-0.1, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
    glRasterPos2f(-0.08, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'U');
    glRasterPos2f(-0.06, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'T');
    glRasterPos2f(-0.02, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
    glRasterPos2f(0.00, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'F');
    glRasterPos2f(0.04, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
    glRasterPos2f(0.06, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');

    //player2 score
    glColor3f(1, 1, 1);
    glRasterPos2f(0.74, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');
    glRasterPos2f(0.76, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '2');
    glRasterPos2f(0.80, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'S');
    glRasterPos2f(0.82, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'C');
    glRasterPos2f(0.84, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
    glRasterPos2f(0.86, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
    glRasterPos2f(0.88, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(0.9, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ':');

    string p2score = to_string(player2Score);
    glRasterPos2f(0.92, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p2score.c_str()[0]);
    glRasterPos2f(0.94, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p2score.c_str()[1]);
}
void endGame() {
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();
    // show game ended
    glColor3f(1, 0, 0);
    glRasterPos2f(-0.14, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'G');
    glRasterPos2f(-0.12, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
    glRasterPos2f(-0.10, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'M');
    glRasterPos2f(-0.08, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(-0.04, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(-0.02, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'N');
    glRasterPos2f(0.00, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'D');
    glRasterPos2f(0.02, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(0.04, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'D');

    // show which player won the game
    glColor3f(0, 1, 0);
    glRasterPos2f(-0.16, -0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');
    glRasterPos2f(-0.14, -0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'L');
    glRasterPos2f(-0.12, -0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
    glRasterPos2f(-0.10, -0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
    glRasterPos2f(-0.08, -0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(-0.06, -0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
    glRasterPos2f(-0.02, -0.2);
    if (player1Score > player2Score)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
    else
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '2');
    glRasterPos2f(0.02, -0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'W');
    glRasterPos2f(0.04, -0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
    glRasterPos2f(0.06, -0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'N');
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    glPushMatrix();
    if (gameStart) {
        startGame();
    }
    if (duringGame) {
        glPushMatrix();
        viewScore();
        glPopMatrix();
        glPopMatrix();
        glPushMatrix();
        ball();
        glPopMatrix();
        glPushMatrix();
        player1.show();
        glPopMatrix();
        glPushMatrix();
        player2.show();
        glPopMatrix();
        if (detectCollision()) {
            ballSpeedx *= -1;
            if (p1)
            {
                ballPosx += 0.01;
                p1 = false;
            }
            else
            {
                ballPosx -= 0.01;
                p2 = false;
            }

        }
        if (speedInc == 20)
        {
            if (ballSpeedx > 0) {
                speedInc = 0;
                ballSpeedx += 0.0011;
                ballSpeedy += 0.0011;
            }
            else
            {
                speedInc = 0;
                ballSpeedx -= 0.0001;
                ballSpeedy -= 0.0001;
            }
        }

        ballPosy += ballSpeedy;
        ballPosx += ballSpeedx;
        if (ballPosy >= 1 || ballPosy <= -1) ballSpeedy *= -1;
        if (ballPosx >= 1 || ballPosx <= -1) {
            if (ballPosx >= 1) player1Score++;
            else player2Score++;
            ballSpeedx = speedxtemp;
            ballSpeedy = speedytemp;
            ballPosx = ballPosy = 0;
            if (player1Score == finalScore || player2Score == finalScore) {
                duringGame = false;
                gameEnd = true;
            }
        }
    }
    if (gameEnd) {
        endGame();
    }
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W' || key == 's' || key == 'S') player1.update(key);
    else if (key == 27) exit(0);
    else if (key == 13) {
        gameStart = false;
        duringGame = true;
    }
    glutPostRedisplay();
}
void specialkey(int key, int x, int y) {
    if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) player2.update(key);
    else if (key == 27) exit(0);
    glutPostRedisplay();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("PING PONG");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutFullScreen();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkey);
    glutMainLoop();
}