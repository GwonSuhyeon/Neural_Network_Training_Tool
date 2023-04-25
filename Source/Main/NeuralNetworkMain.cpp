

#include "NeuralNetworkMain.h"


NeuralNetworkMain::NeuralNetworkMain()
{

}


NeuralNetworkMain::~NeuralNetworkMain()
{

}


bool NeuralNetworkMain::NNM_Training()
{
	//NeuralNetwork		DeepNeuralNetwork;
	bool				NN_buildResult;
	bool				NN_learnResult;
	bool				NN_saveResult;
	bool				NN_deleteResult;


	//DataPreProcess		DataPreProcessor;
	bool				DPP_initResult;
	bool				DPP_loadResult;
	bool				DPP_scalerResult;
	bool				DPP_deleteResult;
	bool				DPP_splitResult;

	float				**trainX = nullptr;
	float				*trainY = nullptr;
	float				**testX = nullptr;
	float				*testY = nullptr;


	/*
	// �����Լ��� ���Ժ��� �������� Ȯ���ϴ� �ڵ�
	random_device					randomDevice;
	mt19937							mersenneTwister( randomDevice() );
	normal_distribution<float>		randomCreator( RANDOM_MEAN, RANDOM_STANDARD_DEVIATION );
	float value;
	string text;
	FILE *fp;

	fp = fopen( "D:/SVN/Weather_Predict_Neural_Network/random.txt", "wt" );

	for( int i = 0; i < 100000; i++ )
	{
		value = randomCreator( mersenneTwister );
		text = to_string( value );
		fprintf( fp, text.c_str() );
		fprintf( fp, "\n" );
	}
	fclose( fp );
	return 0;
	*/

	//::gLog_LogFile.LS_AddLog( _T( "ERROR - CAcceptSes)" ) );


	{
		DPP_initResult = DataPreProcessor.DPP_Init();
		if( DPP_initResult == INIT_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DataPreProcessor init fail - Main.cpp" ) );

			return false;
		}

		DPP_loadResult = DataPreProcessor.DPP_File_Load();
		if( DPP_loadResult == false )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DataPreProcessor file load fail - Main.cpp" ) );

			return false;
		}

		DPP_scalerResult = DataPreProcessor.DPP_MinMax_Scaling( -1, 1 );
		if( DPP_scalerResult == SCALER_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DataPreProcessor data scaling fail - Main.cpp" ) );

			return false;
		}

		//DPP_splitResult = DataPreProcessor.DPP_Train_Test_Split( E_NOT_SHUFFLE, (float)0.1, (float)0.9, &trainX, &trainY, &testX, &testY );
		DPP_splitResult = DataPreProcessor.DPP_Train_Test_Split( E_SHUFFLE, (float)0.8, (float)0.2, &trainX, &trainY, &testX, &testY );
		if( DPP_splitResult == SPLIT_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DataPreProcessor data split fail - Main.cpp" ) );

			return false;
		}

		DPP_deleteResult = DataPreProcessor.DPP_Delete_WeatherData();
		if( DPP_deleteResult == DELETE_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DaataPreProcessor delete variable fail - Main.cpp" ) );

			return false;
		}
	}



	{
		targetMin = DataPreProcessor.DPP_Get_TargetMin( targetIndex );
		if( targetMin >= MIN_DEFAULT_VALUE )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DataPreProcessor get min value fail - Main.cpp" ) );

			return false;
		}

		targetMax = DataPreProcessor.DPP_Get_TargetMax( targetIndex );
		if( targetMax <= MAX_DEFAULT_VALUE )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DataPreProcessor get max value fail - Main.cpp" ) );

			return false;
		}

		trainDataCnt = DataPreProcessor.DPP_Get_TrainDataCnt();
		if( trainDataCnt == -1 )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DataPreProcessor get train data count fail - Main.cpp" ) );

			return false;
		}

		testDataCnt = DataPreProcessor.DPP_Get_TestDataCnt();
		if( testDataCnt == -1 )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DataPreProcessor get test data count fail - Main.cpp" ) );

			return false;
		}

		DPP_deleteResult = DataPreProcessor.DPP_Delete_S_MinMaxScaler();
		if( DPP_deleteResult == DELETE_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DataPreProcessor delete scaler struct fail - Main.cpp" ) );

			return false;
		}
	}



	{
		NN_buildResult = DeepNeuralNetwork.NN_Model_Build();
		if( NN_buildResult == BUILD_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DeepNeuralNetwork build fail - Main.cpp" ) );

			return false;
		}

		//NN_learnResult = DeepNeuralNetwork.NN_Model_Learn( 1, 1, (float)0.01, E_SGD, E_MSE, trainX, trainY, trainDataCnt, targetMin, targetMax );
		NN_learnResult = DeepNeuralNetwork.NN_Model_Learn( Epoch, BatchSize, LearningRate, E_MGD, E_MSE, trainX, trainY, trainDataCnt, targetMin, targetMax, &( this->LearnedDataCnt ) );
		if( NN_learnResult == LEARN_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DeepNeuralNetwork learn fail - Main.cpp" ) );

			return false;
		}

		NN_saveResult = DeepNeuralNetwork.NN_Model_Save();
		if( NN_saveResult == SAVE_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DeepNeuralNetwork save fail - Main.cpp" ) );

			return false;
		}
	}



	{
		NN_deleteResult = DeepNeuralNetwork.NN_DeletE_LossFunctionType();
		if( NN_deleteResult == DELETE_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DeepNeuralNetwork delete loss function fail - Main.cpp" ) );

			return false;
		}

		NN_deleteResult = DeepNeuralNetwork.NN_DeletE_OptimizerType();
		if( NN_deleteResult == DELETE_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DeepNeuralNetwork delete optimizer fail - Main.cpp" ) );

			return false;
		}

		NN_deleteResult = DeepNeuralNetwork.NN_Delete_Vector_Memory();
		if( NN_deleteResult == DELETE_FAIL )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "DeepNeuralNetwork delete model vector fail - Main.cpp" ) );

			return false;
		}
	}


	for( int i = 0; i < trainDataCnt; i++ )
	{
		if( *( trainX + i ) == nullptr )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "Delete variable( trainX ) fail - Main.cpp" ) );

			return false;
		}

		delete[] * ( trainX + i );
	}

	if( trainX == nullptr )
	{
		::gLog_ErrorLog.LS_AddLog( _T( "Delete variable( trainX ) fail - Main.cpp" ) );

		return false;
	}

	delete[] trainX;

	if( trainY == nullptr )
	{
		::gLog_ErrorLog.LS_AddLog( _T( "Delete variable( trainY ) fail - Main.cpp" ) );

		return false;
	}

	delete[] trainY;


	for( int i = 0; i < testDataCnt; i++ )
	{
		if( *( testX + i ) == nullptr )
		{
			::gLog_ErrorLog.LS_AddLog( _T( "Delete variable( testX ) fail - Main.cpp" ) );

			return false;
		}

		delete[] * ( testX + i );
	}

	if( testX == nullptr )
	{
		::gLog_ErrorLog.LS_AddLog( _T( "Delete variable( testX ) fail - Main.cpp" ) );

		return false;
	}

	delete[] testX;

	if( testY == nullptr )
	{
		::gLog_ErrorLog.LS_AddLog( _T( "Delete variable( testY ) fail - Main.cpp" ) );

		return false;
	}

	delete[] testY;




	return true;
}


bool NeuralNetworkMain::NNM_Model_Run()
{
	return true;
}


void NeuralNetworkMain::Test_Func()
{
	this->Epoch += 10;
	this->BatchSize += 10;
	this->LearningRate += 10.0;


	return;
}