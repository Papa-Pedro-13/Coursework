#pragma once
#include "GL/glut.h"
#include <stdio.h>
#include <math.h>

#define SIZE 13

void printlogo(int res_x, int res_y) {
    int y_max = res_y / 6, y_min = res_y / 4;
    int letter = 20, space = 10, x_center = res_x / 2, x_min = x_center - 4 * letter - 3 * space - space / 2, x_max = x_center + 4 * letter + 3 * space + space / 2;
    int height = 40;
    glColor3f(0.849f, 0.869f, 0.861f); // Color
    glBegin(GL_LINES);
    glVertex2f(x_min, y_min); glVertex2f(x_min, y_min - height * 2); glVertex2f(x_min, y_min - height * 2); glVertex2f(x_min + letter, y_min - height * 2); glVertex2f(x_min + letter, y_min); glVertex2f(x_min + letter, y_min - height * 2); glVertex2f(x_min, y_min - height); glVertex2f(x_min + letter, y_min - height);
    x_min = x_min + letter + space; y_min = y_min - height;
    glVertex2f(x_min, y_min - height / 8); glVertex2f(x_min, y_min + height); glVertex2f(x_min, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min + letter, y_min + height / 4);
    x_min = x_min + letter + space;
    glVertex2f(x_min, y_min); glVertex2f(x_min, y_min + (height - 2.5)); glVertex2f(x_min, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min + letter, y_min + 10); glVertex2f(x_min, y_min + (height - 2.5)); glVertex2f(x_min + letter, y_min + (height - 2.5)); glVertex2f(x_min + letter, y_min + (height - 2.5)); glVertex2f(x_min + letter, y_min + (height - 12.5));
    x_min = x_min + letter + space;
    glVertex2f(x_min, y_min); glVertex2f(x_min, y_min + height - 5); glVertex2f(x_min, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min, y_min + height - 5); glVertex2f(x_min + letter, y_min + height - 5); glVertex2f(x_min + letter, y_min - 5); glVertex2f(x_min + letter, y_min + height);
    x_min = x_min + letter + space;
    glVertex2f(x_min, y_min - 5); glVertex2f(x_min, y_min + height); glVertex2f(x_min, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min + letter, y_min + height);
    x_min = x_min + letter + space;
    glVertex2f(x_min, y_min); glVertex2f(x_min, y_min + (height - 2.5)); glVertex2f(x_min, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min + letter, y_min + (height - 2.5)); glVertex2f(x_min + letter, y_min + (height - 2.5)); glVertex2f(x_min, y_min + (height - 2.5));
    x_min = x_min + letter + space;
    glVertex2f(x_min, y_min); glVertex2f(x_min, y_min + height);
    int xfori = x_min;
    x_min = x_min + space;
    glVertex2f(x_min, y_min); glVertex2f(x_min, y_min + (height - 2.5)); glVertex2f(x_min, y_min); glVertex2f(x_min + letter, y_min); glVertex2f(x_min, y_min + (height - 2.5)); glVertex2f(x_min + letter, y_min + (height - 2.5)); glVertex2f(x_min + letter, y_min + (height - 2.5)); glVertex2f(x_min + letter, y_min - height);

    glEnd();

    glBegin(GL_POLYGON);
    for (float i = 0; i < 2 * 3.14; i += 3.14 / 32)
        glVertex2f(xfori + 5 * sin(i), y_min - 10 + 5 * cos(i));
    glEnd();
}

