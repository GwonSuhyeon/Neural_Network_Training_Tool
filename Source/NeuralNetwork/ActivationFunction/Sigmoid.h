

#include "BaseActivationFunction.h"


class Sigmoid : public BaseActivationFunction
{
public:
	Sigmoid();
	~Sigmoid();


	virtual float	BAF_Activation_To_Neuron( float x );



private:



};