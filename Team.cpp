#include "Team.h"

Team::Team(int id, int points, AVLTree<Player, Player>* players = nullptr, Player* top_scorrer = nullptr,
	 int players_count = EMPTY_NUM, int power = ZERO, int games_played = ZERO, bool has_goal_keeper = false):
	 id(id), points(points), players(), top_scorrer() {};