void PaintNumbers(char* str, int x, int y, int linesize) {
    glBegin(GL_LINES);
    glColor3f(0.237f, 0.227f, 0.242f);
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '0' || str[i] == '2' || str[i] == '3' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9') {
            glVertex2f(x, y);
            glVertex2f(x + linesize, y);
        }
        if (str[i] == '0' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '8' || str[i] == '9') {
            glVertex2f(x, y);
            glVertex2f(x, y + linesize);
        }
        if (str[i] == '0' || str[i] == '2' || str[i] == '6' || str[i] == '8') {
            glVertex2f(x, y + linesize);
            glVertex2f(x, y + 2 * linesize);
        }
        if (str[i] == '0' || str[i] == '2' || str[i] == '3' || str[i] == '5' || str[i] == '6' || str[i] == '8' || str[i] == '9') {
            glVertex2f(x, y + 2 * linesize);
            glVertex2f(x + linesize, y + 2 * linesize);
        }
        if (str[i] == '0' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9') {
            glVertex2f(x + linesize, y + 2 * linesize);
            glVertex2f(x + linesize, y + linesize);
        }
        if (str[i] == '0' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '7' || str[i] == '8' || str[i] == '9') {
            glVertex2f(x + linesize, y + linesize);
            glVertex2f(x + linesize, y);
        }
        if (str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '8' || str[i] == '9') {
            glVertex2f(x, y + linesize);
            glVertex2f(x + linesize, y + linesize);
        }
        if (str[i] == '1') {
            glVertex2f(x + linesize / 2, y + linesize * 2);
            glVertex2f(x + linesize / 2, y);
        }
    }
    glEnd();
}

int PrintLevelBoxes(int res_x, int res_y, int height, int width, int space, int* levelbrick_x, int* levelbrick_y, int level_count) {
    glBegin(GL_QUADS);
    glColor3f(0.65f, 0.63f, 0.72f);

    int bonus_y = res_y - res_y / 3 - 30, lvl_y = res_y - res_y / 4, ly = lvl_y + height, start = space - 15;

    glVertex3f(0, bonus_y, 0);
    glVertex3f(0, bonus_y + height, 0);
    glVertex3f(res_x, bonus_y + height, 0);
    glVertex3f(res_x, bonus_y, 0);
    int levelbonusbrick_y = bonus_y + height;
    for (int i = 1; i < level_count; i++) {
        glColor3f(0.65f, 0.63f, 0.72f);
        glVertex3f(start, lvl_y, 0);
        glVertex3f(start, ly, 0);
        glVertex3f(start + width, ly, 0);
        glVertex3f(start + width, lvl_y, 0);
        char str[3] = { 0 };
        sprintf(str, "%d", i);
        glEnd(); glLineWidth(3.0);
        PaintNumbers(str, start + width / 2 - height / 8, lvl_y + height / 4 - height / 8, height / 4 + height / 8);
        glLineWidth(5.0); glBegin(GL_QUADS);
        levelbrick_x[i] = start; levelbrick_y[i] = ly;
        if (i == level_count / 2) start = start + width + space * 2 + 15;
        else start = start + width + space;
    }
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(res_x / 2 - height, bonus_y + height / 4); glVertex2f(res_x / 2 + height, bonus_y + height / 4); glVertex2f(res_x / 2 + height, bonus_y + height / 4); glVertex2f(res_x / 2 - height / 8, bonus_y + height / 10); glVertex2f(res_x / 2 + height, bonus_y + height / 4); glVertex2f(res_x / 2 - height / 10, bonus_y + height / 4 + height / 8);
    bonus_y += height / 2 + height / 4;
    glVertex2f(res_x / 2 - height, bonus_y); glVertex2f(res_x / 2 + height, bonus_y); glVertex2f(res_x / 2 - height, bonus_y); glVertex2f(res_x / 2 + height / 10, bonus_y - height / 10); glVertex2f(res_x / 2 - height, bonus_y); glVertex2f(res_x / 2 + height / 10, bonus_y + height / 10);
    glEnd();
    return levelbonusbrick_y;
}

