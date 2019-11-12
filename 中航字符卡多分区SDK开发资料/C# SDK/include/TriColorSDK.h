#ifndef __ZH_TRICOLOR_SDK_H__
#define __ZH_TRICOLOR_SDK_H__

#ifdef TRICOLORSDK_EXPORTS
#define TRICOLORSDK_EXPORT_API __declspec(dllexport)
#else
#define TRICOLORSDK_EXPORT_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define TRICOLORSDK_CALLTYPE __cdecl

//�����豸�Ĳ����Ļص�֪ͨ��������
//uDeviceID, �豸��ID���߼��ϵ�ID����ʵ���豸û�й�ϵ
//pNotifiedData, ֪ͨ�ľ������ݣ������û���ͬ�������صĲ�����ͬ����
//uCommand������ǰ������������
//pUserParam�������û����ݲ�������ע���豸��SDK�а󶨵��û�����
typedef void(TRICOLORSDK_CALLTYPE *OnDeviceNotify)(unsigned int uDeviceId, void* pNotifiedData, unsigned int uCommand, void* pUserParam);

namespace ZHSDK_TRICOLOR
{
	enum TEXT_ENCODE_MODE
	{
		TEXT_ENCODE_NONE=-1,
		TEXT_ENCODE_UNICODE=0,
		TEXT_ENCODE_GB2312=1
	};

	enum TEXT_COLOR_TYPE
	{
		TEXT_COLOR_NONE,
		TEXT_COLOR_RED=1,
		TEXT_COLOR_GREEN=2,
		TEXT_COLOR_YELLOW=3,
		TEXT_COLOR_BLUE=4,
		TEXT_COLOR_PURPLE=5,
		TEXT_COLOR_CYAN=6,
		TEXT_COLOR_WHITE=7,
		TEXT_COLOR_MAXVALUE
	};

	enum LIGHTNESS_VALUE
	{
		LIGHTNESS_NONE,
		LIGHTNESS_MINVALUE= 1,
		LIGHTNESS_MAXVALUE= 15
	};

	//��ȡ��ǰSDK�İ汾��
	//�������汾���������汾�ʹΰ汾���Լ�С�汾���ĸ��ֽ���϶���
	//	   MajorVersion.MinorVersion.SubVersion.ReservedVersion
	//MajorVersion����24λ��32λ
	//MinorVersion����16λ��24λ
	//SubVersion��  ��8λ��16λ
	unsigned int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE GetVersion();

	//��ʼ��
	//��������ʼ����ǰ��������
	//������sIp ���ع������õ�IP��ַ����ʽΪxxx.xxx.xxx.xxx
	//	   uPort ���ع���ģʽʱ���õ�Port
	//	   uHeartBeatTimeout ���ع���ģʽʱ��������� ms
	//	   sDeviceType ���ع���ģʽʱ���˵��豸����
	
	//[****�ر�ע��****]
	//�ú������������з�������֮ǰ����
	//��ǰ�汾��Init�������в�������Ч��
	//��ǰ�汾��IP��ַ�Ͷ˿ڣ������Ϸ���У�飬�ⲿ��������֤����Ч��
	
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE Init(const char* sIp = NULL,
									unsigned short uPort=60000, 
									unsigned int uHeartBeatTimeout=10000, 
									const char* sDeviceType="ZH_E8L");
	//����豸���豸�б�
	//���������һ̨�豸��Ϣ���豸�б����ڸ��¸��豸����Ϣ����ʵ���豸������, �����ٸ��豸��״̬
	//������sIp �豸��IP��ַ ��ʽΪxxx.xxx.xxx.xxx
	//	   uPort �豸��Port��
	//     OnDeviceNotify �����豸״̬�仯�Ļص�����
	//	   pUserParam �ص�����ʱ���û��Զ������
	//����ֵ�� �豸�߼�ID�ţ�0Ϊʧ�ܣ�����Ϊ�ɹ�
	//ע�⣺�����豸�Ľ����
	//     ��ǰ�����첽֪ͨ��ʽ�������������ͨ���ص�������֪ͨ������
	//[****�ر�ע��****]
	//��ǰ�汾��Init�������в�������Ч��
	//��ǰ�汾��IP��ַ�Ͷ˿ڣ������Ϸ���У�飬�ⲿ��������֤����Ч��
	unsigned int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE RegisterDevice(const char* sIp,
												       unsigned int uPort, 
													   OnDeviceNotify fNotify=NULL, 
													   void* pUserParam=NULL);
	//ɾ�����豸�б���ɾ��һ̨�豸���Ͽ���ʵ���豸������
	//����: uDevId �豸ID��
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE UnregisterDevice(unsigned int uDevId);

