
//################################################ Jannat Butt 21I-0259     MOAWIZ BIN YAMIN 21I-0323############################################

#include<iostream>
#include"i210323_i210259.h"
#include"artic_brid_funs.h"
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;


//CA-AstroPh.txt

//......................................................Reading File and Making Graph............................................................
buildGraph read_file()
{
	string remove;
	ifstream fileObj("CA-AstroPh.txt");
	buildGraph graphObj(0);
	int read = 0;

	if (fileObj.is_open())
	{
		cout <<setw(57) <<"file successfully read" << endl;
		int index = 0;
		while (index < 3)
		{
			getline(fileObj, remove);
			index++;
		}

		stringstream change_ss;
		change_ss << remove;
		string temp;
		int number;
		int *nodes_edge=new int[2];
		index = 0;

		while (!change_ss.eof()) {
			change_ss >> temp;
			if (stringstream(temp) >> number)
			{
				nodes_edge[index] = number;
				index++;
			}
		}

		index = 0;

		int nodes = nodes_edge[index];
		int edges = nodes_edge[index + 1];

		graphObj.set_nodes(nodes);
		graphObj.set_edge(edges);

		int* from_to = new int[2];
		getline(fileObj, remove);
		graphObj.setVertices(nodes);

		while (fileObj >> read)
		{
			from_to[index] = read;
			index++;
			if (index == 2)
			{
				graphObj.insertEdge(from_to[0], from_to[1]);
				index = 0;
			}
		}

		//system("pause");
		fileObj.close();
	}
	else
	{
		cout << "Failed to open file";
	}
	return graphObj;
}
//.................................................................Menue...........................................................................
int main()
{
	Grapgh g1(5);
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 1);
	g1.addEdge(0, 3);
	g1.addEdge(3, 4);
	system("cls");
	system("cls");
	int choice;
	buildGraph graphObj = read_file();
	/*cout << "Making Adjency Matrix:" << endl;
	int** adjency_matrix = graphObj.make_matrix();
	cout << "Executing Floyd Warshall:" << endl;
	graphObj.floydWarshall(adjency_matrix);
	cout << "Executed Floyd:" << endl;*/
	while (1)
	{
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(60) << "                                 Welcome      To       Graphs     World                     " << endl << endl;
		
		cout << setw(60) << "                                         Choose From Following                               " << endl;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		system("Color C");
 	    cout<<"***********************************************************************************************************"<<endl;
	   cout <<"*"<< "                  "  <<"1. for getting Number of Nodes:"<<endl;
	   cout <<"*"<< "                  " << "2. for getting Number of Edges:"<<endl;
	   cout <<"*"<< "                  " << "3. for getting Number of Sink Nodes:" <<endl;
	   cout <<"*"<< "                  " << "4. for getting Number of Source Nodes:" <<endl;
	   cout <<"*"<< "                  " << "5. for getting Number of Isolated Nodes:"<<endl;
	   cout <<"*"<< "                  " << "6. for getting Out degree distribution:"<<endl;
	   cout <<"*"<< "                  " << "7. for getting In degree distribution:"<<endl;
       cout <<"*"<< "                  " << "8. for getting Shortest Path Length:"<<endl;
	   cout <<"*"<< "                  " << "9. for getting Diametre:" <<endl;
	   cout <<"*" <<"                  "<< "10.for number of articulation nodes:" << endl;
	   cout <<"*" <<"                  " << "11.for number of bridge edges:" << endl;
	   cout <<"*" <<"                  " << "12.for the size of the largest strongly connected component:" << endl;
	   cout <<"*" <<"                  " << "13.the size distribution of all SCCs:" << endl;
	   cout <<"*"<< "                  " << "0. for Exit:"<<endl;
	   cout << "*********************************************************************************************************" << endl;
		cin >> choice;
		cout << endl;
		if (choice == 0)
		{
			cout << "############################################   Thank You    ################################" << endl;
			system("pause");
			break;
		}
		else
		{
			switch (choice)
			{
			case 1:
			{
				
				cout << "No. of Nodes:" << graphObj.get_nodes() << endl<<endl;
				system("pause");
				system("cls");
				break;
			}
			case 2:
			{
				
				cout << "No. of Edges:" << graphObj.get_edge() << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 3:
			{
				
				cout << "No. of Sink Nodes:" << graphObj.sink_nodes() << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 4:
			{
				
				cout << "No. of Source Nodes:" << graphObj.source_nodes() << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 5:
			{
			
				graphObj.isolated_nodes();
				cout << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 6:
			{
			
				graphObj.out_degree();
				cout << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 7:
			{

				graphObj.in_degree();
				cout << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 8:
			{
				//graphObj.shortestDistrb(adjency_matrix)
				cout << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 9:
			{

				//graphObj.diametre(adjency_matrix);
				cout << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 10:
			{
				cout << "ARTICULATION POINTS:";
				g1.count_ArticulatedPoints();
				cout << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 11:
			{
				cout << "BRIDGES EDGES:";
				g1.All_Count_bridge();
				cout << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			case 12:
			{
				cout << "STRONGLY CONNECTED COMPONENT:";
				g1.Max_SCC_count();
				cout << endl << endl;
				system("pause");
				system("cls");
				break;

			}
			case 13:
			{
				cout << "STRONGLY CONNECTED COMPONENT (DISTRIBUTION):" << endl;
				g1.SCC_Distribution_table();
				cout << endl << endl;
				system("pause");
				system("cls");
				break;

			}

			default:
			{
				cout << "Invalid Option" << endl;
				system("cls");
				break;
			}
		}
	}
}

	//buildGraph graphObj(0);
	//graphObj.set_edge(6);
	//graphObj.setVertices(4);
	//graphObj.insertEdge(1,2);
	//graphObj.insertEdge(2,1);
	//graphObj.insertEdge(1,4);
	//graphObj.insertEdge(2,4);
	//graphObj.insertEdge(3,2);
	//graphObj.insertEdge(4,3);
	//   graphObj.out_degree();
	//graphObj.in_degree();
	//int **adjency_matrix=graphObj.make_matrix();
	//graphObj.floydWarshall(adjency_matrix);
	////graphObj.printShortest(adjency_matrix);
	//graphObj.shortestDistrb(adjency_matrix);
	////graphObj.diametre(adjency_matrix);
	return 0;
}