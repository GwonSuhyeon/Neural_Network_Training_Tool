
// NeuralNetworkTrainingToolDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "NeuralNetworkTrainingTool.h"
#include "NeuralNetworkTrainingToolDlg.h"
#include "afxdialogex.h"


// CNeuralNetworkTrainingToolDlg 대화 상자


CNeuralNetworkTrainingToolDlg::CNeuralNetworkTrainingToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEURALNETWORKTRAININGTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNeuralNetworkTrainingToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_TextView, training_TextView );
	DDX_Control( pDX, IDC_PROGRESS, training_ProgressBar );

	DDX_Control( pDX, IDC_TextView2, modelRun_TextView );
	DDX_Control( pDX, IDC_PROGRESS2, modelRun_ProgressBar );
}

BEGIN_MESSAGE_MAP(CNeuralNetworkTrainingToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE( IDC_EDIT_Epoch, &CNeuralNetworkTrainingToolDlg::OnEnChangeEditEpoch )
	ON_EN_CHANGE( IDC_EDIT_BatchSize, &CNeuralNetworkTrainingToolDlg::OnEnChangeEditBatchsize )
	ON_EN_CHANGE( IDC_EDIT_LearningRate, &CNeuralNetworkTrainingToolDlg::OnEnChangeEditLearningrate )
	//ON_EN_CHANGE( IDC_EDIT_DataFile, &CNeuralNetworkTrainingToolDlg::OnEnChangeEditDatafile )
	ON_BN_CLICKED( IDOK, &CNeuralNetworkTrainingToolDlg::OnBnClickedOk )
	ON_BN_CLICKED( IDC_BUTTON_Datafile, &CNeuralNetworkTrainingToolDlg::OnBnClickedDatafileButton )
	ON_BN_CLICKED( IDC_BUTTON_Training, &CNeuralNetworkTrainingToolDlg::OnBnClickedButtonTraining )
	ON_BN_CLICKED( IDC_BUTTON_DataInfo, &CNeuralNetworkTrainingToolDlg::OnBnClickedButtonDatainfo )
	ON_NOTIFY( NM_CUSTOMDRAW, IDC_PROGRESS, &CNeuralNetworkTrainingToolDlg::OnNMCustomdrawProgress )
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED( IDCANCEL, &CNeuralNetworkTrainingToolDlg::OnBnClickedCancel )
	ON_BN_CLICKED( IDC_BUTTON_ModelSave, &CNeuralNetworkTrainingToolDlg::OnBnClickedButtonModelsave )
	ON_BN_CLICKED( IDC_BUTTON_PredictDataList, &CNeuralNetworkTrainingToolDlg::OnBnClickedButtonPredictdatalist )
	ON_BN_CLICKED( IDC_BUTTON_PredictDataInfo, &CNeuralNetworkTrainingToolDlg::OnBnClickedButtonPredictdatainfo )
	ON_BN_CLICKED( IDC_BUTTON_ModelLoad, &CNeuralNetworkTrainingToolDlg::OnBnClickedButtonModelload )
	ON_BN_CLICKED( IDC_BUTTON_ModelRun, &CNeuralNetworkTrainingToolDlg::OnBnClickedButtonModelrun )
END_MESSAGE_MAP()


// CNeuralNetworkTrainingToolDlg 메시지 처리기

BOOL CNeuralNetworkTrainingToolDlg::OnInitDialog()
{
	TCHAR c_CurrentPath[ 512 ] = { 0 };

	CString s_CurrentPath;

	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	this->NN_Main = nullptr;
	this->runningResult = true;

	this->GetWindowRect( this->dialogFrameSize );

	training_ProgressBar.SetRange( 0, 100 );


	GetModuleFileName( NULL, c_CurrentPath, 512 );
	
	/*for( int i = 0; i < sizeof( c_CurrentPath ); i++ )
	{
		if( c_CurrentPath[ i ] == '\\' )
		{
			c_CurrentPath[ i ] = '/';
		}

		if( c_CurrentPath[ i ] == '\0' )
		{
			break;
		}
	}*/
	

	//CString s_CurrentPath( c_CurrentPath );
	s_CurrentPath.Format( _T( "%s" ), c_CurrentPath );

	s_CurrentPath = s_CurrentPath.Left( s_CurrentPath.ReverseFind( '\\' ) );

	strcpy_s( this->c_FolderPath, sizeof( this->c_FolderPath ), CW2A( s_CurrentPath ) );
	this->s_FolderPath = s_CurrentPath;

	SetDlgItemText( IDC_EDIT_ModelSave, this->s_FolderPath );  


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CNeuralNetworkTrainingToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CNeuralNetworkTrainingToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CNeuralNetworkTrainingToolDlg::OnEnChangeEditEpoch()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNeuralNetworkTrainingToolDlg::OnEnChangeEditBatchsize()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNeuralNetworkTrainingToolDlg::OnEnChangeEditLearningrate()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNeuralNetworkTrainingToolDlg::OnEnChangeEditDatafile()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedDatafileButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CString str = _T("텍스트 파일(*.txt)|*.txt|");

	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText( IDC_EDIT_DataFile, strPathName );
	}
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedButtonDatainfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str = _T("텍스트 파일(*.txt)|*.txt|");

	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText( IDC_EDIT_DataInfo, strPathName );
	}
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedButtonModelsave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	BROWSEINFO browseInfo;

	TCHAR c_SelectPath[ 512 ];

	CString s_SelectPath;


	::ZeroMemory( &browseInfo, sizeof( BROWSEINFO ) );
	::ZeroMemory( c_SelectPath, sizeof( c_SelectPath ) );

	browseInfo.hwndOwner = GetSafeHwnd();
	browseInfo.lpszTitle = _T( "학습이 완료된 모델을 저장할 위치를 선택하세요" );
	browseInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder( &browseInfo );
	::SHGetPathFromIDList( pItemIdList, c_SelectPath );

	s_SelectPath.Format( _T( "%s" ), c_SelectPath );
	SetDlgItemText( IDC_EDIT_ModelSave, s_SelectPath );


	return;
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedButtonTraining()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	
	//DataPreProcess		DDP;
	bool				runResult;

	int					epoch			= 0;
	int					batchSize		= 0;
	float				learningRate	= 0;

	CString				floatBuffer = _T( "" );
	CString				dataFileAddrBuffer = _T( "" );
	CString				dataInfoAddrBuffer = _T( "" );
	char				*ptr;

	int					MaxLearnCnt;
	float				status;

	bool				folderCreateResult;
	bool				errorResult;


	epoch			= GetDlgItemInt( IDC_EDIT_Epoch, NULL, false );
	batchSize		= GetDlgItemInt( IDC_EDIT_BatchSize, NULL, false );

	GetDlgItemTextW( IDC_EDIT_LearningRate, floatBuffer );
	ptr				= new char[ floatBuffer.GetLength() ];
	strcpy_s( ptr, sizeof( ptr ), CW2A( floatBuffer ) );	// CW2A : 유니코드 -> 멀티바이트 변환
	learningRate	= atof( ptr );

	GetDlgItemTextW( IDC_EDIT_DataFile, dataFileAddrBuffer );
	GetDlgItemTextW( IDC_EDIT_DataInfo, dataInfoAddrBuffer );

	if( ( epoch == 0 ) | ( batchSize == 0 ) | ( learningRate == 0 ) | ( dataFileAddrBuffer.IsEmpty() == true ) | ( dataInfoAddrBuffer.IsEmpty() == true ) )
	{
		//MessageBoxW( _T( "입력되지 않은 값이 있습니다" ) );
		training_TextView.SetWindowTextW( _T( "입력되지 않은 값이 있습니다" ) );

		return;
	}


	NN_Main = new NeuralNetworkMain();
	if( NN_Main == nullptr )
	{
		training_TextView.SetWindowTextW( _T( "모델을 학습시킬 수 없습니다" ) );

		return;
	}


	training_ProgressBar.SetPos( 0 );

	Deactivation_View();


	NN_Main->Epoch			= epoch;
	NN_Main->BatchSize		= batchSize;
	NN_Main->LearningRate	= learningRate;

	//ptr				= new char[ dataFileAddrBuffer.GetLength() ];
	strcpy_s( NN_Main->DataPreProcessor.m_WeatherData_FileList_Addr, sizeof( NN_Main->DataPreProcessor.m_WeatherData_FileList_Addr ), CW2A( dataFileAddrBuffer ) );
	for( int i = 0; i < dataFileAddrBuffer.GetLength(); i++ )
	{
		if( NN_Main->DataPreProcessor.m_WeatherData_FileList_Addr[ i ] == '\\' )
		{
			NN_Main->DataPreProcessor.m_WeatherData_FileList_Addr[ i ] = '/';
		}
	}
	/*strcpy_s( ptr, sizeof( ptr ), CW2A( dataFileAddrBuffer ) );
	strcpy_s( DDP.m_WeatherData_FileList_Addr, sizeof( DDP.m_WeatherData_FileList_Addr ), ptr );*/


	//ptr				= new char[ dataInfoAddrBuffer.GetLength() ];
	strcpy_s( NN_Main->DataPreProcessor.m_WeatherData_Info_Addr, sizeof( NN_Main->DataPreProcessor.m_WeatherData_Info_Addr ), CW2A( dataInfoAddrBuffer ) );
	for( int i = 0; i < dataInfoAddrBuffer.GetLength(); i++ )
	{
		if( NN_Main->DataPreProcessor.m_WeatherData_Info_Addr[ i ] == '\\' )
		{
			NN_Main->DataPreProcessor.m_WeatherData_Info_Addr[ i ] = '/';
		}
	}
	/*strcpy_s( ptr, sizeof( ptr ), CW2A( dataInfoAddrBuffer ) );
	strcpy_s( DDP.m_WeatherData_Info_Addr, sizeof( DDP.m_WeatherData_Info_Addr ), ptr );*/
	



	NN_Main->DeepNeuralNetwork.Critical_Section_Init();

	thread progressThread( [&] () { Training_Thread_Main(); } );
	//progressThread.detach();

	//CWinThread *thread = NULL;
	//thread = AfxBeginThread( Training_Thread_Main, this );

	training_TextView.SetWindowTextW( _T( "Train Data Loading..." ) );

	
	while( 1 )
	{
		errorResult = Running_Exception_Error();
		if( errorResult == false )
		{
			break;
		}

		Message_Handler();

		//EnterCriticalSection( &( NN_Main->criticalSection ) );
		if( ( NN_Main->trainDataCnt > 0 ) && ( NN_Main->LearnedDataCnt > 0 ) )
		{
			//LeaveCriticalSection( &( NN_Main->criticalSection ) );

			//training_TextView.SetWindowTextW( _T( "Model Training... 0%%" ) );
			training_TextView.SetWindowTextW( _T( "Model Training..." ) );

			break;
		}
		//LeaveCriticalSection( &( NN_Main->criticalSection ) );
	}

	if( errorResult == false )
	{
		progressThread.join();

		NN_Main->DeepNeuralNetwork.Critical_Section_Delete();

		if( Running_Quit() == false )
		{
			AfxGetMainWnd()->PostMessage( WM_QUIT );
		}

		training_TextView.SetWindowTextW( _T( "Fail" ) );
		MessageBoxW( _T( "- Training Fail -" ) );


		return;
	}


	MaxLearnCnt = ( NN_Main->trainDataCnt / NN_Main->BatchSize ) * NN_Main->Epoch;

	while( 1 )
	{
		if( NN_Main->LearnedDataCnt > 0 )
		{
			folderCreateResult = Create_Model_Save_Folder();
			if( folderCreateResult == false )
			{
				if( Running_Quit() == false )
				{
					AfxGetMainWnd()->PostMessage( WM_QUIT );
				}

				//MessageBoxW( _T( "- 모델 저장 위치에 폴더 생성 실패 -" ) );
				training_TextView.SetWindowTextW( _T( "- 모델 저장 위치에 폴더 생성 실패 -" ) );


				return;
			}

			break;
		}
	}

	int progressStep = MaxLearnCnt / 100;
	while( 1 )
	{
		errorResult = Running_Exception_Error();
		if( errorResult == false )
		{
			break;
		}

		Message_Handler();

		EnterCriticalSection( &( NN_Main->DeepNeuralNetwork.criticalSection ) );
		if( ( NN_Main->LearnedDataCnt % progressStep ) == 0 )
		{
			//CString str;

			status = (float)NN_Main->LearnedDataCnt / (float)MaxLearnCnt * 100.0;

			//str.Format( _T( "Model Training... %.3f%%" ), status );
			//str.Format( _T( "Model Training... %d%%" ), (int)status );
			//training_TextView.SetWindowTextW( str );

			training_ProgressBar.SetPos( (int)status );
		}
		

		if( NN_Main->LearnedDataCnt >= MaxLearnCnt )
		{
			training_ProgressBar.SetPos( 100 );

			LeaveCriticalSection( &( NN_Main->DeepNeuralNetwork.criticalSection ) );

			break;
		}
		LeaveCriticalSection( &( NN_Main->DeepNeuralNetwork.criticalSection ) );
	}


	if( errorResult == false )
	{
		progressThread.join();

		NN_Main->DeepNeuralNetwork.Critical_Section_Delete();

		if( Running_Quit() == false )
		{
			AfxGetMainWnd()->PostMessage( WM_QUIT );
		}

		training_TextView.SetWindowTextW( _T( "Fail" ) );
		MessageBoxW( _T( "- Training Fail -" ) );

		return;
	}


	progressThread.join();

	NN_Main->DeepNeuralNetwork.Critical_Section_Delete();

	



	if( Running_Quit() == false )
	{
		AfxGetMainWnd()->PostMessage( WM_QUIT );
	}

	training_TextView.SetWindowTextW( _T( "Complete" ) );

	MessageBoxW( _T( "- Training Success -" ) );


	//NN_Main->DeepNeuralNetwork.NN_Model_Predict();


	/*NN_Main->Test_Func();

	CString str;
	str.Format( _T( "%d\n%d\n%f" ), NN_Main->Epoch, NN_Main->BatchSize, NN_Main->LearningRate );

	training_TextView.SetWindowTextW( str );*/


	return;
}