	//����һ̨�豸��
	//ʵ�ʵ����ɹ���
	//����: uDevId �豸ID��
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE OpenDevice(unsigned int uDevId);

	//Ϩ��һ̨�豸��
	//ʵ�ʵ����ɹ��������豸ע�᷽ʽȷ�� 
	//����: uDevId �豸ID��
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE CloseDevice(unsigned int uDevId);

	//Ϩ��һ̨�豸��
	//ʵ�ʵ����ɹ��������豸ע�᷽ʽȷ�� 
	//����: uDevId �豸ID��
	//	    uLightnessValue ����ֵ, 
	//		ȡֵ��ΧΪ[LIGHTNESS_MINVALUE, LIGHTNESS_MAXVALUE]��������ʵ���豸�����������
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE SetDeviceLightness(unsigned int uDevId,
												  unsigned int uLightnessValue);

	//��ʾָ���豸�ļ�����������
	//����: uDevId �豸ID��
	//	    uEncodeMode ���õı��뷽ʽ
	//		����֧�����ֱ��뷽ʽ��[TEXT_ENCODE_UNICODE, TEXT_ENCODE_GB2312],����Ҫ��Ӳ����֧����������
	//	    uColor �ı���Ϣ���õ���ɫ ȡֵ��ΧΪ[TEXT_COLOR_TYPE], �����ʵ���豸֧���������
	//		pText ��Ҫ��ʾ���ı����ݣ�����unicode�����ʽ
	//      uField �ַ����ڷ�������ΧΪ[0, 65535]
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE ShowInstantText(unsigned int  uDevId,
												unsigned int  uEncodeMode,
												unsigned int  uColor, 
												const wchar_t * pText,
												unsigned int uField = 0);
	//ɾ��ָ���豸�ļ�����������
	//����: uDevId �豸ID��
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE HideInstantText(unsigned int  uDevId,
											   unsigned int uField = 0);

	//����ָ���豸��ָ����������������
	//����: uDevId �豸ID��
	//      uStringIndex ���ڴ洢���豸���߼����к�,������ʵ���豸֧�ֵ����Χ����
	//	    uEncodeMode ���õı��뷽ʽ
	//		����֧�����ֱ��뷽ʽ��[TEXT_ENCODE_UNICODE, TEXT_ENCODE_GB2312],����Ҫ��Ӳ����֧����������
	//	    uColor �ı���Ϣ���õ���ɫ ȡֵ��ΧΪ[TEXT_COLOR_TYPE], �����ʵ���豸֧���������
	//		pText ��Ҫ��ʾ���ı����ݣ�����unicode�����ʽ
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE UpdateDeviceText(unsigned int  uDevId,
												unsigned int  uStringIndex,
												unsigned int  uEncodeMode,
												unsigned int  uColor,
												const wchar_t* pText,
												unsigned int uField = 0);
	//�л���ָ���豸��ָ�����������ֲ���ʾ
	//����: uDevId �豸ID��
	//      uStringIndex ���ڴ洢���豸���߼����к�,������ʵ���豸֧�ֵ����Χ����
	//      uField �ַ����ڷ�������ΧΪ[0, 65535]
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE SwitchDeviceText(unsigned int uDevId,
												int StringIndex,
												unsigned int uField = 0);

	//ɾ��ָ���豸�е�ָ������������
	//����: uDevId �豸ID��
	//      uStringIndex ���ڴ洢���豸���߼����к�,������ʵ���豸֧�ֵ����Χ����
	//      uField �ַ����ڷ�������ΧΪ[0, 65535]
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE DeleteDeviceText(unsigned int uDevId,
												unsigned int uStringIndex,
												unsigned int uField = 0);
	//����ʼ��
	//�������ͷ����е�ǰʹ�õ�ϵͳ��Դ
	//�÷�������֮�����з����ĵ��ö���ʧ��[Init����]
	//����ֵ��1���ɹ�
	//       0: ʧ��
	int TRICOLORSDK_EXPORT_API TRICOLORSDK_CALLTYPE DeInit();
}

#ifdef __cplusplus
}
#endif

#endif