#include "lab_m1/tema1/tema1.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include <vector>
#include <iostream>
#include<string>
#include<queue>
#include <cstdlib>
#include<algorithm>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/tema1_object2D.h"

using namespace std;
using namespace m1;

bool blue_placed = false, white_placed = false, purple_placed = false, lv5_placed = false;
int star1_x = 0, star1_y = 0, star2_x = 0, star2_y = 0, star3_x = 0, star3_y = 0;
float blue_hit = 0, purple_hit = 0, white_hit = 0, grey_hit = 0;
int signal1 = 0, signal2 = 0, signal3 = 0, close_blue = 0, close_white = 0, close_purple = 0, close_lv5 = 0;
int original_size = 150, money = 0;
int mouseX_out = 0, mouseY_out = 0, mouseX_final = 0, mouseY_final = 0, star1 = 0, star2 = 0, star3 = 0, stars_to_take = 0, mouseX_final_f = 0, mouseY_final_f = 0;
int blue = 0, white = 0, purple = 0, lv5 = 0, released = 0, l = 0, button_mouse = 0, new_pos_blue_x, new_pos_blue_y;
int previous_y_blue = 0, previous_y_white = 0, previous_y_purple = 0, previous_y_lv5 = 0, pos_white_x = 0, pos_white_y = 0, pos_purple_x = 0, pos_purple_y = 0, pos_lv5_x = 0, pos_lv5_y = 0, pos_blue_x = 0, pos_blue_y = 0;
double time_l = 0, time_p = 0, time_r = 0, time_q = 0, time_is_money = 0, time_enemy = 0;
float movement_blue = 0, movement_white = 0, movement_purple = 0, movement_grey = 0, counting_blue = 0;
float radius_enemy = 45, radius_projectile = 15, radius_cannon = 50, center_enemy = 0, center_projectile = 0;
float progression_enemy = 0, progression_projectile = 0, count_blue = 0, count_white = 0, count_purple = 0, count_lv5 = 0;
int placed_blue = 0, placed_purple = 0, placed_white = 0, placed_lv5 = 0, line1 = 0, line2 = 0, line3 = 0, line = 0;
float intermediateScale_blue = 0.5f, intermediateScale_white = 0.5f, intermediateScale_purple = 0.5f, intermediateScale_lv5 = 0.5f;

std::string colour, colour_enemy, colour_cannon;
std::vector<std::tuple<int, int, string, int, int, int>> indexes;
std::vector<std::tuple<int, int, int>> cannons_blue; 
std::vector<std::tuple<int, int, int>> cannons_white;
std::vector<std::tuple<int, int, int>> cannons_purple;
std::vector<std::tuple<int, int, int>> cannons_lv5;
std::vector<std::tuple<int, int>> currency;
std::vector<std::tuple<int, int, string, int, int, int>> elements_to_delete;
int index_currency_x = 0, index_currency_y = 0;
float x_max = 1280;
float x_min = 260;
float y_max = 450;
float y_min = 150;

float final_x_line1 = 0;
float final_x_line2 = 0;
float final_x_line3 = 0;
float final_y = 0;
float final_x = 0;


struct projectile
{
    float cx = 0;
    float interaction_enemy = 0;
    float time = 0;
    float radius_projectile = 0;
};

struct enemy {
    float center_enemy = 0;
    float radius_enemy = 0;
    std::string colour;
    std::string colour_enemy;
    float interaction_enemy = 0;
    float interaction_healthbar = 0;
};

struct cannon {
    float enemy_contact = 0;
    std::string cannon_colour;
};


std::vector<projectile> projectilesblue;
std::vector<projectile> projectileswhite;
std::vector<projectile> projectilespurple;
std::vector<projectile> projectileslv5;

std::vector<enemy>enemies;
std::vector<cannon>cannons;





/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


tema1::tema1()
{
}


tema1::~tema1()
{
}


void tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    WindowProperties wp;
    wp.resolution = glm::ivec2(1280, 720);
    PlaySound("./assets/music_game/Pulse of the Night.wav", NULL, SND_FILENAME | SND_ASYNC);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    final_x_line1 = rand() % (1280 - 260 + 1) + 260;
    final_x_line2 = rand() % (1280 - 390 + 1) + 390;
    final_x_line3 = rand() % (1280 - 520 + 1) + 520;
    final_y = rand() % (450 - 150 + 1) + 150;

    new_pos_blue_x = 0;
    new_pos_blue_y = 0;

    blue_hit = 0;
    white_hit = 0;
    purple_hit = 0;
    grey_hit = 0;
 
    cx = 0;
    cy = 0;
    square_x = 300;
    rectangle_x = 200;

    translateX = 0;
    translateY = 0;
    index_currency_y = 850;
    index_currency_x = 550;

    scaleX = 1;
    scaleY = 1; 

    angularStep = 0;

    Mesh* square1 = tema1_object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = tema1_object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square2);

    Mesh* square3 = tema1_object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(square3);

    Mesh* cannon_blue = tema1_object2D::CreateCannon("cannon_blue", corner, squareSide, glm::vec3(0, 0, 0.5f), true);
    AddMeshToList(cannon_blue);

    Mesh* cannon_white = tema1_object2D::CreateCannon("cannon_white", corner, squareSide, glm::vec3(1, 1, 1), true);
    AddMeshToList(cannon_white);

    Mesh* cannon_purple = tema1_object2D::CreateCannon("cannon_purple", corner, squareSide, glm::vec3(1, 0, 1), true);
    AddMeshToList(cannon_purple);

    Mesh* cannon_lv5 = tema1_object2D::CreateCannon("cannon_lv5", corner, squareSide, glm::vec3(0.5f, 0.5f, 0.5f), true);
    AddMeshToList(cannon_lv5);

    Mesh* projectile = tema1_object2D::CreateProjectile("projectile", corner, squareSide, glm::vec3(2, 0.5f, 1), true);
    AddMeshToList(projectile);

    Mesh* projectile_blue = tema1_object2D::CreateProjectile("projectile_blue", corner, squareSide, glm::vec3(0, 0, 0.5f), true);
    AddMeshToList(projectile_blue);

    Mesh* projectile_white = tema1_object2D::CreateProjectile("projectile_white", corner, squareSide, glm::vec3(1, 1, 1), true);
    AddMeshToList(projectile_white);
    
    Mesh* projectile_purple = tema1_object2D::CreateProjectile("projectile_purple", corner, squareSide, glm::vec3(1, 0, 1), true);
    AddMeshToList(projectile_purple);

    Mesh* projectile_grey = tema1_object2D::CreateProjectile("projectile_grey", corner, squareSide, glm::vec3(0.5f, 0.5f, 0.5f), true);
    AddMeshToList(projectile_grey);

    Mesh* enemy = tema1_object2D::CreateEnemy("enemy", corner, squareSide, glm::vec3(2, 0.5f, 1), true);
    AddMeshToList(enemy);

    Mesh* enemy_blue = tema1_object2D::CreateEnemy("enemy_blue", corner, squareSide, glm::vec3(0, 0, 0.3f), true); 
    AddMeshToList(enemy_blue);

    Mesh* enemy_white = tema1_object2D::CreateEnemy("enemy_white", corner, squareSide, glm::vec3(1, 1, 1), true);
    AddMeshToList(enemy_white);

    Mesh* enemy_purple = tema1_object2D::CreateEnemy("enemy_purple", corner, squareSide, glm::vec3(1, 0, 1), true);
    AddMeshToList(enemy_purple);

    Mesh* enemy_grey = tema1_object2D::CreateEnemy("enemy_grey", corner, squareSide, glm::vec3(0.5f, 0.5f, 0.5f), true);
    AddMeshToList(enemy_grey);

    Mesh* heart = tema1_object2D::CreateHearts("heart", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(heart);
}


