
#include <iostream>
#include <cstdlib>   
#include <ctime>     
#include <cmath>     
#include "coordinate.h"

using namespace std;


// add new nodes
void add_coordinate(Coordinate *list_end, float x, float y)
{
  
  Coordinate *first = list_end;
  while (first->previous != NULL)
    first = first->previous;


  Coordinate *node = new Coordinate;
  node->x = x;
  node->y = y;
  node->coord_id = list_length(first);  

  node->next = NULL;           
  node->previous = list_end;   
  list_end->next = node;       
}


// Prints every node from the first node to the last node.
void forward_display(Coordinate *list_beginning)
{
  Coordinate *p = list_beginning;   
  while (p != NULL)                 
  {
    cout << "ID " << p->coord_id << ": (" << p->x << ", " << p->y << ")" << endl;
    p = p->next;                    
  }
}


// Prints every node from the last node to the first node.
void backward_display(Coordinate *list_end)
{
  Coordinate *p = list_end;
  while (p != NULL)
  {
    cout << "ID " << p->coord_id << ": (" << p->x << ", " << p->y << ")" << endl;
    p = p->previous;                
  }
}


// Removes the node with the given id and frees its memory.
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{

  if (list_beginning->coord_id == coord_id_to_delete)
  {
    Coordinate *second = list_beginning->next;


    if (second == NULL)
    {
      cout << "Can't delete the only node in the list." << endl;
      return;
    }


    list_beginning->x = second->x;
    list_beginning->y = second->y;
    list_beginning->coord_id = second->coord_id;


    list_beginning->next = second->next;
    if (second->next != NULL)                    
      second->next->previous = list_beginning;   

    delete second;   
    return;
  }


  Coordinate *p = list_beginning->next;
  while (p != NULL && p->coord_id != coord_id_to_delete)
    p = p->next;

  
  if (p == NULL)
  {
    cout << "ID " << coord_id_to_delete << " not found." << endl;
    return;
  }

  p->previous->next = p->next;      
  if (p->next != NULL)              
    p->next->previous = p->previous;  

  delete p;   
}


// Returns how many nodes are in the list.
int list_length(Coordinate *list_beginning)
{
  int count = 0;
  Coordinate *p = list_beginning;
  while (p != NULL)
  {
    count++;        
    p = p->next;    
  }
  return count;
}


// Finds the node closest to the point (x, y), then prints that
// node and the distance to it.
void closest_to(Coordinate *list_beginning, float x, float y)
{
  
  Coordinate *closest = list_beginning;
  float best = sqrt((list_beginning->x - x) * (list_beginning->x - x) +
                    (list_beginning->y - y) * (list_beginning->y - y));

  
  Coordinate *p = list_beginning->next;
  while (p != NULL)
  {
    float d = sqrt((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y));
    if (d < best)
    {
      best = d;
      closest = p;
    }
    p = p->next;
  }

  // Print the result.
  cout << "Closest to (" << x << ", " << y << ") is ID " << closest->coord_id
       << " at (" << closest->x << ", " << closest->y << "), distance " << best << endl;
}


int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    cout << "Usage: ./main <number of coordinates>" << endl;
    return 1;
  }

  
  int count = atoi(argv[1]);
  if (count < 1)
  {
    cout << "Enter a number of 1 or more." << endl;
    return 1;
  }


  srand(time(NULL));

  // Create the first node by hand. head always points to the first node.
  Coordinate *head = new Coordinate;
  head->x = rand() % 101;     
  head->y = rand() % 101;
  head->coord_id = 0;
  head->next = NULL;          
  head->previous = NULL;      

  // Add the rest. tail always points to the last node.
  Coordinate *tail = head;
  for (int i = 1; i < count; i++)
  {
    add_coordinate(tail, rand() % 101, rand() % 101);
    tail = tail->next;        
  }

  // Show the list in both directions.
  cout << "Length: " << list_length(head) << endl;
  cout << "Forward:" << endl;
  forward_display(head);
  cout << "Backward:" << endl;
  backward_display(tail);

  // Find the closest node to a supplied point.
  closest_to(head, 50, 50);

  // Delete the first node, then node two.
  delete_coordinate(head, 0);
  delete_coordinate(head, 2);

  // Show the list again to see the result of the deletes.
  cout << "After deleting ID 0 and ID 2, length: " << list_length(head) << endl;
  forward_display(head);

  // Closest-to again with a different point.
  closest_to(head, 10, 90);

  // Free all remaining nodes so there are no memory leaks.
  while (head != NULL)
  {
    Coordinate *next = head->next;   
    delete head;
    head = next;
  }

  return 0;
}