void CNeuralNetworkTrainingToolDlg::OnNMCustomdrawProgress( NMHDR *pNMHDR, LRESULT *pResult )
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>( pNMHDR );
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CNeuralNetworkTrainingToolDlg::Training_Thread_Main()
{
	//CNeuralNetworkTrainingToolDlg *dialog = nullptr;

	bool runResult;

	/*
	dialog = (CNeuralNetworkTrainingToolDlg *)AfxGetApp()->m_pMainWnd;
	if( dialog == nullptr )
	{
		// 아래 2개의 코드는 서로 같은 기능을 함.
		// mfc 응용 프로그램의 메인 스레드의 각종 메시지를 처리하는 메시지 루프에 WM_QUIT를 전달함.
		// 메시지 루프는 WM_QUIT가 종료 조건임.

		AfxGetMainWnd()->PostMessage( WM_QUIT );
		//PostQuitMessage(0);
	}
	*/

	runResult = NN_Main->NNM_Training();
	if( runResult == false )
	{
		this->runningResult = false;
	}
	else
	{
		this->runningResult = true;
	}
	
	//delete dialog;


	return;
}


void CNeuralNetworkTrainingToolDlg::Model_Run_Thread_Main()
{
	bool runResult;


	runResult = NN_Main->NNM_Model_Run();
	if( runResult == false )
	{
		this->runningResult = false;
	}
	else
	{
		this->runningResult = true;
	}


	return;
}


