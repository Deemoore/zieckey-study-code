# -*- coding:UTF-8 -*-  

'''
Created on 2011-11-20

@author: Administrator
'''

from xml.dom import minidom

from xml.etree import ElementTree

def test_xml(input_file):
    
    xmldoc = minidom.parse(input_file)
    root = xmldoc.documentElement
    
    f = open('test_data/gre_one_word_one_line.txt', 'w+')
    
    for node in root.getElementsByTagName('word'):
        c = node.firstChild
        if c != None:
            print c.data
            f.write(c.data + '\n')
            
        
        
# -*- coding:UTF-8 -*-  
  
class Person(object):  
    '''  
    联系人：姓名，性别(0:男，1:女)，手机  
    '''  
    name = None  
    sex = None  
    mobile = None  
      
  
    def __init__(self,name,sex,mobile):  
          
        self.name = name  
        self.sex = sex  
        self.mobile = mobile  
      
    def setName(self,name):  
        self.name = name  
      
    def setSex(self,sex):  
        self.sex = sex  
      
    def setMobile(self,mobile):  
        self.mobile = mobile  
          
          
def personToXML(person):  
        '''将Person对象转换成xml格式的数据'''  
        name = person.name  
        sex = person.sex  
        mobile = person.mobile  
        root = ElementTree.Element('personList')  
        personE = ElementTree.SubElement(root, 'person')  
        nameE = ElementTree.SubElement(personE, 'name')  
        nameE.text = name  
        sexE = ElementTree.SubElement(personE, 'sex')  
        if sex == '0':  
            sexE.text = '男'  
        elif sex == '1':  
            sexE.text = '女'  
        mobileE = ElementTree.SubElement(personE, 'mobile')  
        mobileE.text = mobile  
        rough_string = ElementTree.tostring(root, 'utf-8')  
        reparsed = minidom.parseString(rough_string)  
        return reparsed.toprettyxml(indent="  " , encoding="utf-8");
        
def test_xml2():
    person = Person('janny', '1', '15801463655')
    print personToXML(person)        

