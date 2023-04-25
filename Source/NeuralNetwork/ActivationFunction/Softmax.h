

#include "BaseActivationFunction.h"


class Softmax : public BaseActivationFunction
{
public:
	Softmax();
	~Softmax();


	virtual float	BAF_Activation_To_Neuron( float x );



private:



};