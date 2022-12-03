#include "Player.h"

bool PlayerLevel::operator>(PlayerLevel* level1, PlayerLevel* level2) {
	if (level1->goals == level2->goals) {
		if (level1->cards == level2->cards) {
			return (level1->id > level2->id)
		} else
			return (level1->cards < level2->cards);
	} else {
		return (level1->goals > level2->goals);
	}
}

Player::Player(int playerId, Team* team, int gamesPlayed, int goals, int cards, bool goalKeeper):
		id(playerId), team(team), games_played(gamesPlayed), goals(goals), is_goal_keeper(goalKeeper) {
	PlayerLevel *player_level = new PlayerLevel(goals, cards, playerId);
}