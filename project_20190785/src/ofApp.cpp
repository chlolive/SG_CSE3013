#include "ofApp.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {
	//Limit the speed of program to 60 frames per sec
	ofSetFrameRate(15);
	//Set the background as white
	ofBackground(255, 255, 255);
	ofSetLineWidth(4);

	//Initialize all flags
	count = 0;

	num_of_job = 0; //Number of jobs +1 = Number of max heap elements 
	num_of_heap = 0;
	num_of_can = 0; //Number of elements of candidate heap

	load_flag = 0; //Check if the input txt file is well opened
	draw_timeline_flag = 0; //Check whether to draw frame of timeline
	draw_scale_flag = 0;
	draw_candidate_flag = 0;
	draw_result_flag = 0; //Check whether to draw result of scheduling
	write_id_flag = 0;
	draw_target_flag = 0;
	//Set font
	font.loadFont("verdana.ttf", 12, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	int i=0, j=0;
	ofSetColor(204, 204, 255); //Light purple color
	ofDrawRectangle(0, 0, 1100, 30);
	ofDrawRectangle(0, 728, 1100, 40);

	char str[30];
	sprintf(str, "Comsil Project - 20190785");
	ofSetColor(0, 0, 0); //Black
	font.drawString(str, 10, 20);


	/****Draw shapes for timeline****/
	if (draw_timeline_flag) {
		//Set the line width as 4
		ofSetLineWidth(4);
		ofSetColor(102, 102, 102);

		//1. Draw horizontal line
		ofDrawLine(20, 700, 1020, 700);

		//2. Draw vertical line & write scale
		for (i = 0; i <= 1020; i += 50) {
			ofDrawLine(20 + i, 690, 20 + i, 710);
			sprintf(str, "%d", i / 50);
			ofDrawBitmapString(str, 15 + i, 720);

		}

	}

	/***Draw shapes for scale of timeline***/
	if (draw_scale_flag) {

		//Draw thin vertical line
		ofSetColor(204, 204, 204); //Light gray color
		ofSetLineWidth(2);
		for (i = 0; i <= 1020; i += 50) {
			ofDrawLine(20 + i, 40, 20 + i, 690);
		}

	}

	/***Draw candidates on the screen***/
	if (draw_candidate_flag) {
		char job_id[30];
		ofSetColor(0, 0, 0); //Black color

		for (i = 1; i <= num_of_job; i++) {
			ofDrawRectangle(20, 40 + (i - 1) * 31, (candidate[i].dead) * 50, 30);
			sprintf(job_id, "%c (%d)", candidate[i].id, candidate[i].profit);
			font.drawString(job_id, 25 + (candidate[i].dead) * 50, 60 + (i - 1) * 31);
		}
	}

	/***Draw shapes for result of scheduling***/
	if (draw_result_flag) {

		ofSetColor(255, 153, 204); //Light pink color

		for (i = 1; i <= 21; i++) {
			if (schedule[i] != '\0') { //If the slot of schedule is not empty
				//Indicate there is a job which is assigned through drawing rectangle
				ofDrawRectangle(25 + (i - 1) * 50, 660, 40, 30); 
			}
			for (j = 1; j <= num_of_can; j++) {
				if (candidate[j].id == schedule[i]) {
					ofDrawRectangle(20 + (i - 1) * 50, 40 + (j - 1) * 31, 50, 30);
				}
			}
		}
	}

	/***Draw shapes for target in the result of scheduling***/
	if (draw_target_flag) {

		ofSetColor(102, 255, 255); //Light blue color
		i = selected_job;
		ofDrawRectangle(25 + (i - 1) * 50, 660, 40, 30);

		for (j = 1; j <= num_of_can; j++) {
			if (candidate[j].id == schedule[i]) {
				ofDrawRectangle(20 + (i - 1) * 50, 40 + (j - 1) * 31, 50, 30);
			}
		}


	}

	/***Write each job ID which has been selected for scheduling***/
	if (write_id_flag) {
		char str1[10];
		char str2[10];
		int idx = 1;

		ofSetColor(0, 0, 0); //Black color
		for (i = 1; i <= 21; i++) {
			if (schedule[i] != '\0') { //If the slot of schedule is not empty
				//Write id of the job in that slot
				sprintf(str1, "%c", schedule[i]);
				font.drawString(str1, 40 + (i - 1) * 50, 680);
			}
			for (j = 1; j <= num_of_can; j++) {
				if (candidate[j].id == schedule[i]) {
					sprintf(str2, "%d", idx);
					font.drawString(str2, 40 + (i - 1) * 50, 60 + (j - 1) * 31);
					idx++;
				}
			}
		}
	}

	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 't') {
		if (!load_flag) return;
		draw_timeline_flag = 1;
		cout << "The timeline('t' key) is drawn." << endl;
	}

	if (key == 's') {
		if (!load_flag) return;
		draw_scale_flag = 1;
		cout << "The scale('s' key) is drawn." << endl;
	}

	if (key == 'c') {
		if (!load_flag) return;
		draw_candidate_flag = 1;
		cout << "The candidates('c' key) of jobs are drawn." << endl;
	}

	if (key == 'r') {
		if (!load_flag) return;
		draw_result_flag = 1;
		write_id_flag = 1;
		cout << "The result('r' key) of scheduling is drawn." << endl;
	}

	if (key == 'q') {
		if (!load_flag) return;

		//Reset the flags
		load_flag = 0;
		draw_timeline_flag = 0;
		draw_scale_flag = 0;
		draw_candidate_flag = 0;
		draw_result_flag = 0;
		num_of_job = 0;
		write_id_flag = 0;
		draw_target_flag = 0;

		//Free the dynamically allocated memory
		if (disjoint_set != NULL) {
			free(disjoint_set);
			disjoint_set = NULL;
		}
		cout << "Memory for disjoint_set has been freed." << endl;
		if (job_heap != NULL) {
			free(job_heap);
			job_heap = NULL;
		}
		cout << "Memory for job_heap has been freed." << endl;

		if (candidate != NULL) {
			free(candidate);
			candidate = NULL;
		}
		cout << "Memory for candidate has been freed." << endl;


		cout << "Quit('q' key) the program." << endl;
		_Exit(0);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'l') {
		// Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only .txt file.");

		// Check whether the user opened a file
		if (openFileResult.bSuccess) {
			ofLogVerbose("The input file is appropriately selected.");

			//We have a file, check it and process it
			openFile(openFileResult);
		}
	}

	if (key == OF_KEY_RIGHT) {
		selected_job++;
		if (selected_job == MAX(count + 1,21)) selected_job = 1;

		draw_target_flag = 1;
		write_id_flag = 1;
	}

	if (key == OF_KEY_LEFT) {
		selected_job--;
		if (selected_job < 1) selected_job = MAX(count, 20);

		draw_target_flag = 1;
		write_id_flag = 1;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::openFile(ofFileDialogResult openResult) {


	string filename = openResult.getName();
	ofFile file(filename);

	if (file.exists()) {
		cout << "There is a target file." << endl;
		load_flag = 1;
	}
	else cout << "There is no target file" << endl;

	ofBuffer buffer(file);



	//Read the target file line by line and store the information of job
	for (ofBuffer::Line begin = buffer.getLines().begin(), end = buffer.getLines().end(); begin != end; begin++) {
		string line = (*begin);

		//Split line into strings
		vector<string> words = ofSplitString(line, " ");

		//If the sentence consists of 1 word, recognize as total number of jobs
		if (words.size() == 1) {
			num_of_job = atoi(words[0].c_str());
			if (num_of_job > 20) {
				cout << "The numbers of job are out of range" << endl;
				return;
			}
			else {
				cout << "Total number of job is " << num_of_job << endl;

				
				job_heap = (Job*)malloc(sizeof(Job) * (num_of_job + 1));

			}
		}

		//If the sentence consists of 3 words, recognize as information of each job
		else if (words.size() == 3) {

			//Get the one line of input data
			Job input;
			input.id = words[0][0];
			input.dead = atoi(words[1].c_str());
			input.profit = atoi(words[2].c_str());

			//Handling error for limit of deadline of job
			if (input.dead > 20) {
				cout << "The deadline of Job '" << input.id << "' is out of range" << endl;
				return;
			}

			//The maximum of number of job is set to 20
			if (num_of_job > 20) {
				cout << "The numbers of job are out of range" << endl;
				break;
			}

			//Insert the input data into max heap
			/*********1st step: Sort the jobs in non-ascending order by profit*********/
			insert_maxheap(job_heap, input, &num_of_heap);

		}

		//If the sentence consists of neither 1 word nor 3 words, recognize as error of input file format
		else {
			cout << "The format of input file is wrong.\n" << endl;
			return;
		}
	} //End of get input from file

	candidate = (Job*)malloc(sizeof(Job) * (num_of_job + 1));
	num_of_can = num_of_heap;
	int i;
	for (i = 0; i <= num_of_job; i++) {
		candidate[i] = job_heap[i];
	}
	insertion_sort(candidate, 1, num_of_can);


	make_schedule();

}

Node* ofApp::initDisjoint(Node* disjoint_set, int n) {
	/***Purpose of the function: Initialize all elements of disjoint set***/

	disjoint_set = (Node*)malloc(sizeof(Node) * n);
	for (int i = 0; i < n; i++) {
		disjoint_set[i].parent = i;
		disjoint_set[i].rank = 0;
	}
	return disjoint_set;
}

int ofApp::Find(Node* disjoint_set, int i) {
	/***Purpose of the function: find the ancestor of i element***/

	//Repeat the while loop until it reach the node whose value is same with job num itself
	while (disjoint_set[i].parent != i) {
		i = disjoint_set[i].parent;
	}
	return i;
}

void ofApp::Union(Node* disjoint_set, int i, int j) {
	/***Purpose of the function: unite two sets who include i and j respectively***/


	//find the root node of i and j
	int i_root = Find(disjoint_set, i);
	int j_root = Find(disjoint_set, j);

	//Absorb the smaller rank of set into a tree whose root node value is greater or equal
	if (disjoint_set[i_root].rank < disjoint_set[j_root].rank) {
		disjoint_set[i_root].parent = j_root;
	}
	else if (disjoint_set[i_root].rank > disjoint_set[j_root].rank) {
		disjoint_set[j_root].parent = i_root;
	}
	else {
		if (i_root < j_root) {
			disjoint_set[j_root].parent = i_root;
			disjoint_set[i_root].rank++;
		}
		else {
			disjoint_set[i_root].parent = j_root;
			disjoint_set[j_root].rank++;
		}
	}
	return;
}


void ofApp::insert_maxheap(Job* job_heap, Job data, int* num_of_heap) {
	/***Purpose of the function: insert the data which we get from input txt file into max heap schedule***/
	//This is for sorting the profits of jobs in non-increasing order

	if ((*num_of_heap) == 20) {
		fprintf(stderr, "The max heap is full.\n");
		std::exit(1);
	}
	(*num_of_heap)++;

	int i = (*num_of_heap);
	while (1) {
		if (i == 1) break; //If number of elements is 1, there's nothing to compare
		//'i' keep going up while it find right place to insert the data
		if (data.profit <= job_heap[i / 2].profit) break; 
		job_heap[i] = job_heap[i / 2];
		i /= 2;
	}
	//Finally, i find right place and insert the data into the place
	job_heap[i] = data;
	return;
}


Job ofApp::delete_maxheap(Job* job_heap, int* num_of_heap) {
	/***Purpose of the function: delete the maximum element from max heap***/
	//It means that we select the job whose profit is the biggest in the schedule

	if ((*num_of_heap) == 0) {
		fprintf(stderr, "The heap is empty.\n");
		std::exit(1);
	}

	//Save first element in 'first'
	Job first = job_heap[1];

	//Save the last element in 'last'
	Job last = job_heap[(*num_of_heap)];
	(*num_of_heap)--;

	//Starting point of parent and child
	int parent = 1, child = 2;

	while (1) {
		if (child > (*num_of_heap)) break;

		//Check which one is bigger among left child and right child
		if (child <= (*num_of_heap) - 1) {
			if (job_heap[child + 1].profit > job_heap[child].profit) ++child;
		}

		//Find the place where 'last' should be inputed
		if (last.profit >= job_heap[child].profit) break;

		//Move the 'child' up to 'parent'
		job_heap[parent] = job_heap[child];

		//Move to down in the heap
		parent = child;
		child = child * 2;
	}

	//Input the 'last' into the place where we had found in previous process
	job_heap[parent] = last;

	//Return the element what we have removed from the heap
	return first;
}

void ofApp::make_schedule() {
	Job data;
	int root;
	disjoint_set = initDisjoint(disjoint_set, 21);

	while (num_of_heap > 0) {

		//Get the job which has biggest profit
		data = delete_maxheap(job_heap, &num_of_heap);

		Union(disjoint_set, data.dead, data.dead - 1);
		root = disjoint_set[data.dead].parent;
		for (int x = data.dead; x > 0; x--) {
			if (disjoint_set[x].parent != root) break;
			if (!schedule[x]) {
				schedule[x] = data.id;
				count++;
				break;
			}
		}

	}
}

int ofApp::insertion_sort(Job* data, int left, int right) {
	if (left < 0 || right < 0 || left > right || data == NULL) {
		return -1;
	} //return error code when execution is not available

	int i, j;
	Job temp;
	int size = right - left + 1; //size of data
	for (i = 1; i <= size; i++) {
		temp = data[i]; //Store information of the object into 'tmp'
		j = i; //Set the last point of comparison
		//Keep comparison until it becomes smaller than other
		while ((temp.profit > data[j - 1].profit) && (j > 1)) {
			data[j] = data[j - 1];
			j--;
		}
		data[j] = temp;
	}
	return 0;
}