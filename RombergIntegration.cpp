#include "RombergIntegration.h"
#include "RecursiveIntegration.h"
#include "QueueLinked.h"
#include "Double.h"
using CSC2110::Double;

using namespace std;
#include <iostream>

#include <math.h>

//a is the lower limit and b is the upper limit
double RombergIntegration::accurateRomberg(MultiVarFunction* f, double a, double b, int level)
{
   Double* db;  //use this variable to place and retrieve values on the queue
   
   QueueLinked<Double>* q1 = new QueueLinked<Double>;
   QueueLinked<Double>* q2 = new QueueLinked<Double>;



   int counter = 0;
   int n = 1;  //current number of intervals
   while ( counter < 4 )
   {
      //DO THIS
      //obtain the required number of trapezoid evaluations depending on the number of levels requested
      //put all of the level 0 results on the q1

db = new Double( RecursiveIntegration::romberg(f,a,b,n) );
q1->enqueue(db);








      n = 2*n;  //double the number of intervals
      counter++;
   }

  




   //q1 now has all of the level 0 integration results

   double factor;  //use this to compute the current Romberg Factor (4^k stuff)
   int power = 1;  //k, used to compute the Romberg Factor

   //if level 0 has been requested, the loop will not execute
   //the total number of executions of the loop is ??

   //DO THIS
   int iterations =  level   ;        //can be precomputed
   
   
	/*for (int i = level; i > 1; i--)		// This gets the discreet math formula, 
	{
		iterations = iterations + ( i - 1 );
	}*/
	

   while (iterations > 0)
   {
      //DO THIS
      //use the algorithm described in the lab to improve the accuracy of your level 0 results
		
	
	  double lA;
	  double mA;

	  int queueLoop = ( q1->size() - 1 );

	  for (int i = 0; i<( queueLoop ); i++)
	   {
	   Double* temp = q1->peek();
	   
		lA = q1->dequeue()->getValue();
		
		mA = q1->peek()->getValue();
	  
		Double* db = new Double( ( ( (pow(4,power)) * mA ) - lA ) / ( (pow(4,power) - 1 ) ) );
		q2->enqueue(db);
		
		delete temp;

		}
		
		
		

		if (q1->size() == 1)
		{
		
		q1->dequeueAll();
		queueLoop = q2->size();
		
		for (int i = 0; i < ( queueLoop ); i++)
	    {
		
			Double* temp = q2->peek();
			q1->enqueue(temp);
			q2->dequeue();
			//delete temp;
		}
			q2->dequeueAll();
		}


	power++;
      iterations--;
   }

   //obtain the final answer
   db = q1->dequeue();
   double result = db->getValue();  
   delete db;

   delete q1;
   delete q2;

   return result;


}
