#pragma once

#include "ofMain.h"

#include <cstdlib>

#define MAX(x,y) ((x)>(y)? (x):(y))

/*Class Job is needed to store information of each job
which is the element of max heap*/
class Job {
public:
	char id; //ID of the job
	int dead; //Deadline of job
	int profit; //Profit of job
};

class Node {
public:
	int parent; //Slot number of parent node
	int rank; //Height of the node
};
class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


	//Open input file and store the information of jobs in array 'schedule'
	void openFile(ofFileDialogResult openResult);

	//The functions needed to disjoint set manipulation
	Node* initDisjoint(Node* disjoint_set, int n);
	int Find(Node* disjoint_set, int i);
	void Union(Node* disjoint_set, int i, int j);

	//The functions needed to sort the jobs in non-increasing order by profit
	void insert_maxheap(Job* job_heap, Job data, int* num_of_job);
	Job delete_maxheap(Job* job_heap, int* num_of_job);

	//The insertion sort function for sorting candidate array
	int insertion_sort(Job* data, int left, int right);

	//The function for assigning job into schedule slot
	void make_schedule();

	Node* disjoint_set;
	Job* job_heap; //Max heap which sort all jobs in non-increasing order by profit
	Job* candidate; //Array which sort jobs perfectly by insertion sort (to draw candidates on screen)

	char schedule[21]; //Store the result of job scheduling (each slot for assigned job ID)
	int count; //Count how many jobs are assigned into 'schedule'

	int num_of_job; //Total number of jobs 
	int num_of_heap; //NUmber of elements of job_heap
	int num_of_can; //Number of elements of candidate array

	/****'l' key operation****/
	int load_flag; //Check if the input txt file is well opened

	/****'t' key operation****/
	int draw_timeline_flag; //Check whether to draw frame of timeline

	/****'s' key operation****/
	int draw_scale_flag; //Check whether to draw scale 

	/****'c' key operation****/
	int draw_candidate_flag; //Check whether to draw candidates on screen

	/****'r' key operation****/
	int draw_result_flag; //Check whether to draw result of scheduling
	int write_id_flag; //Check whether to write ID of each job on the rectangle

	/****'<-' or '->' key operation****/
	int draw_target_flag; //Check whether to indicate the target of rectangle(job)
	int selected_job; //To indicate which job slots will be draw as light blue rectangle

	ofTrueTypeFont font;
};
