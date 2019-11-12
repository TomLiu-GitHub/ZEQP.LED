
// demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "demo.h"
#include "demoDlg.h"
#include "afxdialogex.h"

#include "TriColorSDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace ZHSDK_TRICOLOR;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdemoDlg �Ի���

#define WM_DEVICENOTIFY WM_USER+1000

CdemoDlg::CdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CdemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstDevices);
}

BEGIN_MESSAGE_MAP(CdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADDDEVICE, &CdemoDlg::OnBnClickedButtonAdddevice)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CdemoDlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_DEINIT, &CdemoDlg::OnBnClickedButtonDeinit)
	ON_BN_CLICKED(IDC_BUTTON_SHOWINSTANT, &CdemoDlg::OnBnClickedButtonShowinstant)
	ON_BN_CLICKED(IDC_BUTTON_HIDEINSTANT, &CdemoDlg::OnBnClickedButtonHideinstant)
	ON_BN_CLICKED(IDC_BUTTON_UPDATETEXT, &CdemoDlg::OnBnClickedButtonUpdatetext)
	ON_BN_CLICKED(IDC_BUTTON_DELTEXT, &CdemoDlg::OnBnClickedButtonDeltext)
	ON_BN_CLICKED(IDC_BUTTON_PREVTEXT, &CdemoDlg::OnBnClickedButtonPrevtext)
	ON_BN_CLICKED(IDC_BUTTON_NEXTTEXT, &CdemoDlg::OnBnClickedButtonNexttext)
	ON_BN_CLICKED(IDC_BUTTON_SWITCHTEXT, &CdemoDlg::OnBnClickedButtonSwitchtext)
	ON_BN_CLICKED(IDC_BUTTON_DELDEVICE, &CdemoDlg::OnBnClickedButtonDeldevice)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CdemoDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON_OPENDEVICE, &CdemoDlg::OnBnClickedButtonOpendevice)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEDEVICE, &CdemoDlg::OnBnClickedButtonClosedevice)
	ON_BN_CLICKED(IDC_BUTTON_LIGHTNESS, &CdemoDlg::OnBnClickedButtonLightness)
	ON_MESSAGE(WM_DEVICENOTIFY, OnDeviceMessage)
END_MESSAGE_MAP()


// CdemoDlg ��Ϣ�������

BOOL CdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	InitGUI();

	CString sVersion;
	sVersion.Format(_T("SDK[%d.%d.%d]\r\n"), 
		((ZHSDK_TRICOLOR::GetVersion() >> 24) & 0xFF), 
		((ZHSDK_TRICOLOR::GetVersion() >> 16) & 0xFF),
		((ZHSDK_TRICOLOR::GetVersion() >> 8)) & 0xFF);
	OutputDebugString(sVersion);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString TranslateAction(unsigned int uOper)
{
	switch (uOper)
	{
	case 0x21:
		return _T("����Ļ");
	case 0x22:
		return _T("�ر���Ļ");
	case 0x24:
		return _T("��������");
	case 0x29:
		return _T("�����ı�");
	case 0x2A:
		return _T("ɾ���ı�");
	case 0x3F:
		return _T("�л��ı�");
	default:
		return _T("δ֪����");
	}
	return _T("�ղ���");
}
void CdemoDlg::OnDeviceNotify(unsigned int uDeviceId, void* pNotifiedData, unsigned int uOper, void* pUserParam)
{
	CdemoDlg* pDlg = (CdemoDlg*)pUserParam;
	if (pDlg == NULL) return;

	CString sLog;
	if (uOper == 0)
	{
		pDlg->PostMessage(WM_DEVICENOTIFY, uDeviceId, (LPARAM)pNotifiedData);

		sLog.Format(_T("deviceid[%d], %s\r\n"), uDeviceId, pNotifiedData == NULL ? _T("disconnected!") : _T("connected!"));		
	}
	else
	{
		sLog.Format(_T("deviceid[%d] action[%s], %s\r\n"), uDeviceId, TranslateAction(uOper), pNotifiedData == NULL ? _T("failed!") : _T("success!"));
	}

	OutputDebugString(sLog);
}

LRESULT CdemoDlg::OnDeviceMessage(WPARAM wparam, LPARAM lparam)
{
	int row = m_lstDevices.GetItemCount();
	for (int i = 0; i < row; i++)
	{
		unsigned int dwId = m_lstDevices.GetItemData(i);
		if (dwId == wparam)
		{
			m_lstDevices.SetItemText(i, 3, ((lparam == NULL) ? _T("�Ͽ�") : _T("����")));
			break;
		}
	}
	return 0;
}

