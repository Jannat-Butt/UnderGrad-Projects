
#include<iostream>
#include"list.h"
#include <iomanip>
using namespace std;
//#include<fstream>
//#include<string>
//#include<sstream>
//#include"i210323_i210259.h"

#define NIL -1
//golbal array for storing all SCC 
int SCC_Dis[5000][1] = { 0 };


//...............................................Node Class.........................................................
class Node
{

	int data = 0;
	Node* next;
public:
	Node(int value)
	{
		this->data = value;
		next = NULL;
	}
	Node()
	{
		data = 0;
		next = NULL;
	}
	void set_data(int v)
	{
		data = v;
	}
	void set_next(Node* next_ptr)
	{
		next = next_ptr;
	}
	int get_data()
	{
		return data;
	}
	Node* get_next()
	{
		return next;
	}

};
//................................................Adjency List.......................................................
class AdjList
{
public:
	Node* head;
	AdjList()
	{
		head = NULL;
	}
	//................................................Insertion........................................................
	void insertAtEnd(int value) {
		if (head == NULL)
		{
			Node* n_node = new Node(value);
			head = n_node;
			return;
		}
		else
		{
			Node* temp = head;
			while (temp->get_next() != NULL)
			{
				temp = temp->get_next();
			}
			Node* n_node = new Node(value);
			temp->set_next(n_node);
			return;
		}
		return;
	}

};
//....................................................Graph Class...................................................
class Grapgh {
public:
	int vertices;
	AdjList* adj;
	bool* visited;
public:
	Grapgh(int max)
	{
		this->vertices = max;
		adj = new AdjList[max];

	}
	//...................................................Insert Edges................................................_
	void addEdge(int src, int dest)
	{
		adj[src].insertAtEnd(dest);
	}

	//.................................................Breath FirsT Search.............................................
	void BFS(int start)
	{
		visited = new bool[vertices];
		for (int i = 0; i < vertices; i++)
		{
			visited[i] = false;
		}
		List queue;
		visited[start] = true;
		queue.push_back(start);
		while (!queue.empty()) {
			int currVertex = queue.front();
			cout << currVertex << " ";
			queue.pop_front();
			Node* temp = adj[currVertex].head;
			while (temp)
			{
				int adjVertex = temp->get_data();

				if (visited[adjVertex] == 0)
				{
					visited[adjVertex] = 1;
					queue.push_back(adjVertex);
				}
				temp = temp->get_next();
			}


		}
	}
	//..........................................................DFS................................................
	void DFS(int start)
	{
		//Visted Node array
		visited = new bool[vertices];
		for (int i = 0; i < vertices; i++)
		{
			visited[i] = false;
		}
		//stack object
		List Stack;

		visited[start] = true;
		Stack.push_front(start);
		while (!Stack.empty())
		{
			int currVertex = Stack.front();
			cout << currVertex << " ";
			Stack.pop_front();
			Node* temp = adj[currVertex].head;
			while (temp)
			{
				int adjVertex = temp->get_data();

				if (visited[adjVertex] == 0)
				{
					visited[adjVertex] = 1;
					Stack.push_front(adjVertex);
				}
				temp = temp->get_next();
			}


		}
	}
	//..................................................................CountingBridges..................................................

	void CountingBridges(int u, bool array_discovered[], int discovery_time[], int low_time_array[], int nodes_parent[], int& count)