/*
UINT CNeuralNetworkTrainingToolDlg::Training_Thread_Main( LPVOID _param )
{
	CNeuralNetworkTrainingToolDlg *dialog = nullptr;

	bool runResult;


	dialog = (CNeuralNetworkTrainingToolDlg *)AfxGetApp()->m_pMainWnd;

	runResult = dialog->NN_Main->NNM_Training();
	if( runResult == false )
	{
		return -1;
	}

	if( dialog == nullptr )
	{
		return -1;
	}

	delete dialog;


	return 0;
}
*/


void CNeuralNetworkTrainingToolDlg::Message_Handler()
{
	MSG message;
	
	bool peekResult;


	while( 1 )
	{
		peekResult = PeekMessageW( &message, GetSafeHwnd(), NULL, NULL, PM_REMOVE );
		if( peekResult == FALSE )
		{
			break;
		}

		TranslateMessage( &message );
		DispatchMessageW( &message );
	}


	return;
}


void CNeuralNetworkTrainingToolDlg::OnGetMinMaxInfo( MINMAXINFO* lpMMI )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//lpMMI->ptMinTrackSize = CPoint( 1352, 1072 );
	//lpMMI->ptMaxTrackSize = CPoint( 1352, 1072 );

	CDialogEx::OnGetMinMaxInfo( lpMMI );
}


