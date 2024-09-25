#include <iostream>
#include <conio.h>
#include <windows.h>

class WuKong {

public:
    double atkrate = 1.0;
    double defrate = 1.0;
    int hp = 200;
    int atk = 15;
    int def = 20;
    int step = 1;
    int tmpstep;
    double damagerate = 1.0;   
};

class Enermy {

public:
    double atkrate = 1.5;
    double defrate = 0.8;
    int hp = 600;
    int atk = 10;
    int def = 0;
    int step = 2;
    int tmpstep;
    double damagerate = 1.0;
};

class SkillProperty {

public:
    int time;
    int stepup;
    int atkup;
    int defup;
    double atkrate;
    double defrate;
    double damagerate;
    int tmptime = 0;
    int mark = 0;
};

class CurrantWukong : public WuKong {

public:

    class Pskill : public SkillProperty {

    public:

        void function(CurrantWukong& p) {
            tmptime = time;
            p.atk += atkup;
            p.def += defup;
            p.step += stepup;
            p.atkrate *= atkrate;
            p.defrate *= defrate;
            p.damagerate = damagerate;
            mark = 1;
            if (p.step > 3) p.step = 3; 
        }

        void reset(CurrantWukong& cp) {
            cp.atk -= atkup;
            cp.def -= defup;
            cp.atkrate /= atkrate;
            cp.defrate /= defrate;
            cp.step -= stepup;
            tmptime = 0;
            mark = 0;
        }

    };
    Pskill wsk1 = {2, 0, 30, 0, 2.0, 1.0, 1.0};
    Pskill wsk2 = {2, 0, 0, 35, 1.0, 0.5, 1.0};
    Pskill wsk3 = {3, 1, 0, 0, 1.0, 1.0, 1.5};

};

class CurrantEnermy : public Enermy {

public:

    class Eskill : public SkillProperty {

    public:

        void function(CurrantEnermy& e){
            tmptime = time;
            e.atk += atkup;
            e.def += defup;
            e.step += stepup;
            e.atkrate *= atkrate;
            e.defrate *= defrate;
            e.damagerate = damagerate;
            mark = 1;
            if (e.step > 3) e.step = 3;
        }

        void reset(CurrantEnermy& ce) {
            ce.atk -= atkup;
            ce.def -= defup;
            ce.atkrate /= atkrate;
            ce.defrate /= defrate;
            ce.step -= stepup;
            tmptime = 0;
            mark = 0;
        }

    };
    Eskill esk1 = {4, 0, 15, 0, 1.2, 1.0, 1.0};
    Eskill esk2 = {2, 0, 0, 50, 1.0, 0.7, 1.0};
    Eskill esk3 = {1, 0, 20, 0, 1.2, 2.5, 1.0};

};

void PAttack(CurrantEnermy& e, CurrantWukong& p) {
    int damage = p.damagerate * p.atk * p.atkrate * (1 - e.def / (100 + e.def * 2.0)) * e.defrate;
    std::cout << "xx受到" << damage << "伤害" << std::endl;
    e.hp -= damage;
    p.damagerate = 1.0;
    Sleep(1000);
    if (e.hp > 0) {
        std::cout << "xx剩余血量" << e.hp << std::endl;
        Sleep(2000);
    }
}

void EAttack(CurrantWukong& p, CurrantEnermy& e) {
    int damage = e.damagerate * e.atk * e.atkrate * (1 - p.def / (100 + p.def * 2.0)) * p.defrate;
    std::cout << "you受到" << damage << "伤害" << std::endl;
    p.hp -= damage;
    e.damagerate = 1.0;
    Sleep(1000);
    if (p.hp > 0) {
        std::cout << "you剩余血量" << p.hp << std::endl;
        Sleep(2000);
    }
}

void PSkilllast(CurrantWukong& cp) {
    cp.tmpstep = cp.step;
    if (cp.wsk1.mark) {
        if (cp.wsk1.tmptime) {
            cp.wsk1.tmptime--;
        } else {
            cp.wsk1.reset(cp);
        }
    }
    if (cp.wsk2.mark) {
        if (cp.wsk2.tmptime) {
            cp.wsk2.tmptime--;
        } else {
            cp.wsk2.reset(cp);
        }
    }
    if (cp.wsk3.mark) {
        if (cp.wsk3.tmptime) {
            cp.wsk3.tmptime--;
        } else {
            cp.wsk3.reset(cp);
        }
    }
}

