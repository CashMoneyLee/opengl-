#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <math.h>

static double time = 0;
static double time2 = 0;
static double time3 = 0;
static double time4 = 0;
static double time5 = 0;

GLfloat R_Arm_x = 0;
GLfloat R_Arm_y = 0;
GLfloat L_Arm_x = 0;
GLfloat L_Arm_y = 0;
GLfloat R_Leg_x = 0;
GLfloat R_Leg_y = 0;
GLfloat L_Leg_x = 0;
GLfloat L_Leg_y = 0;
GLfloat R = 0;
GLfloat R2 = 0;

GLUquadricObj* cyl;

int a = 0;
int b = 0;
int c = 0;

static int flag = 0;
static int key = 0;

#define RUN 1     
#define JAP  2    
#define ROCKET  3    
#define YUNA   4
#define PUNCH_SEQUENCE 5
#define EXIT   6

void glInit(void) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    GLfloat ambientlight[] = { 0.3f,0.3f,0.3f,1.0f };
    GLfloat diffuseLight[] = { 0.7f, 0.7f,0.7f,1.0f };
    GLfloat specular[] = { 1.0f, 1.0f,1.0f,1.0f };
    GLfloat specref[] = { 1.0f, 1.0f,1.0f,1.0f };
    GLfloat position[] = { 400,0,3000,0, -700.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, diffuseLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, position);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}
void Draw_Color(int i) {
    if (i == RUN) {
        glColor3f(0.0, 1.0, 0.0);
    }
    else if (i == JAP) {
        glColor3f(1.0, 1.0, 0.0);
    }
    else if (i == ROCKET) {
        glColor3f(0.0, 1.0, 1.0);
    }
    else if (i == YUNA) {
        glColor3f(1.0, 0.0, 1.0);
    }
    else if (i == PUNCH_SEQUENCE) {
        glColor3f(1.0, 0.0, 1.0);
    }
    else if (i == EXIT) {
        glColor3f(0.2, 0.2, 0.2);
    }
}

void Change_Wire_Or_Solid(int i) {
    if (flag == 1)
        gluQuadricDrawStyle(cyl, GLU_LINE);
}

void DrawL_Arm(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glRotatef(x, a, b, c);
    glRotatef(90.0, 1.0, 0.0, 0.0);

    glTranslatef(0.25, 0.0, 0.0);
    glRotatef(15.0, 0.0, 1.0, 0.0);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
}

void DrawL_Hand(int y, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0.0, 0.0, 0.22);
    glRotatef(y, a, b, c);
    Change_Wire_Or_Solid(flag);
    if (key == YUNA) gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1);

    else gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
    glPopMatrix();

}

void DrawL_HandRocket() {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0.0, 0.0, R);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
    glPopMatrix();
}

void DrawR_Arm(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glRotatef(x, a, b, c);
    glRotatef(90, 1, 0, 0);

    glTranslatef(-0.25, 0, 0);
    glRotatef(-15, 0, 1, 0);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
}

void DrawR_Hand(int y, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0.0, 0.0, 0.22);
    glRotatef(y, a, b, c);
    Change_Wire_Or_Solid(flag);
    if (key == YUNA) gluCylinder(cyl, 0.05, 0.02, 0.2, 50, 1);

    else gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
    glPopMatrix();

}

void DrawR_HandRocket() {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0.0, 0.0, R2);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
    glPopMatrix();
}

void DrawBody(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(x, a, b, c);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);
    glPopMatrix();
}

void DrawL_Legs(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.1, 0.0, 0.42);
    glRotatef(x, a, b, c);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);
}

void DrawL_foot(int y, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0.0, 0.0, 0.18);
    glRotatef(y, a, b, c);
    Change_Wire_Or_Solid(flag);
    if (key == YUNA) gluCylinder(cyl, 0.05, 0.03, 0.2, 50, 1);
    else gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
    glPopMatrix();
}

void DrawR_Legs(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(-0.1, 0.0, 0.42);
    glRotatef(x, a, b, c);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);
}

void DrawR_foot(int y, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0.0, 0.0, 0.18);
    glRotatef(y, a, b, c);
    Change_Wire_Or_Solid(flag);
    if (key == YUNA) gluCylinder(cyl, 0.05, 0.03, 0.2, 15, 1);
    else gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
    glPopMatrix();
}

void DrawNeck() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    cyl = gluNewQuadric();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, -0.045);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1);
    glPopMatrix();
}

void DrawGround() {
    Draw_Color(flag);
    glTranslatef(0.0, -2.73, 0.0);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1);
    Change_Wire_Or_Solid(flag);
    gluSphere(cyl, 2.5, 30, 90);
}

