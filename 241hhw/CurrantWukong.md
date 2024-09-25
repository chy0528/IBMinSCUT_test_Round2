# OOP实验的说明

------------------------------------

## 背景  

~~大圣在路上遇见了捣乱的小妖，但大圣今天心情很差，不屑于出手，请你帮大圣解决小妖。~~

一个简单的回合制遭遇战。

## 游玩Tips  

- 跟据提示选择选项 没提示为按任意键继续

  ~~请不要输入太快~~

- 在合适的时机使用技能是制胜关键

- 游玩愉快

------------------------------------

## 类与重要函数

### 类

#### 父类

- `class WuKong{}   class Enermy{}`

  储存了敌我对象的原始数值

- `class SkillProperty{}`

  储存敌我双方技能的基本参数

#### 子类

- `class CurrantWukong : public WuKong {}`

  `class CurrantEnermy : public Enermy {}`

  将父类的原始数值继承用于相关计算，并定义自身所属技能

- `class Pskill : public SkillProperty {}`

  `class Eskill : public SkillProperty {}`

  继承技能基本参数，同时具有技能开关相关效果函数，以用于相关计算

------------------------------------

### 函数

#### 主要函数

- `void PAttack(CurrantEnermy& e, CurrantWukong& p) {}`

  进行攻击计算

- `void function(CurrantEnermy& e) {}`

  技能效果（开）

  `void reset(CurrantEnermy& ce) {}`
  
  技能效果（关）

- `void ESkilllast(CurrantEnermy& ce) {}`

  控制技能持续时间

- `bool Battleloop(CurrantWukong& cp, CurrantEnermy& ce) {}`

  进行战斗相关数据计算
