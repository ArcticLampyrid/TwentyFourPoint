#include <QLocale>
#include <random>
#include <random_nickname.h>

using namespace Qt::StringLiterals;

static QString adjective[] = {
    u"不可直视之"_s, u"阴郁"_s,   u"可笑"_s,   u"恐怖"_s, u"暗淡"_s, u"灿烂"_s, u"空灵"_s,       u"梦幻"_s, u"差不多"_s,
    u"柔软"_s,       u"紧致"_s,   u"光滑"_s,   u"粗糙"_s, u"松软"_s, u"干燥"_s, u"极限"_s,       u"微观"_s, u"迷你"_s,
    u"异常"_s,       u"荒唐"_s,   u"任意"_s,   u"随意"_s, u"可爱"_s, u"诡异"_s, u"瘆人"_s,       u"片状"_s, u"条状"_s,
    u"球状"_s,       u"直形"_s,   u"蛇形"_s,   u"反"_s,   u"逆"_s,   u"饱满"_s, u"炎热"_s,       u"炽热"_s, u"寒冷"_s,
    u"无色"_s,       u"绿色"_s,   u"靛蓝"_s,   u"猩红"_s, u"深蓝"_s, u"海蓝"_s, u"无法触及的"_s, u"热烈"_s, u"寂静"_s,
    u"永恒"_s,       u"畸形"_s,   u"残缺"_s,   u"破碎"_s, u"纯净"_s, u"式微"_s, u"葳蕤"_s,       u"液态"_s, u"固态"_s,
    u"气态"_s,       u"冰冷"_s,   u"温热"_s,   u"炽热"_s, u"酷寒"_s, u"随机"_s, u"珍奇"_s,       u"熱烈"_s, u"静寂"_s,
    u"永遠"_s,       u"奇形"_s,   u"欠損"_s,   u"破砕"_s, u"清浄"_s, u"式微"_s, u"葳蕤"_s,       u"液体"_s, u"固体"_s,
    u"気体"_s,       u"冷たい"_s, u"温かい"_s, u"熱い"_s, u"酷寒"_s,
};