void PaintFinishedLvl(int res_x, int res_y, int brick_w, int brick_h, int lastlevel) {
    glBegin(GL_QUADS);
    glColor3f(0.65f, 0.63f, 0.72f);
    glVertex3f(res_x / 2 - brick_w / 2, res_y / 4 + res_y / 16, 0);
    glVertex3f(res_x / 2 - brick_w / 2, res_y / 4 + res_y / 16 + brick_h, 0);
    glVertex3f(res_x / 2 + brick_w / 2, res_y / 4 + res_y / 16 + brick_h, 0);
    glVertex3f(res_x / 2 + brick_w / 2, res_y / 4 + res_y / 16, 0);
    glEnd();
    glLineWidth(3.0);

    if (lastlevel == 5) {
        glColor3f(0.237f, 0.227f, 0.242f);
        glLineWidth(2.0);
        glBegin(GL_LINES);
        int arrow_y = res_y / 4 + res_y / 16 + brick_h / 4;
        glVertex2f(res_x / 2 - brick_w / 4, arrow_y);
        glVertex2f(res_x / 2 + brick_w / 4, arrow_y);
        glVertex2f(res_x / 2 + brick_w / 4, arrow_y);
        glVertex2f(res_x / 2 + brick_w / 16, arrow_y - brick_h / 8);
        glVertex2f(res_x / 2 + brick_w / 4, arrow_y);
        glVertex2f(res_x / 2 + brick_w / 16, arrow_y + brick_h / 8);
        arrow_y += brick_h / 2;
        glVertex2f(res_x / 2 - brick_w / 4, arrow_y);
        glVertex2f(res_x / 2 + brick_w / 4, arrow_y);
        glVertex2f(res_x / 2 - brick_w / 4, arrow_y);
        glVertex2f(res_x / 2 - brick_w / 16, arrow_y - brick_h / 8);
        glVertex2f(res_x / 2 - brick_w / 4, arrow_y);
        glVertex2f(res_x / 2 - brick_w / 16, arrow_y + brick_h / 8);
        glEnd();
    }
    else {
        char str[3] = { 0 };
        sprintf(str, "%d", lastlevel);
        PaintNumbers(str, res_x / 2 - (brick_h / 4 + brick_h / 8) / 2, res_y / 4 + res_y / 16 + brick_h / 8, brick_h / 4 + brick_h / 8);
    }

}

void printRecordAfterLvl(int nextX, int linesize, int recordY, char* score) {
    int maxX = nextX;

    glVertex2f(maxX, recordY);
    glVertex2f(maxX, recordY + 2 * linesize);
    glVertex2f(maxX, recordY);
    glVertex2f(maxX + linesize / 2, recordY + linesize);
    glVertex2f(maxX + linesize / 2, recordY + linesize);
    glVertex2f(maxX + linesize, recordY);
    glVertex2f(maxX + linesize, recordY);
    glVertex2f(maxX + linesize, recordY + 2 * linesize);
    maxX = maxX + linesize + 5;

    glVertex2f(maxX, recordY);
    glVertex2f(maxX, recordY + 2 * linesize);
    glVertex2f(maxX, recordY);
    glVertex2f(maxX + linesize, recordY);
    glVertex2f(maxX + linesize, recordY);
    glVertex2f(maxX + linesize, recordY + 2 * linesize);
    glVertex2f(maxX, recordY + linesize);
    glVertex2f(maxX + linesize, recordY + linesize);
    maxX = maxX + linesize + 5;

    glVertex2f(maxX, recordY);
    glVertex2f(maxX + linesize, recordY + 2 * linesize);
    glVertex2f(maxX + linesize, recordY);
    glVertex2f(maxX, recordY + 2 * linesize);
    maxX = maxX + linesize + 5;
    glVertex2f(maxX, recordY + linesize / 2);
    glVertex2f(maxX, recordY + linesize / 2 + 2);
    glVertex2f(maxX, recordY + linesize + linesize / 2);
    glVertex2f(maxX, recordY + linesize + linesize / 2 + 2);

    nextX += 60;
    for (int i = 0; i < strlen(score); i++) {
        if (score[i] == '0' || score[i] == '2' || score[i] == '3' || score[i] == '5' || score[i] == '6' || score[i] == '7' || score[i] == '8' || score[i] == '9') {
            glVertex2f(nextX, recordY);
            glVertex2f(nextX + linesize, recordY);
        }
        if (score[i] == '0' || score[i] == '4' || score[i] == '5' || score[i] == '6' || score[i] == '8' || score[i] == '9') {
            glVertex2f(nextX, recordY);
            glVertex2f(nextX, recordY + linesize);
        }
        if (score[i] == '0' || score[i] == '2' || score[i] == '6' || score[i] == '8') {
            glVertex2f(nextX, recordY + linesize);
            glVertex2f(nextX, recordY + 2 * linesize);
        }
        if (score[i] == '0' || score[i] == '2' || score[i] == '3' || score[i] == '5' || score[i] == '6' || score[i] == '8' || score[i] == '9') {
            glVertex2f(nextX, recordY + 2 * linesize);
            glVertex2f(nextX + linesize, recordY + 2 * linesize);
        }
        if (score[i] == '0' || score[i] == '3' || score[i] == '4' || score[i] == '5' || score[i] == '6' || score[i] == '7' || score[i] == '8' || score[i] == '9') {
            glVertex2f(nextX + linesize, recordY + 2 * linesize);
            glVertex2f(nextX + linesize, recordY + linesize);
        }
        if (score[i] == '0' || score[i] == '2' || score[i] == '3' || score[i] == '4' || score[i] == '7' || score[i] == '8' || score[i] == '9') {
            glVertex2f(nextX + linesize, recordY + linesize);
            glVertex2f(nextX + linesize, recordY);
        }
        if (score[i] == '2' || score[i] == '3' || score[i] == '4' || score[i] == '5' || score[i] == '6' || score[i] == '8' || score[i] == '9') {
            glVertex2f(nextX, recordY + linesize);
            glVertex2f(nextX + linesize, recordY + linesize);
        }
        if (score[i] == '1') {
            glVertex2f(nextX + linesize, recordY + linesize * 2);
            glVertex2f(nextX + linesize, recordY);
        }
        nextX += 15;
    }
}

