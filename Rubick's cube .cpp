#include <iostream>
#include <array>

class rubiks_cube {
public:
    enum color { e_white, e_red, e_green, e_orange, e_blue, e_yellow };
    enum side { e_top, e_front, e_left, e_back, e_right, e_bottom };
    enum direction { e_middle, e_equator, e_standing };

private:
    std::array<std::array<color, 4>, 6> cube;
    color colors[6] = { e_white, e_red, e_green, e_orange, e_blue, e_yellow};

    void swap (color &a, color &b){
        color tmp = a;
        a = b;
        b = tmp;
    }

    void reorder (side side){
        swap(cube[side][1], cube[side][2]);
        swap(cube[side][0], cube[side][1]);
        swap(cube[side][2], cube[side][3]);
    }
    void reorder_d(side side){
        swap(cube[side][0], cube[side][3]);
        swap(cube[side][0], cube[side][1]);
        swap(cube[side][2], cube[side][3]);
    }

public:
    rubiks_cube(){
        for (int i = 0; i < 6; ++i){
            for (int j = 0; j < 4; ++j){
                cube[i][j] = colors[i];
            }
        }
    }

    rubiks_cube(const rubiks_cube &other) {
        cube = other.cube;
    }

    rubiks_cube &operator = (const rubiks_cube &other)= default;

    ~rubiks_cube() = default;

    void rotate_cube (direction direct, int count){
        if(count < 0) count = count % 4 + 4;
        else count = count % 4;

        if (direct == e_middle){
            for(int i = 0; i < count; ++i) {
                reorder_d(e_left);
                reorder(e_right);

                std::array<color, 4> tmp(cube[e_bottom]);
                cube[e_bottom] = cube[e_back];
                cube[e_back] = cube[e_top];
                cube[e_top] = cube[e_front];
                cube[e_front] = tmp;
                reorder(e_back);
                reorder(e_back);
                reorder(e_bottom);
                reorder(e_bottom);
            }

        }


        else if (direct == e_equator){
            for(int i = 0; i < count; ++i) {
                reorder(e_top);
                reorder_d(e_bottom);

                std::array<color, 4> tmp(cube[e_right]);
                cube[e_right] = cube[e_back];
                cube[e_back] = cube[e_left];
                cube[e_left] = cube[e_front];
                cube[e_front] = tmp;
            }
        }

        else if (direct == e_standing){
            for(int i = 0; i < count; ++i) {
                reorder(e_front);
                reorder_d(e_back);

                std::array<color,4> tmp(cube[e_bottom]);
                cube[e_bottom] = cube[e_right];
                cube[e_right] = cube[e_top];
                cube[e_top] = cube[e_left];
                cube[e_left] = tmp;

                reorder(e_bottom);
                reorder(e_right);
                reorder(e_left);
                reorder(e_top);
            }
        }
    }

    void rotate_side(side side, int count){
        if(count < 0) count = count % 4 + 4;
        else count = count % 4;

        if(side == e_front){
            for (int i = 0; i < count; ++i) {
                reorder(e_front);

                swap(cube[e_top][2], cube[e_right][0]);
                swap(cube[e_top][3], cube[e_right][2]);

                swap(cube[e_top][2], cube[e_bottom][1]);
                swap(cube[e_top][3], cube[e_bottom][0]);

                swap(cube[e_top][2], cube[e_left][3]);
                swap(cube[e_top][3], cube[e_left][1]);

            }
        }
        else if (side == e_top){
            for (int i = 0; i < count; ++i) {
                reorder(e_top);

                swap(cube[e_back][0], cube[e_right][0]);
                swap(cube[e_back][1], cube[e_right][1]);

                swap(cube[e_back][0], cube[e_front][0]);
                swap(cube[e_back][1], cube[e_front][1]);

                swap(cube[e_back][0], cube[e_left][0]);
                swap(cube[e_back][1], cube[e_left][1]);

            }
        }

        else if (side == e_right){
            for (int i = 0; i < count; ++i) {
                reorder(e_right);

                swap(cube[e_top][3], cube[e_back][0]);
                swap(cube[e_top][1], cube[e_back][2]);

                swap(cube[e_top][3], cube[e_bottom][3]);
                swap(cube[e_top][1], cube[e_bottom][1]);

                swap(cube[e_top][3], cube[e_front][3]);
                swap(cube[e_top][1], cube[e_front][1]);

            }
        }

        else if (side == e_back){
            for (int i = 0; i < count; ++i) {
                reorder(e_back);

                swap(cube[e_top][0], cube[e_left][2]);
                swap(cube[e_top][1], cube[e_left][0]);

                swap(cube[e_top][0], cube[e_bottom][3]);
                swap(cube[e_top][1], cube[e_bottom][2]);

                swap(cube[e_top][0], cube[e_right][1]);
                swap(cube[e_top][1], cube[e_right][3]);

            }
        }

        else if (side == e_left){
            for (int i = 0; i < count; ++i) {
                reorder(e_left);

                swap(cube[e_top][0], cube[e_front][0]);
                swap(cube[e_top][2], cube[e_front][2]);

                swap(cube[e_top][0], cube[e_bottom][0]);
                swap(cube[e_top][2], cube[e_bottom][2]);

                swap(cube[e_top][0], cube[e_back][3]);
                swap(cube[e_top][2], cube[e_back][1]);

            }
        }

        else if (side == e_bottom){
            for (int i = 0; i < count; ++i) {
                reorder(e_bottom);

                swap(cube[e_front][2], cube[e_right][2]);
                swap(cube[e_front][3], cube[e_right][3]);

                swap(cube[e_front][2], cube[e_back][2]);
                swap(cube[e_front][3], cube[e_back][3]);

                swap(cube[e_front][2], cube[e_left][2]);
                swap(cube[e_front][3], cube[e_left][3]);

            }
        }

    }

    const std::array<color, 4> &get_side (side side) const{
        return cube[side];
    }
};