bool CNeuralNetworkTrainingToolDlg::Create_Model_Save_Folder()
{
	CTime time;
	CString folderName;
	CString directoryPath;

	bool result;
	
	
	time = CTime::GetCurrentTime();

	folderName = _T( "Model_" ) + time.Format( _T( "%Y%m%d%H%M%S" ) );

	directoryPath = this->s_FolderPath + "\\" + folderName;

	result = CreateDirectoryW( directoryPath, NULL );
	if( result == false )
	{
		return false;
	}


	strcpy_s( this->NN_Main->DeepNeuralNetwork.m_modelSave_Directory_Addr, sizeof( this->NN_Main->DeepNeuralNetwork.m_modelSave_Directory_Addr), CW2A( directoryPath ) );
	for( int i = 0; i < directoryPath.GetLength(); i++ )
	{
		if( this->NN_Main->DeepNeuralNetwork.m_modelSave_Directory_Addr[ i ] == '\\' )
		{
			this->NN_Main->DeepNeuralNetwork.m_modelSave_Directory_Addr[ i ] = '/';
		}
	}

	
	return true;
}


bool CNeuralNetworkTrainingToolDlg::Running_Exception_Error()
{
	if( this->runningResult == false )
	{
		return false;
	}


	return true;
}


bool CNeuralNetworkTrainingToolDlg::Running_Quit()
{
	if( this->NN_Main == nullptr )
	{
		return false;
	}

	delete this->NN_Main;

	this->NN_Main = nullptr;
	this->runningResult = true;

	Activation_View();


	return true;
}