void PaintButtonsAfterLvl(int* lvlFinB_x, int* lvlFinB_y) {
    glColor3f(0.849f, 0.869f, 0.861f);
    glBegin(GL_QUADS);
    lvlFinB_x[1] = 233; lvlFinB_y[1] = 360;
    glVertex3f(233, 320, 0);
    glVertex3f(233, 360, 0);
    glVertex3f(313, 360, 0);
    glVertex3f(313, 320, 0);
    lvlFinB_x[0] = 123; lvlFinB_y[0] = 360;
    glVertex3f(123, 320, 0);
    glVertex3f(123, 360, 0);
    glVertex3f(203, 360, 0);
    glVertex3f(203, 320, 0);
    lvlFinB_x[2] = 343; lvlFinB_y[2] = 360;
    glVertex3f(343, 320, 0);
    glVertex3f(343, 360, 0);
    glVertex3f(423, 360, 0);
    glVertex3f(423, 320, 0);
    glEnd();

    glColor3f(0.237f, 0.227f, 0.242f);
    glBegin(GL_LINES);
    glVertex2f(143, 330); glVertex2f(183, 330); glVertex2f(143, 340); glVertex2f(183, 340); glVertex2f(143, 350); glVertex2f(183, 350);
    glVertex2f(263, 325); glVertex2f(263, 355); glVertex2f(263, 325); glVertex2f(258, 345); glVertex2f(263, 325); glVertex2f(268, 345); glVertex2f(283, 325); glVertex2f(283, 355); glVertex2f(283, 355); glVertex2f(278, 335); glVertex2f(283, 355); glVertex2f(288, 335);
    glVertex2f(363, 340); glVertex2f(403, 340); glVertex2f(403, 340); glVertex2f(383, 335); glVertex2f(403, 340); glVertex2f(383, 345);
    glEnd();
}

void PaintBall(float b_menu_x, float b_menu_y, float ball_r) {
    glColor3f(0.849f, 0.869f, 0.861f);
    glBegin(GL_POLYGON);
    for (float i = 0; i < 2 * 3.14; i += 3.14 / 32)
        glVertex2f(b_menu_x + ball_r * sin(i), b_menu_y + ball_r * cos(i));
    glEnd();
}

