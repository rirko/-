#pragma once
#include <stdio.h>//标准输入输出
#include <stdlib.h>//标准库
#include <conio.h>//键盘交互
#include <math.h>//数学
#include <Windows.h>//系统
#include <string.h>//字符串
#include <graphics.h>
#include <easyx.h>

#include"STG_io.h"
#include"STG_define.h"
#include"STG_global.h"
#include"STG_thread.h"
#include"STG_anime.h"
void dialogue_1() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(crarcter_assistant, _T("助手：医生！卡兰德克塔娜医生！今天又有患有瘟疫的病人来找你了！"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：好的！我知道了，谢谢你！让他进来吧！"));
	dialogue(_T("（这么一来，就是第995位病人了，离“那个目标”，还差六人）"));
	dialogue(_T("患者：打扰了……"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：没关系的，请进……嗯？"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：啊？是您！希波克拉底先生！您怎么也……"));
	dialogue(_T("希波克拉底：啊，我亲爱的小卡兰德克塔娜！"));
	dialogue(_T("希波克拉底：我也没想到啊，我会以这样的身份与你重逢"));
	dialogue(_T("希波克拉底：前两天我发现自己染上了瘟疫")); 
	dialogue(_T("希波克拉底：大抵是四处游荡行医的时候不小心染上的吧")); 
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：您总是这样，为了万物众生，无私地奔走在瘟疫的第一线"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：17年前我母亲因瘟疫去世后，也是您收养了我、并且教会了我医术")); 
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：真的，对您是感激不尽"));
	dialogue(_T("希波克拉底：我收养你，也只是出于对没能救回你母亲的性命而愧疚罢了"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：可是……"));
	dialogue(_T("希波克拉底：不用为我脱罪"));
	dialogue(_T("希波克拉底：小卡兰德克塔娜啊，我现在是真没有脸来见你"));
	dialogue(_T("希波克拉底：你是如此的纯洁善良，而我……说白了，其实是你的杀母仇人……"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：才不是这样，希波克拉底先生！我们都知道，您不是这样的人！"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：等着吧，我一定会治好你的！"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(5000);
}

void dialogue_1pass() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：呼……总算是成功了。希波克拉底先生的命，终究还是保住了"));
	dialogue(crarcter_kami, _T("阿斯克勒皮厄斯：卡兰德克塔娜，这次也干得不错嘛"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：这次也是多亏有您在了，阿斯克勒皮厄斯大人"));
	dialogue(crarcter_kami, _T("阿斯克勒皮厄斯：哈哈，那是，我的协助对你这个初出茅庐的新人医生而言也是相当重要的"));
	dialogue(crarcter_kami, _T("阿斯克勒皮厄斯：平凡的人类能与身为天神的我交流、并且获得我的医术能力的加持"));
	dialogue(crarcter_kami, _T("……阿斯克勒皮厄斯：难以想象。姑且也算是你的幸运了吧"));
	dialogue(crarcter_kami, _T("阿斯克勒皮厄斯：但是你也要牢记这种沟通加持的风险……"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：我知道的，稍有不慎，就会让病人病情迅速恶化死去"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：而我也难逃生命危险"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：记住就好"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：而且你现在也是在和那位神明交易吧……一定要记住，提防那家伙"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：他可是连我都会忌惮的存在"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：感谢您的忠告，我会注意的"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：那位……阿瑞斯大人的事，也已经接近尾声"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：你也辛苦了"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：这些宝珠，是你应得的"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_2() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(_T("                    次日"));
	dialogue(crarcter_assistant, _T("       助手：医生，又有病人来了！"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：好的，请让她进来吧"));
	dialogue(crarcter_assistant, _T("       助手：好的！"));
	dialogue(_T(""));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：您好，请坐"));
	dialogue(_T("？？？：医生您好，我的名字是埃拉，是一位孩子的母亲"));
	dialogue(_T("埃拉：我的家里十分贫困，如您所见，这场瘟疫给我们带来了饥荒"));
	dialogue(_T("埃拉：而现在为了给孩子寻找食量，我又不得不奔走于大街小巷中，结果……"));
	dialogue(_T("埃拉：很对不起您还有我的小女孩丽娜，我染上了这种奇怪的病……"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：您的遭遇，我也十分痛心。"));
	dialogue(_T("埃拉：求求医生您，救救我吧！我甘愿成为仆人来报答您的恩情"));
	dialogue(_T("埃拉：丽娜她也还需要我，如果我不在了的话她、她就……"));
	dialogue(crarcter_doctor, _T("（这份沉重感，究竟是……怎么回事？）"));
	dialogue(crarcter_doctor, _T("（17年前的希波克拉底先生在那个时候面对的……也是这样的情形吗？）"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：好的，我一定会的，救治您"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：让您和您的女儿在这场瘟疫过去后")); 
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：能够继续平凡且幸福的日常"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_2pass() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：这下就是第996位患者了"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：是的，离与阿瑞斯大人的打赌的胜利，又更近了一步"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：阿瑞斯那个混蛋看到了估计也会讶然于你的毅力吧"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：想想看他那表情……我还是很乐意看到的"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：不过阿瑞斯大人也说了，他之所以要降下瘟疫，原因是在于……"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：人类之间频繁的战争。他痛恨战事"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：尤其是强国发起的霸权战争，已经彻底将他激怒了"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：可是他这样让瘟疫降临人间也真是……更多的还是伤及无辜吧"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……      "));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_3() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(crarcter_assistant, _T("助手：医生！医生！又有患者了！"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：请让他进来吧"));
	dialogue(crarcter_assistant, _T("助手：……可、可是……"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：怎么了吗？"));
	dialogue(crarcter_assistant, _T("助手：那个人……是那个强盗伊塔利安！")); 
	dialogue(crarcter_assistant, _T("助手：就是您母亲去世后潜入您的家中窃走了一切私物的强盗！"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……      "));
	dialogue(crarcter_assistant, _T("助手：您真确定要让他进来吗？"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……让他进来吧，那些都已经是过去的事了"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：虽然不可能会忘记，但也没必要在这种时候再提起 "));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：况且，救人是医生的天职，医者仁心，对待病人要一视同仁"));
	dialogue(crarcter_assistant, _T("助手：好……好的……"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_3pass() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：不愧是你啊，小丫头。你的这份胸怀，我很喜欢"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：我想这也是你能够与我产生链接并且获得我的力量的原因所在"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……或许吧，他现在也只是个可怜人"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：比起曾经的那些仇恨，摆在眼前的困境更值得我们去关注")); 
	dialogue( _T("(是的，比起仅仅只是记住那些仇恨……还不如将份仇恨化作对抗瘟疫的力量)"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_4() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：您好，请进吧"));
	dialogue(_T("   ？？？：……     "));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：请问您也是要来找我治病的吗？还是……"));
	dialogue(_T("？？？：医生，你的名字是卡兰德克塔娜吧"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：没错，怎么了吗？"));
	dialogue(_T("？？？：你的父亲……曾经是王国军的一名士兵？"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：是的，但是他在我很小的时候就阵亡了"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：您是我父亲的故人？"));
	dialogue(_T("   ？？？：……     "));
	dialogue(_T("？？？：医生，如果我是杀死你父亲的那名敌国士兵"));
	dialogue(_T("？？？：你会救助我吗？"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……"));
	dialogue(_T("战俘：20多年前，是我夺去了那名男子的性命，破坏了你的家庭"));
	dialogue(_T("战俘：使得你的母亲成为了独自抚养女儿的寡妇"));
	dialogue(_T("战俘：那是我第一次杀人，也是最后一次")); 
	dialogue(_T("战俘：我军战败了，我也成为了战俘"));
	dialogue(_T("战俘：都是这可恨的战争，杀人已经成为了理所当然的事"));
	dialogue(_T("战俘：也正是因为这战争，我才沦为了杀人犯……不，不仅仅是因为战争"));
	dialogue(_T("战俘：这就是我的错，如今我染上这样的瘟疫也是上苍给予我的惩罚"));
	dialogue(_T("战俘：孩子啊，如果可以的话，我希望能由你来亲手杀掉我"));
	dialogue(_T("战俘：用你的这双手终结我的生命，大概也是我最好的结局了"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……我是一名医生"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：医生的手，不是用来结束生命、而是用来拯救生命的"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：先生，我不知道你姓甚名谁，但是，拯救你是我的天职"));
	dialogue(_T("战俘：……你是认真的吗？"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：是的，将你的性命，放心大胆地交付于我吧"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_4pass() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：小丫头，有件事，我必须要告诉你了"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：我的协助，只能维持到这里了"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：再这样利用下去，你的生命力可能就真的要完全丧失了"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：人类过于借助神的力量是绝对要付出代价的"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：付出代价……可是……"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……我与降下这场瘟疫的阿瑞斯大人打过赌"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：只要救活一千人，这场瘟疫就一定会从这片大地上消失"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：没有您的力量，我……我可能……"));
	dialogue(_T("阿斯克勒皮俄斯：没问题的。你经历过了那么多次考验"));
	dialogue(_T("我想哪怕没有我的能力的加护，你也一定能凭借自己的力量战胜瘟疫吧"));
	dialogue(_T("我也是……不希望看到你惨死于我的能力之下"));
	dialogue(_T("就此别过吧，小卡兰德克塔娜"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……我知道了"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：这么多天，承蒙您的关照了，阿斯克勒皮俄斯大人"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	setbkmode(OPAQUE);
	cleardevice();
	FlushBatchDraw();
	
	for (i = 0; i < 240; i++) {
		setbkcolor(RED);
		cleardevice();
		int w = rand() % 2;
		outtextxy(100+w, 450+w, _T("生命降为1，护盾消失，从当前关卡开始回档功能无效"));
		anime_line(BLACK);
		FlushBatchDraw();
		blanktime();
	}
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_5() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(_T("                几天后      "));
	dialogue(_T("？？？：您好，您就是卡兰德克塔娜医生吧"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：是的，有什么可以帮助您的吗"));
	dialogue(_T("？？？：我是附近市里的市民，最近不是闹那个什么瘟疫嘛……"));
	dialogue(_T("患病的市民：我就是上街走走，结果一个不小心就染上了"));
	dialogue(_T("患病的市民：不过和现在不同，那个时候大家也都不怎么在意嘛"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……好吧，我知道了。我会尽力救你的"));
	dialogue(crarcter_doctor, _T("（我能做到吗……没有阿斯克勒皮俄斯大人的协助……）"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_5pass() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(crarcter_doctor, _T("（意外的比想象中的要简单）"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：这样下来，就只剩下一个人了……"));
	dialogue(crarcter_assistant, _T(" 助手：卡兰德克塔娜医生，您已经连续工作很长时间了"));
	dialogue(crarcter_assistant, _T(" 助手：感觉您今天有点不在状态……需要休息一下吗？"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：谢谢，我没事"));
	dialogue(crarcter_doctor, _T("（快了，就要实现那个目标了）"));
	dialogue(crarcter_doctor, _T("（阿瑞斯大人……哪怕仅凭借我区区凡人之力，我也会打败你的！等着吧！）"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_6() {
	fps = 60;
	static int i = 0;
	setbkcolor(0xC7F2F8);
	cleardevice();
	FlushBatchDraw();
	dialogue(_T("                一天后"));
	dialogue(_T("？？？：哟，那个什么卡医生就是你吧"));
	dialogue(_T("？？？：快来给我看看，我这到底是怎么回事了！"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……这位先生，请您稍等"));
	dialogue(_T("？？？：昨天我儿子也过来这里了，他这孩子啊……"));
	dialogue(_T("上一个患者的父亲：就是从小到大都很不幸的那种"));
	dialogue(_T("上一个患者的父亲：什么坏事总是会莫名其妙被按在他头上。就连看个病都还要跑那么远……"));
	dialogue(_T("上一个患者的父亲：喂，在听我说话吗？！"));
	dialogue(_T("上一个患者的父亲：快点，给我看病啊，医生，你的职责就是救治病人吧！"));
	dialogue(_T("上一个患者的父亲：我也是患者，别磨蹭了，赶紧把我治好啊混蛋！"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：请您注意你的言辞"));
	dialogue(_T("上一个患者的父亲：哈？！你这是什么态度？！"));
	dialogue(_T("上一个患者的父亲：你凭什么用这种语气和我说话？！我又不会不给你钱！"));
	dialogue(crarcter_assistant, _T("助手：医生！这位先生，请问……"));
	dialogue(_T("上一个患者的父亲：要不是我生了这个病，你赚不到这个钱！"));
	dialogue(_T("上一个患者的父亲：感激我都还来不及吧！"));
	dialogue(crarcter_assistant, _T("       助手：你！       "));
	dialogue(crarcter_doctor, _T("（这话也太过分了吧……算了，忍忍就过去了……）"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：好吧，我知道了，您请"));
	dialogue(crarcter_assistant, _T("       助手：医生……   "));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}

void dialogue_lost() {
	fps = 60;
	static int i = 0;
	setbkcolor(BLACK);
	cleardevice();
	FlushBatchDraw();
	dialogue_white(_T("                    力 尽 倒 下"));
	dialogue_white(_T("                    生命值降为0"));
	dialogue_white(_T(""));
	dialogue_white(_T(""));
	dialogue_white(_T("           “喂！卡兰德克塔娜！喂！！！”"));
	dialogue_white(_T("          “卡兰德克塔娜！！振作一点！！”"));
	dialogue_white(_T("      “……没办法了……，只能再回溯一次……” "));
	dialogue_white(_T("          “这样下去……迟早有一天……”      "));
	setbkcolor(WHITE);
	dialogue(_T("                  "));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：我这是……"));
	dialogue(crarcter_assistant, _T("助手：医生？病人正在里面等您"));
	dialogue(crarcter_doctor, _T("卡兰德克塔娜：……知道了，我这就过去"));
	dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：……"));
	i = 0;
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	while (true)
	{
		i++;
		if (i > 30)break;
		int w = rand() % WIDTH - 200;
		int h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, &blood[0], SRCPAINT);
		anime_line(BLACK);
		FlushBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	anime_line(BLACK);
	FlushBatchDraw();
	Sleep(1000);
}