def test_write_kaoyandanci():
    words = "a,ability,about,above,abroad,absence,absent,accept,acceptable,accident,accordance,according,accordingto,account,ache,acid,across,act,action,active,activity,actor,actress,actual,add,addition,address,adjective,admiration,admire,admit,admittance,adult,advance,advantage,adventure,adverb,advertise,advertisement,advice,advise,affair,afford,afraid,after,afternoon,afterwards,again,against,age,ago,agree,agreement,ahead,aim,air,aircraft,airforce,airport,alcohol,alike,alive,all,allow,almost,alone,along,aloud,alphabet,already,also,although,altogetherv,always,among,amount,amuse,amusement,amusing,an,ancient,and,anger,angle,angry,animal,ankle,annoy,annoyance,another,answer,ant,anxiety,anxious,any,anyhow,anyone,anything,anywhere,apart,apparatus,appear,appearance,apple,appoint,approval,approve,arch,area,argue,argument,arm,armor,arms,army,around,arrange,arrangement,arrival,arrive,art,article,artificial,as,ash,ashamed,aside,ask,asleep,association,at,atom,attack,attempt,attend,attendance,attention,attract,attractive,aunt,autumn,average,avoid,awake,awayv,awkward,baby,back,background,backward,backwards,bacteria,bad,bag,bake,balance,ball,banana,band,bank,bar,bare,barrel,base,basket,bath,bathe,battle,be,beak,beam,bean,bear,beard,beat,beautiful,beauty,because,become,bed,bee,beer,before,beg,begin,beginning,behave,behavior,behind,belief,believe,bell,belong,below,belt,bend,beneath,berry,beside,besides,best,better,between,beyond,bicycle,big,bill,bind,bird,birth,birthday,bit,bite,bitter,black,blade,blame,bleed,bless,blind,block,blood,blow,blue,board,boat,body,boil,bomb,bone,book,boot,border,born,borrow,both,bottle,bottom,bowels,bowl,box,boy,brain,branch,brass,brave,bread,breadth,break,breakfast,breast,breath,breathe,breed,brick,bridge,bright,bring,broad,broadcast,brother,brown,brush,bucket,build,building,bullet,bunch,burial,burn,burst,bury,bus,bush,business,busy,butC,butter,button,buy,by,cage,cake,calculate,calculator,call,calm,camera,camp,can,candle,cap,capital,captain,car,card,cardboard,care,careful,careless,carriage,carry,cart,case,castle,cat,catch,cattle,cause,cell,cement,cent,center,centimeter,central,century,ceremony,certain,chain,chair,chairperson,chalk,chance,change,character,charge,charm,chase,cheap,cheat,check,cheek,cheer,cheerful,cheese,chemical,chemistry,chest,chicken,chief,child,childhood,children,chimney,chin,chocolate,choice,choose,church,cigarette,cinema,circle,circular,citizen,city,civilization,claim,class,clay,clean,clear,clerk,clever,cliff,climb,clock,clockwork,close,cloth,clothes,clothing,cloud,club,coal,coast,coat,coffee,coin,cold,collar,collect,college,color,comb,combination,combine,come,comfort,comfortable,command,committee,common,companion,company,compare,comparison,compete,competition,competitor,complain,complaint,complete,compound,computer,concern,concerning,concert,condition,confidence,confident,confuse,connect,conscience,conscious,consider,consist,consonant,contain,contents,continue,continuous,contract,control,convenient,conversation,cook,cool,copper,copy,cord,corn,corner,correct,cost,cotton,cough,could,council,count,country,courage,course,court,cover,cow,coward,cowardly,crack,crash,cream,creature,creep,cricket,crime,criminal,crop,cross,crowd,cruel,cruelty,crush,cry,cultivate,cup,cupboard,cure,curl,current,curse,curtain,curve,custom,customer,cut,cycle,dailyv,damage,dance,danger,dangerous,dare,daring,dark,date,daughter,day,dead,deal,dear,death,debt,decay,deceit,deceive,decide,decimal,decision,declaration,declare,decorate,decoration,decrease,deep,deer,defeat,defend,defense,degree,delay,delicate,delight,deliver,demand,department,depend,dependent,depth,descend,describe,description,descriptive,desert,deserve,desirable,desire,desk,destroy,destruction,detail,determination,determined,develop,devil,diamond,dictionary,die,difference,different,difficult,difficulty,dig,dinner,dip,direct,direction,dirt,dirty,disappoint,discourage,discouragement,discover,discovery,dish,dismiss,distance,distant,ditch,divide,division,do,doctor,dog,dollar,door,doorway,dot,double,doubt,down,drag,draw,drawer,dream,dress,drink,drive,drop,drown,drug,drum,drunk,dry,duck,dull,during,dust,duty,each,eager,ear,early,earn,earth,east,eastern,easy,eat,edge,educate,education,effect,effective,effort,egg,eight,eighth,either,elastic,elbow,elect,election,electric,electricity,elephant,else,employ,employer,employment,empty,enclose,enclosure,encourage,encouragement,end,enemy,engine,engineer,English,enjoy,enjoyment,enough,enter,entertain,entertainment,entrance,envelope,equal,equality,escape,especially,establish,establishment,evenv,evening,event,ever,every,everyone,everything,everywhere,evil,exact,examination,examine,example,excellent,except,exchange,excite,excited,exciting,excuse,exercise,exist,existence,expect,expensive,experience,explain,explanation,explode,explosion,explosive,express,expression,extreme,eye,eyelid,face,fact,factory,fail,failure,faint,fair,fairy,faith,faithful,fall,false,fame,familiar,family,famous,fancy,far,farm,farmer,farmyard,fashion,fashionable,fastv,fasten,fat,fate,father,fault,favor,favorable,favorite,fear,feather,feed,feel,feeling,feelings,fellow,female,fence,fever,few,field,fierce,fifth,fight,figure,fill,film,find,fine,finger,finish,fire,fireplace,firm,first,fish,fisherman,fit,five,fix,flag,flame,flash,flat,flesh,flight,float,flood,floor,flour,flow,flower,fly,fold,follow,fond,food,fool,foolish,foot,football,footpath,footstep,for,forbid,force,forehead,foreign,foreigner,forest,forget,forgive,fork,form,formal,former,formerly,fort,fortunate,fortune,forwardv,forwards,four,fourth,fox,frame,free,freedom,freeze,frequent,fresh,friend,friendly,frighten,frightening,from,front,fruit,fulfill,full,fun,funeral,funny,fur,furnish,furniture,further,future,gain,game,garage,garden,garment,gas,gasoline],gate,gather,general,generous,gentle,gentleman,get,gift,girl,give,glad,glass,glory,glue,go,goat,god,God,gold,golden,good,good-bye,goods,govern,government,grace,graceful,gradual,grain,gram,grammar,grand,grandfather,grandmother,grass,grateful,grave,gray,great,green,greet,greeting,grief,grieve,ground,group,grow,growth,guard,guess,guest,guidance,guide,guilt,gun,habit,habitual,hair,hairy,half,hall,hammer,hand,handkerchief,handle,hang,happen,happy,hard,harden,hardly,hardship,harm,harmful,harmless,hasty,hat,hate,hatred,have,he,head,health,healthy,hear,heart,heat,heaven,heavy,heel,height,help,helpful,hen,her,here,hers,herself,hide,highv,hill,him,himself,hire,his,historical,history,hit,hold,holiday,hollow,holy,homev,honest,honesty,honor,honorable,hook,hope,hopeful,hopeless,horizon,horn,horse,hospital,host,hot,hotel,hour,hourly,house,howhuman,humor,humorous,hundred,hundredth,hunger,hungry,hunt,hurry,hurt,husband,hut,I,ice,icy,idea,if,ill,image,imaginary,imagination,imagine,importance,important,improve,improvement,in,include,including,income,increase,indoor,indoors,industrial,industry,infect,infection,infectious,influence,influential,inform,information,ink,inner,inquire,inquiry,insect,inside,instead,instruct,instruction,instrument,insurance,insure,intend,intention,interest,interesting,international,interrupt,interruption,into,introduce,introduction,invent,invention,invitation,invite,inwards,iron,island,itits,itself,jaw,jealous,jealousy,jelly,jewel,jewelry,job,join,joint,joke,journey,joy,judge,judgment,juice,jump,just,justice,keen,keep,key,kick,kill,kilo,kilogram,kilometer,kind,king,kingdom,kiss,kitchen,knee,kneel,knife,knock,knot,know,knowledge,labor,lack,ladder,lady,lake,lamb,lamp,land,language,large,lastlate,lately,laugh,laughter,law,lawyer,lay,lazy,lead,lead,leaf,lean,learn,least,leather,leave,left,leg,legal,lend,length,less,lesson,let,letter,levelv,library,lid,lie,life,lift,light,lightning,likeP,likely,limb,limit,line,lion,lip,liquid,list,listen,liter,literature,little,live,load,loaf,local,lock,lodging,lodgings,log,lonely,longv,look,loose,lord,lose,loss,lot,loud,love,low,lower,loyal,loyalty,luck,lump,lung,machine,machinery,mad,magazine,magic,magician,mail,main,make,male,man,manage,manager,manner,many,map,march,mark,market,marriage,marry,mass,master,mat,match,material,matter,may,me,meal,mean,meaning,means,measure,meat,medical,medicine,meet,meeting,melt,member,memory,mend,mention,merry,message,messenger,metal,meter,method,metric,microscope,middle,might,mile,military,milk,million,millionth,mind,minemineral,minister,minute,mirror,miss,mist,mistake,mix,mixture,model,modern,moment,money,monkey,month,monthly,moon,moral,morals,more,morning,most,mother,motor,mountain,mouse,mouth,move,much,mud,multiply,murder,muscle,music,musician,must,my,myself,mysterious,mystery,nail,name,narrow,nasty,nation,national,nature,naval,navy,nearnearly,neat,necessary,neck,need,needle,neighbor,neighborhood,neither,nerve,nervous,nest,net,network,never,new,news,newspaper,next,nice,night,nine,ninth,noone,noble,nobleman,noise,none,nonsense,nor,north,northern,nose,not,nothing,notice,noun,now,nowhere,number,nurse,nut,nylon,o'clock,obedience,obedient,obey,object,obtain,occasion,ocean,odd,of,off,offend,offense,offensive,offer,office,officer,official,often,oil,old,old-fashioned,once,one,oneself,onion,only,open,operate,operation,opinion,opponent,oppose,opposite,opposition,or,orange,order,ordinary,organ,organization,origin,other,otherwise,ought,our,ours,ourselves,outv,outdoor,outdoors,outer,outside,overowe,owingto,ownoxygen,pack,packet,page,pain,painful,paint,painting,pair,palace,pale,pan,paper,parallel,parcel,parent,park,parliament,part,participle,particular,partner,party,pass,passage,passenger,past,pastry,path,patience,patient,pattern,pause,pay,payment,peace,peaceful,pen,pence,pencil,people,pepper,perfect,perform,perhaps,period,permission,permit,person,personal,persuade,pet,photograph,photography,phrase,physical,piano,pick,picture,piece,pig,pile,pilot,pin,pink,pipe,pity,place,plain,plan,plane,plant,plastic,plate,play,pleasant,please,pleased,pleasure,plentyplural,pocket,poem,poet,poetry,point,pointed,poison,poisonous,pole,police,polish,polite,political,politician,politics,pool,poor,popular,popularity,population,port,position,possess,possession,possibility,possible,possibly,post,pot,potato,pound,pour,powder,power,powerful,practical,practice,praise,pray,prayer,precious,preparation,prepare,presence,present,preserve,president,press,pressure,pretend,pretty,prevent,price,prickly,pride,priest,prince,principle,print,prison,prisoner,private,prize,probability,probable,problem,process,procession,produce,product,production,profession,profit,promise,pronounce,pronunciation,proof,proper,property,protect,protection,protective,proud,prove,provide,provision,provisions,public,pull,pump,punish,punishment,pupil,pure,purple,purpose,push,put,quality,quantity,quarrel,quarter,queen,question,quick,quiet,quite,rabbit,race,radio,railway,rain,raise,range,rank,rapid,rare,rat,rate,rather,raw,reach,read,ready,real,really,reason,reasonable,receive,recent,recently,recognition,recognize,record,red,reduce,reduction,refusal,refuse,regard,regular,related,relation,relative,religion,religious,remain,remark,remember,remind,remove,rent,repair,repeat,reply,report,represent,representative,republic,request,respect,respectful,responsible,rest,restaurant,result,return,reward,rice,rich,rid,ride,rightv,ring,ripe,rise,risk,river,road,rob,rock,rod,roll,roof,room,root,rope,rose,rough,roundrow,royal,rub,rubber,rude,ruin,rule,ruler,run,rush,sad,safe,safety,sail,sale,salt,same,sand,satisfaction,satisfactory,satisfy,save,say,scale,scatter,scene,scenery,school,science,scientific,scientist,scissors,screw,sea,search,season,seat,secondsecrecy,secret,secretary,see,seed,seem,seize,sell,send,sensation,sense,senseless,sensible,sensitive,sentence,separate,serious,servant,serve,service,set,settle,seven,seventh,several,severe,sew,sex,sexual,shade,shadow,shake,shall,shame,shape,share,sharp,she,sheep,sheet,shelf,shell,shelter,shield,shine,ship,shirt,shock,shoe,shoot,shop,shopkeeper,shore,short,shot,should,shoulder,shout,show,shut,sick,side,sideways,sight,sign,signal,signature,silence,silent,silk,silly,silver,similar,similarity,simple,since,sincere,sing,single,singular,sink,sister,sit,situation,six,sixth,size,skill,skillful,skin,skirt,sky,slave,sleep,slide,slight,slip,slippery,slope,slow,small,smell,smile,smoke,smooth,snake,snow,so,soap,social,society,sock,soft,soil,soldier,solemn,solid,somesomehow,someone,something,sometimes,somewhere,son,song,soon,sore,sorrow,sorry,sort,soul,sound,soup,sour,south,southern,space,spacecraft,spade,speak,spear,special,specialist,speech,speed,spell,spend,spin,spirit,spite,splendid,split,spoil,spoon,sport,spot,spread,spring,square,stage,stair,stamp,stand,standard,star,start,state,station,stay,steady,steal,steam,steel,steep,stem,step,stick,sticky,stiff,stillv,sting,stitch,stomach,stone,stop,store,storm,story,straightv,strange,stranger,stream,street,strength,stretch,strike,string,stroke,strong,structure,struggle,student,study,stupid,style,subject,substance,subtract,succeed,success,successful,such,suck,sudden,suffer,sugar,suggest,suit,suitable,sum,summer,sun,supper,supply,support,suppose,sure,surface,surprise,surround,swallow,swear,sweep,sweet,swell,swim,swing,sword,sympathetic,sympathy,system,table,tail,take,talk,tall,taste,tax,taxi,tea,teach,team,tear,tear,telephone,television,tell,temper,temperature,temple,tend,tendency,tender,tennis,tense,tent,terrible,terror,test,than,thank,thatthe,theater,their,theirs,them,themselves,thenv,there,therefore,these,they,thick,thief,thin,thing,think,third,thirst,thirsty,thisthorough,those,though,thought,thousand,thousandth,thread,threat,threaten,three,throat,throughthrow,thumb,thunder,thus,ticket,tidy,tie,tiger,tight,time,timetable,tin,tire,tire,title,to,tobacco,today,toe,together,tomorrow,tongue,tonight,too,tool,tooth,top,total,touch,tour,tourist,towards,tower,town,toy,track,trade,traffic,train,translate,transparent,trap,travel,treat,treatment,tree,tremble,tribe,trick,trip,tropical,trouble,trousers,true,trunk,trust,truth,try,tube,tune,turn,twice,twist,type,typical,ugly,uncle,underP,understand,undo,uniform,union,unit,unite,universal,universe,university,until,up,upper,uprightv,upset,upsidedown,upstairs,urge,urgent,us,use,useful,useless,usual,valley,valuable,value,variety,various,vary,vegetable,vehicle,verb,veryv,victory,view,village,violence,violent,visit,voice,vote,vowel,voyage,wages,waist,wait,waiter,wake,walk,wall,wander,want,war,warm,warmth,warn,wash,waste,watch,water,wave,way,we,weak,wealth,weapon,wear,weather,weave,wedding,week,weeklyv,weigh,weight,welcome,wellv,west,western,wet,what,whatever,wheat,wheel,whenwhenever,where,whether,which,whichever,while,whip,whisper,whistle,white,who,whoever,whole,why,wicked,wide,widespread,width,wife,wildv,will,willing,win,wind,wind,window,wine,wing,winter,wire,wisdom,wise,wish,with,within,withoutP,witness,woman,wonder,wood,wooden,wool,woolen,word,work,world,worm,worry,worse,worship,worst,worth,worthy,worthyof,would,wound,wrap,wreck,wrist,write,wrongwrongdoing,yard,year,yearly,yellow,yes,yesterday,yet,you,young,your,yours,yourself,youth,zero"
    import string
    new_words = string.replace(words, ',', '\n')
    f = open('Kaoyan.txt', 'w+')
    f.write(new_words)
    f.close()
    print 'done'
    
if __name__ == '__main__':
    #test_xml('test_data/gre.xml')
    #test_xml2()
    test_write_kaoyandanci()
