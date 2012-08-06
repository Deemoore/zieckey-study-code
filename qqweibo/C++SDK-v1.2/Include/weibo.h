
#ifndef __TXWB_WEIBO__
#define __TXWB_WEIBO__

#include "WeiboApi.h"


//////////////////////////////////////////////////////////////////////////
//此头文件中的接口是对WeiboApi.h 中的接口的包装，这些接口定义于Txweibo 域
//使用说明：例如Statuses/home_timeline 主页时间线的接口是Txweibo::statuses::home_timeline()
//以域名间隔后面两个单词，最后一个是函数名。
//
//////////////////////////////////////////////////////////////////////////
namespace TXWeibo
{

	namespace  status
	{
		inline HTTP_RESULTCODE  home_timeline(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_HOME_TL, oQWBlogParam, pResultData, nLen);
			}
		
		inline HTTP_RESULTCODE  public_timeline(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_PUBLIC_TL, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  home_timeline(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_USER_TL, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  mentions_timeline(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_MENTIONS_TL, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  ht_timeline(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_HT_TL, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  broadcast_timeline(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_BROADCASET_TL, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  special_timeline(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_SPECIAL_TL, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  area_timeline(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_AREA_TL, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  home_timeline_ids(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_HOME_TL_IDS, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  user_timeline_ids(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_USERS_TL_IDS, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  broadcast_timeline_ids(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_BROADCASET_TL_IDS, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  mentions_timeline_ids(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_MENTIONS_TL_IDS, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  users_timeline(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_USERS_TL, oQWBlogParam, pResultData, nLen);
			}
		inline HTTP_RESULTCODE  users_timeline_ids(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_STATUSES_USERS_TL_IDS, oQWBlogParam, pResultData, nLen);
			}

			
	}


	namespace t
	{
		inline HTTP_RESULTCODE  show(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_SHOW, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  add(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_ADD, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  del(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_DEL, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  re_add(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_RE_ADD, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  reply(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_REPLY, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  add_pic(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_ADD_PIC, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  re_count(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_RE_COUNT, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  re_list(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_RE_LIST, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  comment(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_COMMENT, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  add_music(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_ADD_MUSIC, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  add_video(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_ADD_VIDEO, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  getvideoinfo(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_GETVIDEOINFO, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  list(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_T_LIST, oQWBlogParam, pResultData, nLen);
			}

			//13
	}


	namespace user
	{
		inline HTTP_RESULTCODE  info(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_USER_INFO, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  update(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_USER_UPDATE, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  update_head(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_USER_UPDATE_HEAD, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  other_info(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_USER_OTHER_INFO, oQWBlogParam, pResultData, nLen);
			}

		
	}


	namespace friends
	{
		inline HTTP_RESULTCODE  fanslist(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_FANSLIST, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  idollist(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_IDOLLIST, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  blacklist(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_BLACKLIST, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  speciallist(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_SPECIALLIST, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  add(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_ADD, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  del(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_DEL, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  addspecial(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_ADDSPECIAL, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  delspecial(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_DELSPECIAL, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  addblacklist(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_ADDBLACKLIST, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  delblacklist(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_DELBLACKLIST, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  check(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_CHECK, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  user_fanslist(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_USER_FANSLIST, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  user_idollist(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_USER_IDOLLIST, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  user_speciallist(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FRIENDS_USER_SPECIALLIST, oQWBlogParam, pResultData, nLen);
			}

		
	}


	namespace private
	{
		inline HTTP_RESULTCODE  add(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_PRIVATE_ADD, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  del(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_PRIVATE_DEL, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  recv(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_PRIVATE_RECV, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  send(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_PRIVATE_SEND, oQWBlogParam, pResultData, nLen);
			}
	}


	namespace search 
	{
		inline HTTP_RESULTCODE  user(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_SEARCH_USER, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  t(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_SEARCH_T, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  userbytag(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_SEARCH_USERBYTAG, oQWBlogParam, pResultData, nLen);
			}
	}


	namespace trends
	{
		inline HTTP_RESULTCODE  ht(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_TRENDS_HT, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  t(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_TRENDS_T, oQWBlogParam, pResultData, nLen);
			}


		
	}


	namespace info 
	{
		inline HTTP_RESULTCODE  update(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_INFO_UPDATE, oQWBlogParam, pResultData, nLen);
			}
	}



	namespace fav
	{
		inline HTTP_RESULTCODE  addt(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FAV_ADDT, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  delt(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FAV_DELT, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  list_t(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FAV_LIST_T, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  addht(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FAV_ADDHT, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  delht(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FAV_DELHT, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  list_ht(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_FAV_LIST_HT, oQWBlogParam, pResultData, nLen);
			}

		
	}

	namespace ht 
	{
		inline HTTP_RESULTCODE  ids(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_HT_IDS, oQWBlogParam, pResultData, nLen);
			}


		inline HTTP_RESULTCODE  info(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_HT_INFO, oQWBlogParam, pResultData, nLen);
			}

	}

	namespace tag 
	{
		inline HTTP_RESULTCODE  add(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_TAG_ADD, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  del(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_TAG_DEL, oQWBlogParam, pResultData, nLen);
			}
		
	}

	namespace other 
	{
		inline HTTP_RESULTCODE  knownperson(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_OTHER_KNOWNPERSON, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  shorturl(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_OTHER_SHORTURL, oQWBlogParam, pResultData, nLen);
			}

		inline HTTP_RESULTCODE  videokey(CWeiboParam oQWBlogParam,
			char * & pResultData ,int & nLen){
				return SyncRequestByOption(TXWB_OTHER_VIDEOKEY, oQWBlogParam, pResultData, nLen);
			}
	}

}

#endif