void tema1::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void tema1::Update(float deltaTimeSeconds)
{


    cx += 100 * deltaTimeSeconds;
    cy += 150 * deltaTimeSeconds;
    hiro = deltaTimeSeconds;

    if (money == 0) {
        indexes.clear();
    }

    // rendering collected stars
    if (time_is_money >= 10) {
        if (star1 == 0) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(star1_x, star1_y);
            modelMatrix *= transform2D::Scale(0.3f, 0.3f);
            RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
        }

        if (star2 == 0) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(star2_x, star2_y);
            modelMatrix *= transform2D::Scale(0.3f, 0.3f);
            RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
        }

        if (star3 == 0) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(star3_x, star3_y);
            modelMatrix *= transform2D::Scale(0.3f, 0.3f);
            RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
        }
        if (time_is_money >= 20) {
            time_is_money = 0;
            star1 = 0;
            star2 = 0;
            star3 = 0;
            star1_x = rand() % (651 - 800 + 1) + 800 + 50;
            star1_y = rand() % (321 - 1 + 1) + 1;
            star3_x = rand() % (1150 - 1210 + 1) + 1210;
            star3_y = rand() % (321 - 1 + 1) + 1;
            star2_x = rand() % (850 - 1000 + 1) + 1000;
            star2_y = rand() % (321 - 1 + 1) + 1;
        }
        
    }
    
    angularStep += deltaTimeSeconds;

    // barrier
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10 , 150);
    modelMatrix *= transform2D::Scale(1.5f, 4);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    // cost cannon blue
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20, 580);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);


    // cannon blue
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, 650);
    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
    RenderMesh2D(meshes["cannon_blue"], shaders["VertexColor"], modelMatrix);

    // deleting stars system for currency for purchasing cannons
    if (stars_to_take == 0) {
        for (int i = 0; i < money; i++) {
            int x = std::get<0>(currency[i]);
            int y = std::get<1>(currency[i]);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(x, y);
            modelMatrix *= transform2D::Scale(0.15f, 0.15f);
            RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
        }
    }
    else {
        if (mouseX_final_f != 0 && mouseY_final_f != 0) {
            money -= stars_to_take;
            stars_to_take = 0;
            
            mouseX_final_f = 0;
            mouseY_final_f = 0;
        }
        for (int i = 0; i < money; i++) {
            int x = std::get<0>(currency[i]);
            int y = std::get<1>(currency[i]);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(x, y);
            modelMatrix *= transform2D::Scale(0.15f, 0.15f);
            RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
        }

    }

    // duplicating blue cannon for drag & drop

    if (blue == 1 && window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(mouseX_out, 720 -  mouseY_out);
        modelMatrix *= transform2D::Scale(0.3f, 0.3f);
        RenderMesh2D(meshes["cannon_blue"], shaders["VertexColor"], modelMatrix);
    }

    // window for cannon_blue
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20, 600);
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 650);
    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
    RenderMesh2D(meshes["cannon_white"], shaders["VertexColor"], modelMatrix);

    // duplicating white cannon for drag & drop

    if (white == 1 && window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(mouseX_out, 720 - mouseY_out);
        modelMatrix *= transform2D::Scale(0.3f, 0.3f);
        RenderMesh2D(meshes["cannon_white"], shaders["VertexColor"], modelMatrix);
    }

    // cost for cannon white
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(220, 580);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 580);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);

    // window for cannon_white
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(220, 600);
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    // cost for cannon_purple
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(420, 580);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(450, 580);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);


    // cannon purple
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(450, 650);
    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
    RenderMesh2D(meshes["cannon_purple"], shaders["VertexColor"], modelMatrix);

    // duplicating purple cannon for drag & drop

    if (purple == 1 && window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(mouseX_out, 720 - mouseY_out);
        modelMatrix *= transform2D::Scale(0.3f, 0.3f);
        RenderMesh2D(meshes["cannon_purple"], shaders["VertexColor"], modelMatrix);
    }

    // window for cannon_purple

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(420, 600);
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    // cost for lv5

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(620, 580);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(650, 580);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(680, 580);
    modelMatrix *= transform2D::Scale(0.15f, 0.15f);
    RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);

    // cannon lv5

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(660, 650);
    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
    RenderMesh2D(meshes["cannon_lv5"], shaders["VertexColor"], modelMatrix);

    // duplicating lv5 cannon for drag & drop

    if (lv5 == 1 && window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(mouseX_out, 720 - mouseY_out);
        modelMatrix *= transform2D::Scale(0.3f, 0.3f);
        RenderMesh2D(meshes["cannon_lv5"], shaders["VertexColor"], modelMatrix);
    }

    // window for cannon_lv5

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(630, 600);
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    // selecting positions for the cannons

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (mouseX_final > (j + 1) * (original_size - 20) && mouseX_final < (j + 1) * original_size && mouseY_final < (i + 1) * original_size
                && mouseY_final > i * original_size && blue == 1 && money >= 1 && released == 1) {

                indexes.push_back(std::make_tuple((j + 1) * (original_size - 20) + 30, 650 - (i * original_size), "blue", mouseY_final, mouseX_final, 0));
                
                if (i == 1) {
                    previous_y_blue = mouseY_final;
                    count_blue++;
                }

                pos_blue_x = (j + 1) * (original_size - 20) + 30;
                pos_blue_y = 650 - (i * original_size);
                cannons_blue.push_back(std::make_tuple(pos_blue_x, pos_blue_y, 0));


                if (button_mouse == 1) {
                    stars_to_take = 1;
                }
                blue_placed = true;
                blue = 0;
                placed_blue++;
                
                
            }

            if (mouseX_final > (j + 1) * (original_size - 20) && mouseX_final < (j + 1) * original_size && mouseY_final < (i + 1) * original_size
                && mouseY_final > i * original_size && white == 1 && money >= 2 && released == 1) {
                indexes.push_back(std::make_tuple((j + 1) * (original_size - 20) + 30, 650 - (i * original_size), "white", mouseY_final, mouseX_final, white_hit));

                if (i == 1) {
                    previous_y_white = mouseY_final;
                }
                pos_white_x = (j + 1) * (original_size - 20) + 30;
                pos_white_y = 650 - (i * original_size);
                cannons_white.push_back(std::make_tuple(pos_white_x, pos_white_y, 0));

                if (button_mouse == 1) {
                    stars_to_take = 2;
                }
                white_placed = true;
                white = 0;
                placed_white++;

            }

            if (mouseX_final > (j + 1) * (original_size - 20) && mouseX_final < (j + 1) * original_size && mouseY_final < (i + 1) * original_size
                && mouseY_final > i * original_size && purple == 1 && money >= 2 && released == 1) {

                indexes.push_back(std::make_tuple((j + 1) * (original_size - 20) + 30, 650 - (i * original_size), "purple", mouseY_final, mouseX_final, purple_hit));
                
                if (i == 1) {
                    previous_y_purple = mouseY_final;
                }
                pos_purple_x = (j + 1) * (original_size - 20) + 30;
                pos_purple_y = 650 - (i * original_size);
                cannons_purple.push_back(std::make_tuple(pos_purple_x, pos_purple_y, 0));

                if (button_mouse == 1) {
                    stars_to_take = 2;
                }
                purple_placed = true;
                purple = 0;
                placed_purple++;

            }

            if (mouseX_final > (j + 1) * (original_size - 20) && mouseX_final < (j + 1) * original_size && mouseY_final < (i + 1) * original_size
                && mouseY_final > i * original_size && lv5 == 1 && money >= 3 && released == 1) {
                indexes.push_back(std::make_tuple((j + 1) * (original_size - 20) + 30, 650 - (i * original_size), "lv5", mouseY_final, mouseX_final, grey_hit));

                if (i == 1) {
                    previous_y_lv5 = mouseY_final;
                }
                pos_lv5_x = (j + 1) * (original_size - 20) + 30;
                pos_lv5_y = 650 - (i * original_size);
                cannons_lv5.push_back(std::make_tuple(pos_lv5_x, pos_lv5_y, 0));

                if (button_mouse == 1) {
                    stars_to_take = 3;
                }
                lv5_placed = true;
                lv5 = 0;
                placed_lv5++;
            }

        }
    }

    // eliminating duplicates in terms of positions depending on x and y

    using MyTuple = std::tuple<int, int, std::string, int, int, int>;
    
    struct TupleCompare {
        bool operator()(const MyTuple& tuple1, const MyTuple& tuple2) const {
            return std::get<0>(tuple1) == std::get<0>(tuple2) && std::get<1>(tuple1) == std::get<1>(tuple2);
        }
    };

    indexes.erase(std::unique(indexes.begin(), indexes.end(), TupleCompare()), indexes.end());

    // time for projectiles (each type) and enemies

    if (time_l >= 200) {
        projectile projectile_1;
        projectile_1.cx = 1;
        projectile_1.interaction_enemy = 0;
        if (projectilesblue.empty()) {
            projectilesblue.push_back(projectile_1);
        }
        
        time_l = 0;
        deltaTimeSeconds = 0;
    }

    if (time_p >= 200) {
        projectile projectile_2;
        projectile_2.cx = 1;
        projectile_2.interaction_enemy = 0;
        if (projectileswhite.empty()) {
            projectileswhite.push_back(projectile_2);
        }
        time_p = 0;
        deltaTimeSeconds = 0;
    }

    if (time_r >= 200) {
        projectile projectile_3;
        projectile_3.cx = 1;
        projectile_3.interaction_enemy = 0;
        if (projectilespurple.empty()) {
            projectilespurple.push_back(projectile_3);
        }
        time_r = 0;
        deltaTimeSeconds = 0;
    }

    if (time_q >= 200) {
        projectile projectile_4;
        projectile_4.cx = 1;
        projectile_4.interaction_enemy = 0;
        if (projectileslv5.empty()) {
            projectileslv5.push_back(projectile_4);
        }
        time_q = 0;
        deltaTimeSeconds = 0;
    }

    if (time_enemy >= 150) {
        enemy enemy_1;
        enemy_1.radius_enemy = radius_enemy;
        int num = rand() % 4;
        int sw = rand() % 3;

        // randomize enemy_colours and positions
        switch (sw) {
        case 0:
            line1 = 200;
            line2 = 350;
            line3 = 500;
            break;
        case 1:
            line1 = 350;
            line2 = 500;
            line3 = 200;
            break;
        case 2:
            line1 = 500;
            line2 = 200;
            line3 = 350;
            break;
        default :
            break;
        }

        switch (num) {
        case 0:
            colour_enemy = "blue";
            break;
        case 1:
            colour_enemy = "white";
            break;
        case 2:
            colour_enemy = "purple";
            break;
        case 3:
            colour_enemy = "lv5";
            break;
        default:
            break;
        }

        enemy_1.colour = colour_enemy;
        enemy_1.center_enemy = 0;
        enemy_1.interaction_enemy = 0;
        enemy_1.interaction_healthbar = 0;
        deltaTimeSeconds = 0;
        movement_blue = 0;
        movement_white = 0;
        movement_purple = 0;
        movement_grey = 0;
        if (enemies.empty()) {
            enemies.push_back(enemy_1);
        }
        time_enemy = 0;
        

    }

    for (auto &enemy : enemies) {
        std::string colo = enemy.colour;

        //disappearning animations for each enemy
        if (movement_blue == 1) {
            if (intermediateScale_blue > 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1280 - center_enemy, line3);
                modelMatrix *= transform2D::Scale(intermediateScale_blue, intermediateScale_blue);
                RenderMesh2D(meshes["enemy_blue"], shaders["VertexColor"], modelMatrix);
                intermediateScale_blue -= deltaTimeSeconds;
            }
            else {
                enemy.interaction_enemy = 1;
                enemy.center_enemy = 0;
                center_enemy = 0;
                enemies.pop_back();
                intermediateScale_blue = 0.5f;
            }
           
        }
        else if (movement_white == 1) {
            if (intermediateScale_white > 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1280 - center_enemy, line1);
                modelMatrix *= transform2D::Scale(intermediateScale_white, intermediateScale_white);
                RenderMesh2D(meshes["enemy_white"], shaders["VertexColor"], modelMatrix);
                intermediateScale_white -= deltaTimeSeconds;
            }
            else {
                enemy.interaction_enemy = 1;
                enemy.center_enemy = 0;
                center_enemy = 0;
                enemies.pop_back();
                intermediateScale_white = 0.5f;
            }
        }
        else if (movement_purple == 1) {
            if (intermediateScale_purple > 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1280 - center_enemy, line2);
                modelMatrix *= transform2D::Scale(intermediateScale_purple, intermediateScale_purple);
                RenderMesh2D(meshes["enemy_purple"], shaders["VertexColor"], modelMatrix);
                intermediateScale_purple -= deltaTimeSeconds;
            }
            else {
                enemy.interaction_enemy = 1;
                enemy.center_enemy = 0;
                center_enemy = 0;
                enemies.pop_back();
                intermediateScale_purple = 0.5f;
            }
        }
        else if (movement_grey == 1) {
            if (intermediateScale_lv5 > 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1280 - center_enemy, line2);
                modelMatrix *= transform2D::Scale(intermediateScale_lv5, intermediateScale_lv5);
                RenderMesh2D(meshes["enemy_grey"], shaders["VertexColor"], modelMatrix);
                intermediateScale_lv5 -= deltaTimeSeconds;
            }
            else {
                enemy.interaction_enemy = 1;
                enemy.center_enemy = 0;
                center_enemy = 0;
                enemies.pop_back();
                intermediateScale_lv5 = 0.5f;
            }
        }

        // enemy conflicts with each cannon for each colour 
        if (colo == "blue" && movement_blue == 0) {
            float center = enemy.center_enemy;
            center += 50 * deltaTimeSeconds;
            if (enemy.interaction_healthbar == 0 && 1280 - center <= 10 && 1280 - center >= 0 && signal1 == 0) {
                signal1 = 1;
                enemy.interaction_healthbar = 1;
            }
            
            if (enemy.interaction_healthbar == 0 && signal1 == 1 && signal2 == 0 && 1280 - center <= 10 && 1280 - center >= 0) {
                signal2 = 1;
                enemy.interaction_healthbar = 1;
            }

            if (enemy.interaction_healthbar == 0 && signal3 == 0 && 1280 - center <= 10 && 1280 - center >= 0) {
                signal3 = 1;
                enemy.interaction_healthbar = 1;
            }
            enemy.center_enemy = center;
            center_enemy = center;

            if (placed_blue > 0) {
                for (int i = 0; i < cannons_blue.size(); i++) {
                    int x = std::get<0>(cannons_blue[i]);
                    int y = std::get<1>(cannons_blue[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line3) {
                        std::get<2>(cannons_blue[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "blue";
                    }
                }
            }
            
            if (placed_white > 0) {
                for (int i = 0; i < cannons_white.size(); i++) {
                    int x = std::get<0>(cannons_white[i]);
                    int y = std::get<1>(cannons_white[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line3) {
                        std::get<2>(cannons_white[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "white";
                    }
                }
            }
            
            if (placed_purple > 0) {
                for (int i = 0; i < cannons_purple.size(); i++) {
                    int x = std::get<0>(cannons_purple[i]);
                    int y = std::get<1>(cannons_purple[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line3) {
                        std::get<2>(cannons_purple[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "purple";
                    }
                }
            }
            
            if (placed_lv5 > 0) {
                for (int i = 0; i < cannons_lv5.size(); i++) {
                    int x = std::get<0>(cannons_lv5[i]);
                    int y = std::get<1>(cannons_lv5[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line3) {
                        std::get<2>(cannons_lv5[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "lv5";
                    }
                }
            }
            

            if (1280 - center < 0 && movement_blue == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_white == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_purple == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_grey == 0 && !enemies.empty()) {
                enemies.pop_back();
            }

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1280 - center, line3);
            modelMatrix *= transform2D::Scale(0.3f, 0.3f);
            RenderMesh2D(meshes["enemy_blue"], shaders["VertexColor"], modelMatrix);
            
            
            
        } 
        else if (colo == "white" && movement_white == 0) {
            float center = enemy.center_enemy;
            center += 50 * deltaTimeSeconds;
            enemy.center_enemy = center;
            if (enemy.interaction_healthbar == 0 && 1280 - center <= 10 && 1280 - center >= 0 && signal1 == 0) {
                signal1 = 1;
                enemy.interaction_healthbar = 1;
            }

            if (enemy.interaction_healthbar == 0 && signal1 == 1 && signal2 == 0 && 1280 - center <= 10 && 1280 - center >= 0) {
                signal2 = 1;
                enemy.interaction_healthbar = 1;
            }

            if (enemy.interaction_healthbar == 0 && signal3 == 0 && 1280 - center <= 10 && 1280 - center >= 0) {
                signal3 = 1;
                enemy.interaction_healthbar = 1;
            }
            enemy.center_enemy = center;
            center_enemy = center;
            
            if (placed_blue > 0) {
                for (int i = 0; i < cannons_blue.size(); i++) {
                    int x = std::get<0>(cannons_blue[i]);
                    int y = std::get<1>(cannons_blue[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line1) {
                        std::get<2>(cannons_blue[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "blue";
                    }
                }
            }

            if (placed_white > 0) {
                for (int i = 0; i < cannons_white.size(); i++) {
                    int x = std::get<0>(cannons_white[i]);
                    int y = std::get<1>(cannons_white[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line1) {
                        std::get<2>(cannons_white[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "white";
                    }
                }
            }

            if (placed_purple > 0) {
                for (int i = 0; i < cannons_purple.size(); i++) {
                    int x = std::get<0>(cannons_purple[i]);
                    int y = std::get<1>(cannons_purple[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line1) {
                        std::get<2>(cannons_purple[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "purple";
                    }
                }
            }

           if (placed_lv5 > 0) {
                for (int i = 0; i < cannons_lv5.size(); i++) {
                    int x = std::get<0>(cannons_lv5[i]);
                    int y = std::get<1>(cannons_lv5[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line1) {
                        std::get<2>(cannons_lv5[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "lv5";
                    }
                }
            }
            

            if (1280 - center < 0 && movement_blue == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_white == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_purple == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_grey == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1280 - center, line1);
            modelMatrix *= transform2D::Scale(0.3f, 0.3f);
            RenderMesh2D(meshes["enemy_white"], shaders["VertexColor"], modelMatrix);
            
        } 
        else if (colo == "purple" && movement_purple == 0) {
            float center = enemy.center_enemy;
            center += 50 * deltaTimeSeconds;
            if (enemy.interaction_healthbar == 0 && 1280 - center <= 10 && 1280 - center >= 0 && signal1 == 0) {
                signal1 = 1;
                enemy.interaction_healthbar = 1;
            }

            if (enemy.interaction_healthbar == 0 && signal1 == 1 && signal2 == 0 && 1280 - center <= 10 && 1280 - center >= 0) {
                signal2 = 1;
                enemy.interaction_healthbar = 1;
            }

            if (enemy.interaction_healthbar == 0 && signal3 == 0 && 1280 - center <= 10 && 1280 - center >= 0) {
                signal3 = 1;
                enemy.interaction_healthbar = 1;
            }
            enemy.center_enemy = center;
            center_enemy = center;

            if (placed_blue > 0) {
                for (int i = 0; i < cannons_blue.size(); i++) {
                    int x = std::get<0>(cannons_blue[i]);
                    int y = std::get<1>(cannons_blue[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line2) {
                        std::get<2>(cannons_blue[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "blue";
                    }
                }
            }

            if (placed_white > 0) {
                for (int i = 0; i < cannons_white.size(); i++) {
                    int x = std::get<0>(cannons_white[i]);
                    int y = std::get<1>(cannons_white[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line2) {
                        std::get<2>(cannons_white[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "white";
                    }
                }
            }

            if (placed_purple > 0) {
                for (int i = 0; i < cannons_purple.size(); i++) {
                    int x = std::get<0>(cannons_purple[i]);
                    int y = std::get<1>(cannons_purple[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line2) {
                        std::get<2>(cannons_purple[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "purple";
                    }
                }
            }

            if (placed_lv5 > 0) {
                for (int i = 0; i < cannons_lv5.size(); i++) {
                    int x = std::get<0>(cannons_lv5[i]);
                    int y = std::get<1>(cannons_lv5[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line2) {
                        std::get<2>(cannons_lv5[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "lv5";
                    }
                }
            }


            if (1280 - center < 0 && movement_blue == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_white == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_purple == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_grey == 0 && !enemies.empty()) {
                enemies.pop_back();
            }

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1280 - center, line2);
            modelMatrix *= transform2D::Scale(0.3f, 0.3f);
            RenderMesh2D(meshes["enemy_purple"], shaders["VertexColor"], modelMatrix);
            
        }
        else if (colo == "lv5" && movement_grey == 0) {
            float center = enemy.center_enemy;
            center += 50 * deltaTimeSeconds;
            enemy.center_enemy = center;

            if (enemy.interaction_healthbar == 0 && 1280 - center <= 10 && 1280 - center >= 0 && signal1 == 0) {
                signal1 = 1;
                enemy.interaction_healthbar = 1;
            }

            if (enemy.interaction_healthbar == 0 && signal1 == 1 && signal2 == 0 && 1280 - center <= 10 && 1280 - center >= 0) {
                signal2 = 1;
                enemy.interaction_healthbar = 1;
            }

            if (enemy.interaction_healthbar == 0 && signal3 == 0 && 1280 - center <= 10 && 1280 - center >= 0) {
                signal3 = 1;
                enemy.interaction_healthbar = 1;
            }
            enemy.center_enemy = center;
            center_enemy = center;

            if (placed_blue > 0) {
                for (int i = 0; i < cannons_blue.size(); i++) {
                    int x = std::get<0>(cannons_blue[i]);
                    int y = std::get<1>(cannons_blue[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line2) {
                        std::get<2>(cannons_blue[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "blue";
                    }
                }
            }

            if (placed_white > 0) {
                for (int i = 0; i < cannons_white.size(); i++) {
                    int x = std::get<0>(cannons_white[i]);
                    int y = std::get<1>(cannons_white[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line2) {
                        std::get<2>(cannons_white[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "white";
                    }
                }
            }

            if (placed_purple > 0) {
                for (int i = 0; i < cannons_purple.size(); i++) {
                    int x = std::get<0>(cannons_purple[i]);
                    int y = std::get<1>(cannons_purple[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line2) {
                        std::get<2>(cannons_purple[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "purple";
                    }
                }
            }

            if (placed_lv5 > 0) {
                for (int i = 0; i < cannons_lv5.size(); i++) {
                    int x = std::get<0>(cannons_lv5[i]);
                    int y = std::get<1>(cannons_lv5[i]);
                    if (radius_enemy + radius_projectile > glm::distance(1280 - center, ((float)x)) && y == line2) {
                        std::get<2>(cannons_lv5[i]) = 1;
                        enemy.interaction_enemy = 1;
                        enemy.colour_enemy = "lv5";
                    }
                }
            }

            if (1280 - center < 0 && movement_blue == 0 && !enemies.empty()){
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_white == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_purple == 0 && !enemies.empty()) {
                enemies.pop_back();
            }
            if (1280 - center < 0 && movement_grey == 0 && !enemies.empty()) {
                enemies.pop_back();
            }

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1280 - center, line2);
            modelMatrix *= transform2D::Scale(0.3f, 0.3f);
            RenderMesh2D(meshes["enemy_grey"], shaders["VertexColor"], modelMatrix);
        }
        
    }

    // eliminating cannons if touched by enemy
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].colour == "blue") {
            if (enemies[i].interaction_enemy == 1) {
                if (enemies[i].colour_enemy == "blue") {
                    for (int i = 0; i < cannons_blue.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "blue";
                        int x = std::get<0>(cannons_blue[i]);
                        int y = std::get<1>(cannons_blue[i]);
                        int state = std::get<2>(cannons_blue[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_blue.empty()) {
                                cannons_blue.erase(std::remove(cannons_blue.begin(), cannons_blue.end(), cannons_blue[i]), cannons_blue.end());
                                placed_blue = cannons_blue.size();
                            }
                            
                        }

                    }

                }
                if (enemies[i].colour_enemy == "white") {
                    for (int i = 0; i < cannons_white.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "white";
                        int x = std::get<0>(cannons_white[i]);
                        int y = std::get<1>(cannons_white[i]);
                        int state = std::get<2>(cannons_white[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_white.empty()) {
                                cannons_white.erase(std::remove(cannons_white.begin(), cannons_white.end(), cannons_white[i]), cannons_white.end());
                                placed_white = cannons_white.size();
                            }
                            
                        }

                    }

                }
                if (enemies[i].colour_enemy == "purple") {
                    for (int i = 0; i < cannons_purple.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "purple";
                        int x = std::get<0>(cannons_purple[i]);
                        int y = std::get<1>(cannons_purple[i]);
                        int state = std::get<2>(cannons_purple[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_purple.empty()) {
                                cannons_purple.erase(std::remove(cannons_purple.begin(), cannons_purple.end(), cannons_purple[i]), cannons_purple.end());
                                placed_purple = cannons_purple.size();
                            }
                            
                        }

                    }



                }
                if (enemies[i].colour_enemy == "lv5") {
                    for (int i = 0; i < cannons_lv5.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "lv5";
                        int x = std::get<0>(cannons_lv5[i]);
                        int y = std::get<1>(cannons_lv5[i]);
                        int state = std::get<2>(cannons_lv5[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_lv5.empty()) {
                                cannons_lv5.erase(std::remove(cannons_lv5.begin(), cannons_lv5.end(), cannons_lv5[i]), cannons_lv5.end());
                                placed_lv5 = cannons_lv5.size();
                            }
                            
                        }

                    }
                }
               
            }
        }

        if (enemies[i].colour == "white") {
            if (enemies[i].interaction_enemy == 1) {
                if (enemies[i].colour_enemy == "blue") {
                    for (int i = 0; i < cannons_blue.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "blue";
                        int x = std::get<0>(cannons_blue[i]);
                        int y = std::get<1>(cannons_blue[i]);
                        int state = std::get<2>(cannons_blue[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_blue.empty()) {
                                cannons_blue.erase(std::remove(cannons_blue.begin(), cannons_blue.end(), cannons_blue[i]), cannons_blue.end());
                                placed_blue = cannons_blue.size();
                            }

                        }

                    }

                }
                if (enemies[i].colour_enemy == "white") {
                    for (int i = 0; i < cannons_white.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "white";
                        int x = std::get<0>(cannons_white[i]);
                        int y = std::get<1>(cannons_white[i]);
                        int state = std::get<2>(cannons_white[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_white.empty()) {
                                cannons_white.erase(std::remove(cannons_white.begin(), cannons_white.end(), cannons_white[i]), cannons_white.end());
                                placed_white = cannons_white.size();
                            }

                        }

                    }

                }
                if (enemies[i].colour_enemy == "purple") {
                    for (int i = 0; i < cannons_purple.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "purple";
                        int x = std::get<0>(cannons_purple[i]);
                        int y = std::get<1>(cannons_purple[i]);
                        int state = std::get<2>(cannons_purple[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_purple.empty()) {
                                cannons_purple.erase(std::remove(cannons_purple.begin(), cannons_purple.end(), cannons_purple[i]), cannons_purple.end());
                                placed_purple = cannons_purple.size();
                            }

                        }

                    }



                }
                if (enemies[i].colour_enemy == "lv5") {
                    for (int i = 0; i < cannons_lv5.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "lv5";
                        int x = std::get<0>(cannons_lv5[i]);
                        int y = std::get<1>(cannons_lv5[i]);
                        int state = std::get<2>(cannons_lv5[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_lv5.empty()) {
                                cannons_lv5.erase(std::remove(cannons_lv5.begin(), cannons_lv5.end(), cannons_lv5[i]), cannons_lv5.end());
                                placed_lv5 = cannons_lv5.size();
                            }

                        }

                    }
                }
            }
        }

        if (enemies[i].colour == "purple") {
            if (enemies[i].interaction_enemy == 1) {
                if (enemies[i].colour_enemy == "blue") {
                    for (int i = 0; i < cannons_blue.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "blue";
                        int x = std::get<0>(cannons_blue[i]);
                        int y = std::get<1>(cannons_blue[i]);
                        int state = std::get<2>(cannons_blue[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_blue.empty()) {
                                cannons_blue.erase(std::remove(cannons_blue.begin(), cannons_blue.end(), cannons_blue[i]), cannons_blue.end());
                                placed_blue = cannons_blue.size();
                            }

                        }

                    }

                }
                if (enemies[i].colour_enemy == "white") {
                    for (int i = 0; i < cannons_white.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "white";
                        int x = std::get<0>(cannons_white[i]);
                        int y = std::get<1>(cannons_white[i]);
                        int state = std::get<2>(cannons_white[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_white.empty()) {
                                cannons_white.erase(std::remove(cannons_white.begin(), cannons_white.end(), cannons_white[i]), cannons_white.end());
                                placed_white = cannons_white.size();
                            }

                        }

                    }

                }
                if (enemies[i].colour_enemy == "purple") {
                    for (int i = 0; i < cannons_purple.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "purple";
                        int x = std::get<0>(cannons_purple[i]);
                        int y = std::get<1>(cannons_purple[i]);
                        int state = std::get<2>(cannons_purple[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_purple.empty()) {
                                cannons_purple.erase(std::remove(cannons_purple.begin(), cannons_purple.end(), cannons_purple[i]), cannons_purple.end());
                                placed_purple = cannons_purple.size();
                            }

                        }

                    }



                }
                if (enemies[i].colour_enemy == "lv5") {
                    for (int i = 0; i < cannons_lv5.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "lv5";
                        int x = std::get<0>(cannons_lv5[i]);
                        int y = std::get<1>(cannons_lv5[i]);
                        int state = std::get<2>(cannons_lv5[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_lv5.empty()) {
                                cannons_lv5.erase(std::remove(cannons_lv5.begin(), cannons_lv5.end(), cannons_lv5[i]), cannons_lv5.end());
                                placed_lv5 = cannons_lv5.size();
                            }

                        }

                    }
                }
            }
        }

        if (enemies[i].colour == "lv5") {
            if (enemies[i].interaction_enemy == 1) {
                if (enemies[i].colour_enemy == "blue") {
                    for (int i = 0; i < cannons_blue.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "blue";
                        int x = std::get<0>(cannons_blue[i]);
                        int y = std::get<1>(cannons_blue[i]);
                        int state = std::get<2>(cannons_blue[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_blue.empty()) {
                                cannons_blue.erase(std::remove(cannons_blue.begin(), cannons_blue.end(), cannons_blue[i]), cannons_blue.end());
                                placed_blue = cannons_blue.size();
                            }

                        }

                    }

                }
                if (enemies[i].colour_enemy == "white") {
                    for (int i = 0; i < cannons_white.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "white";
                        int x = std::get<0>(cannons_white[i]);
                        int y = std::get<1>(cannons_white[i]);
                        int state = std::get<2>(cannons_white[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_white.empty()) {
                                cannons_white.erase(std::remove(cannons_white.begin(), cannons_white.end(), cannons_white[i]), cannons_white.end());
                                placed_white = cannons_white.size();
                            }

                        }

                    }

                }
                if (enemies[i].colour_enemy == "purple") {
                    for (int i = 0; i < cannons_purple.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "purple";
                        int x = std::get<0>(cannons_purple[i]);
                        int y = std::get<1>(cannons_purple[i]);
                        int state = std::get<2>(cannons_purple[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_purple.empty()) {
                                cannons_purple.erase(std::remove(cannons_purple.begin(), cannons_purple.end(), cannons_purple[i]), cannons_purple.end());
                                placed_purple = cannons_purple.size();
                            }

                        }

                    }
                }
                if (enemies[i].colour_enemy == "lv5") {
                    for (int i = 0; i < cannons_lv5.size(); i++) {
                        using ColorTuple = std::tuple<int, int, string, int, int, int>;
                        std::string colorToDelete = "lv5";
                        int x = std::get<0>(cannons_lv5[i]);
                        int y = std::get<1>(cannons_lv5[i]);
                        int state = std::get<2>(cannons_lv5[i]);
                        if (state == 1 && !indexes.empty()) {
                            indexes.erase(std::remove_if(indexes.begin(), indexes.end(),
                                [colorToDelete, x, y](const ColorTuple& tuple) {
                                    return std::get<2>(tuple) == colorToDelete
                                        && std::get<0>(tuple) == x && std::get<1>(tuple) == y;
                                }),
                                indexes.end());
                            if (!cannons_lv5.empty()) {
                                cannons_lv5.erase(std::remove(cannons_lv5.begin(), cannons_lv5.end(), cannons_lv5[i]), cannons_lv5.end());
                                placed_lv5 = cannons_lv5.size();
                            }

                        }

                    }
                }
            }
        }
    }   
    
    // rendering cannons and collisions between projectiles and enemies

    for (const auto& tuple : indexes) {
        colour = std::get<2>(tuple);
            if (colour == "blue") {
                if (previous_y_blue == std::get<3>(tuple)) {
                    previous_y_blue = std::get<3>(tuple);
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                    RenderMesh2D(meshes["cannon_blue"], shaders["VertexColor"], modelMatrix);
                    if (colour_enemy == "blue" && pos_blue_y == line3 && movement_blue == 0) {
                        for (int i = 0; i < projectilesblue.size(); i++) {
                            float proj_cx = projectilesblue[i].cx;
                            proj_cx += 15 * deltaTimeSeconds;
                            projectilesblue[i].cx = proj_cx;
                            center_projectile = std::get<0>(tuple) + proj_cx;
                            modelMatrix = glm::mat3(1);
                            if (projectilesblue[i].interaction_enemy == 0) {
                                modelMatrix *= transform2D::Translate(pos_blue_x + proj_cx, pos_blue_y);
                                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                                modelMatrix *= transform2D::Rotate(angularStep);
                                RenderMesh2D(meshes["projectile_blue"], shaders["VertexColor"], modelMatrix);
                            }

                            if (radius_projectile + radius_enemy >= glm::distance(center_projectile, 1280 - center_enemy)) {
                                movement_blue = 1;
                                projectilesblue[i].interaction_enemy = 1;
                                projectilesblue.pop_back();
                            }
                        }
                    }
                }
                else {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                    RenderMesh2D(meshes["cannon_blue"], shaders["VertexColor"], modelMatrix);

                    if (colour_enemy == "blue" && pos_blue_y == line3 && movement_blue == 0) {
                        for (auto& proj : projectilesblue) {
                            float proj_cx = proj.cx;
                            proj_cx += 15 * deltaTimeSeconds;
                            proj.cx = proj_cx;
                            center_projectile = std::get<0>(tuple) + proj_cx;
                            modelMatrix = glm::mat3(1);
                            if (proj.interaction_enemy == 0) {
                                modelMatrix *= transform2D::Translate(pos_blue_x + proj_cx, pos_blue_y);
                                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                                modelMatrix *= transform2D::Rotate(angularStep);
                                RenderMesh2D(meshes["projectile_blue"], shaders["VertexColor"], modelMatrix);

                            }
                            if (radius_projectile + radius_enemy >= glm::distance(center_projectile, 1280 - center_enemy)) {
                                movement_blue = 1;
                                proj.interaction_enemy = 1;
                                projectilesblue.pop_back();
                            }

                        }
                        
                    }

                    
                }


            }
            else if (colour == "white") {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                RenderMesh2D(meshes["cannon_white"], shaders["VertexColor"], modelMatrix);
                if (previous_y_white == std::get<3>(tuple)) {
                    previous_y_white = std::get<3>(tuple);
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                    RenderMesh2D(meshes["cannon_white"], shaders["VertexColor"], modelMatrix);

                    if (colour_enemy == "white" && pos_white_y == line1 && movement_white == 0) {
                        for (auto& projwhite : projectileswhite) {
                            float proj_cx = projwhite.cx;
                            proj_cx += 15 * deltaTimeSeconds;
                            projwhite.cx = proj_cx;
                            center_projectile = std::get<0>(tuple) + proj_cx;
                            modelMatrix = glm::mat3(1);
                            if (projwhite.interaction_enemy == 0) {
                                modelMatrix *= transform2D::Translate(pos_white_x + proj_cx, pos_white_y);
                                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                                modelMatrix *= transform2D::Rotate(angularStep);
                                RenderMesh2D(meshes["projectile_white"], shaders["VertexColor"], modelMatrix);
                            }
                            if (radius_projectile + radius_enemy >= glm::distance(center_projectile, 1280 - center_enemy)) {
                                movement_white = 1;
                                projwhite.interaction_enemy = 1;
                                projectileswhite.pop_back();
                            }
                        }
                    }
                    
                }
                else {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                    RenderMesh2D(meshes["cannon_white"], shaders["VertexColor"], modelMatrix);
                    if (colour_enemy == "white" && pos_white_y == line1 && movement_white == 0) {
                        for (auto& projwhite : projectileswhite) {
                            float proj_cx = projwhite.cx;
                            proj_cx += 15 * deltaTimeSeconds;
                            projwhite.cx = proj_cx;
                            center_projectile = std::get<0>(tuple) + proj_cx;
                            modelMatrix = glm::mat3(1);
                            if (projwhite.interaction_enemy == 0) {
                                modelMatrix *= transform2D::Translate(pos_white_x + proj_cx, pos_white_y);
                                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                                modelMatrix *= transform2D::Rotate(angularStep);
                                RenderMesh2D(meshes["projectile_white"], shaders["VertexColor"], modelMatrix);

                            }

                            if (radius_projectile + radius_enemy >= glm::distance(center_projectile, 1280 - center_enemy)) {
                                movement_white = 1;
                                projwhite.interaction_enemy = 1;
                                projectileswhite.pop_back();
                            }
                        }
                    }
                }

            }
            else if (colour == "purple") {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                RenderMesh2D(meshes["cannon_purple"], shaders["VertexColor"], modelMatrix);
                if (previous_y_purple == std::get<3>(tuple)) {
                    previous_y_purple = std::get<3>(tuple);
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                    RenderMesh2D(meshes["cannon_purple"], shaders["VertexColor"], modelMatrix);
                    if (colour_enemy == "purple" && pos_purple_y == line2 && movement_purple == 0) {
                        for (auto& projpurple : projectilespurple) {
                            float proj_cx = projpurple.cx;
                            proj_cx += 15 * deltaTimeSeconds;
                            projpurple.cx = proj_cx;
                            center_projectile = std::get<0>(tuple) + proj_cx;
                            modelMatrix = glm::mat3(1);
                            if (projpurple.interaction_enemy == 0) {
                                modelMatrix *= transform2D::Translate(pos_purple_x + proj_cx, pos_purple_y);
                                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                                modelMatrix *= transform2D::Rotate(angularStep);
                                RenderMesh2D(meshes["projectile_purple"], shaders["VertexColor"], modelMatrix);
                            }
                            if (radius_projectile + radius_enemy >= glm::distance(center_projectile, 1280 - center_enemy)) {
                                movement_purple = 1;
                                projpurple.interaction_enemy = 1;
                                projectilespurple.pop_back();
                            }
                        }
                    }

                }
                else{
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                    RenderMesh2D(meshes["cannon_purple"], shaders["VertexColor"], modelMatrix);

                    if (colour_enemy == "purple" && pos_purple_y == line2 && movement_purple == 0) {
                        for (auto& projpurple : projectilespurple) {
                            float proj_cx = projpurple.cx;
                            proj_cx += 15 * deltaTimeSeconds;
                            projpurple.cx = proj_cx;
                            center_projectile = std::get<0>(tuple) + proj_cx;
                            modelMatrix = glm::mat3(1);
                            if (projpurple.interaction_enemy == 0) {
                                modelMatrix *= transform2D::Translate(pos_purple_x + proj_cx, pos_purple_y);
                                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                                modelMatrix *= transform2D::Rotate(angularStep);
                                RenderMesh2D(meshes["projectile_purple"], shaders["VertexColor"], modelMatrix);

                            }
                            if (radius_projectile + radius_enemy >= glm::distance(center_projectile, 1280 - center_enemy)) {
                                movement_purple = 1;
                                projpurple.interaction_enemy = 1;
                                projectilespurple.pop_back();
                            }

                        }
                    }
                    
                }
            }
            else if (colour == "lv5") {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                RenderMesh2D(meshes["cannon_lv5"], shaders["VertexColor"], modelMatrix);
                if (previous_y_lv5 == std::get<3>(tuple)) {
                    previous_y_lv5 = std::get<3>(tuple);
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                    RenderMesh2D(meshes["cannon_lv5"], shaders["VertexColor"], modelMatrix);

                    if (colour_enemy == "lv5" && pos_lv5_y == line2 && movement_grey == 0) {
                        for (auto& projlv5 : projectileslv5) {
                            float proj_cx = projlv5.cx;
                            proj_cx += 15 * deltaTimeSeconds;
                            projlv5.cx = proj_cx;
                            center_projectile = std::get<0>(tuple) + proj_cx;
                            modelMatrix = glm::mat3(1);
                            if (projlv5.interaction_enemy == 0) {
                                modelMatrix *= transform2D::Translate(pos_lv5_x + proj_cx, pos_lv5_y);
                                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                                modelMatrix *= transform2D::Rotate(angularStep);
                                RenderMesh2D(meshes["projectile_grey"], shaders["VertexColor"], modelMatrix);
                            }
                            if (radius_projectile + radius_enemy >= glm::distance(center_projectile, 1280 - center_enemy)) {

                                movement_grey = 1;
                                projlv5.interaction_enemy = 1;
                                projectileslv5.pop_back();
                            }
                        }

                    }
                }
                else {

                    previous_y_lv5 = std::get<3>(tuple);
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(std::get<0>(tuple), std::get<1>(tuple));
                    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                    RenderMesh2D(meshes["cannon_lv5"], shaders["VertexColor"], modelMatrix);
                    if (colour_enemy == "lv5" && pos_lv5_y == line2 && movement_grey == 0) {
                        for (auto& projlv5 : projectileslv5) {
                            float proj_cx = projlv5.cx;
                            proj_cx += 15 * deltaTimeSeconds;
                            projlv5.cx = proj_cx;
                            center_projectile = std::get<0>(tuple) + proj_cx;
                            modelMatrix = glm::mat3(1);
                            if (projlv5.interaction_enemy == 0) {
                                modelMatrix *= transform2D::Translate(pos_lv5_x + proj_cx, pos_lv5_y);
                                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                                modelMatrix *= transform2D::Rotate(angularStep);
                                RenderMesh2D(meshes["projectile_grey"], shaders["VertexColor"], modelMatrix);
                            }
                            if (radius_projectile + radius_enemy >= glm::distance(center_projectile, 1280 - center_enemy)) {
                                movement_grey = 1;
                                projlv5.interaction_enemy = 1;
                                projectileslv5.pop_back();
                            }

                        }
                    }

                }



            }
        }       

    // rendering the squares of the matrix

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate((j + 1) * (original_size - 20), i * original_size);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
    }
    // health bars

    if (signal1 == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(850, 600);
        modelMatrix *= transform2D::Scale(0.6f, 0.6f);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix); // health bar 1
    }
    
    if (signal2 == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1000, 600);
        modelMatrix *= transform2D::Scale(0.6f, 0.6f);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix); // health bar 2
    }
   
    if (signal3 == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1150, 600);
        modelMatrix *= transform2D::Scale(0.6f, 0.6f);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix); // health bar 3
    }
   
     

    time_l += 10 * deltaTimeSeconds;
    time_p += 10 * deltaTimeSeconds;
    time_r += 10 * deltaTimeSeconds;
    time_q += 10 * deltaTimeSeconds;
    time_is_money += 5 * deltaTimeSeconds;
    time_enemy += 5 * deltaTimeSeconds;
    
}


void tema1::FrameEnd()
{

    if (signal1 == 1 && signal2 == 1 && signal3 == 1) {
        window->Close();
    }

}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
   


}


void tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mouseX_out = mouseX;
    mouseY_out = mouseY;

    // Add mouse move event
}


void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // selecting stars, cannons
    released = 0;

    button_mouse = button;
    if (button == 1 && mouseX > 760 && mouseX <= star1_x + 35 && mouseY < 720 + star1_y + 10 && star1 == 0) {
        star1 = 1;
        star2 = 0;
        star3 = 0;
        currency.push_back(std::make_tuple(index_currency_y, index_currency_x));
        money++;
        index_currency_y += 30;
    }

    if (button == 1 && mouseX > star1_x + 35 && mouseX <= star2_x + 35 && mouseY < 720 + star2_y + 10 && star2 == 0) {
        star1 = 1;
        star2 = 1;
        star3 = 0;
        currency.push_back(std::make_tuple(index_currency_y, index_currency_x));
        money++;
        index_currency_y += 30;
    }


    else if (button == 1 && mouseX > star2_x + 35 && mouseX <= star3_x + 35 && mouseY < 720 + star3_y + 10 && star3 == 0) {
        star1 = 1;
        star2 = 1;
        star3 = 1;
        currency.push_back(std::make_tuple(index_currency_y, index_currency_x));
        money++;
        index_currency_y += 30;
    }

    if (mouseX >= 50 && mouseX < 150  && mouseY >= 40 && mouseY < 65) {
        blue = 1;
        white = 0;
        purple = 0;
        lv5 = 0;
    }
    else {
        blue = 0;
    }
    
    if (mouseX >= 250 && mouseX < 350 && mouseY >= 40 && mouseY < 65) {
        white = 1;
        blue = 0;
        purple = 0;
        lv5 = 0;

    }
    else {
        white = 0;
    }
    
    if (mouseX >= 450 && mouseX < 550 && mouseY >= 40 && mouseY < 65) {
        purple = 1;
        blue = 0;
        white = 0;
        lv5 = 0;

    }
    else {
        purple = 0;
    }
    
    if (mouseX >= 660 && mouseX < 760 && mouseY >= 40 && mouseY < 65) {
        lv5 = 1;
        purple = 0;
        blue = 0;
        white = 0;
        purple = 0;

    }
    else {
        lv5 = 0;
    }

}


void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

    // removing cannons from positions
    released = 1;
    if (button == 2 && released == 1) {
        for (int i = 0; i < indexes.size(); i++) {
            int x = std::get<0>(indexes[i]);
            int y = std::get<1>(indexes[i]);
            if (mouseX <= x && 720 - mouseY < y) {
                 indexes.erase(std::remove(indexes.begin(), indexes.end(), indexes[i]), indexes.end());
            }
               
        }

    }
    
    mouseX_final = mouseX;
    mouseY_final = mouseY;
    mouseX_final_f = mouseX;
    mouseY_final_f = mouseY;

}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema1::OnWindowResize(int width, int height)
{
}
