#include "Player.h"

//bool PlayerLevel::operator>(PlayerLevel* level1, PlayerLevel* level2) {
//	if (level1->goals == level2->goals) {
//		if (level1->cards == level2->cards) {
//			return (level1->id > level2->id);
//		} else
//			return (level1->cards < level2->cards);
//	} else {
//		return (level1->goals > level2->goals);
//	}
//}

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


Player::Player(int playerId, Team* team, int gamesPlayed, int goals, int cards, bool goalKeeper):
		id(playerId), team(team), games_played(gamesPlayed), goals(goals), is_goal_keeper(goalKeeper) {
	level = new PlayerLevel(goals, cards, playerId);
}

void Player::update_level() {
	level->cards = cards;
	level->goals = goals;
}

int Player::get_total_games_played() {
	return (team->games_played + games_played);
}