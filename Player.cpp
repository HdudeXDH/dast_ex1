#include "Player.h"

bool PlayerLevel::operator>(const PlayerLevel & otherlevel) {
	if (this->goals == otherlevel.goals) {
		if (this->cards == otherlevel.cards) {
			return (this->id > otherlevel.id);
		} else
			return (this->cards < otherlevel.cards);
	} else {
		return (this->goals > otherlevel.goals);
	}
}

bool PlayerLevel::operator<(const PlayerLevel & otherlevel) {
    if (*this==otherlevel) return false;
    return !(*this>otherlevel);
}


bool PlayerLevel::operator==(const PlayerLevel & otherlevel) {
	return (this->goals == otherlevel.goals) &&(this->id == otherlevel.id) &&(this->cards == otherlevel.cards);
}


//ctor at team cpp

void Player::update_level() {
	level->cards = cards;
	level->goals = goals;
}

//int Player::get_total_games_played() {
//	return (team->games_played + games_played);
//}