	{
		static int time = 0;
		array_discovered[u] = true;
		//discovery time 
		//low time
		//parent array keeping parent nodes 
		discovery_time[u] = low_time_array[u] = ++time;
		//using DFS algorithm 
		List Stack;
		Stack.push_front(u);
		while (!Stack.empty())
		{

			int v = Stack.front();
			Stack.pop_front();
			//this temp Node will store the head of the corresponding adjancy list
			Node* temp = adj[v].head;

			//this while loop will traverse till the end of the linked nodes corresponding to adjancy list
			while (temp)//
			{
				int adjVertex = temp->get_data();
				//checking if node is visited
				if (!array_discovered[adjVertex])
				{

					nodes_parent[adjVertex] = u;
					//recursive call to the same function
					//to reach the depth of the tree
					CountingBridges(adjVertex, array_discovered, discovery_time, low_time_array, nodes_parent, count);
					low_time_array[u] = min(low_time_array[u], low_time_array[adjVertex]);

					if (low_time_array[adjVertex] > discovery_time[u])
					{
						//getting the count of bridges
						count++;

					}
				}
				else if (adjVertex != nodes_parent[u])
				{
					low_time_array[u] = min(low_time_array[u], discovery_time[adjVertex]);
				}
				// moving the temp node forward to the next node til the end of the linkage
				temp = temp->get_next();
			}


		}
	}
	//.........................................function that returns the count of all bridges in a graph........................................
	void All_Count_bridge()
	{

		int count = 0;
		bool* visitedd = new bool[vertices];
		int* array_discovered = new int[vertices];
		int* low_time_array = new int[vertices];
		int* nodes_parent = new int[vertices];

		//initializing the arrays

		for (int i = 0; i < vertices; i++)
		{
			nodes_parent[i] = NIL;
			visitedd[i] = false;
		}
		for (int i = 0; i < vertices; i++)
		{
			//function calling for n number of vertices 
			//check condition if the vertice is not visited in the first place
			if (visitedd[i] == false)
			{
				CountingBridges(i, visitedd, array_discovered, low_time_array, nodes_parent, count);
			}
		}
		cout << count << endl;
	}
	//visited array stores nodes that are visited
	//nodes_parent are parent node
	void ArticulatedPoints(int u, bool nodes_visited[], int discovery_time[], int low[], int& time, int  nodes_parent, bool isAP[])
	{
		int children = 0;
		nodes_visited[u] = true;
		discovery_time[u] = low[u] = ++time;
		//using DFS algorithm 
		List Stack;
		Stack.push_front(u);
		while (!Stack.empty())
		{
			int v = Stack.front();
			Stack.pop_front();
			//this temp Node will store the head of the corresponding adjancy list
			Node* temp = adj[v].head;
			while (temp)//this while loop will traverse till the end of the linked nodes corresponding to adjancy list
			{
				int adjVertex = temp->get_data();
				//checking if node is visited
				if (!nodes_visited[adjVertex])
				{

					children++;
					//recursive call to the same function
					//to reach the depth of the tree
					ArticulatedPoints(adjVertex, nodes_visited, discovery_time, low, time, u, isAP);
					low[u] = min(low[u], low[adjVertex]);

					if (nodes_parent != -1 && low[adjVertex] >= discovery_time[u])
					{
						//marking the node as articulated node
						isAP[u] = true;
					}
				}
				else if (adjVertex != nodes_parent)
				{
					low[u] = min(low[u], discovery_time[adjVertex]);
				}
				// moving the temp node forward to the next node till the end of the linkage
				temp = temp->get_next();
			}


		}
		if (nodes_parent == -1 && children > 1)
		{
			isAP[u] = true;
		}
	}

	void count_ArticulatedPoints()

	{
		int count = 0;
		int* array_discovered = new int[vertices];
		int* low_time_array = new int[vertices];
		bool* visited = new bool[vertices];
		bool* isAP = new bool[vertices];
		int time = 0, par = -1;
		//initializing the array
		for (int i = 0; i < vertices; i++)
		{

			visited[i] = false;
		}
		for (int u = 0; u < vertices; u++)
		{
			//function calling for n number of vertices 

			if (!visited[u])////check condition if the vertice is not visited in the first place
			{

				ArticulatedPoints(u, visited, array_discovered, low_time_array, time, par, isAP);
			}
		}

		for (int u = 0; u < vertices; u++)
		{
			//check condition to get the count of articulated nodes
			if (isAP[u] == true)
			{
				count++;
			}
		}
		cout << count << endl;
	}



