#include "worldcup23a1.h"

world_cup_t::world_cup_t(): top_scorrer(nullptr), players_count(EMPTY_NUM)
{
    legitimate_teams = AVLTree<int, Team*>();
    players_by_level = AVLTree<PlayerLevel, Player*>();
    teams = AVLTree<int , Team>();
    players_by_id = AVLTree<int, Player>();
}

world_cup_t::~world_cup_t()
{
	// the default dTor is fine :)
}


StatusType world_cup_t::add_team(int teamId, int points)
{
	if (teamId <= 0 || points < 0) {
		return StatusType::INVALID_INPUT;
	}
	std::shared_ptr<Node<Team_id, Team>> search_result = teams.search(teamId, true);
	if(search_result != nullptr) {
		if (search_result->value.id ==teamId) return StatusType::FAILURE;
	}
	try {
		teams.add(teamId, Team(teamId, points));
	}
	catch (AVLTree<Team_id, Team>::NodeAlreadyExists& err) {
		return StatusType::FAILURE;
	}
	catch (std::bad_alloc& err){
		return StatusType::ALLOCATION_ERROR;
	}
//    printPlayersNextups();
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	if (teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	std::shared_ptr<Node<int, Team>> search_result = teams.search(teamId);
	if (search_result == nullptr) {
		// team doens't exists
		return StatusType::FAILURE;
	}
	Team* team_to_remove = &search_result->value;
	if (!((team_to_remove->players).is_empty())) {
		// team has players
		return StatusType::FAILURE;
	}
	try {
		teams.remove_by_key(teamId);
	}
	catch (std::exception& err){
		return StatusType::ALLOCATION_ERROR; //ERROR_ALLOCATION;
	}
    return StatusType::SUCCESS;
}

void world_cup_t::renew_player_nextup_nextdown(std::shared_ptr<Node<PlayerLevel, Player*> > new_player_by_level){
    std::shared_ptr<Node<PlayerLevel, Player*>>nextup = players_by_level.find_next_up(new_player_by_level);
    Player* nextdown;
    if (nextup== nullptr){
        nextdown = top_scorrer;
        top_scorrer=new_player_by_level->value;
        new_player_by_level->value->next_down=nextdown;
    } else {
        nextdown = nextup->value->next_down;
        new_player_by_level->value->next_down=nextdown;
        nextup->value->next_down=new_player_by_level->value;
        new_player_by_level->value->next_up=nextup->value;
    }
    if (nextdown != nullptr){
        nextdown->next_up=new_player_by_level->value;
    }
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
	if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals <0 || cards < 0 ) {
		return StatusType::INVALID_INPUT;
	}
	if (gamesPlayed == 0 && (goals > 0 || cards > 0)) {
		return StatusType::INVALID_INPUT;
	}
	std::shared_ptr<Node<Team_id, Team>> team_search_result = teams.search(teamId);
    std::shared_ptr<Node<int, Player> >player_search_result = players_by_id.search(playerId); //std::shared_ptr<Node<Player_id, Player>
	if(team_search_result == nullptr || player_search_result != nullptr ) {
		return StatusType::FAILURE;
	}
	Team *team_to_add_player = &team_search_result->value;
	try {

        std::shared_ptr<Node<int, Player>> new_player = players_by_id.add(playerId, Player(playerId,&team_search_result->value, gamesPlayed, goals, cards, goalKeeper));
        std::shared_ptr<Node<PlayerLevel, Player*> >new_player_by_level = players_by_level.add(new_player->value.level, &new_player->value);
        renew_player_nextup_nextdown(new_player_by_level);
		bool was_team_legitimate_before_adding = team_to_add_player->is_legitimate_for_match();
		team_to_add_player->add_player_to_team(&new_player->value);
		if (team_to_add_player->is_legitimate_for_match() && !was_team_legitimate_before_adding) {
			legitimate_teams.add(teamId, team_to_add_player);
		}
		players_count = players_count + 1;
		top_scorrer = players_by_level.max_node()->value;
	}
	catch (std::bad_alloc& err){
		return StatusType::ALLOCATION_ERROR;
	}
//    printPlayersNextups();
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if (playerId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	std::shared_ptr<Node<Player_id, Player>>player_node_in_id_tree = players_by_id.search(playerId);
	if (player_node_in_id_tree == nullptr) {
		return StatusType::FAILURE;
	}
	Team *players_team = player_node_in_id_tree->value.team;
	PlayerLevel level = player_node_in_id_tree->value.level;
	std::shared_ptr<Node<PlayerLevel, Player*>>player_node_in_level_tree = players_by_level.search(level);
	try {
		// remove player from all AVL trees
		bool was_team_legitimate_before_removing = players_team->is_legitimate_for_match();
		if (player_node_in_id_tree->value.next_down != nullptr) {
            player_node_in_id_tree->value.next_down->next_up = player_node_in_id_tree->value.next_up;
        }
		if (player_node_in_id_tree->value.next_up != nullptr) {
            player_node_in_id_tree->value.next_up->next_down = player_node_in_id_tree->value.next_down;
        }
        players_by_level.remove_by_key(player_node_in_level_tree->key);
        players_team->remove_player_from_team(&player_node_in_id_tree->value);
        players_by_id.remove_by_key(player_node_in_id_tree->key);
        players_count = players_count - 1;
		if (was_team_legitimate_before_removing && !players_team->is_legitimate_for_match()) {
			legitimate_teams.remove_by_key(players_team->id);
		}
        std::shared_ptr<Node<PlayerLevel,Player*>>new_top_scorrer = players_by_level.max_node();
        if (new_top_scorrer == nullptr){
            top_scorrer= nullptr;
        }
		else {top_scorrer = players_by_level.max_node()->value;}
	} catch (std::exception& err) {
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	if (playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived <0) {
		return StatusType::INVALID_INPUT;
	}
	std::shared_ptr<Node<Player_id, Player>>player_node_in_id_tree = players_by_id.search(playerId);
    if (player_node_in_id_tree == nullptr) {
        return StatusType::FAILURE;
    }
    Player * player = &(player_node_in_id_tree->value);
    if (player->next_down != nullptr) {player->next_down->next_up = player->next_up;}
    if (player->next_up != nullptr) {player->next_up->next_down = player->next_down;}
//    std::cout<<"alon------"<<std::endl;
//    printPlayersNextups();
//    std::cout<<"alon!------"<<std::endl;
    Team * team = player->team;
	team->remove_player_from_team(player);
    try {
        players_by_level.remove_by_key(player->level);
    } catch (std::exception& err) {
        return StatusType::ALLOCATION_ERROR;
    }
	player->games_played = (player->games_played + gamesPlayed);
	player->goals = (player->goals + scoredGoals);
	player->cards = (player->cards + cardsReceived);
	player->update_level();
	try {
        std::shared_ptr<Node<PlayerLevel, Player*>>new_player_by_level =players_by_level.add(player->level, player);
        if (top_scorrer==player) top_scorrer=player->next_down;
        renew_player_nextup_nextdown(new_player_by_level);
		team->add_player_to_team(player);
	} catch (std::exception& err) {
		return StatusType::ALLOCATION_ERROR;
	}
//    printPlayersNextups();
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	if (teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0) {
		return StatusType::INVALID_INPUT;
	}
    std::shared_ptr<Node<int,Team>> team1_node =  teams.search(teamId1);
    std::shared_ptr<Node<int,Team>> team2_node =  teams.search(teamId2);

	if (team1_node == nullptr || team2_node == nullptr ) {
		return StatusType::FAILURE;
	}
    Team* team1 = &team1_node->value;
    Team* team2 = &team2_node->value;

    if (!(team1->is_legitimate_for_match()) || !(team2->is_legitimate_for_match())) {
        return StatusType::FAILURE;
    }

	int team1_overall_score = team1->get_overall_score();
	int team2_overall_score = team2->get_overall_score();
	if (team1_overall_score == team2_overall_score) {
		team1->points = team1->points + 1;
		team2->points = team2->points + 1;
	} else if (team1_overall_score > team2_overall_score) {
		team1->points = team1->points + 3;
	} else {
		team2->points = team2->points + 3;
	}
	team1->bump_games_played();
	team2->bump_games_played();
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	if (playerId <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
    std::shared_ptr<Node <int, Player>> player_node = players_by_id.search(playerId);
	if (player_node == nullptr) {
		return output_t<int>(StatusType::FAILURE);
	}
	int num_of_games = player_node->value.get_total_games_played();
	return output_t<int>(num_of_games);
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if (teamId <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
    std::shared_ptr<Node <int, Team>> team_node = teams.search(teamId);

	if (team_node == nullptr) {
		return output_t<int>(StatusType::FAILURE);
	}
	return output_t<int>(team_node->value.points);
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// team search and validation
    if (teamId1==teamId2 || newTeamId <= 0 || teamId2 <= 0 || teamId1 <= 0) return StatusType::INVALID_INPUT;
    std::shared_ptr<Node <int, Team>> team1_node = teams.search(teamId1);
    std::shared_ptr<Node <int, Team>> team2_node = teams.search(teamId2);
    if (team1_node == nullptr || team2_node == nullptr) {
		return StatusType::FAILURE;
	}
	std::shared_ptr<Node <int, Team>> newteam_node = teams.search(newTeamId);
	if ((newteam_node != nullptr) && (newteam_node != team1_node) && (newteam_node != team2_node)) {
		return StatusType::FAILURE;
	}

	// create new team if the teamid is new
	if (newteam_node != team1_node && newteam_node != team2_node) {
		add_team(newTeamId,team1_node->value.points+team2_node->value.points);
	}
	newteam_node = teams.search(newTeamId);
    if (newteam_node== nullptr){
    }
    Team * newteam = &(newteam_node->value);
    Team * team1 = &(team1_node->value);
    Team * team2 = &(team2_node->value);
    if (team1->is_legitimate_for_match()) legitimate_teams.remove_by_key(teamId1);
    if (team2->is_legitimate_for_match()) legitimate_teams.remove_by_key(teamId2);
    std::shared_ptr<Node<PlayerLevel, Player*>>* team1_array = team1->players.export_to_array();
    for (int i=0;i<team1->players_count;i++){
		team1_array[i]->value->games_played+=team1->games_played-team1_array[i]->value->teams_matches_pre_arrival_count;
		team1_array[i]->value->team = newteam;
        team1_array[i]->value->teams_matches_pre_arrival_count=0;
    }
    std::shared_ptr<Node<PlayerLevel, Player*>>* team2_array = team2->players.export_to_array();
    for (int i=0;i<team2->players_count;i++){
		team2_array[i]->value->games_played+=team2->games_played-team2_array[i]->value->teams_matches_pre_arrival_count;
		team2_array[i]->value->team = newteam;
        team2_array[i]->value->teams_matches_pre_arrival_count=0;
    }

    //merging the trees
    newteam->players.merge_trees(team1->players,team2->players);
    newteam->players_by_id.merge_trees(team1->players_by_id,team2->players_by_id);
    newteam->players_count = team1->players_count + team2->players_count;
    newteam->goal_keepers_count = team1->goal_keepers_count + team2->goal_keepers_count;
    newteam->power = team1->power + team2->power;
    newteam->points= team1->points+team2->points;
	newteam->games_played = 0;
    if (newteam->is_legitimate_for_match()) legitimate_teams.add(newTeamId, newteam);
    if (team1->top_scorrer==nullptr||team2->top_scorrer==nullptr) {newteam->top_scorrer= team1->top_scorrer==nullptr?team2->top_scorrer:team1->top_scorrer;} else
    if (team1->top_scorrer->level>team2->top_scorrer->level) {newteam->top_scorrer= team1->top_scorrer;}
    else {newteam->top_scorrer= team2->top_scorrer;}
    if (teamId1!=newTeamId){
        teams.remove_by_key(teamId1);
    }
    if (teamId2!=newTeamId){
        teams.remove_by_key(teamId2);
    }
    delete[] team2_array;
    delete[] team1_array;
//    printPlayersNextups();
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	if (teamId == 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	if (teamId > 0 ) {
        std::shared_ptr<Node <int, Team>> team_node = teams.search(teamId);
		if (team_node == nullptr) {
			return output_t<int>(StatusType::FAILURE);
		}
		if (team_node->value.top_scorrer==nullptr) return output_t<int>(StatusType::FAILURE);
		return team_node->value.top_scorrer->id;
	} else {
		if(top_scorrer==nullptr) return output_t<int>(StatusType::FAILURE);
		return top_scorrer->id;
	}
}

output_t<int> world_cup_t::get_all_players_count(int teamId) {
	if (teamId == 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	if (teamId > 0) {
		std::shared_ptr<Node<int, Team>> team_node = teams.search(teamId);
		if (team_node == nullptr) {
			return output_t<int>(StatusType::FAILURE);
		}
		return output_t<int>(team_node->value.players_count);
	} else {
		return output_t<int>(players_count);
	}
}

void print_player_ptr(std::shared_ptr<Node<PlayerLevel, Player*>> ptr){
    if (ptr== nullptr) std::cout<<"None";
    else  std::cout<<ptr->value->id;
}
void print_player_ptr(Player* ptr){
    if (ptr== nullptr) std::cout<<"None";
    else  std::cout<<ptr->id;
}

void world_cup_t::printPlayersNextups(){
    std::shared_ptr<Node<PlayerLevel, Player*>>* block_array =players_by_level.export_to_array();
    for (int i=0; i< players_by_level.size;i++){
        std::cout<< block_array[i]->value->id <<",nextdown[";
        print_player_ptr(block_array[i]->value->next_down);
        std::cout<<"],nextup[";
        print_player_ptr(block_array[i]->value->next_up);
        std::cout<<"]"<<std::endl;
    }
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if (teamId == 0 || output == nullptr) {
		return StatusType::INVALID_INPUT;
	}
	if (players_by_id.size == 0 ) {
		return StatusType::FAILURE;
	}
	if (teamId > 0 ) {
        std::shared_ptr<Node <int, Team>> team_node = teams.search(teamId);

        if (team_node == nullptr) {
            return StatusType::FAILURE;
        }
        Team & team = team_node->value;
		if (team.players.is_empty()) {
			return StatusType::FAILURE;
		}
        std::shared_ptr<Node<PlayerLevel, Player*>>* block_array =team.players.export_to_array();
		for (int i=0; i< team.players.size;i++){
            output[i] =  block_array[i]->value->id;
		}
        delete [] block_array;
		return StatusType::SUCCESS;
	} else if (teamId < 0 && players_by_level.size == 0) {
		return StatusType::FAILURE;
	}

	std::shared_ptr<Node<PlayerLevel, Player*>>* block_array =players_by_level.export_to_array();
	for (int i=0; i< players_by_level.size;i++){
		output[i] =  block_array[i]->value->id;
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	if (playerId <= 0 || teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}
    std::shared_ptr<Node <int, Team>> team_node = teams.search(teamId);
    if (team_node== nullptr){
        return StatusType::FAILURE;
    }
    std::shared_ptr<Node <int, Player*>> player_node = team_node->value.players_by_id.search(playerId);
    if (player_node== nullptr){
        return StatusType::FAILURE;
    }
	if(players_by_id.size == 1) {
		return StatusType::FAILURE;
	}
//    printBT(players_by_level.root.get());
//    printPlayersNextups();
	return player_node->value->getCloset()->id;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	if (minTeamId < 0 || maxTeamId < 0 || minTeamId > maxTeamId) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	if (legitimate_teams.size == 0) {
		return output_t<int>(StatusType::FAILURE);
	}

    std::shared_ptr<LinkedList<int, int>> playing_teams = export_lagitimate_teams_to_list(minTeamId, maxTeamId);
	if (playing_teams->size <= 0) {
		return output_t<int>(StatusType::FAILURE);
	}
    std::shared_ptr<LinkedList_Node<int, int>> first_team = playing_teams->head->next, second_team;
    std::shared_ptr<LinkedList_Node<int, int>> next_pair;
	int new_value;
	while(playing_teams->size > 1) {
		while (first_team!=nullptr && first_team->next != nullptr){
            second_team = first_team->next;
			new_value = first_team->value + second_team->value + POINTS_TO_ADD;
            next_pair = second_team->next;
			if(first_team->value < second_team->value || (first_team->value == second_team->value && first_team->key < second_team->key)) {
                second_team->value = new_value;
                playing_teams->remove_node(first_team);
			} else {
                first_team->value = new_value;
                playing_teams->remove_node(second_team);
            }
            first_team = next_pair;

		}
		first_team = playing_teams->head->next;
	}
	assert(playing_teams->size == 1);
	int winner = playing_teams->head->next->key;
//    printPlayersNextups();
	return output_t<int>(winner);
}


///// -------------------- private methods ---------------------

std::shared_ptr<LinkedList<int, int>> world_cup_t::export_lagitimate_teams_to_list(int minTeamId, int maxTeamId) {
    std::shared_ptr<LinkedList<int, int>> playing_teams = std::shared_ptr<LinkedList<int, int>>(new LinkedList<int, int>());
	Recursive_export_legitimate_teams_to_list(legitimate_teams.root, playing_teams,minTeamId, maxTeamId);
	return playing_teams;
}


void world_cup_t::Recursive_export_legitimate_teams_to_list(std::shared_ptr<Node<int, Team*>> root, std::shared_ptr<LinkedList<int, int>> list, int minId, int maxId) {
	if (root->key > minId) {
		if (root->left != nullptr) {
			Recursive_export_legitimate_teams_to_list(root->left, list, minId, maxId);
		}
	}
	if (root->key <= maxId && root->key >= minId) {
		list->add(root->key, root->value->get_overall_score());
	}
	if (root->key < maxId) {
		if (root->right != nullptr) {
			Recursive_export_legitimate_teams_to_list(root->right, list, minId, maxId);
		}
	}
}