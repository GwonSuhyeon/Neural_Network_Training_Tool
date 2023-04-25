

#include "../LogSystem/LogSystem.h"
#include "DataPreProcess.h"
#include "../NeuralNetwork/NeuralNetwork.h"


#define		BUILD_SUCCESS		true
#define		BUILD_FAIL			false
#define		LEARN_FAIL			false
#define		SAVE_FAIL			false
#define		DELETE_FAIL			false


using namespace std;


enum RunType
{
	E_DataLoad		= 0,
	E_ModelLearn	= 1
};


class NeuralNetworkMain
{
public :
	NeuralNetworkMain();
	~NeuralNetworkMain();


	

	bool	NNM_Training();
	bool	NNM_Model_Run();

	void	Test_Func();


	

	NeuralNetwork		DeepNeuralNetwork;
	DataPreProcess		DataPreProcessor;

	int		Epoch;
	int		BatchSize;
	float	LearningRate;

	int		LearnedDataCnt;
	int		trainDataCnt = 0;
	int		testDataCnt = 0;

	int		computedDataCnt = 0;
	int		predictDataCnt = 0;


private:

	int		targetIndex = 0;
	float	targetMin = MIN_DEFAULT_VALUE;
	float	targetMax = MAX_DEFAULT_VALUE;


};