void DrawHead() {
    glTranslatef(0.0, 0.02, 0.0);
    glPushMatrix();
    cyl = gluNewQuadric();
    Change_Wire_Or_Solid(flag);
    Draw_Color(key);
    gluSphere(cyl, 0.20, 30, 10);

    glRotatef(90.0, 1.0, 0.0, 0.0);

    glTranslatef(-0.16, 0.0, -0.22);
    glRotatef(35.0, 0.0, 1.0, 0.0);
    gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
    glPopMatrix();
    glPushMatrix();

    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.16, 0.0, -0.22);
    glRotatef(-35.0, 0.0, 1.0, 0.0);
    gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
    glPopMatrix();
    glPushMatrix();

    glTranslatef(-0.1, 0.1, 0.13);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(cyl, 0.03, 10, 10);
    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.1, 0.1, 0.13);
    gluSphere(cyl, 0.03, 10, 10);
    glPopMatrix();
}

void DrawAndroid() {
    DrawBody(0, 0, 0, 0);
    DrawNeck();
    DrawHead();
    DrawR_Arm(R_Arm_x, 1, 0, 0);
    if (key == ROCKET)
        DrawR_HandRocket();
    else
        DrawR_Hand(R_Arm_y, 1, 0, 0);
    DrawL_Arm(L_Arm_x, 1, 0, 0);
    if (key == ROCKET) DrawL_HandRocket();
    else DrawL_Hand(L_Arm_y, 1, 0, 0);
    DrawL_Legs(L_Leg_x, 1, 0, 0);
    DrawL_foot(L_Leg_y, 1, 0, 0);
    DrawR_Legs(R_Leg_x, 1, 0, 0);
    DrawR_foot(R_Leg_y, 1, 0, 0);
}

bool isJumping = false; // 점프 상태를 나타내는 변수
bool isRotating = false; // 회전 상태를 나타내는 변수
bool isReversing = false; // 회전 방향 반전 상태를 나타내는 변수
float jumpHeight = 0.0;  // 현재 점프 높이
float jumpSpeed = 0.1;   // 점프 속도
float gravity = 0.01;    // 중력
float rotationAngle = 0.0; // 회전 각도
float rotationSpeed = 5.0; // 회전 속도 (더 빠르게 회전하도록 설정)

void Run() {
    glLoadIdentity();

    // 팔과 다리 움직임 (달리기)
    L_Arm_x = sin(time) * 80;
    R_Arm_x = -L_Arm_x;
    R_Arm_y = -abs(int(sin(time) * 60 + 50));
    L_Arm_y = -abs(int(-sin(time) * 60 + 50));
    R_Leg_y = abs(int(sin(time) * 30 - 30));
    L_Leg_y = abs(int(sin(time) * 30 - 30));
    R_Leg_x = sin(time) * 60;
    L_Leg_x = -R_Leg_x;

    // 점프 동작 처리
    if (isJumping) {
        jumpHeight += jumpSpeed; // 점프 상승
        jumpSpeed -= gravity;    // 중력으로 점프 속도 감소

        if (jumpHeight <= 0) {  // 땅에 도달하면 점프 종료
            jumpHeight = 0.0;
            jumpSpeed = 0.1;    // 초기 속도로 리셋
            isJumping = false;
        }
    }

    cyl = gluNewQuadric();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    DrawGround();
    glLoadIdentity();

    // 달리기 시 캐릭터의 약간의 흔들림 추가
    glRotatef(-230.0, 0, 1, 0);
    glRotatef(abs(int(sin(time) * 16)), 1, 0, 0);
    glRotatef(sin(time) * 16, 0, 1, 0);

    // 점프 높이를 적용
    float i = abs(int(sin(time) * 0.08));
    glPushMatrix();
    glTranslatef(0.0, i + jumpHeight, 0); // 점프 높이 반영
    glTranslatef(0.0, 0.5, 0.0);

    // 회전 적용 (점프 후 'g'키를 눌렀을 때)
    if (isRotating) {
        rotationAngle += rotationSpeed; // 빠르게 회전
        if (rotationAngle >= 180.0) {
            rotationAngle = 180.0; // 180도까지만 회전
            isRotating = false; // 회전 끝났으면 상태 리셋
        }
    }

    // 회전 상태 반전 처리
    if (isReversing) {
        rotationAngle -= rotationSpeed; // 회전 각도를 반대로 되돌림
        if (rotationAngle <= 0.0) {
            rotationAngle = 0.0; // 0도까지만 되돌림
            isReversing = false; // 반전 상태 리셋
        }
    }

    glRotatef(rotationAngle, 0, 1, 0); // 회전 적용

    DrawAndroid();
    glutSwapBuffers();
}

