#include<iostream>
#include<fstream>
#include<iomanip>


using namespace std;
int i = 0;

//..............................................adjencyListNode.....................................................
class adjencyListNode
{
private:
	int values;
	adjencyListNode* next;
public:
	adjencyListNode();
	void set_value(int );
	int get_value();
	void set_next(adjencyListNode*);
	adjencyListNode* get_next();
};
adjencyListNode::adjencyListNode()
{
	values = -1;
	next = NULL;
}
void adjencyListNode::set_value(int v)
{
	this->values = v;
}
int adjencyListNode::get_value()
{
	return (values);
}
void adjencyListNode::set_next(adjencyListNode* node)
{
	next = node;
}
adjencyListNode* adjencyListNode::get_next()
{
	return next;
}
class adjencyList
{
private:
	adjencyListNode* head;
public:
	adjencyList();
	void set_head(adjencyListNode*);
	adjencyListNode* get_head();
};

adjencyList::adjencyList()
{
	head = NULL;
}
void  adjencyList::set_head(adjencyListNode* h)
{
	this->head = h;
}
adjencyListNode* adjencyList ::get_head()
{
	return (head);
}
//................................................class buildGraph.....................................................
class buildGraph
{
private:
	int vertices;
	adjencyList* arrayOfVert;
	int nodes_count;
	int edges;
	/*int min_node;
	int max_node;*/
public:
	buildGraph(int);
	void insertEdge(int, int);
	void displayGraph();
	void setVertices(int vert);
	int getVertices();
	void set_nodes(int);
	int get_nodes();
	int sink_nodes();
	void set_edge(int);
	int get_edge();
	int source_nodes();
	void articulation();
	void depth_first_art(int, int*, int*, int*, bool*);
	void isolated_nodes();
	void out_degree();
	void in_degree();
	int** make_matrix();
	void floydWarshall(int *array[]);
	void diametre(int **);
	void printShortest(int**);
	void shortestDistrb(int**);
};
buildGraph::buildGraph(int vert)
{
	vertices = vert;
	arrayOfVert = NULL;
	nodes_count = 0;
	edges = -1;
	/*min_node = -1;
	max_node = -1;*/
}

void buildGraph::set_nodes(int n)
{
	this->nodes_count = n;
}
int buildGraph::get_nodes()
{
	return nodes_count;
}
void buildGraph::set_edge(int edg)
{
	edges = edg;
}
int buildGraph::get_edge()
{
	return edges;
}
void buildGraph::setVertices(int vert)
{
	this->vertices = vert;
	arrayOfVert = new adjencyList[vertices];
	for (int index = this->vertices; index < vert; index++)
	{
		arrayOfVert[index].set_head(NULL);
	}
}
//...................................................insertEdge........................................................
void buildGraph::insertEdge(int fromNode, int toNode)
{
	
	bool flag1 = true;
	bool flag2 = true;
	if (i == 0)
	{
		adjencyListNode* new_Node1 = new adjencyListNode;
		new_Node1->set_value(fromNode);
		adjencyListNode* new_Node2 = new adjencyListNode;
		new_Node2->set_value(toNode);
		new_Node1->set_next(new_Node2);
		arrayOfVert[i].set_head(new_Node1);
		i++;
		 new_Node1 = new adjencyListNode;
		new_Node1->set_value(toNode);
		arrayOfVert[i].set_head(new_Node1);
		i++;
	}
	else
	{
		for (int index = 0; index < i; index++)
		{
			if (arrayOfVert[index].get_head()->get_value() == fromNode)
			{
				adjencyListNode* new_Node2 = new adjencyListNode;
				new_Node2->set_value(toNode);
				adjencyListNode* traverse_forw = arrayOfVert[index].get_head();
				adjencyListNode* prev_node = traverse_forw;
				while (traverse_forw != NULL)
				{
					prev_node = traverse_forw;
					traverse_forw=traverse_forw->get_next();
					flag1 = false;
				}
				prev_node->set_next(new_Node2);
				break;
			}

		}
		if (flag1 == true)
		{
			adjencyListNode* new_Node1 = new adjencyListNode;
			new_Node1->set_value(fromNode);
			adjencyListNode* new_Node2 = new adjencyListNode;
			new_Node2->set_value(toNode);
			new_Node1->set_next(new_Node2);
			arrayOfVert[i].set_head(new_Node1);
			i++;
		}
		for (int index = 0; index < i; index++)
		{
			if (arrayOfVert[index].get_head()->get_value() == toNode)
			{
				flag2 = false;
				break;
			}
		}
		if (flag2 == true)
		{
			adjencyListNode* new_Node1 = new adjencyListNode;
			new_Node1->set_value(toNode);
			arrayOfVert[i].set_head(new_Node1);
			i++;
		}
		
	}
}//...........................................................displayGraph............................................
void buildGraph::displayGraph()
{
	for (int index = 0; index < this->vertices; index++)
	{
		adjencyListNode* temp = this->arrayOfVert[index].get_head();
		if (temp)
		{
			cout << "Neighbours of " << temp->get_value() << " are:";
			temp = temp->get_next();
			while (temp)
			{

				cout << temp->get_value() << " ";
				temp = temp->get_next();

			}
			cout << endl;
		}
		else
		{
			break;
		}
	}
}
//..............................................................sink_nodes...........................................
int buildGraph:: sink_nodes()
{
	int sink = 0;
	for (int index = 0; index < this->vertices; index++)
	{
		adjencyListNode* temp = this->arrayOfVert[index].get_head();
		if (temp->get_next() == NULL)
		{
			sink++;
		}
	}
	return sink;
}