void CNeuralNetworkTrainingToolDlg::Activation_View()
{
	GetDlgItem( IDOK )->EnableWindow( TRUE );
	GetDlgItem( IDCANCEL )->EnableWindow( TRUE );

	GetDlgItem( IDC_EDIT_Epoch )->EnableWindow( TRUE );
	GetDlgItem( IDC_EDIT_BatchSize )->EnableWindow( TRUE );
	GetDlgItem( IDC_EDIT_LearningRate )->EnableWindow( TRUE );

	GetDlgItem( IDC_EDIT_DataFile )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_Datafile )->EnableWindow( TRUE );

	GetDlgItem( IDC_EDIT_DataInfo )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_DataInfo )->EnableWindow( TRUE );

	GetDlgItem( IDC_EDIT_ModelSave )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_ModelSave )->EnableWindow( TRUE );

	GetDlgItem( IDC_BUTTON_Training )->EnableWindow( TRUE );

	GetDlgItem( IDC_EDIT_PredictDataInfo )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_PredictDataInfo )->EnableWindow( TRUE );

	GetDlgItem( IDC_EDIT_PredictDataList )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_PredictDataList )->EnableWindow( TRUE );

	GetDlgItem( IDC_EDIT_ModelLoad )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_ModelLoad )->EnableWindow( TRUE );

	GetDlgItem( IDC_BUTTON_ModelRun )->EnableWindow( TRUE );


	return;
}


