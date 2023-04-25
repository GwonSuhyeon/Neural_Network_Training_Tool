


#include "BaseLayer.h"



BaseLayer::BaseLayer( E_LayerType layerType, E_ActivationType activationType, string structureName )
{
	bool initResult;

	initResult = BL_Init_BaseLayer( layerType, structureName );
	if( initResult == false )
	{
		this->m_exception_report = E_EXCEPTION_OCCUR;
	}


	initResult = BL_Init_Activation_Function( activationType );
	if( initResult == false )
	{
		this->m_exception_report = E_EXCEPTION_OCCUR;
	}
}


BaseLayer::~BaseLayer()
{
	bool deleteResult;

	deleteResult = BL_Delete_Activation_Function();
	if( deleteResult == false )
	{
		// ���ܸ� ����ó�� ��ü�� �Ѱ��ָ� �ٸ� ������ �� ����ó�� ��ü�� ���ؼ� ���ܹ߻� ���θ� Ȯ���Ѵ�.
	}

#ifdef _DEBUG
	cout << "BaseLayer - " << m_layerName << " ��ȯ ����" << endl << endl;
#endif
}


E_Exception BaseLayer::BL_Get_Exception_Report()
{
	return this->m_exception_report;
}


bool BaseLayer::BL_Init_BaseLayer( E_LayerType layerType , string structureName )
{
	if( structureName.empty() == true )
	{
		return false;
	}

	this->m_exception_report = E_EXCEPTION_NOT_OCCUR;
	this->m_layerType = layerType;
	this->m_layerName = structureName;

	return true;
}


bool BaseLayer::BL_Init_Activation_Function( E_ActivationType activationType )
{
	if( m_activationFunction != nullptr )
	{
		// Ȱ��ȭ �Լ��� �̹� �ʱ�ȭ��.
		// Init�Լ��� �ٸ� �������� ȣ���ؼ� �ߺ�ȣ���� �Ǿ��ٴ� �ǹ���.
		return false;
	}


	// Ȱ��ȭ �Լ� Ŭ������ ActivationFunctino Ŭ������ ��ĳ���� ��. ��ü �Ҹ� �� �ٿ�ĳ���� �ʿ���.
	switch( activationType )
	{
	case E_Sigmoid:
	{
		m_activationFunction = new Sigmoid();
		if( m_activationFunction == nullptr )
		{
			// Ȱ��ȭ �Լ� ���� ����
			return false;
		}

		break;
	}


	case E_ReLU:
	{
		m_activationFunction = new ReLU();
		if( m_activationFunction == nullptr )
		{
			// Ȱ��ȭ �Լ� ���� ����
			return false;
		}

		break;
	}


	default:
		break;
	}

	this->m_ActivationFunctionType = activationType;

	return true;
}


BaseActivationFunction* BaseLayer::BL_Get_Activation_Function()
{
	return this->m_activationFunction;
}


E_ActivationType BaseLayer::BL_Get_Activation_Type()
{
	return this->m_ActivationFunctionType;
}


bool BaseLayer::BL_Delete_Activation_Function()
{
	if( this->m_activationFunction == nullptr )
	{
		return false;
	}

	switch( this->m_ActivationFunctionType )
	{
	case E_Sigmoid:
	{
		Sigmoid *sigmoid = (Sigmoid *)this->m_activationFunction;
		delete sigmoid;
		break;
	}


	case E_ReLU:
	{
		ReLU *relu = (ReLU*)this->m_activationFunction;
		delete relu;
		break;
	}


	default:
		break;
	}

	/*if( this->m_activationFunction != nullptr )
	{
		cout << "Ȱ��ȭ �Լ� ��ȯ ����" << endl;

		return false;
	}*/

	cout << "Ȱ��ȭ �Լ� ��ȯ ����" << endl;


	return true;
}


void BaseLayer::BL_Print_BaseLayer_Info()
{
	cout << "---------------------------------" << endl;
	cout << "Layer Name : " << this->m_layerName << endl;

	return;
}


string BaseLayer::BL_Get_BaseLayer_Name()
{
	return this->m_layerName;
}


E_LayerType BaseLayer::BL_Get_BaseLayer_Type()
{
	return this->m_layerType;
}


#ifdef _DEBUG
void BaseLayer::BL_func()
{
	return;
}
#endif


float BaseLayer::BL_Get_Predicted_Value()
{
	return (float)99.0;
}


bool BaseLayer::BL_ForewardPass( float *trainData, BaseLayer *nextLayer )
{
	return false;
}


bool BaseLayer::BL_ForewardPass( BaseLayer *nextLayer )
{
	return false;
}


bool BaseLayer::BL_BackwardPass( int previousNeuronSize, float *upStreamBundle, float error, int batchSize, E_UpStreamGradientOccur computeOccur )
{
	return false;
}