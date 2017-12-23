#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <math.h>

float a, b, radio = 1.0;

float time_vector[];
float time_ = 0.0;
float centros[];
float total_distance = 0.0;
float delimitator_radio[];

float w1= 0.5, w2 = 0.4,w3 = 0.1;

// after sensing having all beacons

typedef struct{
	float x, y;
}beacon;

typedef struct{
	float x,y;
} point;

typedef struct {
	point position;
	float angle;	
} position;

beacon beacon_list[];
//list all beacs in liked list

//set GA params

int size_list_beacs = 0;
point nearest_beacon;
float step = 0.1;
position robot_position;
position prev_robot_position;
int k;
float distance = 0.0;
float prev_distance = 0.0;

while(size_list_beacs > 0){
	
	//get the nearest beacon to the robot
	get_nearest_beacon(struct robot_posotion, point beacon_list[], &neasrest_beacon, &distance);
		
	//remove a beacon from list at the k position
	remove_beacon(&beacon_list, int k);
	
	while(distance < .3){
		
		//scaneia a área
		
		//designa os pontos obstáculos
		
		//get obstacles points and free points
		
		//rotate 360
		
		//call GA function
		
		prev_robot_position = robot_position;
		prev_distance = distance;
		
		move_robot(robot_position, nearest_beacon, step);
		
		// add currently point to the traveled points list
		
		// increment the total distance traveled
		
		//test if the distance between the robot and the target is bigger that previous step		
						
	}
	
}


int main(void){
    
}

float euclid_distance(point p1, point p2){
	return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
}

get_nearest_beacon(point robot_posotion.position, point beacon_vector[], point* nearest_beacon, float* distance){
	nearest_beacon->x = 0;
	nearest_beacon->y = 0;
	*distance = 0;
}

void remove_beacon(point* beacon_list, int k){
	
}

/************************************************************************/
/* Moves the robots to specific position with a pre defined step        */
/************************************************************************/
void move_robot(position* position_robot, point target, float step ){
	
	float distance = euclid_distance(position_robot->position, target);
	
	while(distance > step + .1){		
		// rest of the code here
		distance = euclid_distance(position_robot->position, target);		
	}
		
}
