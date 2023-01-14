#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include "GL/freeglut.h"
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "funcs.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int nullrestart = 0;
int isNextLevel = 0;
// Resolution
int res_x = 545, res_y = 600;
// Deck
int d_w = 105, d_h = 8.0, d_x, d_y;
int deck_vel = 0, d_vel = 7, d_anim_left = 0, d_anim_seconds = 5;
// Combo
int balls_combo[7] = { 0 };
int rating = 0, combonus = 20, shouldcheck = 1;
char ratingstr[10] = { 0 };
// Menu
float b_menu_x, b_menu_y;
float balls_x[7] = { 0 }, balls_y[7] = { 0 }, ball_r = 7.5, x_vel, y_vel;
float ball_x, ball_y;
int ball_status = 0;
int vel_temp = 0;
int gamestarted = 0;
int gamemenu = 0;
int temp = 0, startvel = 2;
int x_velocity = 3, y_velocity = 3;
int x_vels[7], y_vels[7];
int startvels[7];
// Balls
int balls_count = 0, max_balls = 6;
int balls[7] = { 0 }, isLastBallConverted = 0;
// Bricks
float brick_w = 40, brick_h = 40;
int raws = 5, col = 12, health;
int space = 5;
int brick_pos_x[10][13];
int brick_pos_y[10][13];
int brick_status[11][13] = { 1 }; // 0 - ÌÂÚ / 1 - ‰‡
int brick_health[10][13] = { 1 };
// Menu
int gameactive = 0, isLvlFinished = 0, lastlevel = 0;
int level_count = 5; // —ÍÓÎ¸ÍÓ ÛÓ‚ÌÂÈ ‚ Ë„Â
int level, levelbrick[5], levelbrick_x[5], levelbrick_y[5], levelbonusbrick_y = 0;
char score[10];
int startX = 0, nextX = 0, linesize = 10, recordY = 480;
int isMaxRecord = 0, RecBoxX = 0, RecBoxY = 445, lvlrecords[6] = { 0 };
int lvlFinB_x[3] = { 0 }, lvlFinB_y[3] = { 0 };
// Bonus
int bonus_x[4] = { 0 }, bonus_y[4] = { 0 }, bonus_status[4] = { 0 };
int bonus_falling = 0, bonus_yvel = 3, bonus_r = 6;
int whichbonus[4] = { 0 }; // 1 - Long Deck, 2 - 2 balls, 3 - Delete Vertical
int d_hits_left = 10, bonus_width = 50;
int colstodestroy[13] = { 0 };

void printscore() {
    if (shouldcheck == 0) {
        sprintf(score, "%d", lvlrecords[level - 1]);

        int fullLength = 60 + (strlen(score)) * 15 - 5;
        startX = 273 - fullLength / 2;
        nextX = startX;
        return;
    }
    int toWrite = 0;
    char tempstr[10] = { 0 };
    FILE* file = fopen("score.txt", "r");
    while (!feof(file)) {
        fgets(tempstr, 10, file);
        lvlrecords[toWrite] = atoi(tempstr);
        toWrite++;
        isMaxRecord = 1;
    }
    fclose(file);
    sprintf(score, "%d", lvlrecords[level - 1]);
    int fullLength = 60 + (strlen(score)) * 15 - 5;
    startX = 273 - fullLength / 2;
    nextX = startX;
    shouldcheck = 0;

}

void varnulls() {
    for (int i = 0; i < 7; i++) {
        balls_combo[i] = 0;
    }
    nextX = 0; RecBoxX = 0; RecBoxY = 445;
    recordY = 0; isMaxRecord = 0; shouldcheck = 1;
    score[0] = '\n'; ratingstr[0] = '\n'; rating = 0;
    for (int i = 0; i < max_balls; i++) {
        if (i != 0) {
            balls[i] = 0;
        }
        balls_x[i] = 0;
        balls_y[i] = 0;
        x_vels[i] = 0;
        y_vels[i] = 0;

    }
    ball_status = 0; balls_count = 0;
    d_hits_left = 10; d_w = 105; d_h = 6;
    bonus_falling = 0;
    for (int i = 1; i < 4; i++) {
        bonus_status[i] = 0;
        bonus_x[i] = 0;
        bonus_y[i] = 0;
        whichbonus[i] = 0;
    }
    // Œ·ÌÛÎÂÌËÂ ÛÓ‚Ìˇ
    for (int i = 1; i <= raws; i++) {
        for (int j = 1; j <= col; j++) {
            brick_status[i][j] = 0;
            brick_health[i][j] = 0;
            brick_pos_x[i][j] = 0;
            brick_pos_y[i][j] = 0;
        }
    }
    brick_pos_x[0][1] = space; brick_pos_x[0][2] = 2 * space + brick_w; brick_pos_x[0][3] = 3 * space + 2 * brick_w; brick_pos_x[0][4] = 4 * space + 3 * brick_w; brick_pos_x[0][5] = 5 * space + 4 * brick_w; brick_pos_x[0][6] = 6 * space + 5 * brick_w; brick_pos_x[0][7] = 7 * space + 6 * brick_w; brick_pos_x[0][8] = 8 * space + 7 * brick_w; brick_pos_x[0][9] = 9 * space + 8 * brick_w; brick_pos_x[0][10] = 10 * space + 9 * brick_w;  brick_pos_x[0][11] = 11 * space + 10 * brick_w; brick_pos_x[0][12] = 12 * space + 11 * brick_w;

}

