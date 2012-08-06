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
		L"时间线相关：主时间线",
		L"时间线相关：广播大厅时间线",
		L"时间线相关：其他用户发表时间线",
		L"时间线相关：用户提及时间线",
		L"时间线相关：话题时间线",
		L"时间线相关：我发表时间线",
		L"时间线相关：特别收听的人发表时间线",
		L"时间线相关：地区发表时间线",
		L"时间线相关：主页时间线索引",
		L"时间线相关：其他用户发表时间线索引",
		L"时间线相关：我发表时间线索引",
		L"时间线相关：用户提及时间线索引",
		L"时间线相关：多用户时间线",
		L"时间线相关：多用户时间线索引",
		//=14
		
		L"微博相关：获取一条微博数据",
		L"微博相关：发表一条微博",
		L"微博相关：删除一条微博",
		L"微博相关：转播一条微博",
		L"微博相关：回复一条微博",
		L"微博相关：发表一条带图的微博",
		L"微博相关：转播数或点评数",
		L"微博相关：获取单条微博的转发或点评列表",
		L"微博相关：点评一条微博",
		L"微博相关：发表音乐微博",
		L"微博相关：发表视频微博",
		L"微博相关：获取视频信息",
		L"微博相关：根据ID批量获取微博内容",
		L"微博相关：预发表一条视频微博",
		//=28

		L"账户相关：获取自己的详细信息",
		L"账户相关：更新用户信息",
		L"账户相关：更新用户头像信息",
		L"账户相关：更新用户教育信息",
		L"账户相关：获取其他人资料",
		L"账户相关：获取一批人的简单资料",
		
		//33
				
		
		L"关系链相关：我的听众列表",
		L"关系链相关：我的收听人列表",
		L"关系链相关：黑名单列表",
		L"关系链相关：特别收听列表",
		L"关系链相关：收听某个用户",
		L"关系链相关：取消收听某个用户",
		L"关系链相关：特别收听某个用户",
		L"关系链相关：取消特别收听某个用户",
		L"关系链相关：添加某个用户到黑名单",
		L"关系链相关：从黑名单中删除某个用户",
		L"关系链相关：检测是否是我的听众或收听的人",
		L"关系链相关：其他账户听众列表",
		L"关系链相关：其他账户收听的人列表",
		L"关系链相关：其他账户特别收听的人列表",
		L"关系链相关：我的粉丝列表，简单信息（200个）",
		L"关系链相关：我的偶像列表，简单信息（200个）",
		
		//49

		
		L"私信相关：发私信",
		L"私信相关：删除一条私信",
		L"私信相关：收件箱",
		L"私信相关：发件箱",
		//53


		L"搜索相关：搜索用户",
		L"搜索相关：搜索微博",
		L"搜索相关：通过标签搜索用户",
		//56


		L"热度,趋势：话题热榜",
		L"热度,趋势：转播热榜",
		//58
		
		
		L"数据更新相关：查看数据更新条数",
		//59


		L"数据收藏：收藏一条微博",
		L"数据收藏：从收藏删除一条微博",
		L"数据收藏：收藏的微博列表",
		L"数据收藏：话题订阅",
		L"数据收藏：从收藏删除话题",
		L"数据收藏：获取已订阅话题列表",
		//65


		L"话题相关：根据话题名称查询话题ID",
		L"话题相关：根据话题ID获取话题相关微博",
		//67
		
		
		L"标签相关：添加标签",
		L"标签相关：删除标签",
		//69
		
		
		L"其他：我可能认识的人",
		L"其他：短URL变长URL",
		L"其他：获取视频上传的key"
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
			//Statuses/home_timeline 主页时间线
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20")
		},

		{
			//Statuses/public_timeline 广播大厅时间线
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pos",L"0"),
			MAKESTRPAIR(L"reqnum",L"20")
		},

		{
			//Statuses/user_timeline 其他用户发表时间线
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0"),
			MAKESTRPAIR(L"name",L"t")
		},

		{
			//Statuses/mentions_timeline 用户提及时间线
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")
		},

		{
			//Statuses/ht_timeline 话题时间线
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"httext",L"abc"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pageinfo",L""),
			MAKESTRPAIR(L"reqnum",L"20")
		},

		{
			//Statuses/broadcast_timeline 我发表时间线
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")
		},

		{
			//Statuses/special_timeline 特别收听的人发表时间线
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			
		 },

		{
			//Statuses/area_timeline 地区发表时间线
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pos",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"country",L""),
			MAKESTRPAIR(L"province",L""),
			MAKESTRPAIR(L"city",L"")
			
		},

		{
			//Statuses/home_timeline_ids 主页时间线索引
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20")
				
		},

		{
			//Statuses/user_timeline_ids 其他用户发表时间线索引
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")
		 },

		{
			//Statuses/broadcast_timeline_ids 我发表时间线索引
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")

		},

		{
			//Statuses/mentions_timeline_ids 用户提及时间线索引
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0")
		},

		{
			//Statuses/users_timeline 多用户发表时间线
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0"),
			MAKESTRPAIR(L"names",L"")
		},

		{
			//Statuses/users_timeline_ids 多用户发表时间线索引
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"20"),
			MAKESTRPAIR(L"lastid",L"0"),
			MAKESTRPAIR(L"names",L"")
		},

		//微博相关
		{
			//t/show 获取一条微博数据
			MAKESTRPAIR(L"format",L"json"),	
			MAKESTRPAIR(L"id",L"12704604231530709392")	
		},

		{
			//t/add 发表一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L"")
		},

		{
			//t/del 删除一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"12704604231530709392")
		},

		{
			//t/re_add 转播一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"reid",L"123456789")
		},

		{
			//t/reply 回复一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"reid",L"123456789")
		},

		{
			//t/add_pic 回复一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"pic",L"")
					//MAKESTRPAIR(L"reid",L"123456789")
					//pic  太大无法在base_string 中提交，应该以post方式，数据格式采用enctype="multipart/form-data" 
		},


		{
			//t/re_count 删除一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"ids",L"12704604231530709392"),
			MAKESTRPAIR(L"flag",L"0")
		},

		{
			//t/re_list 回复一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"flag",L"0"),
			MAKESTRPAIR(L"rootid",L"123456789"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"123456789"),
			MAKESTRPAIR(L"twitterid",L"0")
		},
				 
		{
			//t/comment 回复一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"reid",L"123456789")		 
		},


		{
			//t/add_music 回复一条微博
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
			//t/add_video 回复一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"url",L"http://url.cn")	
		},

		{
			//t/getvideoinfo 回复一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"url",L"http://url.cn")
		},
		{
			//t/list 回复一条微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"ids",L"123456789")
		},
		{
			//t/add_video_prev 预发表一条视频微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"content",L"test"),
			MAKESTRPAIR(L"clientip",L"127.0.0.1"),
			MAKESTRPAIR(L"jing",L""),
			MAKESTRPAIR(L"wei",L""),
			MAKESTRPAIR(L"vid",L"12348")
		},

				//////////////////////////////////////////////////////////////////////////
				// 账户相关
		{
			//user/info 获取用户信息
			MAKESTRPAIR(L"format",L"json")		
		},

		{
			//user/update 更新用户信息
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
			//user/update_head 更新用户头像信息
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pic",L"")
			//pic 字段，不能放在签名参数中，否则会出错，后面会加在post表单中
		},

		{
			//user/update_edu 更新教育信息
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"feildid",L"1"),
			MAKESTRPAIR(L"year",L"2009"),
			MAKESTRPAIR(L"schoolid",L"0"),
			MAKESTRPAIR(L"departmentid",L"0"),
			MAKESTRPAIR(L"level",L"0")
		},

		{
			//user/other_info 获取其他人资料
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"name",L"abc")
		},

		{
			//user/infos 获取其他人资料
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"names",L"abc,efg")
		},


				  //////////////////////////////////////////////////////////////////////////
	 //关系链相关
	{
		//friends/fanslist 我的听众列表 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0"),
	},
  
	{
		//friends/idollist 我的收听的人列表
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")	 
	},

	{
		//Friends/blacklist 黑名单列表
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")
	}, 

	{						  
		//Friends/speciallist 特别收听列表
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")
	},

	{
		//friends/add 收听某个用户
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/del取消收听某个用户 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/addspecial 特别收听某个用户
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/delspecial 取消特别收听某个用户
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/addblacklist 添加某个用户到黑名单
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/delblacklist 从黑名单中删除某个用户
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/check 检测是否我听众或收听的人
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"names",L"xxxx,yyyy,zzzz"),
		MAKESTRPAIR(L"flag",L"0")
	},

	{  
		//friends/user_fanslist 其他帐户听众列表
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/user_idollist 其他帐户收听的人列表 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0"),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//friends/user_speciallist 其他帐户特别收听的人列表
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0"),
		MAKESTRPAIR(L"name",L"xxxx")
	},
				  
	{
		//Friends/fanslist_s 黑名单列表
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")
	}, 

	{
		//Friends/idollist_s 黑名单列表
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"startindex",L"0")
	}, 

				  //////////////////////////////////////////////////////////////////////////
				 //私信相关
	{
		//private/add 发私信 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"content",L"test"),
		MAKESTRPAIR(L"clientip",L"127.0.0.1"),
		MAKESTRPAIR(L"jing",L""),
		MAKESTRPAIR(L"wei",L""),
		MAKESTRPAIR(L"name",L"xxxx")
	},

	{
		//private/del 删除一条私信
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"id",L"123456789")
	},
				
	{
  		//private/recv 收件箱 
		MAKESTRPAIR(L"format",L"json"),
		MAKESTRPAIR(L"pageflag",L"0"),
		MAKESTRPAIR(L"pagetime",L"0"),
		MAKESTRPAIR(L"reqnum",L"30"),
		MAKESTRPAIR(L"lastid",L"0")
	},

		{
			//private/send 发件箱 
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"reqnum",L"30"),
			MAKESTRPAIR(L"lastid",L"0")
		},

		//////////////////////////////////////////////////////////////////////////
		//搜索相关
		{
			//Search/user 搜索用户
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"keyword",L"abc"),
			MAKESTRPAIR(L"pageisize",L"10"),
			MAKESTRPAIR(L"page",L"1")
		},

		{	  
			//Search/t 搜索微博
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"keyword",L"abc"),
			MAKESTRPAIR(L"pageisize",L"10"),
			MAKESTRPAIR(L"page",L"1")
		},
		  
		{
			//Search/userbytag 搜索用户通过标签
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"keyword",L"abc"),
			MAKESTRPAIR(L"pageisize",L"10"),
			MAKESTRPAIR(L"page",L"1")
		},

		//////////////////////////////////////////////////////////////////////////
		//热度趋势相关

		{
			 //trends/ht 话题热榜
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"type",L"1"),
			MAKESTRPAIR(L"reqnum",L"30"),
			MAKESTRPAIR(L"pos",L"0")
		},

		{
			//Trends/t 转播热榜
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"reqnum",L"30"),
			MAKESTRPAIR(L"pos",L"0")
		 },

		//////////////////////////////////////////////////////////////////////////
		//数据更新相关

		{
			//info/update 查看数据更新条数
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"op",L"0"),
			MAKESTRPAIR(L"type",L"5")
		},

		//////////////////////////////////////////////////////////////////////////
		//数据收藏相关
		{
			//fav/addt 收藏一条微博 
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"1234567789")
		},

		{
			//fav/delt 删除一条微博从收藏
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"12345667889")
		},

		{
			//fav/list_t 收藏的微博列表
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"nexttime",L"0"),
			MAKESTRPAIR(L"pretime",L"0"),
			MAKESTRPAIR(L"reqnum",L"30"),
			MAKESTRPAIR(L"lastid",L"0")
		 },

		{
			//fav/addht 订阅话题
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"123456789")
		},

		{
			//fav/delht 删除话题从收藏
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"id",L"123456789")
		},

		{
			//fav/list_ht 已订阅话题列表
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"reqnum",L"15"),
			MAKESTRPAIR(L"pageflag",L"0"),
			MAKESTRPAIR(L"pagetime",L"0"),
			MAKESTRPAIR(L"lastid",L"0")
		},



				  //////////////////////////////////////////////////////////////////////////
				  //话题相关
		{
			//ht/ids 根据话名查话题ID
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"httexts",L"abc,efg")
		},

		{
			//ht/info 根据话题ID获取话题相关信息
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"ids",L"12344545,4342356")
		},


				  //////////////////////////////////////////////////////////////////////////
		//标签相关
		{
			//tag/add 添加标签
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"tag",L"abc")
		},

		{
			//tag/del 删除标签
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"tagid",L"123456789")
		},


				  //////////////////////////////////////////////////////////////////////////
		//其他
		{	
			//other/kownperson 我可能认识的人
			MAKESTRPAIR(L"format",L"json")
		},

		{
			//other/shorturl短URL变长URL
			MAKESTRPAIR(L"format",L"json"),
			MAKESTRPAIR(L"url",L"xxxx")
		},

		{
			//other/videokey 获取视频上传的KEY
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