void saverecord(char* score, int rating, int* lvlrecords, int level) {
    int maxRecord = atoi(score);
    if (rating > maxRecord) {
        lvlrecords[level - 1] = rating;
        FILE* filetoscore = fopen("score.txt", "w");
        char tempstr[10] = { 0 };
        for (int i = 0; i < 6; i++) {
            fprintf(filetoscore, "%d", lvlrecords[i]);
            fprintf(filetoscore, "\n");
        }
        fclose(filetoscore);
    }
}

void PrintScoreOnLvl(int linesize, char* ratingstr, int rating) {
    if (rating != 0) {
        sprintf(ratingstr, "%d", rating);
        int RecBoxX = 273 - (strlen(ratingstr) * 15 - 5) / 2;
        RecBoxX -= 5;
        int ratinglength = strlen(ratingstr) * 15;
        glColor3f(0.5, 0.5, 0.5);
        int RecBoxY = 445;
        glBegin(GL_QUADS);
        glVertex2f(RecBoxX, RecBoxY);
        glVertex2f(RecBoxX, RecBoxY + 2 * linesize + 10);
        glVertex2f(RecBoxX + ratinglength + 5, RecBoxY + 2 * linesize + 10);
        glVertex2f(RecBoxX + ratinglength + 5, RecBoxY);
        glEnd();

        int nextX = RecBoxX + 5;
        int recordY = 450;
        glBegin(GL_LINES);
        glColor4f(0.237f, 0.227f, 0.242f, 1.0);

        for (int i = 0; i < strlen(ratingstr); i++) {
            if (ratingstr[i] == '0' || ratingstr[i] == '2' || ratingstr[i] == '3' || ratingstr[i] == '5' || ratingstr[i] == '6' || ratingstr[i] == '7' || ratingstr[i] == '8' || ratingstr[i] == '9') {
                glVertex2f(nextX, recordY);
                glVertex2f(nextX + linesize, recordY);
            }
            if (ratingstr[i] == '0' || ratingstr[i] == '4' || ratingstr[i] == '5' || ratingstr[i] == '6' || ratingstr[i] == '8' || ratingstr[i] == '9') {
                glVertex2f(nextX, recordY);
                glVertex2f(nextX, recordY + linesize);
            }
            if (ratingstr[i] == '0' || ratingstr[i] == '2' || ratingstr[i] == '6' || ratingstr[i] == '8') {
                glVertex2f(nextX, recordY + linesize);
                glVertex2f(nextX, recordY + 2 * linesize);
            }
            if (ratingstr[i] == '0' || ratingstr[i] == '2' || ratingstr[i] == '3' || ratingstr[i] == '5' || ratingstr[i] == '6' || ratingstr[i] == '8' || ratingstr[i] == '9') {
                glVertex2f(nextX, recordY + 2 * linesize);
                glVertex2f(nextX + linesize, recordY + 2 * linesize);
            }
            if (ratingstr[i] == '0' || ratingstr[i] == '1' || ratingstr[i] == '3' || ratingstr[i] == '4' || ratingstr[i] == '5' || ratingstr[i] == '6' || ratingstr[i] == '7' || ratingstr[i] == '8' || ratingstr[i] == '9') {
                glVertex2f(nextX + linesize, recordY + 2 * linesize);
                glVertex2f(nextX + linesize, recordY + linesize);
            }
            if (ratingstr[i] == '0' || ratingstr[i] == '1' || ratingstr[i] == '2' || ratingstr[i] == '3' || ratingstr[i] == '4' || ratingstr[i] == '7' || ratingstr[i] == '8' || ratingstr[i] == '9') {
                glVertex2f(nextX + linesize, recordY + linesize);
                glVertex2f(nextX + linesize, recordY);
            }
            if (ratingstr[i] == '2' || ratingstr[i] == '3' || ratingstr[i] == '4' || ratingstr[i] == '5' || ratingstr[i] == '6' || ratingstr[i] == '8' || ratingstr[i] == '9') {
                glVertex2f(nextX, recordY + linesize);
                glVertex2f(nextX + linesize, recordY + linesize);
            }
            if (ratingstr[i] == '1') {
                glVertex2f(nextX, recordY + linesize);
                glVertex2f(nextX + linesize, recordY);
            }
            nextX += 15;
        }
        glEnd();
    }
}

