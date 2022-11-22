#ifndef DAST_EX1_TEAM_H
#define DAST_EX1_TEAM_H
#include "AVLTree.h"
#include "Player.h"

class Team {
private:
    int id;
    int points;
    AVLTree<Player, Player>* players;
    Player* top_scorrer;
    int players_count;
    bool has_goal_keeper;
    int power;
    int games_played;

public:
    Team() = delete;
    Team(int id);
    ~Team();
    /**
     * those methods are for the Team only, and will be executed from the add_player and remove_player methods
     * **/
    Node<int, Player&>* add_player_to_team(Player& player);
    Node<int, Player&>* remove_player_from_team(Player& player);

    /**
     * getters and setters : according to need
     */

};

#endif //DAST_EX1_TEAM_H