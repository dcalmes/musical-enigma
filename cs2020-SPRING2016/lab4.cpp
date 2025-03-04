// Lab 4
// Description: Creating and manipulating linked lists.
// Programmer:	Douglas G Calmes
// Class:		CS 2020, Spring 2016


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//Structures
struct Node
{
	string	movieTitle;
	string	Director;
	string	movieRating;
	int		numberCopies;
	Node*	pNext;
};

//Prototypes
void CreateDVDLinkedList(Node* &); 
void ShowDVDInformation(Node*);
void DisplayDVDLibrary(Node*);
Node* FindDVDbyTitle(Node*, string);
void CheckOut(Node*);
void CheckIn(Node*);
void DeleteList(Node*);
int Menu();

int main()
{
	int	choice = 0;
	string findTitle;
	Node* pHead = nullptr;
	Node* pFind = nullptr;

	CreateDVDLinkedList(pHead);

	// Do-While look to continually allow the user to execute the menu commands until finished.
	// This loop is executed based on the number (1-4) that was chosen, while terminating if 5 was chosen.
	do
	{
		choice = Menu();

		if (choice == 1)
		{
			cout << "Title?" << endl;
			cin.ignore();
			getline(cin, findTitle);

			pFind = FindDVDbyTitle(pHead, findTitle);
			CheckOut(pFind);
		}
		if (choice == 2)
		{
			cout << "Title?" << endl;
			cin.ignore();
			getline(cin, findTitle);

			pFind = FindDVDbyTitle(pHead, findTitle);
			CheckIn(pFind);
		}
		if (choice == 3)
		{
			cout << "Title?" << endl;
			cin.ignore();
			getline(cin, findTitle);

			pFind = FindDVDbyTitle(pHead, findTitle);
			ShowDVDInformation(pFind);

		}
		if (choice == 4)
		{
			DisplayDVDLibrary(pHead);

		}
		if (choice == 5)
		{
			DeleteList(pHead);
		}
	} while (choice == 1 || choice == 2 || choice == 3 || choice == 4);



	system("Pause");
	return 0;
}

// Function:	CreateDVDLinkedList
// Description: The purpose of this function is to read in the data file and create
//				the linked list of DVD nodes
// Programmer:	Douglas G Calmes
// Class:		CS 2020, Spring 2016
// Parameters:	pHead	- Pointer to head of linked list.
// Returns:		This function is void.

void CreateDVDLinkedList(Node* & pHead)
{
	ifstream infile;

	infile.open("lab4.txt");

	Node* pNew;
	Node* pTemp;

	if (infile)
	{
		while (!infile.eof())
		{
			pNew = new Node;
			pNew->pNext = nullptr;
			
			getline(infile, pNew->movieTitle);
			getline(infile, pNew->Director);
			getline(infile, pNew->movieRating);
			infile >> pNew->numberCopies;
			infile.ignore();
				
			if (pHead == nullptr)
				pHead = pNew;
			else
			{
				pTemp = pHead;
				while (pTemp->pNext != nullptr)
				{
					pTemp = pTemp->pNext;
				}
				pTemp->pNext = pNew;
			}
		}
		infile.close();
	}

	//Display error message if file was not opened

	else
		cout << "Error: File was not found!";

	
}

// Function:	ShowDVDInformation
// Description: This program is given a pointer to the node created by FindDVDbyTitle
//				function and then displays the DVD information.
// Programmer:	Douglas G Calmes
// Class:		CS 2020, Spring 2016
// Parameters:	pFind	- Pointer to the *Node that was passed by FindDVDbyTitle function
// Returns:		This function is void.

void ShowDVDInformation(Node* pFind)
{
	cout << left << setw(45) << "Title" << setw(20) << "Director" << setw(10) << "Rating" << setw(10) << "Count" << endl;
	cout << left << setw(45) << pFind->movieTitle << setw(20) << pFind->Director << setw(10) << pFind->movieRating << setw(10) << pFind->numberCopies << endl;
}

