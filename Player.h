#ifndef DAST_EX1_PLAYER_H
#define DAST_EX1_PLAYER_H
#include <iostream>

class Team;
class PlayerLevel {
public:
	int goals;
	int cards;
	int id;

	// big 3
	PlayerLevel(int goals, int cards, int id):goals(goals), cards(cards), id(id){}
	~PlayerLevel() = default;
	//compare method overload
	bool operator>(const PlayerLevel & otherlevel);//(PlayerLevel* level1, PlayerLevel* level2);
    bool operator==(const PlayerLevel & otherlevel);
    bool operator<(const PlayerLevel & otherlevel);
};


class Player {
public:
	int id;
    Team* team;
	int games_played;
	int goals;
	int cards;
	bool is_goal_keeper;
	int teams_matches_pre_arrival_count;
	PlayerLevel level;
	Player* next_up;
    Player* next_down;


	Player()= delete;
	Player(int playerId, Team* team, int gamesPlayed, int goals, int cards, bool goalKeeper);
    ~Player() {};
	void update_level();
    bool operator> (const Player& other) const;
	int get_total_games_played();
    Player * getCloset(){
        if (next_up== nullptr){return next_down;}
        if (next_down== nullptr){return next_up;}
        if (next_down->goals!=next_up->goals) {
            int downDelta = goals-next_down->goals;
            int upDelta = goals-next_up->goals;
            if ((long)downDelta*(long)downDelta<(long)upDelta*(long)upDelta) return next_down;
			if ((long)downDelta*(long)downDelta>(long)upDelta*(long)upDelta) return next_up;
        }
        if (next_down->cards!=next_up->cards) {
            int downDelta = cards-next_down->cards;
            int upDelta = cards-next_up->cards;
            if ((long)downDelta*(long)downDelta<(long)upDelta*(long)upDelta) return next_down;//if (downDelta*downDelta<upDelta*upDelta) return next_down;
			if ((long)downDelta*(long)downDelta>(long)upDelta*(long)upDelta) return next_up;
        }
        if (next_down->id!=next_up->id) {
            int downDelta = id-next_down->id;
            int upDelta = id-next_up->id;
            if ((long)downDelta*(long)downDelta<(long)upDelta*(long)upDelta) return next_down;//if (downDelta*downDelta<upDelta*upDelta) return next_down;
            if ((long)downDelta*(long)downDelta>(long)upDelta*(long)upDelta) return next_up;
        }
        if (next_down->id>next_up->id) return next_down;
        else return next_up;
    }
};


#endif //DAST_EX1_PLAYER_H