void PaintBalls(int max_balls, int* balls, float* balls_x, float* balls_y, float ball_r) {
    for (int v = 0; v < max_balls; v++) {
        if (balls[v] == 0) continue;
        glColor3f(0.849f, 0.869f, 0.861f);
        glBegin(GL_POLYGON);
        for (float i = 0; i < 2 * 3.14; i += 3.14 / 32)
            glVertex2f(balls_x[v] + ball_r * sin(i), balls_y[v] + ball_r * cos(i));
        glEnd();
    }
}

void PaintBonuses(int bonus_falling, int* bonus_status, int* whichbonus, int bonus_r, int* bonus_y, int* bonus_x) {
    if (bonus_falling != 0) {
        for (int k = 1; k <= 3; k++) {
            if (bonus_status[k] == 0) continue;
            if (whichbonus[k] == 1) glColor3f(1, 1, 0.600f);
            else if (whichbonus[k] == 2) glColor3f(0.8, 0.6, 0.600f);
            else if (whichbonus[k] == 3) glColor3f(0.4, 0.9, 0.660f);
            glBegin(GL_POLYGON);
            for (float i = 0; i < 2 * 3.14; i += 3.14 / 4)
                glVertex2f(bonus_x[k] + bonus_r * sin(i), bonus_y[k] + bonus_r * cos(i));
            glEnd();
        }
    }
}

void PaintBricks(int brick_w, int brick_h, int(*brick_status)[SIZE], int(*brick_pos_x)[SIZE], int(*brick_pos_y)[SIZE], int(*brick_health)[SIZE], int space, int rows, int col) {
    glBegin(GL_QUADS);
    int lastx = 0, lasty = 0;
    int x1 = 0, y1 = 0, x2 = x1 + brick_w, y2 = y1, x3 = x2, y3 = y2 + brick_h, x4 = x3 - brick_w, y4 = y3;

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= col; j++) {

            if (brick_status[i][j] == 0) {
                y1 = (i - 1) * space + (i - 1) * brick_h;
                x2 = x1 + space; y2 = y1 + brick_h + space; x3 = x2 + brick_w; y3 = y2; x4 = x3; y4 = y3 - brick_h;
                x1 = x4; y1 = y4;
            }

            else {
                if (brick_health[i][j] == 1) glColor3f(0.45f, 0.43f, 0.52f);
                else if (brick_health[i][j] == 2) glColor3f(0.65f, 0.63f, 0.72f);
                else if (brick_health[i][j] == 3) glColor3f(0.849f, 0.869f, 0.861f);
                y1 = (i - 1) * space + (i - 1) * brick_h;
                glVertex3f(x1 + space, y1 + space, 0);
                x1 += space; y1 += space;
                x2 = x1; y2 = y1 + brick_h; x3 = x2 + brick_w; y3 = y2; x4 = x3; y4 = y3 - brick_h;
                glVertex3f(x2, y2, 0);
                glVertex3f(x3, y3, 0);
                glVertex3f(x4, y4, 0);

                brick_pos_x[i][j] = x1;
                brick_pos_y[i][j] = y1;

                x1 = x4; y1 = y4;
            }
        }
        x1 = 0;
    }

    brick_pos_x[0][0] += space; brick_pos_x[1][0] += 45; brick_pos_x[2][0] += 45; brick_pos_x[3][0] += 45; brick_pos_x[4][0] += 45;
    brick_pos_y[0][0] += space; brick_pos_y[1][0] += 45; brick_pos_y[2][0] += 45; brick_pos_y[3][0] += 45; brick_pos_y[4][0] += 45;

    glEnd();
}

void CreateScoreFile(int level_count) {
    FILE* fcheck = fopen("score.txt", "r");
    if (fcheck == NULL) {
        FILE* fstart = fopen("score.txt", "w");
        for (int i = 0; i < level_count; i++) printf("0\n");
        fclose(fstart);
        return;
    }
    fclose(fcheck);
}