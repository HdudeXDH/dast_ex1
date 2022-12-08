#include "worldcup23a1.h"

world_cup_t::world_cup_t(): top_scorrer(nullptr), players_count(EMPTY_NUM)
{
    legitimate_teams = AVLTree<int, Team*>();
    players_by_level = AVLTree<PlayerLevel, Player*>();
    teams = AVLTree<int , Team>();//AVLTree<Team_id , Team*>();
    players_by_id = AVLTree<int, Player>();//AVLTree<Player_id, Player*>();
}

world_cup_t::~world_cup_t()
{
//	delete players_by_level;
//    delete legitimate_teams;
//    delete teams;
//    delete players_by_id;
    // todo: maybe default
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
	if (teamId <= 0 || points < 0) {
		return StatusType::INVALID_INPUT;
	}
	Node<Team_id, Team> *search_result = teams.search(teamId, true);
	if(search_result != nullptr) {
		if (search_result->value.id ==teamId) return StatusType::FAILURE;
	}
	try {
//		Team* new_team = new
		teams.add(teamId, Team(teamId, points));
	}
	catch (AVLTree<Team_id, Team>::NodeAlreadyExists& err) {
		return StatusType::FAILURE;
	}
	catch (std::bad_alloc& err){
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	if (teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	Node<int, Team>* search_result = teams.search(teamId); //Node<Team_id, Team>* //AVLTree<Team_id, Team>::search(teamId);
	// todo check what is returned if key doesnt exist
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
        legitimate_teams.remove_by_key(teamId);

//		delete team_to_remove;
	}
	// todo check what is the spesific type of the deletion exeption
	catch (std::exception& err){
		return StatusType::ALLOCATION_ERROR; //ERROR_ALLOCATION;
	}
    return StatusType::SUCCESS;
}

void world_cup_t::renew_player_nextup_nextdown(Node<PlayerLevel, Player*> * new_player_by_level){
    Node<PlayerLevel, Player*> *nextup = players_by_level.find_next_up(new_player_by_level);
//        printBT(players_by_id.root);
    Player* nextdown;
    //todo: weird prints======= delete me
//    if (nextup!=nullptr) std::cout <<new_player_by_level->value->id<<"("<<new_player_by_level->value->goals<<"), nextup:"<<nextup->value->id<<", goals:"<<nextup->value->goals<<std::endl;
//    else{ std::cout <<new_player_by_level->value->id<<" - Big("<<new_player_by_level->value->goals<<")"<<std::endl;}
//    if (top_scorrer!=nullptr) {std::cout <<"oldBig["<<top_scorrer->id<<"]"<<top_scorrer->goals<<std::endl;}
//    if (playerId==187){
//        Node <PlayerLevel, Player*> ** testArr =players_by_level.export_to_array();
//        for (int i=0; i<players_by_level.size;i++){
//            std::cout<<testArr[i]->value->id<<"("<<testArr[i]->value->goals<<","<<testArr[i]->value->cards<<")"<<std::endl;
//        }
////            res=  players_by_id.search(75);
//
//    }


    if (nextup== nullptr){
        nextdown = top_scorrer;
        top_scorrer=new_player_by_level->value;
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
	Node<Team_id, Team> *team_search_result = teams.search(teamId);
    Node<int, Player> *player_search_result = players_by_id.search(playerId); //Node<Player_id, Player>
	if(team_search_result == nullptr || player_search_result != nullptr ) {
		return StatusType::FAILURE;
	}
	Team *team_to_add_player = &team_search_result->value;
	try {
		// after discussion - use regular ptrs here
//		Player* new_player = new Player(playerId,team_search_result, gamesPlayed, goals, cards, goalKeeper);
        Node<int, Player> *new_player = players_by_id.add(playerId, Player(playerId,&team_search_result->value, gamesPlayed, goals, cards, goalKeeper));
        Node<PlayerLevel, Player*> *new_player_by_level = players_by_level.add(*new_player->value.level, &new_player->value);
        renew_player_nextup_nextdown(new_player_by_level);
        //        Node<PlayerLevel, Player*> *nextup = players_by_level.find_next_up(new_player_by_level);
////        printBT(players_by_id.root);
//        Player* nextdown;
//        //todo: weird prints======= delete me
//        if (nextup!=nullptr) std::cout <<new_player_by_level->value->id<<"("<<new_player_by_level->value->goals<<"), nextup:"<<nextup->value->id<<", goals:"<<nextup->value->goals<<std::endl;
//        else{ std::cout <<new_player_by_level->value->id<<" - Big("<<new_player_by_level->value->goals<<")"<<std::endl;}
//        if (top_scorrer!=nullptr) {std::cout <<"oldBig["<<top_scorrer->id<<"]"<<top_scorrer->goals<<std::endl;}
//        if (playerId==187){
//            Node <PlayerLevel, Player*> ** testArr =players_by_level.export_to_array();
//            for (int i=0; i<players_by_level.size;i++){
//                std::cout<<testArr[i]->value->id<<"("<<testArr[i]->value->goals<<","<<testArr[i]->value->cards<<")"<<std::endl;
//            }
////            res=  players_by_id.search(75);
//
//        }
//
//
//        if (nextup== nullptr){
//            nextdown = top_scorrer;
//            top_scorrer=new_player_by_level->value;
//        } else {
//            nextdown = nextup->value->next_down;
//            new_player_by_level->value->next_down=nextdown;
//            nextup->value->next_down=new_player_by_level->value;
//            new_player_by_level->value->next_up=nextup->value;
//        }
//        if (nextdown != nullptr){
//            nextdown->next_up=new_player_by_level->value;
//        }
         // nextdown.nextup=current
         // current.nextdown=nextdown
        //nextup.nextdown = current
        //current.nextup=nextup


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
//    team_to_add_player->validate_sizes();
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if (playerId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	Node<Player_id, Player> *player_node_in_id_tree = players_by_id.search(playerId);
	if (player_node_in_id_tree == nullptr) {
		return StatusType::FAILURE;
	}
	Player *player_to_remove = &player_node_in_id_tree->value;
	Team *players_team = player_to_remove->team;
	PlayerLevel  level = *player_to_remove->level;
	Node<PlayerLevel, Player*> *player_node_in_level_tree = players_by_level.search(level);
	try {
		// remove player from all AVL trees
		bool was_team_legitimate_before_removing = players_team->is_legitimate_for_match();
		if (player_to_remove->next_down != nullptr) {player_to_remove->next_down->next_up = player_to_remove->next_up;}
		if (player_to_remove->next_up != nullptr) {player_to_remove->next_up->next_down = player_to_remove->next_down;}
		players_by_level.remove_by_key(player_node_in_level_tree->key);
        players_team->remove_player_from_team(player_to_remove);
        players_by_id.remove_by_key(player_node_in_id_tree->key);
        players_count = players_count - 1;
		if (was_team_legitimate_before_removing && !players_team->is_legitimate_for_match()) {
			legitimate_teams.remove_by_key(players_team->id);
		}
		//delete player
//		delete player_to_remove;
		top_scorrer = players_by_level.max_node()->value;
	} catch (std::exception& err) {
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	Node<int, Player> * player75 = players_by_id.search(75);
	if (playerId <= 0 || gamesPlayed <= 0 || scoredGoals <= 0 || cardsReceived <=0) {
		return StatusType::INVALID_INPUT;
	}
	Node<Player_id, Player> *player_node_in_id_tree = players_by_id.search(playerId);
    if (player_node_in_id_tree == nullptr) {
        return StatusType::FAILURE;
    }
    Player * player = &(player_node_in_id_tree->value);
    //update next_up & next down
    if (player->next_down != nullptr) {player->next_down->next_up = player->next_up;}
    if (player->next_up != nullptr) {player->next_up->next_down = player->next_down;}

    Team * team = player->team;
//    int teamId = team->id;
//    bool isGoalKeeper = player_node_in_id_tree->value.is_goal_keeper;
//    int newgameplayed = (player->games_played + gamesPlayed);
//    int newgoals = (player->goals + scoredGoals);
//	int newcards = (player->cards + cardsReceived);
//    remove_player(playerId);
//    add_player(playerId,teamId,newgameplayed,newgoals,newcards,isGoalKeeper);
	// remove (in order to add)
	team->remove_player_from_team(player);
    try {
        players_by_level.remove_by_key(*player->level);
    } catch (std::exception& err) {
        return StatusType::ALLOCATION_ERROR;
    }
	player->games_played = (player->games_played + gamesPlayed);
	player->goals = (player->goals + scoredGoals);
	player->cards = (player->cards + cardsReceived);
	player->update_level();
	try {
        Node<PlayerLevel, Player*> *new_player_by_level =players_by_level.add(*player->level, player);
        renew_player_nextup_nextdown(new_player_by_level);
		team->add_player_to_team(player);
	} catch (std::exception& err) {
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	if (teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0) {
		return StatusType::INVALID_INPUT;
	}
    Node<int,Team> * team1_node =  teams.search(teamId1);
    Node<int,Team> * team2_node =  teams.search(teamId2);

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
	Node <int, Player> * player_node = players_by_id.search(playerId);
	if (player_node == nullptr) {
		return output_t<int>(StatusType::FAILURE);
	}
	int num_of_games = player_node->value.get_total_games_played();
	// todo check syntax correctness
	return output_t<int>(num_of_games);
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if (teamId <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
    Node <int, Team> * team_node = teams.search(teamId);

	if (team_node == nullptr) {
		return output_t<int>(StatusType::FAILURE);
	}
	return output_t<int>(team_node->value.points);
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// team search and validation
    if (teamId1==teamId2) return StatusType::INVALID_INPUT;
    Node <int, Team> * team1_node = teams.search(teamId1);
    Node <int, Team> * team2_node = teams.search(teamId2);
    if (team1_node == nullptr || team2_node == nullptr) {
		return StatusType::FAILURE;
	}
	Node <int, Team> * newteam_node = teams.search(newTeamId);
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

    //todo: update all players
    Node<PlayerLevel, Player*>** team1_array = team1->players.export_to_array();
	Node<int, Player> * player75 = players_by_id.search(75);
    for (int i=0;i<team1->players_count;i++){
		team1_array[i]->value->team = newteam;
        team1_array[i]->value->games_played+=team1->games_played-team1_array[i]->value->teams_matches_pre_arrival_count;
    }
    Node<PlayerLevel, Player*>** team2_array = team2->players.export_to_array();
    for (int i=0;i<team2->players_count;i++){
		team2_array[i]->value->team = newteam;
        team2_array[i]->value->games_played+=team2->games_played-team2_array[i]->value->teams_matches_pre_arrival_count;
    }
    //merging the trees
    newteam->players.merge_trees(team2->players,team2->players);
    newteam->players_by_id.merge_trees(team2->players_by_id,team2->players_by_id);
    newteam->players_count = team1->players_count + team2->players_count;
    newteam->goal_keepers_count = team1->goal_keepers_count + team2->goal_keepers_count;
    newteam->power = team1->power + team2->power;
    newteam->points= team1->points+team2->points;
//    bool was_team_legitimate_before_adding = team_to_add_player->is_legitimate_for_match();
//    team_to_add_player->add_player_to_team(&new_player->value);
//    if (team_to_add_player->is_legitimate_for_match() && !was_team_legitimate_before_adding) {
//        legitimate_teams.add(teamId, team_to_add_player);
//    }
    //return alon
    if (newteam->is_legitimate_for_match()) legitimate_teams.add(newTeamId, newteam);

    if (*team1->top_scorrer->level>*team2->top_scorrer->level) {newteam->top_scorrer= team1->top_scorrer;}
    else {newteam->top_scorrer= team2->top_scorrer;}
    if (teamId1!=newTeamId){
        teams.remove_by_key(teamId1);
    }
    if (teamId2!=newTeamId){
        teams.remove_by_key(teamId2);
    }
//    newteam->validate_sizes();
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	if (teamId == 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	if (teamId > 0 ) {
        Node <int, Team> * team_node = teams.search(teamId);
//		Team* team = teams.search(teamId);
		if (team_node == nullptr) {
			return output_t<int>(StatusType::FAILURE);
		}
//        Node<PlayerLevel, Player*> * m = team_node->value.players.max_node(); //todo: delete!! for testing only!
		return team_node->value.top_scorrer->id;
	} else {
		return top_scorrer->id;
	}
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if (teamId == 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	if (teamId > 0 ) {
        Node <int, Team> * team_node = teams.search(teamId);
//		Team* team = teams.search(teamId);
		if (team_node == nullptr) {
			return output_t<int>(StatusType::FAILURE);
		}
		return output_t<int>(team_node->value.players_count);
	} else {
		return output_t<int>(players_count);
	}
	// TODO: Your code goes here ?????
//    static int i = 0;
//    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	//todo: negative values?
    if (teamId == 0 || output == nullptr) {
		return StatusType::INVALID_INPUT;
	}
	if (teamId > 0 ) {
        Node <int, Team> * team_node = teams.search(teamId);

        if (team_node == nullptr) {
            return StatusType::FAILURE;
        }
        Team & team = team_node->value;
        //todo: validate corrent complexity
        Node<PlayerLevel, Player*>** block_array =team.players.export_to_array();
		for (int i=0; i< team.players_count;i++){
            output[i] =  block_array[i]->value->id;
        }
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: what if invalid/doesnt Exist teamID/playerId?
    Node <int, Team> * team_node = teams.search(teamId);
    if (team_node== nullptr){
        return StatusType::FAILURE;
    }
    Node <int, Player*> * player_node = team_node->value.players_by_id.search(playerId);
    if (player_node== nullptr){
        return StatusType::FAILURE;
    }
//    Node <int, Player> * res;
//    if (playerId==187){
//        Node <PlayerLevel, Player*> ** testArr =players_by_level.export_to_array();
//        for (int i=0; i<players_by_level.size;i++){
//            std::cout<<testArr[i]->value->id<<"("<<testArr[i]->value->goals<<","<<testArr[i]->value->cards<<")"<<std::endl;
//        }
//        res=  players_by_id.search(75);
//
//    }

//    Node <PlayerLevel, Player*> * res2 = players_by_level.find_next_up(players_by_level.search(*player_node->value->level));



	return player_node->value->getCloset()->id;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	if (minTeamId < 0 || maxTeamId < 0 || minTeamId > maxTeamId) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	LinkedList<int, int> *playing_teams;
//    int ix=0; // bad example minTeamId = 3, max = 19
//    Node<int, Team> * deleteme[teams.size];
//    teams.Recursive_export_to_array(teams.root, deleteme,&ix);
//    int ix2=0;
//    Node<int, Team*> * deleteme2[legitimate_teams.size];
//    legitimate_teams.Recursive_export_to_array(legitimate_teams.root, deleteme2,&ix2);
    playing_teams = export_lagitimate_teams_to_list(minTeamId, maxTeamId);
	if (playing_teams->size <= 0) {
		return output_t<int>(StatusType::FAILURE);
	}
	LinkedList_Node<int, int> * first_team = playing_teams->head->next, *second_team;
    LinkedList_Node<int, int> *next_pair;
	int new_value;
	while(playing_teams->size > 1) {
		while (first_team!=nullptr && first_team->next != nullptr){
            second_team = first_team->next;
			new_value = first_team->value + second_team->value + POINTS_TO_ADD;
            next_pair = second_team->next;
//            if (minTeamId==3&&maxTeamId==19){
//                std::cout<<"[<"<<first_team->key<<","<<first_team->value<<">,<"<<second_team->key<<","<<second_team->value<<">]";
//            }
			if(first_team->value < second_team->value || (first_team->value == second_team->value && first_team->key < second_team->key)) {
                second_team->value = new_value;
                playing_teams->remove_node(first_team);
//                if (minTeamId==3&&maxTeamId==19){
//                    std::cout<<"("<<second_team->key<<","<<second_team->value<<")";
//                }

			} else {
                first_team->value = new_value;
                playing_teams->remove_node(second_team);
//                std::cout<<"("<<first_team->key<<","<<first_team->value<<")";
            }
            first_team = next_pair;

		}
//        if (minTeamId==3&&maxTeamId==19){
//            std::cout<<"  | end round!---------"<<std::endl;
//        }
		first_team = playing_teams->head->next;
	}
	assert(playing_teams->size == 1);
	return output_t<int>(playing_teams->head->next->key);
    // if num players < num teams, get player list, and
    //todo: create "valid" teams
    //teams.Recursive_export_to_array()
    return 0;
}

///// -------------------- private methods ---------------------

LinkedList<int, int>* world_cup_t::export_lagitimate_teams_to_list(int minTeamId, int maxTeamId) {
	LinkedList<int, int>* playing_teams = new LinkedList<int, int>();
    int ix2=0;
    Node<int, Team*> * raw_array[legitimate_teams.size];
    legitimate_teams.Recursive_export_to_array(legitimate_teams.root, raw_array,&ix2);
    for (int i=0;i<ix2;i++){
        if ((raw_array[i]->key <=maxTeamId)&&(raw_array[i]->key >=minTeamId)){
            playing_teams->add(raw_array[i]->key, raw_array[i]->value->get_overall_score());
        }

    }
//	recursive_export_to_list(minTeamId, maxTeamId, legitimate_teams.root, playing_teams);
	return playing_teams;
}

void world_cup_t::recursive_export_to_list(int minTeamId, int maxTeamId, Node<int, Team*>* start, LinkedList<int, int>* list) {
	int key = start->key;
	if ( key < minTeamId ) {
		if (start->right == nullptr) {
			return ;
		}
		recursive_export_to_list(minTeamId, maxTeamId, start->right, list);
	}
	if (key >= minTeamId && key <= maxTeamId) {
		int score = start->value->get_overall_score();
		list->add(key, score);
	}
	if (key  > maxTeamId) {
		if (start->left == nullptr) {
			return ;
		}
		recursive_export_to_list(minTeamId, maxTeamId, start->left, list);
	}
}