void CNeuralNetworkTrainingToolDlg::Deactivation_View()
{
	GetDlgItem( IDOK )->EnableWindow( FALSE );
	GetDlgItem( IDCANCEL )->EnableWindow( FALSE );

	GetDlgItem( IDC_EDIT_Epoch )->EnableWindow( FALSE );
	GetDlgItem( IDC_EDIT_BatchSize )->EnableWindow( FALSE );
	GetDlgItem( IDC_EDIT_LearningRate )->EnableWindow( FALSE );

	GetDlgItem( IDC_EDIT_DataFile )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_Datafile )->EnableWindow( FALSE );

	GetDlgItem( IDC_EDIT_DataInfo )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DataInfo )->EnableWindow( FALSE );

	GetDlgItem( IDC_EDIT_ModelSave )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_ModelSave )->EnableWindow( FALSE );

	GetDlgItem( IDC_BUTTON_Training )->EnableWindow( FALSE );

	GetDlgItem( IDC_EDIT_PredictDataInfo )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_PredictDataInfo )->EnableWindow( FALSE );

	GetDlgItem( IDC_EDIT_PredictDataList )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_PredictDataList )->EnableWindow( FALSE );

	GetDlgItem( IDC_EDIT_ModelLoad )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_ModelLoad )->EnableWindow( FALSE );

	GetDlgItem( IDC_BUTTON_ModelRun )->EnableWindow( FALSE );


	return;
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedButtonPredictdatalist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str = _T("텍스트 파일(*.txt)|*.txt|");

	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText( IDC_EDIT_PredictDataList, strPathName );
	}


	return;
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedButtonPredictdatainfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str = _T("텍스트 파일(*.txt)|*.txt|");

	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText( IDC_EDIT_PredictDataInfo, strPathName );
	}


	return;
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedButtonModelload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	BROWSEINFO browseInfo;

	TCHAR c_SelectPath[ 512 ];

	CString s_SelectPath;


	::ZeroMemory( &browseInfo, sizeof( BROWSEINFO ) );
	::ZeroMemory( c_SelectPath, sizeof( c_SelectPath ) );

	browseInfo.hwndOwner = GetSafeHwnd();
	browseInfo.lpszTitle = _T( "불러올 모델 위치를 선택하세요" );
	browseInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder( &browseInfo );
	::SHGetPathFromIDList( pItemIdList, c_SelectPath );

	s_SelectPath.Format( _T( "%s" ), c_SelectPath );
	SetDlgItemText( IDC_EDIT_ModelLoad, s_SelectPath );


	return;
}