void cb(int stroka, int ryad, int health) {
    brick_status[stroka][ryad] = 1; brick_health[stroka][ryad] = health; brick_pos_x[stroka][ryad] = (ryad)*space + (ryad - 1) * brick_w; brick_pos_y[stroka][ryad] = (stroka)*space + (stroka - 1) * brick_h;
}
void cbs(int stroka, int ryad1, int ryad2, int health) {
    for (int i = ryad1; i <= ryad2; i++) {
        brick_status[stroka][i] = 1; brick_health[stroka][i] = health; brick_pos_x[stroka][i] = (i)*space + (i - 1) * brick_w; brick_pos_y[stroka][i] = (stroka)*space + (stroka - 1) * brick_h;
    }
}
void cbxs(int stroka, char* str, int health) {
    int i = 0, j = 0, array[13] = { 0 }, a = 0, numbers = 0;
    char str2[30] = "0";
    while (i < strlen(str)) {
        while (str[i] != 32 && str[i] != 0) {
            str2[j] = str[i];
            j++; i++;
        }
        str2[j] = 0;
        array[a] = atoi(str2);
        numbers++;
        a++; j = 0;
        i++;
    }
    for (i = 0; i < numbers; i++) {
        brick_status[stroka][array[i]] = 1;
        brick_health[stroka][array[i]] = health;
        brick_pos_x[stroka][array[i]] = (array[i]) * space + (array[i] - 1) * brick_w;
        brick_pos_y[stroka][array[i]] = (stroka)*space + (stroka - 1) * brick_h;
    }
}

void levelswitcher() {
    varnulls();
    startvels[0] = 1;
    switch (level) {
    case(1): // –‡Ì‰ÓÏÌ˚È ÛÓ‚ÂÌ¸
        raws = 8;
        col = 12;
        cbs(5, 6, 7, 2); cb(6, 5, 1); cbs(6, 6, 7, 3); cb(6, 8, 1); cbs(7, 4, 9, 1);
        break;
    case(2):
        raws = 10;
        col = 12;
        cbxs(1, "1 12", 2); cbs(1, 3, 4, 2); cbs(1, 6, 7, 2); cbs(1, 9, 10, 2); cbxs(2, "2 5 8 11", 2); cbxs(3, "2 11", 2); cbxs(4, "2 11", 2); cbs(4, 5, 8, 1); cbs(5, 6, 7, 3); cbs(5, 4, 9, 1); cbxs(5, "3 4 9 10", 1); cbs(6, 5, 8, 2); cbs(7, 5, 8, 2); cbxs(8, "3 10", 2); cbxs(9, "4 9", 2); cbs(9, 5, 8, 3);
        break;
    case 3:
        raws = 8;
        col = 12;
        cbxs(2, "2 11", 1); cbxs(3, "2 11", 1); cbxs(1, "4 9", 1); cbs(1, 5, 8, 3); cbxs(2, "4 5 8 9", 1); cbs(2, 6, 7, 3); cbs(3, 5, 8, 1); cbxs(5, "2 4 9 11", 1); cbxs(5, "3 10", 2); cbxs(6, "1 5", 1); cbxs(6, "3 10", 3); cbxs(6, "2 4 9 11", 2); cbxs(6, "1 5 8 12", 1); cbxs(7, "2 4 9 11", 1); cbxs(7, "3 10", 2);
        break;
    case 4:
        col = 12;
        raws = 8;

        cbxs(1, "5 8", 2); cbxs(2, "6 7", 1); cbs(3, 4, 9, 1); cbxs(4, "3 10", 1); cbxs(4, "5 8", 2); cbxs(5, "3 10", 1); cbs(5, 4, 9, 3); cbs(6, 5, 7, 2); cbxs(6, "3 8", 1); cbxs(7, "4 9", 1); cbxs(8, "4 5 8 9", 1);
        break;
    case 5:
        col = 12;
        raws = 5 + rand() % 5;
        for (int i = 1; i <= raws; i++) {
            for (int j = 1; j <= col; j++) {
                brick_status[i][j] = rand() % 2;
                brick_health[i][j] = 1 + rand() % 2;
                brick_pos_x[i][j] = j * space + (j - 3) * brick_w;
                brick_pos_y[i][j] = i * space + (i - 3) * brick_h;
            }
        }
    default: break;
    }
}