void CdemoDlg::InitGUI()
{
	//��listctrl
	DWORD dwStyle = m_lstDevices.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_FULLROWSELECT;//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_SINGLEROW;
	m_lstDevices.SetExtendedStyle(dwStyle); //������չ���
	m_lstDevices.InsertColumn(0, _T("���"), LVCFMT_RIGHT, 30);
	m_lstDevices.InsertColumn(1, _T("��ַ"), LVCFMT_LEFT, 100);
	m_lstDevices.InsertColumn(2, _T("�˿�"), LVCFMT_RIGHT, 50);
	m_lstDevices.InsertColumn(3, _T("״̬"), LVCFMT_RIGHT, 50);
	m_lstDevices.InsertColumn(4, _T("ID"), LVCFMT_RIGHT, 30);

	((CButton*)GetDlgItem(IDC_BUTTON_INIT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DEINIT))->EnableWindow(FALSE);

	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_ENCODE))->InsertString(0, _T("UNICODE"));
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_ENCODE))->SetItemData(0, TEXT_ENCODE_UNICODE);
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_ENCODE))->InsertString(1, _T("GB2312"));
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_ENCODE))->SetItemData(1, TEXT_ENCODE_GB2312);
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_ENCODE))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTENCODE))->InsertString(0, _T("UNICODE"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTENCODE))->SetItemData(0, TEXT_ENCODE_UNICODE);
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTENCODE))->InsertString(1, _T("GB2312"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTENCODE))->SetItemData(1, TEXT_ENCODE_GB2312);
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTENCODE))->SetCurSel(0);


	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->InsertString(0, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->SetItemData(0, TEXT_COLOR_RED);
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->InsertString(1, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->SetItemData(1, TEXT_COLOR_GREEN);

	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->InsertString(2, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->SetItemData(2, TEXT_COLOR_YELLOW);
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->InsertString(3, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->SetItemData(3, TEXT_COLOR_BLUE);

	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->InsertString(4, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->SetItemData(4, TEXT_COLOR_PURPLE);
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->InsertString(5, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->SetItemData(5, TEXT_COLOR_CYAN);
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->InsertString(6, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->SetItemData(6, TEXT_COLOR_WHITE);
	((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->SetCurSel(0);


	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->InsertString(0, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->SetItemData(0, TEXT_COLOR_RED);
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->InsertString(1, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->SetItemData(1, TEXT_COLOR_GREEN);

	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->InsertString(2, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->SetItemData(2, TEXT_COLOR_YELLOW);
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->InsertString(3, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->SetItemData(3, TEXT_COLOR_BLUE);

	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->InsertString(4, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->SetItemData(4, TEXT_COLOR_PURPLE);
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->InsertString(5, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->SetItemData(5, TEXT_COLOR_CYAN);
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->InsertString(6, _T("��ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->SetItemData(6, TEXT_COLOR_WHITE);
	((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->SetCurSel(0);

	SetDlgItemText(IDC_EDIT_DEVICEIP, _T("192.168.11.10"));
	SetDlgItemText(IDC_EDIT_DEVICEPORT, _T("58258"));

	SetDlgItemText(IDC_EDIT_TEXTFIELD, _T("0"));
}

void CdemoDlg::CalcListCtrlLineNumber(CListCtrl* pCtrl)
{
	for (int i = 0; i < pCtrl->GetItemCount(); i++)
	{
		CString sLineNumber;
		sLineNumber.Format(_T("%d"), i + 1);

		pCtrl->SetItemText(i, 0, sLineNumber);
	}
}

void CdemoDlg::OnBnClickedButtonAdddevice()
{
	CString sDeviceIp, sDevicePort;
	
	GetDlgItemText(IDC_EDIT_DEVICEIP, sDeviceIp);
	GetDlgItemText(IDC_EDIT_DEVICEPORT, sDevicePort);
	sDeviceIp.Trim(); sDevicePort.Trim();

	int isFound = 0;
	int row = m_lstDevices.GetItemCount();
	for (int i = 0; i < row; i++)
	{
		CString sIP, sPort;
		sIP = m_lstDevices.GetItemText(i, 1);
		sPort = m_lstDevices.GetItemText(i, 2);

		if (sIP == sDeviceIp && sPort == sDevicePort)
		{
			isFound = 1;
			break;
		}
	}
	if (isFound) return;

	unsigned int uDevId = 0;
	if ((uDevId=ZHSDK_TRICOLOR::RegisterDevice(CStringA(sDeviceIp), _ttoi(sDevicePort), OnDeviceNotify, this)) != 0)
	{
		m_lstDevices.InsertItem(row, _T(""));
		m_lstDevices.SetItemText(row, 1, sDeviceIp);
		m_lstDevices.SetItemText(row, 2, sDevicePort);
		m_lstDevices.SetItemText(row, 3, _T("�Ͽ�"));

		CString ID;
		ID.Format(_T("%d"), uDevId);
		m_lstDevices.SetItemText(row, 4, ID);

		m_lstDevices.SetItemData(row, uDevId);

		CalcListCtrlLineNumber(&m_lstDevices);

		m_uCurrentDeviceID = uDevId;
	}
}

void CdemoDlg::OnBnClickedButtonDeldevice()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int isFound = 0;
	int row = m_lstDevices.GetItemCount();
	for (int i = 0; i < row; i++)
	{
		CString sIP, sPort;
		sIP = m_lstDevices.GetItemText(i, 1);
		sPort = m_lstDevices.GetItemText(i, 2);

		if (m_sCurrentDeviceIP.GetLength() && m_sCurrentDevicePort.GetLength())
		{
			if (sIP == m_sCurrentDeviceIP && sPort == m_sCurrentDevicePort)
			{
				m_uCurrentDeviceID = (unsigned int)m_lstDevices.GetItemData(i);
				m_lstDevices.DeleteItem(i);
				isFound = 1;
				break;
			}
		}
		else if (m_uCurrentDeviceID != 0)
		{
			if ((unsigned int)m_lstDevices.GetItemData(i) == m_uCurrentDeviceID)
			{
				m_lstDevices.DeleteItem(i);
				isFound = 1;
				break;
			}
		}
		
	}
	if (isFound)
	{
		ZHSDK_TRICOLOR::UnregisterDevice(m_uCurrentDeviceID);

		SetDlgItemText(IDC_EDIT_DEVICEIP, _T(""));
		SetDlgItemText(IDC_EDIT_DEVICEPORT, _T(""));
	}

	m_uCurrentDeviceID = 0;
	m_sCurrentDeviceIP = _T("");
	m_sCurrentDevicePort = _T("");
}

void CdemoDlg::OnBnClickedButtonInit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sIP, sPort, sDeviceType;
	
	GetDlgItemText(IDC_EDIT_LOCALIP, sIP);
	GetDlgItemText(IDC_EDIT_PORT, sPort);
	GetDlgItemText(IDC_EDIT_DEVICETYPE, sDeviceType);

	sIP.Trim(); sPort.Trim(); sDeviceType.Trim();
	if (ZHSDK_TRICOLOR::Init(CStringA(sIP), _ttoi(sPort), 5000, CStringA(sDeviceType)) > 0)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_INIT))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_DEINIT))->EnableWindow(TRUE);
	}
}

void CdemoDlg::OnBnClickedButtonDeinit()
{
	ZHSDK_TRICOLOR::DeInit();

	((CButton*)GetDlgItem(IDC_BUTTON_INIT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DEINIT))->EnableWindow(FALSE);
}


void CdemoDlg::OnBnClickedButtonOpendevice()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::OpenDevice(m_uCurrentDeviceID);
	}
}

void CdemoDlg::OnBnClickedButtonClosedevice()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::CloseDevice(m_uCurrentDeviceID);
	}
}

void CdemoDlg::OnBnClickedButtonShowinstant()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sText;
	GetDlgItemText(IDC_EDIT_INSTANTTEXT, sText);
	if (sText.Trim().GetLength() == 0) return;

	CString sField;
	GetDlgItemText(IDC_EDIT_TEXTFIELD, sField);
	if (sField.Trim().GetLength() == 0) return;

	int iRow = 0;
	unsigned int uColor=0;	
	iRow = ((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->GetCurSel();
	uColor = ((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_COLOR))->GetItemData(iRow);

	unsigned int uEncoder = 0;
	iRow = ((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_ENCODE))->GetCurSel();
	uEncoder = ((CComboBox*)GetDlgItem(IDC_COMBO_INSTANTTEXT_ENCODE))->GetItemData(iRow);
	
	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::ShowInstantText(m_uCurrentDeviceID, uEncoder, uColor, sText, _ttoi(sField));
	}
}

void CdemoDlg::OnBnClickedButtonHideinstant()
{
	CString sField;
	GetDlgItemText(IDC_EDIT_TEXTFIELD, sField);
	if (sField.Trim().GetLength() == 0) return;

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::HideInstantText(m_uCurrentDeviceID, _ttoi(sField));
	}
}

void CdemoDlg::OnBnClickedButtonUpdatetext()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sTextIndex;
	GetDlgItemText(IDC_EDIT_TEXTINDEX, sTextIndex);
	if (sTextIndex.Trim().GetLength() == 0) return;

	CString sText;
	GetDlgItemText(IDC_EDIT_TEXT, sText);
	if (sText.Trim().GetLength() == 0) return;

	CString sField;
	GetDlgItemText(IDC_EDIT_TEXTFIELD, sField);
	if (sField.Trim().GetLength() == 0) return;

	int iRow = 0;
	unsigned int uColor = 0;
	iRow = ((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->GetCurSel();
	uColor = ((CComboBox*)GetDlgItem(IDC_COMBO_TEXTCOLOR))->GetItemData(iRow);

	unsigned int uEncoder = 0;
	iRow = ((CComboBox*)GetDlgItem(IDC_COMBO_TEXTENCODE))->GetCurSel();
	uEncoder = ((CComboBox*)GetDlgItem(IDC_COMBO_TEXTENCODE))->GetItemData(iRow);

	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::UpdateDeviceText(m_uCurrentDeviceID, _ttol(sTextIndex), uEncoder, uColor, sText, _ttoi(sField));
	}
}

void CdemoDlg::OnBnClickedButtonDeltext()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sIndex;
	GetDlgItemText(IDC_EDIT_TEXTINDEX, sIndex);
	if (sIndex.Trim().GetLength() == 0) return;

	CString sField;
	GetDlgItemText(IDC_EDIT_TEXTFIELD, sField);
	if (sField.Trim().GetLength() == 0) return;

	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::DeleteDeviceText(m_uCurrentDeviceID, _ttol(sIndex), _ttoi(sField));
	}
}

void CdemoDlg::OnBnClickedButtonPrevtext()
{
	CString sField;
	GetDlgItemText(IDC_EDIT_TEXTFIELD, sField);
	if (sField.Trim().GetLength() == 0) return;

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::SwitchDeviceText(m_uCurrentDeviceID, -2, _ttoi(sField));
	}
}

void CdemoDlg::OnBnClickedButtonNexttext()
{
	CString sField;
	GetDlgItemText(IDC_EDIT_TEXTFIELD, sField);
	if (sField.Trim().GetLength() == 0) return;

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::SwitchDeviceText(m_uCurrentDeviceID, -1, _ttoi(sField));
	}
}

void CdemoDlg::OnBnClickedButtonSwitchtext()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sIndex;
	GetDlgItemText(IDC_EDIT_SWITCH_TEXTINDEX, sIndex);
	if (sIndex.Trim().GetLength() == 0) return;

	CString sField;
	GetDlgItemText(IDC_EDIT_TEXTFIELD, sField);
	if (sField.Trim().GetLength() == 0) return;

	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::SwitchDeviceText(m_uCurrentDeviceID, _ttol(sIndex), _ttoi(sField));
	}
}


void CdemoDlg::OnBnClickedButtonLightness()
{
	CString sValue;
	GetDlgItemText(IDC_EDIT_LIGHTNESS, sValue);
	if (sValue.Trim().GetLength() == 0) return;

	if (m_uCurrentDeviceID != 0)
	{
		ZHSDK_TRICOLOR::SetDeviceLightness(m_uCurrentDeviceID, _ttol(sValue));
	}
}


void CdemoDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView->iItem != -1)
	{
		m_sCurrentDeviceIP = m_lstDevices.GetItemText(pNMListView->iItem, 1);
		m_sCurrentDevicePort = m_lstDevices.GetItemText(pNMListView->iItem, 2);
		m_uCurrentDeviceID = (unsigned int)m_lstDevices.GetItemData(pNMListView->iItem);
		
		SetDlgItemText(IDC_EDIT_DEVICEIP, m_sCurrentDeviceIP);
		SetDlgItemText(IDC_EDIT_DEVICEPORT, m_sCurrentDevicePort);
	}

	*pResult = 0;
}
