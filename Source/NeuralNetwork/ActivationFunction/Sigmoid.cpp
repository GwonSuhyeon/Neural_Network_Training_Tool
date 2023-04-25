

#include "Sigmoid.h"



Sigmoid::Sigmoid()
{

}


Sigmoid::~Sigmoid()
{

}


float Sigmoid::BAF_Activation_To_Neuron( float x )
{
	float returnValue;

	returnValue = 1 / ( 1 + ( powf( Base_Of_Natural_Log, ( x * -1 ) ) ) );

	return returnValue;
}