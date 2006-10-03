#ifndef ANIMAL_H
#define ANIMAL_H

#define NUM_NEEDS 7
#define pee 0
#define eat 1
#define sleep 2
#define play 3
#define clean 4
#define love 5
#define idle 6

class Animal:public Object
{
	public:
		Animal(float x, float y, float z);
		

		int pos[3];
		//int priorities[NUM_NEEDS]; //the priority levels of each need
		int min_levels[NUM_NEEDS]; // if the need is below this level, you become ill
		int good_levels[NUM_NEEDS];  //should stay around here
		int max_levels[NUM_NEEDS];  //if the need is above this level, you become ill
		int current_levels[NUM_NEEDS]; //sleep, food, pee, excercise/play, hugs, cleanliness/medicine, 
		int time_stamps[NUM_NEEDS]; //time the action was performed last
		int current_action;
		int update_level(int need, int level); //change the current need level of a specific need
		int update_state();
		int set_action();
		int currentAction;  //pee, eat, sleep, play, clean, 
		//int timeStep; //don't need

}

void Animal::Animal(float x, float y, float z){
//read in the config file to update  needs, priorities, etc.
	
	pos[0] = x; pos[1] = y; pos[2] = z;
	currentAction = IDLE;
}

int Animal::update_state(){


	//update all levels
	for (int i = 0; i< NUM_NEEDS; i++)
	{
		update_level(i, -1); //sub 1 from each level
	}

	if (current_action == IDLE){
		set_action();
	}
	//do the action, will update one or more of the levels
	do_action();

}

int Animal::update_level(int need, int delta)
{
	current_levels[need] += delta;
	//current_time - time_stamps[need]
}


int Animal::set_action()
{
	//current_needs should be ordered in terms of priorities
	for (int i = 0; i < NUM_NEEDS; i++){
		if (current_levels[i] < good_levels[i]) { current_action  = i; break;}
	}
}

int Animal::do_action()
{
	//if we're not at the correct location, go there

	update_level(current_action, 1);

	//if refueled
	if (current_levels[current_action] > good_levels[current_action])
	{
		current_action = IDLE;	
	}
	
}



#endif // ndef ANIMAL_H