	int SCC_Counting(int s, bool visitedV[], int& count)
	{
		int tempCount = 0;
		visitedV[s] = true;
		count++;
		//DFS approch
		List Stack;
		Stack.push_front(s);
		//this loop iterate for all vertices of the graph
		while (!Stack.empty())
		{

			int v = Stack.front();
			Stack.pop_front();
			//this temp Node will store the head of the corresponding adjancy list
			Node* temp = adj[v].head;
			// this while loop will traverse till the end of the linked nodes corresponding to adjancy list
			while (temp)
			{
				int adjVertex = temp->get_data();
				//checking if node is visited
				if (!visitedV[adjVertex])
				{
					//recursive call
					SCC_Counting(adjVertex, visitedV, count);
				}
				// moving the temp node forward to the next node till the end of the linkage
				temp = temp->get_next();
			}


		}
		tempCount = count;

		return tempCount;

	}
	// this function reverse the edges of the current graph and store it in a new graph
	Grapgh reverse_edges()
	{
		Grapgh g(vertices);
		for (int i = 0; i < vertices; i++)
		{
			List stack;
			stack.push_front(i);
			while (!stack.empty())//iteration for all vertices of the orignal graph
			{

				int v = stack.front();
				stack.pop_front();
				//this temp Node will store the head of the corresponding adjancy list
				Node* temp = adj[v].head;
				while (temp) // this while loop will traverse till the end of the linked nodes corresponding to adjancy list
				{
					//reversing the linkages
					int adjVertex = temp->get_data();
					g.adj[adjVertex].insertAtEnd(i);
					// moving the temp node forward to the next node till the end of the linkage
					temp = temp->get_next();
				}


			}


		}
		return g;
	}

	//this function maintain the stack of all strongly components of the graph
	void InOrderFill(int s, bool visitedV[], List& Stack)
	{
		visitedV[s] = true;
		List Stack_;
		Stack_.push_front(s);
		//iteration for all vertices of the orignal graph
		while (!Stack_.empty())
		{

			int v = Stack_.front();
			Stack_.pop_front();
			//this temp Node will store the head of the corresponding adjancy list
			Node* temp = adj[v].head;
			// this while loop will traverse till the end of the linked nodes corresponding to adjancy list
			while (temp)
			{

				int adjVertex = temp->get_data();
				//checking if node is visited
				if (!visitedV[adjVertex])
				{
					//recursive call
					InOrderFill(adjVertex, visitedV, Stack);
				}
				// moving the temp node forward to the next node till the end of the linkage
				temp = temp->get_next();
			}


		}

		Stack.push_front(s);
	}
	void Max_SCC_count()
	{
		int index = 0;
		List Stack;
		// using by reference to get the count of all strongly connected component
		int count = 0;
		int max = 0;
		int temp;
		bool* visitedV = new bool[vertices];
		for (int i = 0; i < vertices; i++)
			visitedV[i] = false;

		for (int i = 0; i < vertices; i++)
		{
			if (visitedV[i] == false)
			{
				InOrderFill(i, visitedV, Stack);
			}
		}

		Grapgh gr = reverse_edges();

		for (int i = 0; i < vertices; i++)
			visitedV[i] = false;

		while (Stack.empty() == false)
		{
			int s = Stack.front();
			Stack.pop_front();

			//checking if node is visited
			if (visitedV[s] == false)
			{
				//return the count of SCC of sub-graph
				temp = gr.SCC_Counting(s, visitedV, count);
				//maintaining a array for Distribution table
				SCC_Dis[index][0] = temp;
				index++;
				//reinitialize the count
				count = 0;
			}
			//check condition to extract max count of SCC
			if (temp > max)
			{
				max = temp;
			}

		}

		cout << max << endl;
	}
	// SCC distribution table function
	void SCC_Distribution_table()
	{
		int array[5000][2] = { 0 };
		int i = 0;
		int j = 0;
		cout << "SCCs" << setw(8) << "Size" << endl;
		while (SCC_Dis[i][0] != 0)
		{
			if (SCC_Dis[i][0] != -1)
			{
				int temp = SCC_Dis[i][0];
				array[j][1] = temp;
				int sccCount = 0;
				int k = 0;
				while (SCC_Dis[k][0] != 0)
				{
					if (SCC_Dis[k][0] == temp)
					{
						sccCount++;
						SCC_Dis[k][0] = -1;
					}
					k++;
				}
				array[j][0] = sccCount;
				j++;
			}
			i++;
		}
		int x = 0;

		//printing size distribution table of All SCCs
		while (array[x][0] != 0)
		{
			cout << array[x][0] << setw(8) << array[x][1] << endl;
			x++;
		}

	}

};