//...............................................source_nodes.......................................................
int buildGraph::source_nodes()
{
	int* store_neighbours = new int[edges];
	for (int i = 0; i < edges; i++)
	{
		store_neighbours[i] = NULL;
	}
	int neigh_index = 0;
	int source = 0;
	for (int index = 0; index < this->vertices; index++)
	{
		adjencyListNode* temp = this->arrayOfVert[index].get_head();
		temp = temp->get_next();
		while (temp)
		{
			*(store_neighbours+index) = temp->get_value();
			temp = temp->get_next();
			neigh_index++;
		}
		
	}
	for (int index = 0; index < vertices; index++)
	{
		int pick = this->arrayOfVert[index].get_head()->get_value();
		bool flag = true;
		for (int j = 0; j < neigh_index; j++)
		{
			if (pick == *(store_neighbours+j))
			{
				flag = false;
				break;
			}
		}
		if (flag == true)
		{
			source++;
		}
	}
	return source;
}
//...................................................isolated_nodes.................................................
void buildGraph::isolated_nodes()
{
	/*int index = 0;
	for (index= 1; index <= this->vertices; index++) 
	{
		if (index * (index - 1) / 2 >=this->edges)
		{
			break;
		}
	}
	cout<<"max. isolated Vertex :"<<(this->vertices-index);*/
	int isolated = 0;
	if (this->vertices <= this->edges*2)
	{
		// all veritces have aedge connected
		cout << "min. isolated vertices: " << "0";
	}
	else
	{
		isolated = 2 *this-> edges; //maximum non isolated vertices
		cout << "min. isolated vertices: " <<this-> vertices - isolated;
	}
}
//...................................................out_degree.........................................................
void buildGraph::out_degree()
{
	int* store_degrees = new int[vertices];
	for (int index = 0; index < this->vertices; index++)
	{
		int neigh = 0;
		adjencyListNode* temp = this->arrayOfVert[index].get_head();
		temp = temp->get_next();
		while (temp)
		{
			neigh++;
			temp = temp->get_next();
		}
		store_degrees[index] = neigh;
	}
	int* store_node_havingDegree = new int[vertices];
	for (int index = 0; index < this->vertices; index++)
	{
		int count_nodes_havingDegree = 0;
		for (int neigh_array = 0; neigh_array < this->vertices; neigh_array++)
		{
			if (index == store_degrees[neigh_array])
			{
				count_nodes_havingDegree++;
			}
		}
		store_node_havingDegree[index] = count_nodes_havingDegree;
	}

	cout << "----------------------------------------------------------------------------------------" << endl;
	cout <<setw(20)<<"No of Nodes: " << setw(30)<< "having degree" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	for (int index = 0; index < this->vertices; index++)
	{
		cout <<setw(17)<< store_node_havingDegree[index]<<setw(30) << index << endl;
		if (index ==800)
		{
			break;
		}
	}
}
//..............................................................in_degree...........................................
void buildGraph::in_degree()
{
	int* store_degrees = new int[vertices];
	for (int index = 0; index < vertices; index++)
	{
		adjencyListNode* temp = this->arrayOfVert[index].get_head();
		int node = temp->get_value();
		int in = 0;
		for (int j = 0; j < vertices; j++)
		{
			adjencyListNode* temp = this->arrayOfVert[j].get_head();
			temp = temp->get_next();
			while (temp)
			{
				if (node == temp->get_value())
				{
					in++;
					temp = temp->get_next();
				}
				else
				{ 
				temp = temp->get_next();
				}
			}
		}
		store_degrees[index] = in;
	}
		int* store_node_havingDegree = new int[vertices];
		for (int index = 0; index < this->vertices; index++)
		{
			int count_nodes_havingDegree = 0;
			for (int neigh_array = 0; neigh_array < this->vertices; neigh_array++)
			{
				if (index == store_degrees[neigh_array])
				{
					count_nodes_havingDegree++;
				}
			}
			store_node_havingDegree[index] = count_nodes_havingDegree;
		}
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << setw(20) << "No of Nodes: " << setw(30) << "having degree" << endl;
		cout << "-----------------------------------------------------------------------------------------" << endl;
		for (int index = 0; index < this->vertices; index++)
		{
			cout << setw(17) << store_node_havingDegree[index] << setw(30) << index << endl;
			if (index == 600)
			{
				break;
			}
		}
    
}
//...........................................................make_matrix..............................................
int ** buildGraph::make_matrix()
{
	int** adjency_Matrix = new int* [vertices+1];
	for (int index = 0; index < vertices+1; index++)
	{
		adjency_Matrix[index] = new int[vertices+1];
	}
	for (int i = 0; i < vertices+1; i++)
	{
		for (int j = 0; j < vertices+1; j++)
		{
			adjency_Matrix[i][j]=12345678;
		}
	}
	for (int ind = 0; ind < vertices; ind++)
	{
		adjencyListNode* temp = this->arrayOfVert[ind].get_head();
		int source = temp->get_value();
		temp = temp->get_next();
		while (temp)
		{
			int to_node = temp->get_value();
			for (int j = 0; j < vertices; j++)
			{
				adjencyListNode* temp2 = this->arrayOfVert[j].get_head();
				if (to_node == temp2->get_value())
				{
					adjency_Matrix[ind][j] = 1;
				}
			}
			if (source != temp->get_value())
			{
				adjency_Matrix[ind][ind] = 0;
			}
			temp = temp->get_next();
		}

	}

	//...............................................Displaying.........................................
	/*for (int i = 0; i < vertices+1; i++)
	{
		for (int j = 0; j < vertices+1; j++)
		{
			cout<<setw(6)<<adjency_Matrix[i][j]<<" ";
		}
		cout << endl;
	}*/
	return (adjency_Matrix);
}
//...............................................printShortest..............................................
void buildGraph::printShortest(int* dist[])
{
	cout << "The following matrix shows the shortest "
		"distances"
		" between every pair of vertices \n";
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if (dist[i][j] == 12345678)
				cout << "INF"
				<< " ";
			else
				cout << dist[i][j] << "   ";
		}
		cout << endl;
	}


}
//..................................................floydWarshall..............................................
void buildGraph::floydWarshall(int *Array[])
{

	for (int k = 0; k < vertices; k++)
	{
		for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				if (Array[i][k] + Array[k][j] < Array[i][j])
					Array[i][j] = Array[i][k] + Array[k][j];
			}
		}
	}

}
//..............................................shortestDistrb..................................................
void buildGraph::shortestDistrb(int** floydAdjency)
{
	int* store_shortestlength = new int[vertices];
	for (int outter = 0; outter<vertices; outter++)
	{
		int nodes_count = 0;
		for (int index = 0; index < vertices; index++)
		{
			for (int j = 0; j < vertices; j++)
			{
				if (floydAdjency[index][j] == outter)
				{
					nodes_count++;
				}
			}
		}
		store_shortestlength[outter] = nodes_count;
	}
	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << setw(20) << "No of Nodes: " << setw(30) << "having Shortest Path" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	for (int ind = 1; ind < vertices; ind++)
	{
		cout << setw(17) << store_shortestlength[ind] << setw(30) << ind << endl;
	}
}
//..................................................diametre...........................................................
void buildGraph::diametre(int **shortestArray)
{
	
	int max = shortestArray[0][0];
	for (int ind = 0; ind < vertices; ind++)
	{
		for (int jth = 0; jth < vertices; jth++)
		{
			if (max <( shortestArray[ind][jth]) && shortestArray[ind][jth]!=12345678)
			{
				max = shortestArray[ind][jth];
			}
		}
	}
	cout << "Diametre Of Graph is:" << max << endl;
}

