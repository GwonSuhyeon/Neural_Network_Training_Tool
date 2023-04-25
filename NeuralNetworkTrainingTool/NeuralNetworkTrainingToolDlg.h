
// NeuralNetworkTrainingToolDlg.h: 헤더 파일
//

#pragma once

#include <cstdlib>
#include <cstring>
#include <thread>

#include "Source/Main/NeuralNetworkMain.h"


using std::thread;


// CNeuralNetworkTrainingToolDlg 대화 상자
class CNeuralNetworkTrainingToolDlg : public CDialogEx
{
// 생성입니다.
public:
	CNeuralNetworkTrainingToolDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEURALNETWORKTRAININGTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	


	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	NeuralNetworkMain	*NN_Main;

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEditEpoch();
	afx_msg void OnEnChangeEditBatchsize();
	afx_msg void OnStnClickedStaticEpoch();
	afx_msg void OnStnClickedStaticEpoch3();
	afx_msg void OnEnChangeEditLearningrate();
	afx_msg void OnEnChangeEditDatafile();
	afx_msg void OnBnClickedDatafileButton();
	afx_msg void OnBnClickedButtonTraining();
	afx_msg void OnStnClickedtraining_TextView();


	CStatic training_TextView;
	CStatic modelRun_TextView;

	CProgressCtrl training_ProgressBar;
	CProgressCtrl modelRun_ProgressBar;

	afx_msg void OnEnChangeEditDatafile2();
	afx_msg void OnBnClickedButtonDatainfo();
	afx_msg void OnNMCustomdrawProgress( NMHDR *pNMHDR, LRESULT *pResult );



	void Training_Thread_Main();
	//static UINT Training_Thread_Main( LPVOID _param );
	void Model_Run_Thread_Main();

	void Message_Handler();

	afx_msg void OnGetMinMaxInfo( MINMAXINFO* lpMMI );

	CRect dialogFrameSize;
	afx_msg void OnBnClickedCancel();

	bool Create_Model_Save_Folder();

	char c_FolderPath[ 512 ] = { 0 };
	CString s_FolderPath;
	CString modelSavePath;
	afx_msg void OnStnClickedStaticDatafile3();
	afx_msg void OnBnClickedButtonModelsave();

	bool runningResult;
	bool Running_Exception_Error();

	bool Running_Quit();
	
	void Activation_View();
	void Deactivation_View();
	afx_msg void OnBnClickedButtonPredictdatalist();
	afx_msg void OnBnClickedButtonPredictdatainfo();
	afx_msg void OnBnClickedButtonModelload();
	afx_msg void OnBnClickedButtonModelrun();
};
