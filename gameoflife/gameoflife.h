#ifndef _GAMEOFLIFE_h
#define _GAMEOFLIFE_h

#define _RULE_NEWS_

#ifdef _RULE_CONWAY_
#define RULE_EL 2
#define RULE_EU 3
#define RULE_FL 3
#define RULE_FU 3
#endif

#ifdef _RULE_34_
#define RULE_EL 3
#define RULE_EU 4
#define RULE_FL 3
#define RULE_FU 4
#endif

#ifdef _RULE_1021_
#define RULE_EL 4
#define RULE_EU 5
#define RULE_FL 5
#define RULE_FU 5
#endif

#ifdef _RULE_5766_
#define RULE_EL 5
#define RULE_EU 7
#define RULE_FL 6
#define RULE_FU 6
#endif

#ifdef _RULE_4526_
#define RULE_EL 4
#define RULE_EU 5
#define RULE_FL 2
#define RULE_FU 6
#endif

#ifdef _RULE_NEWS_
#define RULE_EL 2
#define RULE_EU 2
#define RULE_FL 0
#define RULE_FU 1
#endif

#ifdef _RULE_GROWCHAOS_
#define RULE_EL 1
#define RULE_EU 11
#define RULE_FL 10
#define RULE_FU 12
#endif

#ifdef _RULE_KEEPOSI_
#define RULE_EL 2
#define RULE_EU 2
#define RULE_FL 7
#define RULE_FU 27
#endif

#ifdef _RULE_RANDOMSHAPE_
#define RULE_EL 2
#define RULE_EU 20
#define RULE_FL 15
#define RULE_FU 27
#endif

void rand_gen();
void tick();
void test_two();

#endif