// 점프 시작 함수
void StartJump() {
    if (!isJumping) { // 점프 중이 아닐 때만 실행
        isJumping = true;
    }
}

// 회전 시작 함수
void StartRotation() {
    if (!isRotating && !isJumping) { // 점프 중이 아니고, 회전 중이 아닐 때만 실행
        isRotating = true;
    }
}

// 회전 반전 시작 함수
void StartReverseRotation() {
    if (!isReversing && !isJumping) { // 점프 중이 아니고, 반전 중이 아닐 때만 실행
        isReversing = true;
    }
}

void HandleKeyPress(unsigned char key, int x, int y) {
    if (key == ' ') { // Spacebar를 눌렀을 때
        StartJump();
    }
    if (key == 'g') { // 'g' 키를 눌렀을 때
        StartRotation();
    }
    if (key == 'y') { // 'y' 키를 눌렀을 때
        StartReverseRotation(); // 회전 반전 시작
    }
}

void Jap() {
    glLoadIdentity();
    L_Arm_x = (-40) + sin(time2) * 60;

    R_Arm_x = (-80) - L_Arm_x;

    R_Arm_y = -abs(int(cos(time2) * 80));

    L_Arm_y = -abs(int(-cos(time2) * 40));
    R_Leg_y = abs(int(-sin(time) * 30 - 20));

    L_Leg_y = abs(int(sin(time) * 30 - 20));
    R_Leg_x = sin(time) * 30;

    L_Leg_x = -R_Leg_x;

    cyl = gluNewQuadric();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    DrawGround();
    glLoadIdentity();

    glRotatef(-230.0, 0, 1, 0);
    glRotatef(sin(time) * 10, 0, 0, 1);

    float j = 0;
    j = abs(int(sin(time2) * 0.085));
    glPushMatrix();
    glTranslatef(0.0, j, 0);
    glTranslatef(0.0, 0.5, 0.0);
    DrawAndroid();
    glutSwapBuffers();
}




void ex() {
    glLoadIdentity();

    L_Arm_x = (-40) + sin(time2) * 60;
    R_Arm_x = (-80) - L_Arm_x;
    R_Arm_y = -abs(int(cos(time2) * 10));
    L_Arm_y = -abs(int(-cos(time2) * 10));
    R_Leg_y = abs(int(-sin(time) * 30 - 30));
    L_Leg_y = abs(int(sin(time) * 30 - 30));
    R_Leg_x = sin(time) * 60;
    L_Leg_x = -R_Leg_x;

    cyl = gluNewQuadric();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glRotatef(-180.0, 0, 1, 0);
    glRotatef(time4, 0, 0, 1);
    glScalef(0.4 / (sin(time3)), 0.4 / (sin(time3)), 0.4 / (sin(time3)));

    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    DrawAndroid();
    glutSwapBuffers();
}

void Show() {

}

void Rocket() {

}



void MyKeyboard(unsigned char KeyPressed, int x, int y) {
    switch (KeyPressed) {
    case 'w':
        flag = 1;
        break;
    case 's':
        flag = 0;
        break;
    case 'q':
        key = 6;
        break;
    }
}

void MyDisplay() {
    if (key == RUN) {
        Run();
        glPopMatrix();
    }
    else if (key == JAP) {
        Jap();
        glPopMatrix();
    }
    else if (key == ROCKET) {
        Rocket();
        glPopMatrix();
    }
    else if (key == YUNA) {
        Show();
        glPopMatrix();
    }

    else if (key == 5) {
        // 중지 기능 (필요시)
    }
    else if (key == EXIT) {
        ex();
        glPopMatrix();
    }
}


void MyTimer(int Value) {
    time = time + 0.1;
    time2 = time2 + 0.5;
    time3 = time3 + 0.01;

    time4 = time4 + 1.0;
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer, 1);
}

void MyMainMenu(int entryID) {
    key = entryID;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Catch Me If You Can");
    glInit();

    // 메인 메뉴 생성
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("Run", 1);
    glutAddMenuEntry("Jap", 2);
    glutAddMenuEntry("Shoot", 3);
    glutAddMenuEntry("Skate", 4);
    glutAddMenuEntry("Punch Sequence", 5); // 잽, 스트레이트, 훅, 어퍼컷 추가
    glutAddMenuEntry("중지", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // 키보드 입력 처리 (HandleKeyPress 사용)
    glutKeyboardFunc(HandleKeyPress);

    // 타이머와 디스플레이 함수 등록
    glutTimerFunc(40, MyTimer, 1);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}