static QString noun[] = {
    u"诅咒"_s,     u"记忆"_s,   u"苦痛"_s,   u"阈限"_s,       u"爱情"_s,   u"恐惧"_s,   u"情绪"_s,     u"静谧"_s,
    u"危险"_s,     u"欲望"_s,   u"精神"_s,   u"巫毒"_s,       u"崩溃"_s,   u"怪奇"_s,   u"叙事"_s,     u"维度"_s,
    u"几何"_s,     u"快乐"_s,   u"拓扑"_s,   u"非欧几里得"_s, u"灵体"_s,   u"魂魄"_s,   u"瓶装"_s,     u"罐装"_s,
    u"莫比乌斯"_s, u"元素"_s,   u"游离"_s,   u"幽匿"_s,       u"附魔"_s,   u"魔法"_s,   u"宿命"_s,     u"命运"_s,
    u"生死"_s,     u"勇气"_s,   u"心灵"_s,   u"死亡"_s,       u"生命"_s,   u"宗教"_s,   u"全息"_s,     u"恼怒"_s,
    u"解忧"_s,     u"忧愁"_s,   u"希望"_s,   u"绝望"_s,       u"模因"_s,   u"解构"_s,   u"虚饰"_s,     u"主义"_s,
    u"彼岸"_s,     u"人道"_s,   u"情色"_s,   u"爱恋"_s,       u"民主"_s,   u"霸权"_s,   u"专制"_s,     u"概念"_s,
    u"无穷"_s,     u"灾厄"_s,   u"意识"_s,   u"以太"_s,       u"恶意"_s,   u"意象"_s,   u"欧几里得"_s, u"憎恶"_s,
    u"正义"_s,     u"痛楚"_s,   u"月亮"_s,   u"影子"_s,       u"灯火"_s,   u"秋千"_s,   u"巨鲸"_s,     u"莽兽"_s,
    u"秘典"_s,     u"空间"_s,   u"梦魇"_s,   u"太阳"_s,       u"繁星"_s,   u"银河"_s,   u"天体"_s,     u"日照"_s,
    u"风暴"_s,     u"狂风"_s,   u"探测器"_s, u"城"_s,         u"光束"_s,   u"派对"_s,   u"肢体"_s,     u"面具"_s,
    u"画皮"_s,     u"异象"_s,   u"替身"_s,   u"娃娃"_s,       u"发生器"_s, u"坟墓"_s,   u"雪花"_s,     u"火焰"_s,
    u"水柱"_s,     u"水滴"_s,   u"汁液"_s,   u"环"_s,         u"戒指"_s,   u"闪电"_s,   u"暴雨"_s,     u"声波"_s,
    u"巨浪"_s,     u"潮汐"_s,   u"幻影"_s,   u"先生"_s,       u"女士"_s,   u"夫人"_s,   u"巨人"_s,     u"野兽"_s,
    u"冰晶"_s,     u"晶体"_s,   u"电波"_s,   u"阳光"_s,       u"果实"_s,   u"旗帜"_s,   u"球茎"_s,     u"鸟"_s,
    u"鹰"_s,       u"国度"_s,   u"打击"_s,   u"波动"_s,       u"粒子"_s,   u"反应"_s,   u"咒语"_s,     u"皮肤"_s,
    u"心脏"_s,     u"血液"_s,   u"脑"_s,     u"眼"_s,         u"爪"_s,     u"牙"_s,     u"神"_s,       u"仙子"_s,
    u"精灵"_s,     u"声"_s,     u"抗体"_s,   u"病毒"_s,       u"药水"_s,   u"理论"_s,   u"定理"_s,     u"逻辑"_s,
    u"问题"_s,     u"缺陷"_s,   u"疾病"_s,   u"光源"_s,       u"原木"_s,   u"雕像"_s,   u"赞歌"_s,     u"人"_s,
    u"深渊"_s,     u"投影"_s,   u"证明"_s,   u"保险"_s,       u"村落"_s,   u"峡谷"_s,   u"仙境"_s,     u"陷阱"_s,
    u"蓝图"_s,     u"巨石"_s,   u"宝石"_s,   u"珍珠"_s,       u"玛瑙"_s,   u"水晶"_s,   u"岩"_s,       u"琥珀"_s,
    u"食粮"_s,     u"矢量"_s,   u"尺"_s,     u"仪器"_s,       u"搅拌机"_s, u"理型"_s,   u"原型"_s,     u"系统"_s,
    u"群"_s,       u"集合体"_s, u"孩童"_s,   u"游戏"_s,       u"婴儿"_s,   u"哭闹"_s,   u"香草"_s,     u"草药"_s,
    u"季节"_s,     u"年"_s,     u"月"_s,     u"日"_s,         u"沙发"_s,   u"储物柜"_s, u"集装箱"_s,   u"小屋"_s,
    u"枕头"_s,     u"椅子"_s,   u"床"_s,     u"镜子"_s,       u"碎片"_s,   u"魔法"_s,   u"门"_s,       u"戏法"_s,
    u"提案"_s,     u"宝盒"_s,   u"魔盒"_s,   u"笔"_s,         u"橡皮"_s,   u"胶体"_s,   u"溶液"_s,     u"碎屑"_s,
    u"霜"_s,       u"胶水"_s,   u"日历"_s,   u"叶片"_s,       u"仪表盘"_s, u"杂货店"_s, u"时间"_s,     u"事件"_s,
    u"入口"_s,     u"出口"_s,   u"粉碎器"_s, u"英雄"_s,       u"恶霸"_s,   u"捍卫者"_s, u"吞噬者"_s,   u"观察者"_s,
    u"尖啸者"_s,   u"破坏者"_s, u"救世主"_s, u"上帝"_s,       u"难题"_s,   u"想法"_s,   u"蒸汽"_s,     u"悲剧"_s,
    u"喜剧"_s,     u"世界"_s,   u"宇宙"_s,   u"战士"_s,       u"射手"_s,   u"召唤师"_s, u"法师"_s,     u"巫师"_s,
    u"花"_s,       u"海岸"_s,   u"断崖"_s,   u"剑"_s,         u"刀"_s,     u"枪"_s,     u"矛"_s,       u"盾"_s,
    u"非人"_s,     u"仿生人"_s, u"龙"_s,     u"飞龙"_s,       u"虫"_s,     u"兽"_s,     u"笔记"_s,     u"大师"_s,
    u"洗刷器"_s,   u"园"_s,     u"室"_s,     u"间"_s,         u"房"_s,     u"厅"_s,     u"池"_s,       u"湖"_s,
    u"河"_s,       u"江"_s,     u"海"_s,     u"山"_s,         u"岭"_s,     u"岗"_s,     u"海沟"_s,     u"碑"_s,
    u"所"_s,       u"局"_s,     u"站"_s,     u"酒店"_s,       u"玻璃"_s,   u"电子"_s,   u"霓虹"_s,     u"真菌"_s,
    u"水母"_s,     u"蘑菇"_s,   u"鱼"_s,     u"蛟"_s,         u"鲲"_s,     u"鹏"_s,     u"诡计"_s,     u"活性"_s,
    u"特性"_s,     u"肉体"_s,   u"血肉"_s,   u"霓虹"_s,       u"奶"_s,     u"糖"_s,     u"帽"_s,       u"头盔"_s,
    u"手套"_s,     u"水"_s,     u"液体"_s,   u"天堂"_s,       u"乐园"_s,   u"净土"_s,   u"怀抱"_s,     u"思维"_s,
    u"装置"_s,     u"奇珍"_s,   u"舞步"_s,   u"华尔兹"_s,     u"杯"_s,     u"碗"_s,     u"路"_s,       u"桥"_s,
    u"船"_s,       u"档案"_s,   u"星"_s,     u"皇帝"_s,       u"倒吊者"_s, u"轮盘"_s,   u"十字架"_s,   u"审判"_s,
    u"问候"_s,     u"温室"_s,   u"房"_s,
};

QString random_nickname()
{
    if (QLocale::system().name() != "zh_CN")
    {
        return {};
    }
    QString nickname;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> adjective_distribute(0, sizeof(adjective) / sizeof(adjective[0]) - 1);
    std::uniform_int_distribution<> noun_distribute(0, sizeof(noun) / sizeof(noun[0]) - 1);
    nickname += adjective[adjective_distribute(gen)];
    nickname += noun[noun_distribute(gen)];
    return nickname;
}