void ClickMouse(int button, int a, int x, int y) // Õ‡˜‡ÎÓ Ë„˚ (ÕÛÊÂÌ ÍÎËÍ Ï˚¯Ë)
{
    if (gamemenu == 1 && (button == GLUT_LEFT_BUTTON) && ball_status == 0) {
        gamestarted = 0;
        ball_status = 1;
        balls[0] = 1;
        startvels[0] = 1;
    }
    else if (gamemenu == 2 && button == GLUT_LEFT_BUTTON) {
        gamestarted = 1;
        gameactive = 1;
        gamemenu = 0;
        ball_status = 1;
    }
}
void MoveByKeyboard(int key) {
    switch (key) {
    case GLUT_KEY_LEFT:
        d_anim_left = -d_anim_seconds;
        if (d_x < 0) {
            d_x = 0;
        }
        break;
    case GLUT_KEY_RIGHT:
        d_anim_left = d_anim_seconds;
        if (d_x + d_w > res_x) {
            d_x = res_x - d_w;
        }
        break;
    default:
        deck_vel = 0;
        break;
    }
}
void ClickKeyboard(int key)
{
    if (key == 27) {
        saverecord(score, rating, lvlrecords, level);
        isLvlFinished = 0;
        gamemenu = 1;
        gameactive = 0;
        gamestarted = 0;
        ball_status = 0;
        balls[0] = 0;
        varnulls();
        balls_x[0] = d_x + d_w / 2;
        balls_y[0] = d_y - 8;
        startvels[0] = 0;
        b_menu_x = d_x + d_w / 2;
        b_menu_y = d_y - ball_r / 2 - 8;
    }
    if (key == 32) {
        if (gamemenu == 1 && ball_status == 0) {
            gamestarted = 0;
            ball_status = 1;
            balls[0] = 1;
            startvels[0] = 1;
        }
        else if (gamemenu == 2) {
            gamestarted = 1;
            gameactive = 1;
            gamemenu = 0;
            ball_status = 1;
        }
    }
}