// Function:	DisplayDVDLibrary
// Description: Given a pointer to the first node, display all DVDs owned by the store			
// Programmer:	Douglas G Calmes
// Class:		CS 2020, Spring 2016
// Parameters:	pHead	- Pointer to the head of the linked list.
// Returns:		This function is void.

void DisplayDVDLibrary(Node* pHead)
{
	Node* pTemp = pHead;

	cout << left << setw(45) << "Title" << setw(20) << "Director" << setw(10) << "Rating" << setw(10) << "Count" << endl;

	while (pTemp != nullptr)
	{
		cout << left << setw(45) << pTemp->movieTitle << setw(20) << pTemp->Director << setw(10) << pTemp->movieRating << setw(10) << pTemp->numberCopies << endl;

		pTemp = pTemp->pNext;
	}

}

// Function:	FindDVDbyTitle
// Description: Given pointer to the first node and the title, find and return pointer
//				to the appropriate node in the list or nullptr otherwise
// Programmer:	Douglas G Calmes
// Class:		CS 2020, Spring 2016
// Parameters:	pHead		- Pointer to the head of the linked list
//				findTitle	- The movie that was entered by the user
// Returns:		Node* pFind	- This is passed so it can be used in the Renting, Returning, and Showing of
//			`				  the data of the movie that was entered by the user.

Node* FindDVDbyTitle(Node* pHead, string findTitle)
{
	Node* pTemp = pHead;

	while (pTemp->pNext != nullptr && pTemp->movieTitle != findTitle)
	{
		pTemp = pTemp->pNext;
	}

	if (pTemp->pNext == nullptr)
	{
		cout << findTitle << " not found in the library" << endl;
	}

		return pTemp;

}

// Function:	CheckOut
// Description: Given pointer to the DVD node, decrement number of DVDs currently in the store,
//				if DVD owned by the store and if not already 0.
// Programmer:	Douglas G Calmes
// Class:		CS 2020, Spring 2016
// Parameters:	pFind	- Pointer to the *Node that was passed by FindDVDbyTitle function
// Returns:		This function is void.

void CheckOut(Node* pFind)
{
	pFind->numberCopies--;
	if (pFind->numberCopies < 0)
	{
		cout << "ERROR: All DVDs for this movie are currently rented out" << endl;
		pFind->numberCopies++;
	}
}

// Function:	CheckIn
// Description: Given pointer to the DVD node, increment number of DVDs currently
//				in the store
// Programmer:	Douglas G Calmes
// Class:		CS 2020, Spring 2016
// Parameters:	pFind	- Pointer to the *Node that was passed by FindDVDbyTitle function
// Returns:		This function is void.

void CheckIn(Node* pFind)
{
	pFind->numberCopies++;
}

// Function:	DeleteList
// Description: This program deletes each element of the linked list
// Programmer:	Douglas G Calmes
// Class:		CS 2020, Spring 2016
// Parameters:	pHead	- Pointer to the head of the linked list
// Returns:		This function is void.

void DeleteList(Node* pHead)
{
	Node* pTemp; 

	pTemp = pHead;

	while (pTemp != nullptr) 
	{
		// save pointer to next node in the list 
		pHead = pTemp->pNext;

		delete pTemp;

		// start traversing at next node 
		pTemp = pHead;
	}
}

// Function:	Menu
// Description: This program is used to show the user the options to choose from and asks them to input their choice
// Programmer:	Douglas G Calmes
// Class:		CS 2020, Spring 2016
// Parameters:	
// Returns:		option- this allows the program to use the option that the user has chosen inside the loop

int Menu()
{
	int option=0;

	cout << "1. Rent" << endl;
	cout << "2. Return" << endl;
	cout << "3. Find" << endl;
	cout << "4. Listing" << endl;
	cout << "5. Quit" << endl;
	cout << "Choice? [1, 2, 3, 4, or 5]" << endl;
	cin >> option;

	return option;
}