void ESkilllast(CurrantEnermy& ce) {
    ce.tmpstep = ce.step;
    if (ce.esk1.mark) {
        if (ce.esk1.tmptime) {
            ce.esk1.tmptime--;
        } else {
            ce.esk1.reset(ce);
        }
    }
    if (ce.esk2.mark) {
        if (ce.esk2.tmptime) {
            ce.esk2.tmptime--;
        } else {
            ce.esk2.reset(ce);
        }
    }
    if (ce.esk3.mark) {
        if (ce.esk3.tmptime) {
            ce.esk3.tmptime--;
        } else {
            ce.esk3.reset(ce);
        }
    }
}

bool Battleloop(CurrantWukong& cp, CurrantEnermy& ce) {
    int loop = 1;
    int s_choose;
    cp.tmpstep = cp.step; 
    do{
        

        while (cp.tmpstep > 0) {
            std::cout << "选择您的操作：\n" << "c : 攻击\t" << "s : 打开技能页面\n"; 
            int choose = getch();
            if (choose == 'c') {
                PAttack(ce, cp);
                if (ce.hp < 1) break;
                cp.tmpstep--;
                continue;
            } else if (choose == 's') {
                std::cout << "选择技能：\n" << "1 Skill1 增加攻击力，造成伤害小幅提升，持续2回合\t";
                std::cout << "2 Skill2 增加防御，受到伤害减少，持续2回合\n" << "3 Skill3 造成一次150%倍率的伤害，行动回合增加3回合\n";
                s_choose = getch();
            }
            if (s_choose == '1') {
                if (!cp.wsk1.tmptime) {
                    cp.wsk1.function(cp);
                    std::cout << "攻击和伤害提升\n";
                    Sleep(1000);
                    cp.tmpstep--;
                } else {
                    std::cout << "该技能处于CD中\n";
                    Sleep(1000);
                    continue;
                }

            }

            

            if (s_choose == '2') {
                if (!cp.wsk2.tmptime) {
                    cp.wsk2.function(cp);
                    std::cout << "防御提升，受到伤害减少\n";
                    Sleep(1000);
                    cp.tmpstep--;
                } else {
                    std::cout << "该技能处于CD中\n";
                    Sleep(1000);
                    continue;
                }
            }

            if (s_choose == '3') {
                if (!cp.wsk3.tmptime) {
                    cp.wsk3.function(cp);
                    std::cout << "行动回数增加\n";
                    Sleep(1000);
                    PAttack(ce, cp);
                    if (ce.hp < 1) break;
                    cp.tmpstep--;
                } else {
                    std::cout << "该技能处于CD中\n";
                    Sleep(1000);
                    continue;
                }
            }
        }

        PSkilllast(cp);

        if (ce.hp < 1) break;

        if (loop % 4 == 1) {
            ce.esk1.function(ce);
            std::cout << "xx愤怒地挥舞着刀剑\n攻击与造成伤害提升\n";
            Sleep(1000);
            ce.esk2.function(ce);
            std::cout << "xx全身弥漫着邪气\n防御提升，受到伤害减少\n";
            Sleep(1000);
        }

        if (loop % 4 == 2) {
            EAttack(cp, ce);
            EAttack(cp, ce); 
        }

        if (loop % 4 == 3) {
            ce.esk3.function(ce);
            std::cout << "xx蓄力中，周围弥漫着危险的气息\n";
            Sleep(1000);
        }

        if (loop % 4 == 0) {
            EAttack(cp, ce);
            EAttack(cp, ce);
            EAttack(cp, ce);
        }

        loop++;

        ESkilllast(ce);

    } while(cp.hp > 0 && ce.hp > 0);

    if (cp.hp > 0) return true;
    else return false;
}



int main() {

    CurrantWukong CWK;
    CurrantEnermy cxx;
    
    std::cout << "WARNING!!\tWARNING!!\tWARNING!!\tWARNING!!\n";
    getch();
    std::cout << "\txx emerge and rush towards you\n";
    getch();
    if (Battleloop(CWK, cxx)) std::cout << "恭喜你取得胜利\n";
    else std::cout << "你还没有发挥出大圣真正的实力，这使你充满了决心\n"; 

    return 0;
}