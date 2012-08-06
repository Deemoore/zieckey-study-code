#include "stdafx.h"
#include <weiboapi.h>
#include "ApiType.h"

CApiType::CApiType()
{

	InitApiTypeList();
	InitDefaultParamList();
}

CApiType::~CApiType()
{

}

void CApiType::InitApiTypeList()
{
	//clear the vector firstly

	const WCHAR typelist[TXWB_MAX][64]=
	{
		L"",
		L"ʱ������أ���ʱ����",
		L"ʱ������أ��㲥����ʱ����",
		L"ʱ������أ������û�����ʱ����",
		L"ʱ������أ��û��ἰʱ����",
		L"ʱ������أ�����ʱ����",
		L"ʱ������أ��ҷ���ʱ����",
		L"ʱ������أ��ر��������˷���ʱ����",
		L"ʱ������أ���������ʱ����",
		L"ʱ������أ���ҳʱ��������",
		L"ʱ������أ������û�����ʱ��������",
		L"ʱ������أ��ҷ���ʱ��������",
		L"ʱ������أ��û��ἰʱ��������",
		L"ʱ������أ����û�ʱ����",
		L"ʱ������أ����û�ʱ��������",
		//=14
		
		L"΢����أ���ȡһ��΢������",
		L"΢����أ�����һ��΢��",
		L"΢����أ�ɾ��һ��΢��",
		L"΢����أ�ת��һ��΢��",
		L"΢����أ��ظ�һ��΢��",
		L"΢����أ�����һ����ͼ��΢��",
		L"΢����أ�ת�����������",
		L"΢����أ���ȡ����΢����ת��������б�",
		L"΢����أ�����һ��΢��",
		L"΢����أ���������΢��",
		L"΢����أ�������Ƶ΢��",
		L"΢����أ���ȡ��Ƶ��Ϣ",
		L"΢����أ�����ID������ȡ΢������",
		L"΢����أ�Ԥ����һ����Ƶ΢��",
		//=28

		L"�˻���أ���ȡ�Լ�����ϸ��Ϣ",
		L"�˻���أ������û���Ϣ",
		L"�˻���أ������û�ͷ����Ϣ",
		L"�˻���أ������û�������Ϣ",
		L"�˻���أ���ȡ����������",
		L"�˻���أ���ȡһ���˵ļ�����",
		
		//33
				
		
		L"��ϵ����أ��ҵ������б�",
		L"��ϵ����أ��ҵ��������б�",
		L"��ϵ����أ��������б�",
		L"��ϵ����أ��ر������б�",
		L"��ϵ����أ�����ĳ���û�",
		L"��ϵ����أ�ȡ������ĳ���û�",
		L"��ϵ����أ��ر�����ĳ���û�",
		L"��ϵ����أ�ȡ���ر�����ĳ���û�",
		L"��ϵ����أ����ĳ���û���������",
		L"��ϵ����أ��Ӻ�������ɾ��ĳ���û�",
		L"��ϵ����أ�����Ƿ����ҵ����ڻ���������",
		L"��ϵ����أ������˻������б�",
		L"��ϵ����أ������˻����������б�",
		L"��ϵ����أ������˻��ر����������б�",
		L"��ϵ����أ��ҵķ�˿�б�����Ϣ��200����",
		L"��ϵ����أ��ҵ�ż���б�����Ϣ��200����",
		
		//49

		
		L"˽����أ���˽��",
		L"˽����أ�ɾ��һ��˽��",
		L"˽����أ��ռ���",
		L"˽����أ�������",
		//53


		L"������أ������û�",
		L"������أ�����΢��",
		L"������أ�ͨ����ǩ�����û�",
		//56


		L"�ȶ�,���ƣ������Ȱ�",
		L"�ȶ�,���ƣ�ת���Ȱ�",
		//58
		
		
		L"���ݸ�����أ��鿴���ݸ�������",
		//59


		L"�����ղأ��ղ�һ��΢��",
		L"�����ղأ����ղ�ɾ��һ��΢��",
		L"�����ղأ��ղص�΢���б�",
		L"�����ղأ����ⶩ��",
		L"�����ղأ����ղ�ɾ������",
		L"�����ղأ���ȡ�Ѷ��Ļ����б�",
		//65


		L"������أ����ݻ������Ʋ�ѯ����ID",
		L"������أ����ݻ���ID��ȡ�������΢��",
		//67
		
		
		L"��ǩ��أ���ӱ�ǩ",
		L"��ǩ��أ�ɾ����ǩ",
		//69
		
		
		L"�������ҿ�����ʶ����",
		L"��������URL�䳤URL",
		L"��������ȡ��Ƶ�ϴ���key"
		//72

				
	};

	int i = 0;
	for(i=1;i<TXWB_MAX;++i)
	{
		m_apiTypeNameList[i] = typelist[i];
	}
}