void BallMove()
{

    if (gamestarted == 1) {

        // ∆Ë‚˚ ÎË ÍËÔË˜Ë?
        brick_health[0][0] = 0;
        int temp = 0;
        for (int i = 1; i <= raws; i++) {
            for (int j = 1; j <= col; j++) {
                if (brick_status[i][j] == 1 && brick_health[i][j] != 3) {
                    temp = 1;
                    break;
                }
            }
            if (temp == 1) break;
        }
        if (temp == 0) {
            isLvlFinished = 1;
            lastlevel = level;
            gamestarted = 0;
            gamemenu = 1;
            gameactive = 0;
            ball_status = 0;
            balls[0] = 0;
            balls_x[0] = d_x + d_w / 2;
            balls_y[0] = d_y - 8;
            startvels[0] = 0;
            b_menu_x = d_x + d_w / 2;
            b_menu_y = d_y - ball_r / 2 - 8;
            saverecord(score, rating, lvlrecords, level);
            varnulls();
            return;
        }
        temp = 0;

        // ∆Ë‚˚ ÎË ¯‡ËÍË?
        for (int i = 0; i < max_balls; i++) {
            if (balls[i] == 1) {
                temp = 1;
                break;
            }
        }
        if (temp == 0) {
            isLvlFinished = 1;
            lastlevel = level;
            gamestarted = 0;
            gamemenu = 1;
            gameactive = 0;
            ball_status = 0;
            balls[0] = 0;
            balls_x[0] = d_x + d_w / 2;
            balls_y[0] = d_y - 8;
            startvels[0] = 0;
            b_menu_x = d_x + d_w / 2;
            b_menu_y = d_y - ball_r / 2 - 8;
            saverecord(score, rating, lvlrecords, level);
            varnulls();
            return;

        }

    }

    for (int i = 0; i < max_balls; i++) {     // Move Balls (Add velocity)
        if (balls[i] == 0) continue;
        balls_x[i] += x_vels[i];
        balls_y[i] += y_vels[i];
    }
    if (bonus_falling != 0) {     // If There are bonuses - move them
        for (int i = 1; i < 4; i++) {
            if (bonus_status[i] == 0) continue;
            bonus_y[i] += bonus_yvel;
        }
    }

    if (gamemenu == 1) {
        b_menu_y -= 6;
        ball_x = b_menu_x; ball_y = b_menu_y;
        if (isLvlFinished == 1) {
            if (ball_y - ball_r < lvlFinB_y[1] && ball_y + ball_r > lvlFinB_y[1]) {
                for (int i = 0; i < 3; i++) {
                    if (ball_x + ball_r > lvlFinB_x[i] && ball_x - ball_r < lvlFinB_x[i] + 2 * brick_w) {
                        if (i == 0) {
                            lastlevel = level;
                            gamestarted = 0;
                            gamemenu = 1;
                            gameactive = 0;
                            ball_status = 0;
                            balls[0] = 0;
                            balls_x[0] = d_x + d_w / 2;
                            balls_y[0] = d_y - 8;
                            startvels[0] = 0;
                            b_menu_x = d_x + d_w / 2;
                            b_menu_y = d_y - ball_r / 2 - 8;
                            isLvlFinished = 0;
                            saverecord(score, rating, lvlrecords, level);
                            varnulls();
                            return;
                        }
                        else if (i == 1) {
                            level = lastlevel;
                            levelswitcher();
                            gamemenu = 0;
                            balls[0] = 1;
                            balls_x[0] = d_x + d_w / 2;
                            balls_y[0] = d_y - ball_r / 2 - 8;
                            break;
                        }
                        else if (i == 2) {
                            if (lastlevel == 5) {
                                level = lastlevel;
                            }
                            else level = lastlevel + 1;
                            levelswitcher();
                            gamemenu = 0;
                            balls[0] = 1;
                            balls_x[0] = d_x + d_w / 2;
                            balls_y[0] = d_y - ball_r / 2 - 8;
                            break;
                        }
                    }
                }
            }
            else if (ball_y + ball_r < lvlFinB_y[1]) {
                gamemenu = 0;
                balls[0] = 1;
                balls_x[0] = d_x + d_w / 2;
                balls_y[0] = d_y - ball_r / 2 - 8;
            }

        }
        else if (ball_y - ball_r - 2 < levelbonusbrick_y) {
            level = 5;
            levelswitcher();
            gamemenu = 0;
            balls[0] = 1;
            balls_x[0] = d_x + d_w / 2;
            balls_y[0] = d_y - ball_r / 2 - 8;
        }
        else {
            if (ball_y - ball_r < levelbrick_y[1] && ball_y + ball_r > levelbrick_y[1]) {
                while (gamemenu == 1) {
                    for (int i = 1; i < level_count; i++) {
                        if (ball_x + ball_r > levelbrick_x[i] && ball_x - ball_r < levelbrick_x[i] + 2 * brick_w) {
                            level = i;
                            levelswitcher();
                            gamemenu = 0;
                            balls[0] = 1;
                            balls_x[0] = d_x + d_w / 2;
                            balls_y[0] = d_y - ball_r / 2 - 8;
                            break;
                        }
                    }
                    ball_status = 1;
                    break;
                }
            }
            else if (ball_y - ball_r - 2 < levelbonusbrick_y) {
                level = 5;
                levelswitcher();
                gamemenu = 0;
                balls[0] = 1;
                balls_x[0] = d_x + d_w / 2;
                balls_y[0] = d_y - ball_r / 2 - 8;
            }
        }
    }
    else {
        temp = 0;
        int isHit = 0;
        for (int v = 0; v < max_balls; v++) {
            if (balls[v] == 0) continue;
            ball_x = balls_x[v];
            ball_y = balls_y[v];
            x_vel = x_vels[v];
            y_vel = y_vels[v];

            if (ball_x + ball_r <= 0) {
                ball_x = 0;
                x_vel *= -1;
            }
            else if (ball_y - ball_r <= 0)
            {
                ball_y = 5;
                y_vel *= -1;
            }
            else if (ball_x + ball_r >= res_x)
            {
                ball_x = res_x - ball_r;
                x_vel *= -1;
            }
            else if (ball_y + ball_r + 3 >= d_y && ball_y - ball_r - 3 <= d_y + d_h)
            {

                int d_center = d_x + d_w / 2, d_left = d_x, d_right = d_x + d_w;
                int ball_center = ball_x, ball_left = ball_x - ball_r, ball_right = ball_x + ball_r;
                int washit = 0;
                if (x_vel < 0) {
                    if (ball_center > d_left && ball_center <= d_center) {
                        y_vel *= -1; washit++;
                    }
                    else if (ball_center > d_center && ball_center < d_right) {
                        x_vel *= -1; washit++;
                        y_vel *= -1;
                    }
                }
                else {
                    if (ball_center > d_left && ball_center <= d_center) {
                        y_vel *= -1; washit++;
                        x_vel *= -1;
                    }
                    else if (ball_center > d_center && ball_center < d_right) {
                        y_vel *= -1; washit++;
                    }
                }

                if (washit) {
                    if (d_hits_left < 10) d_hits_left--;
                    balls_combo[v] = 0;
                    ball_y = d_y - ball_r - 3;
                }

            }
            else if (ball_y + 3 > res_y) // Ãˇ˜ËÍ ÛÔ‡Î
            {
                balls[v] = 0;
                balls_combo[v] = 0;
                balls_count--;
                startvels[v] = 0;

            }

            // œÓ‚ÂÍ‡ Ì‡ ÔÓÔ‡‰‡ÌËÂ ‚ Í‚‡‰‡Ú˚
            int rememberHittedCol = 0, rememberHitterRaw = 0;
            for (int i = 1; i <= raws; i++) {
                for (int k = 1; k <= col; k++) {
                    int x_ru = ball_x + ball_r, y_ru = ball_y - ball_r;
                    int x_rd = ball_x + ball_r, y_rd = ball_y + ball_r;
                    int x_lu = ball_x - ball_r, y_lu = ball_y - ball_r;
                    int x_ld = ball_x - ball_r, y_ld = ball_y + ball_r;
                    if (brick_status[i][k] == 0) continue;

                    // ÕËÊÌˇˇ „‡Ì¸
                    if (((y_lu - 3 <= brick_pos_y[i][k] + brick_h && y_ld + 3 > brick_pos_y[i][k] + brick_h && (ball_x - ball_r <= brick_pos_x[i][k] + brick_w || ball_x + ball_r >= brick_pos_x[i][k])) || (y_ru - 3 <= brick_pos_y[i][k] + brick_h && y_rd + 3 > brick_pos_y[i][k] + brick_h && (ball_x - ball_r - 3 <= brick_pos_x[i][k] + brick_w || ball_x + ball_r + 3 >= brick_pos_x[i][k]))) && (ball_x - ball_r - 3 >= brick_pos_x[i][k] || ball_x + ball_r + 3 <= brick_pos_x[i][k] + brick_w) && (y_vel < 0) && (brick_status[i + 1][k] == 0)) { // ÕËÊÌˇˇ „‡Ì¸
                        if (x_ru < brick_pos_x[i][k] + brick_w && x_ru > brick_pos_x[i][k])
                        {
                            y_vel *= -1;
                            temp = 1;

                            if (brick_health[i][k] == 1) {
                                brick_status[i][k] = 0;
                                isHit = 1;
                            }
                            else if (brick_health[i][k] == 2) brick_health[i][k]--;
                        }
                        else if (x_lu < brick_pos_x[i][k] + brick_w && x_lu > brick_pos_x[i][k])
                        {
                            y_vel *= -1;
                            temp = 1;

                            if (brick_health[i][k] == 1) {
                                brick_status[i][k] = 0;
                                isHit = 1;
                            }
                            else if (brick_health[i][k] == 2) brick_health[i][k]--;
                        }
                    }

                    if (temp == 1) {
                        rememberHittedCol = k;
                        break;
                    }

                    // ¬ÂıÌˇˇ „‡Ì¸
                    if (((y_ld + 3 >= brick_pos_y[i][k] && y_lu - 3 < brick_pos_y[i][k] && (ball_x - ball_r - 3 <= brick_pos_x[i][k] + brick_w && ball_x + ball_r + 3 >= brick_pos_x[i][k])) || (y_rd + 3 >= brick_pos_y[i][k] && y_ru - 3 < brick_pos_y[i][k] && (ball_x - ball_r - 3 <= brick_pos_x[i][k] + brick_w && ball_x + ball_r + 3 >= brick_pos_x[i][k]))) && (brick_status[i - 1][k] == 0 && y_vel > 0)) { // ¬ÂıÌˇˇ „‡Ì¸
                        if (x_ld >= brick_pos_x[i][k] && x_ld <= brick_pos_x[i][k] + brick_w)
                        {
                            y_vel *= -1;
                            temp = 1;

                            if (brick_health[i][k] == 1) {
                                brick_status[i][k] = 0;
                                isHit = 1;
                            }
                            else if (brick_health[i][k] == 2) brick_health[i][k]--;
                            //break;
                        }
                        else if (x_rd <= brick_pos_x[i][k] + brick_w && x_rd >= brick_pos_x[i][k])
                        {
                            y_vel *= -1;
                            temp = 1;

                            if (brick_health[i][k] == 1) {
                                brick_status[i][k] = 0;
                                isHit = 1;
                            }
                            else if (brick_health[i][k] == 2) brick_health[i][k]--;

                            //break;
                        }
                    }

                    if (temp == 1) {
                        rememberHittedCol = k;
                        break;
                    }

                    // ÀÂ‚‡ˇ „‡Ì¸
                    if ((((x_ru + 3 >= brick_pos_x[i][k] && x_lu - 3 < brick_pos_x[i][k]) || (x_rd + 3 >= brick_pos_x[i][k] && x_ld - 3 < brick_pos_x[i][k])) && brick_status[i][k - 1] == 0 && ball_x < brick_pos_x[i][k]))
                    {
                        if (y_ru >= brick_pos_y[i][k] && y_ru <= brick_pos_y[i][k] + brick_h)
                        {
                            x_vel *= -1;
                            temp = 1;

                            if (brick_health[i][k] == 1) {
                                brick_status[i][k] = 0;
                                isHit = 1;
                            }
                            else if (brick_health[i][k] == 2) brick_health[i][k]--;

                            //break;

                        }
                        else if (y_rd <= brick_pos_y[i][k] + brick_h && y_rd >= brick_pos_y[i][k])
                        {
                            x_vel *= -1;
                            temp = 1;

                            if (brick_health[i][k] == 1) {
                                brick_status[i][k] = 0;
                                isHit = 1;
                            }
                            else if (brick_health[i][k] == 2) brick_health[i][k]--;

                            //break;
                        }
                    }

                    if (temp == 1) {
                        rememberHittedCol = k;
                        break;
                    }

                    // œ‡‚‡ˇ „‡Ì¸
                    if ((x_lu - 3 <= brick_pos_x[i][k] + brick_w && x_ru + 3 > brick_pos_x[i][k] + brick_w && brick_status[i][k + 1] == 0) || (x_ld - 3 <= brick_pos_x[i][k] + brick_w && x_rd + 3 > brick_pos_x[i][k] + brick_w && brick_status[i][k + 1] == 0))
                    {
                        if (y_lu >= brick_pos_y[i][k] && y_lu <= brick_pos_y[i][k] + brick_h)
                        {
                            x_vel *= -1;
                            temp = 1;

                            if (brick_health[i][k] == 1) {
                                brick_status[i][k] = 0;
                                isHit = 1;
                            }
                            else if (brick_health[i][k] == 2) brick_health[i][k]--;
                        }
                        else if (y_ld <= brick_pos_y[i][k] + brick_h && y_ld >= brick_pos_y[i][k])
                        {
                            x_vel *= -1;
                            temp = 1;

                            if (brick_health[i][k] == 1) {
                                brick_status[i][k] = 0;
                                isHit = 1;
                            }
                            else if (brick_health[i][k] == 2) brick_health[i][k]--;

                        }
                    }
                    if (temp == 1) {
                        rememberHittedCol = k;
                        break;
                    }
                }
                if (temp == 1) {
                    balls_combo[v]++;
                    rating += balls_combo[v] * 10;

                    rememberHitterRaw = i;

                    if (isHit == 1) {
                        int randombonus = 1 + rand() % 1000;
                        if (randombonus > 850) { // 15% chance
                            if (bonus_falling < 3) {
                                for (int l = 1; l <= 3; l++) {
                                    if (bonus_status[l] == 1) continue;
                                    bonus_falling++;
                                    bonus_status[l] = 1;
                                    bonus_x[l] = brick_pos_x[rememberHitterRaw][rememberHittedCol] + brick_w / 2;
                                    bonus_y[l] = brick_pos_y[rememberHitterRaw][rememberHittedCol] + brick_h / 2;

                                    int randomtypebonus = 1 + rand() % 1000;
                                    if (randomtypebonus <= 333) {
                                        whichbonus[l] = 1;
                                    }
                                    else if (randomtypebonus > 333 && randomtypebonus <= 667) {
                                        whichbonus[l] = 2;
                                    }
                                    else if (randomtypebonus > 667) {
                                        whichbonus[l] = 3;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    isHit = 0;
                    break;
                }
            }
            rememberHittedCol = 0; rememberHitterRaw = 0;
            balls_x[v] = ball_x;
            balls_y[v] = ball_y;
            x_vels[v] = x_vel;
            y_vels[v] = y_vel;

            if (d_hits_left == 0) {
                d_w -= bonus_width;
                d_h -= bonus_width;
                d_hits_left = 10;
            }


            if (bonus_falling != 0) {
                for (int i = 1; i <= 3; i++) {
                    if (bonus_x[i] == 0 && bonus_y[i] == 0) continue;
                    if (bonus_y[i] + bonus_r >= d_y && bonus_y[i] - bonus_r <= d_y + d_h)
                    {

                        int d_center = d_x + d_w / 2, d_left = d_x, d_right = d_x + d_w;
                        int ball_center = bonus_x[i], ball_left = bonus_x[i] - bonus_r, ball_right = bonus_x[i] + bonus_r;

                        if (ball_right > d_left && ball_left < d_right)
                        {
                            bonus_falling--;
                            bonus_x[i] = 0;
                            bonus_y[i] = 0;
                            bonus_status[i] = 0;

                            rating += 300;

                            if (whichbonus[i] == 1) { //Long Deck
                                if (d_hits_left == 10) {
                                    d_w += bonus_width;
                                    d_h += bonus_width;
                                    d_hits_left--;
                                }
                            }
                            else if (whichbonus[i] == 2) { // +2 balls
                                if (balls_count < max_balls - 1) {
                                    balls_count += 2;
                                    int tempb = 0;
                                    for (int v = 0; v < max_balls; v++) {
                                        if (tempb == 2) break;
                                        if (balls[v] == 1) continue;
                                        else {
                                            balls[v] = 1;
                                            if (tempb == 0)balls_x[v] = d_x + d_w / 2 - 5 - ball_r;
                                            else if (tempb == 1) balls_x[v] = d_x + d_w / 2 + 5 + ball_r;
                                            // balls_x[v] = d_x + d_w / 2;
                                            balls_y[v] = d_y - ball_r / 2 - 8;
                                            startvels[v] = 1;
                                            tempb++;
                                        }
                                    }
                                }
                                else if (balls_count == max_balls - 1) {
                                    balls_count++;
                                    for (int v = 0; v < max_balls; v++) {
                                        if (balls[v] == 1) continue;
                                        else {
                                            balls[v] = 1;
                                            balls_x[v] = d_x + d_w / 2;
                                            balls_y[v] = d_y - ball_r / 2 - 8;
                                            break;
                                        }
                                    }
                                }
                                whichbonus[i] = 0;
                                break;
                            }
                            else if (whichbonus[i] == 3) { // Delete Vertical
                                for (int block = 1; block <= col; block++) {
                                    if (ball_center >= brick_pos_x[0][block] && ball_center <= brick_pos_x[0][block] + brick_w) {
                                        for (int tempi = 0; tempi < raws; tempi++) {
                                            if (brick_health[tempi][block] == 3) continue;
                                            brick_status[tempi][block] = 0;
                                            brick_health[tempi][block] = 0;
                                        }
                                        for (int tempi = 0; tempi < col; tempi++) {
                                            if (colstodestroy[tempi] != 0) {
                                                colstodestroy[tempi] = 1;
                                            }
                                        }
                                        break;
                                    }
                                }
                            }

                        }

                    }
                    else if (ball_y > res_y) // Bonus Lost
                    {
                        bonus_falling--;
                    }
                }
            }
        }

    }
}

void follow_mouse(int x, int y) // —ÎÂÊÂÌËÂ Á‡ Ï˚¯¸˛
{
    d_x = x - d_w / 2;
    if (gamemenu == 1) {
        if (ball_status == 0) {
            b_menu_x = d_x + d_w / 2;
            b_menu_y = d_y - ball_r / 2 - 8;
            if (b_menu_x < ball_r) b_menu_x = ball_r;
            else if (b_menu_x > res_x - ball_r) b_menu_x = res_x - ball_r;
        }
    }
    else if (gamemenu == 2 && gameactive == 0) {
        balls_x[0] = d_x + d_w / 2;
        balls_y[0] = d_y - ball_r / 2 - 8;
        if (balls_x[0] < ball_r) balls_x[0] = ball_r;
        else if (balls_x[0] > res_x - ball_r) balls_x[0] = res_x - ball_r;
    }
    if (d_x < 0) {
        d_x = 0;
    }
    if (d_x + d_w > res_x) {
        d_x = res_x - d_w;
    }
}

void paint() // –ËÒÓ‚Í‡
{

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.237f, 0.227f, 0.242f, 1.0);
    glColor3f(0.849f, 0.869f, 0.861f);
    glRectf(d_x, d_y, d_x + d_w, d_y + d_h); // Deck Painting
    if (gamemenu == 1) {
        x_vel = 0; y_vel = -6;
        glLineWidth(5.0);
        printlogo(res_x, res_y);
        PaintBall(b_menu_x, b_menu_y, ball_r);
        glClearColor(0.237f, 0.227f, 0.242f, 1.0);

        if (isLvlFinished == 0) {
            levelbonusbrick_y = PrintLevelBoxes(res_x, res_y, 40, 80, 40, levelbrick_x, levelbrick_y, level_count);

        }
        else if (isLvlFinished == 1) {

            PaintFinishedLvl(res_x, res_y, brick_w * 2, brick_h, lastlevel);
            glColor3f(0.65f, 0.63f, 0.72f);
            glLineWidth(2.0);
            glBegin(GL_LINES);
            printscore();
            recordY = 240;
            printRecordAfterLvl(nextX, linesize, recordY, score);
            glEnd();
            PaintButtonsAfterLvl(lvlFinB_x, lvlFinB_y);
        }
        glutSwapBuffers();
    }
    else {
        glLineWidth(2.2);
        if (rating != 0) {
            sprintf(ratingstr, "%d", rating);
            PrintScoreOnLvl(linesize, ratingstr, rating);
        }
        recordY = 480;
        printscore();
        if (isMaxRecord == 1) {
            glBegin(GL_LINES);
            glColor3f(0.5, 0.5, 0.5);
            printRecordAfterLvl(nextX, linesize, recordY, score);
            glEnd();
        }
        if (gamemenu == 0) {
            gamestarted = 1;
            gamemenu = 2;
        }
        PaintBalls(max_balls, balls, balls_x, balls_y, ball_r);
        PaintBricks(brick_w, brick_h, brick_status, brick_pos_x, brick_pos_y, brick_health, space, raws, col);
        PaintBonuses(bonus_falling, bonus_status, whichbonus, bonus_r, bonus_y, bonus_x);
        glutSwapBuffers();
    }
    if (startvel == 1) {
        startvel = 0;
    }
}

void movedeck() {
    if (d_anim_left > 0 && d_x + d_w <= res_x) {
        d_x += d_vel;
        d_anim_left--;
    }
    else if (d_anim_left < 0 && d_x >= 0) {
        d_x -= d_vel;
        d_anim_left++;
    }
    if (gamemenu == 1) {
        if (ball_status == 0) {
            b_menu_x = d_x + d_w / 2;
            b_menu_y = d_y - ball_r / 2 - 8;
        }
    }
    else if (gamemenu == 2 && gameactive == 0) {
        balls_x[0] = d_x + d_w / 2;
        balls_y[0] = d_y - ball_r / 2 - 8;
    }
}

void frame_time() // Œ·ÌÓ‚ÎÂÌËÂ ˝Í‡Ì‡
{
    movedeck();
    if (gamemenu == 0 || gamemenu == 2) {
        for (int i = 0; i < max_balls; i++) {
            if (startvels[i] == 0) continue;
            else if (startvels[i] == 1 && gameactive == 1) {
                srand(time(NULL));
                x_vels[i] = 1 + rand() % 3;
                if (isLastBallConverted == 1) {
                    x_vels[i] *= -1;
                    isLastBallConverted = 0;
                }
                else isLastBallConverted = 1;
                y_vels[i] = 1 + rand() % 3;
                startvels[i] = 2;
                if (y_vels[i] > 0) y_vels[i] *= -1;

            }
            else if (startvels[i] == 2 && gameactive == 1) {
                if (x_vels[i] < 0) {
                    x_vels[i] = -x_velocity;
                }
                else {
                    x_vels[i] = x_velocity;
                }
                y_vels[i] = -y_velocity;

                startvels[i] = 3;
                ball_status = 1;
                gamestarted = 1;
            }

        }
    }

    if (ball_status) {
        if (temp == 0) {
            BallMove();
        }
        else temp = 0;
    }
    paint();
    glutTimerFunc(12, frame_time, 0);

}

int main(int argc, char** argv)
{
    CreateScoreFile(level_count);
    d_x = res_x / 2 - d_w / 2, d_y = res_y - 20;
    gamemenu = 1; balls[0] = 1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(res_x, res_y);
    glutInitWindowPosition(100, 200);
    glutCreateWindow("Arcanoid");
    glutDisplayFunc(paint);
    glutTimerFunc(1, frame_time, 0);
    glutPassiveMotionFunc(follow_mouse);
    glutMouseFunc(ClickMouse);
    glutKeyboardFunc(ClickKeyboard);
    glutSpecialFunc(MoveByKeyboard);
    glClearColor(0.0, 0.0, 0.0, 0.0); // ÷‚ÂÚ ÙÓÌ‡
    glOrtho(0, res_x, res_y, 0, 1, 0);
    glutMainLoop();
    return 0;
}
