/******************
 版本号：v1.0
 作  者：唐攀
 日  期：2019-12-1
******************/

#ifndef COMMON_H
#define COMMON_H

class Common
{
public:
    enum gameLeve       //游戏难度
    {
        LOW_LEVE = 0,
        MIDD_LELEVE = 1,
        HEIGHT_LEVE = 2,
        CUSOM_LEVE = 3
    };

    enum lowset         //初级设定
    {
        LOW_ROW_AND_COL = 10,       //行列数
        LOW_MINE_NUM = 2           //雷数
    };

    enum middleset      //中级设定
    {
        MIDDLE_ROW_AND_COL = 16,
        MIDDLE_MINE_NUM = 40
    };

    enum heightset      //高级设定
    {
        HEIGHT_ROW = 16,
        HEIGHT_COL = 30,
        HEIGHT_MINE_NUM = 99
    };

    enum mapset     //图片大小设置
    {
        MAP_WIDTH = 31,
        MAP_HEIGHT = 31
    };
};

#endif // COMMON_H
