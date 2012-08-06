腾讯微博开放平台C++ SDK 

支持环境 WINDOWS XP, WINDOWS 7 (VS2010)。 
因为作者的pc目前只有这个VS2010环境，所以只配置了这个工程。从代码的角度看，此SDK应该可以支持VC6 以上的版本。只是需要自己配置一下即可。


作者： heloyue
日期： 2011-06-15

维护人：bluentzhao
更新日期：2011-08-30

新增的功能：
    增加了4个API接口，分别是：t/add_video_prev 预发表一条视频微博，user/infos 获取一批人的简单资料
	friends/fanslist_s 我的粉丝列表，简单信息，friends/idollist_s 我的偶像列表，简单信息
修补的问题：
    1、修改了工程属性
    2、解决了一个内存泄露
	
工程配置：

一共分成两个工程
APISDK
APIExample


APISDK 
	基于libhttp, libjson实现了腾讯微博的基本操作借口。
	
	借口分成两类：
		一类是参数设置由CWeiboParam类来实现
		另一类是在参数设置完成的情况下与腾讯开放平台进行交互的接口。在这类接口的基础上又
		为“http://open.t.qq.com/resource.php?i=1,1”上面的每个api包装了一个接口。下面以实例说明这类借口

        比如：Statuses/home_timeline 主页时间线 对应的借口是 TXWeibo::statuses::home_timeline() ， 除了前面的TXWeibo 域外，后面的都与api同名，注意接口全小写。

APIExample
 	基于上述sdk的示例程序，演示了现有的腾讯微博开放平台的所有接口。


编译选项：

目前提供两个编译选项 Debug 和 Release


有问题请联系作者！
联系方式：
2570736544
mail: 2570736544@qq.com
	
		