void CApiType::InitDefaultParamList()
{
#define MAKESTRPAIR(s1,s2)  std::make_pair<std::wstring,std::wstring>(s1,s2)
	 const paramKeyValuePair defaultlist[TXWB_MAX][10] =
	{
		{
			//nothing , just the base
		},

		{
			//Statuses/home_timeline ��ҳʱ����
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20")
		},

		{
			//Statuses/public_timeline �㲥����ʱ����
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pos",L"0"),
			MAKESTRPAIR(L"reqnum",L"20")
		},

		{
			//Statuses/user_timeline �����û�����ʱ����
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0"),
			MAKESTRPAIR(L"name",L"t")
		},

		{
			//Statuses/mentions_timeline �û��ἰʱ����
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")
		},

		{
			//Statuses/ht_timeline ����ʱ����
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"httext",L"abc"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pageinfo",L""),
			MAKESTRPAIR(L"reqnum",L"20")
		},

		{
			//Statuses/broadcast_timeline �ҷ���ʱ����
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")
		},

		{
			//Statuses/special_timeline �ر��������˷���ʱ����
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			
		 },

		{
			//Statuses/area_timeline ��������ʱ����
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pos",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"country",L""),
			MAKESTRPAIR(L"province",L""),
			MAKESTRPAIR(L"city",L"")
			
		},

		{
			//Statuses/home_timeline_ids ��ҳʱ��������
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20")
				
		},

		{
			//Statuses/user_timeline_ids �����û�����ʱ��������
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")
		 },

		{
			//Statuses/broadcast_timeline_ids �ҷ���ʱ��������
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")

		},

		{
			//Statuses/mentions_timeline_ids �û��ἰʱ��������
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")
		},

		{
			//Statuses/users_timeline ���û�����ʱ����
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0"),
			MAKESTRPAIR(L"names",L"")
		},

		{
			//Statuses/users_timeline_ids ���û�����ʱ��������
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0"),
			MAKESTRPAIR(L"names",L"")
		},

		//΢�����
		{
			//t/show ��ȡһ��΢������
			MAKESTRPAIR(L"format",L"json"),	
			MAKESTRPAIR(L"id",L"12704604231530709392")	
		},

		{
			//t/add ����һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L"")
		},

		{
			//t/del ɾ��һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"12704604231530709392")
		},

		{
			//t/re_add ת��һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"reid",L"123456789")
		},

		{
			//t/reply �ظ�һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"reid",L"123456789")
		},

		{
			//t/add_pic �ظ�һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"pic",L"")
					//MAKESTRPAIR(L"reid",L"123456789")
					//pic  ̫���޷���base_string ���ύ��Ӧ����post��ʽ�����ݸ�ʽ����enctype="multipart/form-data" 
		},


		{
			//t/re_count ɾ��һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"ids",L"12704604231530709392"),
			MAKESTRPAIR(L"flag",L"0")
		},

		{
			//t/re_list �ظ�һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"flag",L"0"),
			MAKESTRPAIR(L"rootid",L"123456789"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"123456789"),
			MAKESTRPAIR(L"twitterid",L"0")
		},
				 
		{
			//t/comment �ظ�һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"reid",L"123456789")		 
		},


		{
			//t/add_music �ظ�һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"url",L"http://url.cn"),
			MAKESTRPAIR(L"reid",L"123456789"),
			MAKESTRPAIR(L"title",L"abc"),
			MAKESTRPAIR(L"author",L"cbd")
		},

		{
			//t/add_video �ظ�һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"url",L"http://url.cn")	
		},

		{
			//t/getvideoinfo �ظ�һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"url",L"http://url.cn")
		},
		{
			//t/list �ظ�һ��΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"ids",L"123456789")
		},
		{
			//t/add_video_prev Ԥ����һ����Ƶ΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"vid",L"12348")
		},

				//////////////////////////////////////////////////////////////////////////
				// �˻����
		{
			//user/info ��ȡ�û���Ϣ
			MAKESTRPAIR(L"format",L"json")		
		},

		{
			//user/update �����û���Ϣ
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"nick",L"pao"),
			MAKESTRPAIR(L"sex",L"1"),
			MAKESTRPAIR(L"year",L"2000"),
			MAKESTRPAIR(L"month",L"1"),
			MAKESTRPAIR(L"day",L"1"),
			MAKESTRPAIR(L"countrycode",L""),
			MAKESTRPAIR(L"citycode",L""),
			MAKESTRPAIR(L"provincecode",L""),
			MAKESTRPAIR(L"introduction",L"xxxxx")
		},

		{
			//user/update_head �����û�ͷ����Ϣ
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pic",L"")
			//pic �ֶΣ����ܷ���ǩ�������У�����������������post����
		},

		{
			//user/update_edu ���½�����Ϣ
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"feildid",L"1"),
			MAKESTRPAIR(L"year",L"2009"),
			MAKESTRPAIR(L"schoolid",L"0"),
			MAKESTRPAIR(L"departmentid",L"0"),
			MAKESTRPAIR(L"level",L"0")
		},

		{
			//user/other_info ��ȡ����������
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"name",L"abc")
		},

		{
			//user/infos ��ȡ����������
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"names",L"abc,efg")
		},


				  //////////////////////////////////////////////////////////////////////////
	 //��ϵ�����
	{
		//friends/fanslist �ҵ������б� 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0"),
	},
  
	{
		//friends/idollist �ҵ����������б�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")	 
	},

	{
		//Friends/blacklist �������б�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")
	}, 

	{						  
		//Friends/speciallist �ر������б�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")
	},

	{
		//friends/add ����ĳ���û�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/delȡ������ĳ���û� 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/addspecial �ر�����ĳ���û�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/delspecial ȡ���ر�����ĳ���û�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/addblacklist ���ĳ���û���������
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/delblacklist �Ӻ�������ɾ��ĳ���û�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/check ����Ƿ������ڻ���������
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"names",L"xxxx,yyyy,zzzz"),
		MAKESTRPAIR(L"flag",L"0")
	},

	{  
		//friends/user_fanslist �����ʻ������б�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/user_idollist �����ʻ����������б� 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/user_speciallist �����ʻ��ر����������б�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0"),
		MAKESTRPAIR(L"name",L"xxxx")
	},
				  
	{
		//Friends/fanslist_s �������б�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")
	}, 

	{
		//Friends/idollist_s �������б�
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")
	}, 

				  //////////////////////////////////////////////////////////////////////////
				 //˽�����
	{
		//private/add ��˽�� 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"content",L"test"),
		MAKESTRPAIR(L"clientip",L"127.0.0.1"),
		MAKESTRPAIR(L"jing",L""),
		MAKESTRPAIR(L"wei",L""),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//private/del ɾ��һ��˽��
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"id",L"123456789")
	},
				
	{
  		//private/recv �ռ��� 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"pageflag",L"0"),
		MAKESTRPAIR(L"pagetime",L"0"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"lastid",L"0")
	},

		{
			//private/send ������ 
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"30"),
			MAKESTRPAIR(L"lastid",L"0")
		},

		//////////////////////////////////////////////////////////////////////////
		//�������
		{
			//Search/user �����û�
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"keyword",L"abc"),
			MAKESTRPAIR(L"pageisize",L"10"),
			MAKESTRPAIR(L"page",L"1")
		},

		{	  
			//Search/t ����΢��
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"keyword",L"abc"),
			MAKESTRPAIR(L"pageisize",L"10"),
			MAKESTRPAIR(L"page",L"1")
		},
		  
		{
			//Search/userbytag �����û�ͨ����ǩ
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"keyword",L"abc"),
			MAKESTRPAIR(L"pageisize",L"10"),
			MAKESTRPAIR(L"page",L"1")
		},

		//////////////////////////////////////////////////////////////////////////
		//�ȶ��������

		{
			 //trends/ht �����Ȱ�
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"type",L"1"),
			MAKESTRPAIR(L"reqnum",L"30"),
			MAKESTRPAIR(L"pos",L"0")
		},

		{
			//Trends/t ת���Ȱ�
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"reqnum",L"30"),
			MAKESTRPAIR(L"pos",L"0")
		 },

		//////////////////////////////////////////////////////////////////////////
		//���ݸ������

		{
			//info/update �鿴���ݸ�������
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"op",L"0"),
			MAKESTRPAIR(L"type",L"5")
		},

		//////////////////////////////////////////////////////////////////////////
		//�����ղ����
		{
			//fav/addt �ղ�һ��΢�� 
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"1234567789")
		},

		{
			//fav/delt ɾ��һ��΢�����ղ�
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"12345667889")
		},

		{
			//fav/list_t �ղص�΢���б�
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"nexttime",L"0"),
			MAKESTRPAIR(L"pretime",L"0"),
			MAKESTRPAIR(L"reqnum",L"30"),
			MAKESTRPAIR(L"lastid",L"0")
		 },

		{
			//fav/addht ���Ļ���
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"123456789")
		},

		{
			//fav/delht ɾ��������ղ�
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"123456789")
		},

		{
			//fav/list_ht �Ѷ��Ļ����б�
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"reqnum",L"15"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"lastid",L"0")
		},



				  //////////////////////////////////////////////////////////////////////////
				  //�������
		{
			//ht/ids ���ݻ����黰��ID
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"httexts",L"abc,efg")
		},

		{
			//ht/info ���ݻ���ID��ȡ���������Ϣ
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"ids",L"12344545,4342356")
		},


				  //////////////////////////////////////////////////////////////////////////
		//��ǩ���
		{
			//tag/add ��ӱ�ǩ
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"tag",L"abc")
		},

		{
			//tag/del ɾ����ǩ
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"tagid",L"123456789")
		},


				  //////////////////////////////////////////////////////////////////////////
		//����
		{	
			//other/kownperson �ҿ�����ʶ����
			MAKESTRPAIR(L"format",L"json")
		},

		{
			//other/shorturl��URL�䳤URL
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"url",L"xxxx")
		},

		{
			//other/videokey ��ȡ��Ƶ�ϴ���KEY
			MAKESTRPAIR(L"format",L"json")
		}
	};

	
	int i  , j;
	for(i = 0; i<TXWB_MAX; ++i)
	{
		m_apiDefaultKeyValuePairList[i].clear();

		for(j = 0; j<10; ++j)
		{
			if(defaultlist[i][j].first ==L"")
			{
				//the following is empty
				break;
			}

			//m_apiDefaultKeyValuePairList[i].push_back((LPCSTR*)defaultlist[i][j].first.c_str(),(LPCSTR*)defaultlist[i][j].second.c_str());
			m_apiDefaultKeyValuePairList[i].push_back(defaultlist[i][j]);
		}
	}

}
