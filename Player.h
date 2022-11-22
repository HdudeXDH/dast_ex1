#ifndef DAST_EX1_PLAYER_H
#define DAST_EX1_PLAYER_H
#include "Team.h"

class Player {
private:
    int id;
    Team* team;
    int games_played;
    int cards;
    bool is_goal_keeper;
    int goals;
    int teams_matches_pre_arrival_count;
    Node<int, Player>* next_up;
    Node<int, Player>* next_down;

public:
    Player()= delete;
    Player(int id);
    ~Player()= default;
    bool operator> (const Player& other) const;

    /**
     * getters and setters - add needed
     */
}


#endif //DAST_EX1_PLAYER_H