

#include "../Main/ExceptionHandler.h"
#include "../Main/CommonFunction.h"

#include "../LogSystem/LogSystem.h"

#include "Layer/InputLayer.h"
#include "Layer/OutputLayer.h"
#include "Layer/DenseLayer.h"

#include "LossFunction/MeanSquaredError.h"

#include "Optimizer/MiniBatchGradientDescent.h"

#include <vector>
#include <string>
#include <iomanip>
#include <cmath>


#define		MAX_LAYER_CNT			255		// 모델에 추가할 수 있는 레이어 최대 개수


enum E_PropagationType
{
	E_FOREWARD_PROP = 0,
	E_BACKWARD_PROP = 1
};


enum E_Learning_Progress
{
	E_EPOCH_PROGRESS			= 0,
	E_GRADIENT_UPDATE_PROGRESS	= 1
};


class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	
	E_Exception			NN_Get_Exception_Report();

	bool				NN_Init();
	bool				NN_Init_LossFunction( E_LossFunctionType lossFunction );
	bool				NN_Init_Optimizer( int BatchSize, E_OptimizerType optimizer, int trainDataCnt );

	E_LossFunctionType	NN_Get_LossFunction_Type();
	E_OptimizerType		NN_Get_Optimizer_Type();

	bool				NN_Model_Build();
	bool				NN_Model_Learn( int Epoch, int BatchSize, float LearningRate, E_OptimizerType optimizer, E_LossFunctionType lossFunction, float **trainX, float *trainY, int trainDataCnt, float targetMin, float targetMax, int *LearnedDataCnt );
	bool				NN_Model_Predict( float **testX, float *testY, int testDataCnt );
	bool				NN_Model_Save();

	bool				NN_Add_Layer( E_LayerType layerType, int row, int column, E_ActivationType activationType, string structureName );
	bool				NN_Max_Layer_Checker();

	bool				NN_Propagation( float *unitTrainX, float unitTrainY, int BatchSize, int dataIndex, E_PropagationType propagationType );

	bool				NN_Print_Learning_Progress( E_Learning_Progress progressType, int repeat, int Epoch, int *batchUpdateCnt, float unitTrainY, int BatchSize, int trainDataCnt, float targetMin, float targetMax );

	bool				NN_DeletE_LossFunctionType();
	bool				NN_DeletE_OptimizerType();
	bool				NN_Delete_Vector_Memory();

	bool				NN_File_Close( FILE *fp_filePtr );

	void				Critical_Section_Init();
	void				Critical_Section_Delete();




	CRITICAL_SECTION	criticalSection;

	char				m_modelSave_Directory_Addr[ 512 ];
	char				m_modelLoadAddr[ 512 ];


private:

	E_Exception		m_exceptionOccurReport;	// 예외 발생 여부를 체크하기 위한 변수

	/*
	vector<shared_ptr<ModelStructure>> Model;

	이 코드를 사용하려면

	Model.push_back(shared_ptr<ModelStructure>(IL));

	이렇게 바꿔야 함.
	*/
	//vector<unique_ptr<ModelStructure>> Model;
	vector< BaseLayer* >		Model;

	BaseLossFunction			*m_LossFunction;
	E_LossFunctionType			m_LossFunctionType;

	BaseOptimizer				*m_Optimizer;
	E_OptimizerType				m_OptimizerType;

	E_UpStreamGradientOccur		m_ComputeOccur;

};