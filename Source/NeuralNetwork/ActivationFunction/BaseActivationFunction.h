

#ifndef __ACTIVATIONFUNCTION_H__
#define __ACTIVATIONFUNCTION_H__


#include <cmath>


#define		INVALID_RETURN_VALUE	65535
#define		Base_Of_Natural_Log		2.7182818284


enum E_ActivationType
{
	E_Sigmoid				= 0,
	E_ReLU					= 1,

	E_Invalid_ActivationType	= 99
};


class BaseActivationFunction
{
public:
	BaseActivationFunction();
	~BaseActivationFunction();


	virtual float	BAF_Activation_To_Neuron( float x );


private:



};





#endif