void CNeuralNetworkTrainingToolDlg::OnBnClickedButtonModelrun()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	bool				runResult;

	CString				dataFileAddrBuffer	= _T( "" );
	CString				dataInfoAddrBuffer	= _T( "" );
	CString				modelAddrBuffer		= _T( "" );

	char				*ptr;

	int					MaxPredictCnt;
	float				status;

	bool				folderCreateResult;
	bool				errorResult;



	GetDlgItemTextW( IDC_EDIT_PredictDataList, dataFileAddrBuffer );
	GetDlgItemTextW( IDC_EDIT_PredictDataInfo, dataInfoAddrBuffer );
	GetDlgItemTextW( IDC_EDIT_ModelLoad, modelAddrBuffer );


	if( ( dataFileAddrBuffer.IsEmpty() == true ) | ( dataInfoAddrBuffer.IsEmpty() == true ) | ( modelAddrBuffer.IsEmpty() == true ) )
	{
		//MessageBoxW( _T( "입력되지 않은 값이 있습니다" ) );
		modelRun_TextView.SetWindowTextW( _T( "입력되지 않은 값이 있습니다" ) );

		return;
	}


	NN_Main = new NeuralNetworkMain();
	if( NN_Main == nullptr )
	{
		modelRun_TextView.SetWindowTextW( _T( "모델을 실행할 수 없습니다" ) );

		return;
	}


	modelRun_ProgressBar.SetPos( 0 );

	Deactivation_View();


	strcpy_s( NN_Main->DataPreProcessor.m_WeatherData_FileList_Addr, sizeof( NN_Main->DataPreProcessor.m_WeatherData_FileList_Addr ), CW2A( dataFileAddrBuffer ) );
	for( int i = 0; i < dataFileAddrBuffer.GetLength(); i++ )
	{
		if( NN_Main->DataPreProcessor.m_WeatherData_FileList_Addr[ i ] == '\\' )
		{
			NN_Main->DataPreProcessor.m_WeatherData_FileList_Addr[ i ] = '/';
		}
	}

	strcpy_s( NN_Main->DataPreProcessor.m_WeatherData_Info_Addr, sizeof( NN_Main->DataPreProcessor.m_WeatherData_Info_Addr ), CW2A( dataInfoAddrBuffer ) );
	for( int i = 0; i < dataInfoAddrBuffer.GetLength(); i++ )
	{
		if( NN_Main->DataPreProcessor.m_WeatherData_Info_Addr[ i ] == '\\' )
		{
			NN_Main->DataPreProcessor.m_WeatherData_Info_Addr[ i ] = '/';
		}
	}

	strcpy_s( NN_Main->DeepNeuralNetwork.m_modelLoadAddr, sizeof( NN_Main->DeepNeuralNetwork.m_modelLoadAddr ), CW2A( modelAddrBuffer ) );
	for( int i = 0; i < modelAddrBuffer.GetLength(); i++ )
	{
		if( NN_Main->DeepNeuralNetwork.m_modelLoadAddr[ i ] == '\\' )
		{
			NN_Main->DeepNeuralNetwork.m_modelLoadAddr[ i ] = '/';
		}
	}


	NN_Main->DeepNeuralNetwork.Critical_Section_Init();

	thread progressThread( [&] () { Model_Run_Thread_Main(); } );


	modelRun_TextView.SetWindowTextW( _T( "Predict Data Loading..." ) );


	while( 1 )
	{
		errorResult = Running_Exception_Error();
		if( errorResult == false )
		{
			break;
		}

		Message_Handler();

		if( ( NN_Main->predictDataCnt > 0 ) && ( NN_Main->computedDataCnt > 0 ) )
		{
			modelRun_TextView.SetWindowTextW( _T( "Model Running..." ) );

			break;
		}
	}

	if( errorResult == false )
	{
		progressThread.join();

		NN_Main->DeepNeuralNetwork.Critical_Section_Delete();

		if( Running_Quit() == false )
		{
			AfxGetMainWnd()->PostMessage( WM_QUIT );
		}

		modelRun_TextView.SetWindowTextW( _T( "Fail" ) );
		MessageBoxW( _T( "- Running Fail -" ) );


		return;
	}




	MaxPredictCnt = NN_Main->predictDataCnt;



	int progressStep = MaxPredictCnt / 100;
	while( 1 )
	{
		errorResult = Running_Exception_Error();
		if( errorResult == false )
		{
			break;
		}

		Message_Handler();

		EnterCriticalSection( &( NN_Main->DeepNeuralNetwork.criticalSection ) );
		if( ( NN_Main->computedDataCnt % progressStep ) == 0 )
		{
			status = (float)NN_Main->computedDataCnt / (float)MaxPredictCnt * 100.0;

			modelRun_ProgressBar.SetPos( (int)status );
		}
		

		if( NN_Main->computedDataCnt >= MaxPredictCnt )
		{
			modelRun_ProgressBar.SetPos( 100 );

			LeaveCriticalSection( &( NN_Main->DeepNeuralNetwork.criticalSection ) );

			break;
		}
		LeaveCriticalSection( &( NN_Main->DeepNeuralNetwork.criticalSection ) );
	}


	if( errorResult == false )
	{
		progressThread.join();

		NN_Main->DeepNeuralNetwork.Critical_Section_Delete();

		if( Running_Quit() == false )
		{
			AfxGetMainWnd()->PostMessage( WM_QUIT );
		}

		modelRun_TextView.SetWindowTextW( _T( "Fail" ) );
		MessageBoxW( _T( "- Running Fail -" ) );

		return;
	}


	progressThread.join();

	NN_Main->DeepNeuralNetwork.Critical_Section_Delete();

	



	if( Running_Quit() == false )
	{
		AfxGetMainWnd()->PostMessage( WM_QUIT );
	}

	modelRun_TextView.SetWindowTextW( _T( "Complete" ) );

	MessageBoxW( _T( "- Running Success -" ) );






	return;
}
