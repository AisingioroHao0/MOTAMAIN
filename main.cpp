#include<vector>
#include<map>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include"acllib.h"
#define Windows_Width 900
#define Windows_Height 650
#define Scene_Length 550
#define Element_Length 50
#define Number_size 25
#define Wall 0

#define Up 1
#define Down -1

#define Door 2
#define Red_Door 21
#define Blue_Door 22
#define Yellow_Door 23
#define Black_Door 24
#define Green_Door 25

#define Key 3
#define Red_Key 31
#define Blue_Key 32
#define Yellow_Key 33

#define Equip 4
#define Sword 41
#define Shield 42
#define ATN 43
#define DEF 44
#define Blue_drug 45
#define Red_drug 46

#define Npc 5
#define NPC_key_merchat 50
#define NPC_nature_merchat 51
#define NPC_ATN 52
#define NPC_DEF 53
#define NPC_DOOR 54

#define Monster 10
#define Red_Shrek 100 //70 15 2 2 2
#define Green_Shrek 101 //50 20 1 1 1
#define Black_Shrek 102 //200 35 10 5 5
#define Human_skeleton 103 //110 25 5 5 4
#define Skeleton_Captain 104 //150 40 20 8 6
#define Wizard 105 //125 50 25 10 7
#define Small_Bat 106 //100 20 5 3 3
#define Big_Bat 107 //150 65 30 10 8
#define Red_Bat 108 //550 160 90 25 20
#define Zombie 109 //300 75 45 13 10
#define Swordman 110 //500 115 65 15 15
#define Soldier 111 //450 150 90 25 20
#define Shield_fighter 112 //850 350 200 45 40
#define Knight 113 //1600 1306 1200 117 100
struct Information
{
	int X, Y;
	int ID1, ID2;
};
struct Attribute
{
	int AK, DE, HP;
	int money, exp;
};
struct Data
{
	Attribute attribute;
	ACL_Image image;
};
std::map<int, Data> DataBase;
std::vector<Information> L1, L2, L3, L4, L5, L6;
class Element
{
public:
	Element(Information data2)
	{
		information = data2;
		attribute = DataBase[data2.ID2].attribute;
		level = 0;
		red_key = 0;
		blue_key = 0;
		yellow_key = 0;
		green_key = 0;
	}
	Information information;
	Attribute attribute;
	int red_key, blue_key, yellow_key,green_key,level;
	virtual bool interoperate(Element*)
	{
		return 1;
	}
	virtual ~Element()
	{
		std::cout << "~" << information.ID1 << '\n';
	}
};
class Enemy :
	public Element
{
public:
	Enemy(Information data2):Element(data2) 
	{
	}
	~Enemy()
	{
		std::cout << "~" << information.ID2 << ' ';
	}
};
class Good :
	public Element
{
public:
	Good(Information data2) :Element(data2) 
	{
	}
	~Good()
	{
		std::cout << "~" << information.ID2 << ' ';
	}
};
class NPC :
	public Element
{
public:
	NPC(Information data2 ):Element(data2) 
	{
	}
	~NPC()
	{
		std::cout << "~" <<information.ID2<< ' ';
	}
};
class Protagonist :
	public Element
{
public:
	Protagonist(Information data2) :Element(data2)
	{
		attribute.HP = 800;
		attribute.AK = 20;
		attribute.DE = 20;
		attribute.exp = 100;
		level = 0;
		red_key = 1;
		blue_key = 0;
		yellow_key = 0;
	}
	bool interoperate(Element* object)
	{
		if (object == NULL)
		{
			std::cout << "Obbject_Error";
			return 0;
		}
		switch (object->information.ID1)
		{
		case Npc:
			return 0; break;
		case Key:
			switch (object->information.ID2)
			{
			case Yellow_Key: yellow_key++; return 1;
			case Red_Key: red_key++; return 1;
			case Blue_Key:blue_key++; return 1;
			default:return 0;
			}
		case Door:
			switch (object->information.ID2)
			{
			case Black_Door:
				return 1;
			case Yellow_Door:
				if (yellow_key)
				{
					yellow_key--;
					return 1;
				}
				else
				{
					return 0;
				}
				break;
			case Red_Door:
				if (red_key)
				{
					red_key--;
					return 1;
				}
				else
				{
					return 0;
				}
				break;
			case Blue_Door:
				if (blue_key)
				{
					blue_key--;
					return 1;
				}
				else
				{
					return 0;
				}
				break;
			case Green_Door:
				if (green_key)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			default:return 0;
			}
		case Equip:
			switch (object->information.ID2)
			{
			case Sword:attribute.AK += object->attribute.AK; break;
			case ATN:attribute.AK += object->attribute.AK; break;
			case Shield:attribute.DE += object->attribute.DE; break;
			case DEF:attribute.DE += object->attribute.DE; break;
			case Blue_drug:attribute.HP += object->attribute.HP; break;
			case Red_drug:attribute.HP += object->attribute.HP; break;
			}
			return 1;
		case Monster:
			if (fight(object))
			{
				attribute.money += object->attribute.money;
				attribute.exp += object->attribute.exp;
				system("cls");
				std::cout << "YOU" << "                  "<<"Enemy"<<'\n';
				std::cout << "HP " << attribute.HP << "                  " << object->attribute.HP << '\n';
				std::cout << "AK" << attribute.AK << "                  " << object->attribute.AK << '\n';
				std::cout << "DE" << attribute.DE << "                  " << object->attribute.DE << '\n';
				std::cout << "exp" << attribute.exp << "                  " << object->attribute.exp << '\n';
				std::cout << "money" << attribute.money <<"                  " << object->attribute.money << '\n';
				return 1;
			}
			else
			{
				msgBox("游戏结束","你死了",1);
				return 0;
			}
		}
	}
	bool fight(Element* object)
	{
		if (attribute.DE > object->attribute.AK&&attribute.AK>object->attribute.DE)
		{
			return 1;
		}
		if (object->attribute.DE > attribute.AK)
		{
			return 0;
		}
		int sim_player_hp = attribute.HP, sim_object_hp = object->attribute.HP;
		while (1)
		{
			sim_object_hp -= (attribute.AK - object->attribute.DE);
			if (sim_object_hp <= 0)
			{
				attribute.HP = sim_player_hp;
				return 1;
			}
			sim_player_hp -= (object->attribute.AK - attribute.DE);
			if (sim_player_hp <= 0)
			{
				return 0;
			}
		}
	}
	~Protagonist()
	{
		std::cout << "~" << information.ID2 << ' ';
	}

};
class Scene
{
public:
	Scene(std::vector<Information> data1)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int o = 0; o < 11; o++)
			{
				wall[i][o] = 0;
			}
		}
		for (int i = 0; i < data1.size(); i++)
		{
			if (data1[i].ID1 == Wall)
			{
				wall[data1[i].X][data1[i].Y] = 1;
			}
			else if (data1[i].ID1 == 1)
			{
				upfloor = data1[i];
			}
			else if (data1[i].ID1 == -1)
			{
				downfloor = data1[i];
			}
			else
			{
				Element* tmp = NULL;
				switch (data1[i].ID1)
				{
				case Npc:tmp = new NPC(data1[i]); break;
				case Key:tmp = new Good(data1[i]); break;
				case Door:tmp = new Good(data1[i]); break;
				case Equip:tmp = new Good(data1[i]); break;
				case Monster:tmp = new Enemy(data1[i]); break;
				}
				if (tmp != NULL)
				{
					elementset.push_back(tmp);
				}
			}
		}

	}
	Information upfloor, downfloor;
	std::vector<Element*> elementset;
	ACL_Image image;
	bool wall[11][11];
	void DrawScene()
	{
		beginPaint();
		putImageScale(&image, 0, 0, Windows_Width, Windows_Height);
		for (int i = 0; i < elementset.size(); i++)
		{
			putImageTransparent(&DataBase[elementset[i]->information.ID2].image, elementset[i]->information.X* Element_Length + Element_Length, elementset[i]->information.Y* Element_Length + Element_Length, Element_Length, Element_Length, MAGENTA);
		}
		endPaint();
	}
	~Scene()
	{
		std::cout << "~Scene" << '\n';
	}
};

Element* player;
Information start = { 5,10,-9999,-9999 };
Scene* scene[6];
ACL_Image P_W, P_A, P_S, P_D, P_Npc,P_NPC_ATN,P_NPC_DEF,P_NPC_DOOR,P_NPC_Key,P_NPC_nature,Store;
ACL_Image N0, N1, N2, N3, N4, N5, N6, N7, N8, N9;
ACL_Image HP, AK, DE, EXP, MONEY, RK, BK, YK;
bool bgame = 1, bstore = 0,bplot=0,bbuykey=0,bbuynature=0;//控制函数开关
void DrawPlayer(int key);
void DrawStore();
void DrawAttribute();
void DrawPlot(int ID2);
void ClearDraw();
void keyboardevent(int key, int event);
void mouseevent(int x, int y, int button, int event);
void LoadData();
int Setup()
{
	initConsole();
	initWindow("MODA_Zero", 0, 0, Windows_Width, Windows_Height);
	LoadData();
	player = new Protagonist(start);
	scene[0] = new Scene(L1);
	scene[1] = new Scene(L2);
	scene[2] = new Scene(L3);
	scene[3] = new Scene(L4);
	scene[4] = new Scene(L5);
	scene[5] = new Scene(L6);
	for (auto it = DataBase.begin(); it != DataBase.end(); it++)
	{
		std::cout << it->first << ' ' << it->second.attribute.AK <<' '<< it->second.attribute.DE << ' ' << it->second.attribute.HP<<' ' << it->second.attribute.exp<< it->second.attribute.money<<'\n';
	}
	/*for (int i = 0; i < 11; i++)
	{
		for (int o = 0; o < 11; o++)
		{
			std::cout << scene[2]->wall[o][i] << ' ';
		}
		std::cout << '\n';
	}*/
	loadImage("level1.bmp", &scene[0]->image);
	loadImage("level2.bmp", &scene[1]->image);
	loadImage("level3.bmp", &scene[2]->image);
	loadImage("level4.bmp", &scene[3]->image);
	loadImage("level5.bmp", &scene[4]->image);
	loadImage("level6.bmp", &scene[5]->image);
	scene[0]->DrawScene();
	DrawAttribute();
	DrawPlayer('W');
	registerKeyboardEvent(keyboardevent);
	registerMouseEvent(mouseevent);
	return 0;
}
void keyboardevent(int key, int event)
{
	if (bgame)
	{
		if (event == KEY_DOWN)
		{
			int ox = player->information.X, oy = player->information.Y;
			bool Re_Dw=1;
			switch (key)
			{
			case 'W':oy--; break;
			case 'A':ox--; break;
			case 'S':oy++; break;
			case 'D':ox++; break;
			default:Re_Dw = 0;
			}
			if (ox < 0 || ox >= 11 || oy < 0 || oy >= 11)
			{
				Re_Dw = 0;
			}
			if (Re_Dw)
			{
				if (ox == 5 && oy == 0 && player->level == 2)
				{
					bstore = 1;
					bgame = 0;
					DrawStore();
					Re_Dw = 0;
				}
				else if (scene[player->level]->downfloor.X == ox && scene[player->level]->downfloor.Y == oy)
				{
					player->level--;
					ox = scene[player->level]->upfloor.X;
					oy = scene[player->level]->upfloor.Y;
					goto g1;
				}
				else if (scene[player->level]->upfloor.X == ox && scene[player->level]->upfloor.Y == oy)
				{
					player->level++;
					ox = scene[player->level]->downfloor.X;
					oy = scene[player->level]->downfloor.Y;
					goto g1;
				}
				if (scene[player->level]->wall[ox][oy] != 1)
				{
					for (int i = 0; i < scene[player->level]->elementset.size(); i++)
					{
						if (scene[player->level]->elementset[i] == NULL)
						{
							continue;
						}
						if (ox == scene[player->level]->elementset[i]->information.X && oy == scene[player->level]->elementset[i]->information.Y)
						{
							if (scene[player->level]->elementset[i]->information.ID1 == Npc)
							{
								bplot = 1;
								Re_Dw = 0;
								ClearDraw();
								scene[player->level]->DrawScene();
								DrawPlayer(key);
								DrawAttribute();
								DrawPlot(scene[player->level]->elementset[i]->information.ID2);
								if (scene[player->level]->elementset[i]->information.ID2 == NPC_ATN || scene[player->level]->elementset[i]->information.ID2 == NPC_DEF || scene[player->level]->elementset[i]->information.ID2 == NPC_DOOR)
								{
									delete scene[player->level]->elementset[i];
									break;
								}
							}
							else if (player->interoperate(scene[player->level]->elementset[i]))
							{
								player->information.X = ox;
								player->information.Y = oy;
								delete scene[player->level]->elementset[i];
								ClearDraw();
								scene[player->level]->DrawScene();
								DrawPlayer(key);
								DrawAttribute();
								Re_Dw = 0;
								break;
							}
							Re_Dw = 0;
						}
					}
					g1:if (Re_Dw)
					{
						player->information.X = ox;
						player->information.Y = oy;
						ClearDraw();
						scene[player->level]->DrawScene();
						DrawPlayer(key);
						DrawAttribute();
						Re_Dw = 0;
					}
				}
				else if(Re_Dw)
				{
					scene[player->level]->DrawScene();
					DrawAttribute();
					DrawPlayer(key);
					Re_Dw = 0;
				}
			}
			else
			{
				scene[player->level]->DrawScene();
				DrawAttribute();
				DrawPlayer(key);
			}
		}
	}
}
void DrawPlayer(int key='S')
{
	beginPaint();
	switch (key)
	{
	case 'W':putImageTransparent(&P_W, player->information.X * Element_Length + Element_Length, player->information.Y * Element_Length + Element_Length, Element_Length, Element_Length, MAGENTA); break;
	case 'A':putImageTransparent(&P_A, player->information.X * Element_Length + Element_Length, player->information.Y * Element_Length + Element_Length, Element_Length, Element_Length, MAGENTA); break;
	case 'S':putImageTransparent(&P_S, player->information.X * Element_Length + Element_Length, player->information.Y * Element_Length + Element_Length, Element_Length, Element_Length, MAGENTA); break;
	case 'D':putImageTransparent(&P_D, player->information.X * Element_Length + Element_Length, player->information.Y * Element_Length + Element_Length, Element_Length, Element_Length, MAGENTA); break;
	}
	endPaint();
}
void mouseevent(int x, int y, int button, int event)
{
	if (bstore)
	{
		if (button == LEFT_BUTTON && event == BUTTON_DOWN)
		{
			bool Re_Dw = 0;
			if (x >= 3 * Element_Length && x <= 10*Element_Length)
			{
				if (y >= 9 * Element_Length && y <= 10 * Element_Length)
				{
					Re_Dw = 1;
					bstore = 0;
					bgame = 1;
				}
				else
				{
					if (x >= 8 * Element_Length && x <= 10 * Element_Length)
					{
						switch (y / Element_Length)
						{
						case 5:
							if (player->attribute.money >= 25)
							{
								player->attribute.HP += 800;
								player->attribute.money -= 25;
								Re_Dw = 1;
							}
							break;
						case 6:
							if (player->attribute.money >= 25)
							{
								player->attribute.AK += 25;
								player->attribute.money -= 25;
								Re_Dw = 1;
							}
							break;
						case 7:
							if (player->attribute.money >= 25)
							{
								player->attribute.DE += 25;
								player->attribute.money -= 25;
								Re_Dw = 1;
							}
							break;
						}

					}
				}
			}
			if (Re_Dw&&bstore)
			{
				ClearDraw();
				scene[player->level]->DrawScene();
				DrawPlayer();
				DrawStore();
				DrawAttribute();
			}
			else if (Re_Dw)
			{
				ClearDraw();
				scene[player->level]->DrawScene();
				DrawPlayer();
				DrawAttribute();
			}
		}
	}
	if (bplot)
	{
		if (button == LEFT_BUTTON && event == BUTTON_DOWN)
		{
			if (bbuykey)
			{
				if (x >= 5 * Element_Length && x <= 11 * Element_Length)
				{
					if (y >= 5 * Element_Length && y <= 6.2 * Element_Length)
					{
						if (player->attribute.money >= 25)
						{
							player->blue_key++;
							player->attribute.money -= 25;
							ClearDraw();
							scene[player->level]->DrawScene();
							DrawPlayer();
							DrawAttribute();
							bplot = 0;
							bbuykey = 0;
							bgame = 1;
						}
					}
					else if (y > 6.2 * Element_Length && y <= 7.9 * Element_Length)
					{
						if (player->attribute.money >= 25)
						{
							player->red_key++;
							player->attribute.money -= 25;
							ClearDraw();
							scene[player->level]->DrawScene();
							DrawPlayer();
							DrawAttribute();
							bplot = 0;
							bbuykey = 0;
							bgame = 1;
						}
						else
						{
							msgBox("提示", "金币不足", 0);
						}
					}
					else if (y >= 8 * Element_Length && y <= 9.1 * Element_Length)
					{
						if (player->attribute.money >= 25)
						{
							player->yellow_key++;
							player->attribute.money -= 25;
							ClearDraw();
							scene[player->level]->DrawScene();
							DrawPlayer();
							DrawAttribute();
							bplot = 0;
							bbuykey = 0;
							bgame = 1;
						}
						else
						{
							msgBox("提示", "金币不足", 0);
						}
					}
					else if (y >= 9.2 * Element_Length && y <= 11 * Element_Length)
					{
						ClearDraw();
						scene[player->level]->DrawScene();
						DrawAttribute();
						DrawPlayer();
						bplot = 0;
						bbuykey = 0;
						bgame = 1;
					}
				}
			}
			else if (bbuynature)
			{
				if (x >= 5 * Element_Length && x <= 11 * Element_Length)
				{
					if (y >= 5 * Element_Length && y <= 6.2 * Element_Length)
					{
						if (player->attribute.exp>=25)
						{
							player->attribute.exp -= 25;
							player->attribute.AK += 25;
							bplot = 0;
							bbuynature = 0;
							bgame = 1;
							ClearDraw();
							scene[player->level]->DrawScene();
							DrawPlayer();
							DrawAttribute();
						}
						else
						{
							msgBox("提示", "经验不足", 0);
						}
					}
					else if (y >= 7 * Element_Length && y <= 7.9 * Element_Length)
					{
						if (player->attribute.exp >= 25)
						{
							player->attribute.exp -= 25;
							player->attribute.DE += 25;
							bplot = 0;
							bbuynature = 0;
							bgame = 1;
							ClearDraw();
							scene[player->level]->DrawScene();
							DrawPlayer();
							DrawAttribute();
						}
						else
						{
							msgBox("提示", "经验不足", 0);
						}
					}
					else if (y >= 8 * Element_Length && y <= 9.1 * Element_Length)
					{
						ClearDraw();
						scene[player->level]->DrawScene();
						DrawPlayer();
						DrawAttribute();
						bplot = 0;
						bbuynature = 0;
						bgame = 1;
					}
				}
			}
			else
			{
			    ClearDraw();
			    scene[player->level]->DrawScene();
			    DrawPlayer();
			    DrawAttribute();
				bplot = 0;
				bgame = 1;
			}
		}
	}
}
void DrawStore()
{
	beginPaint();
	putImageTransparent(&Store, 3 * Element_Length,3* Element_Length, 7 * Element_Length, 7 * Element_Length, MAGENTA);
	endPaint();
}
void DrawAttribute()
{
	beginPaint();
	int tmp = player->attribute.HP;
	std::stringstream ss;
	std::string s;
	ss << tmp;
	ss >> s;
	putImageTransparent(&HP, 13 * Element_Length, Element_Length, Element_Length, Element_Length, MAGENTA);
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0':putImageTransparent(&N0, 15 * Element_Length+i* Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '1':putImageTransparent(&N1, 15 * Element_Length + i * Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '2':putImageTransparent(&N2, 15 * Element_Length + i * Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '3':putImageTransparent(&N3, 15 * Element_Length + i * Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '4':putImageTransparent(&N4, 15 * Element_Length + i * Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '5':putImageTransparent(&N5, 15 * Element_Length + i * Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '6':putImageTransparent(&N6, 15 * Element_Length + i * Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '7':putImageTransparent(&N7, 15 * Element_Length + i * Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '8':putImageTransparent(&N8, 15 * Element_Length + i * Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '9':putImageTransparent(&N9, 15 * Element_Length + i * Number_size, Element_Length, Number_size, Element_Length, MAGENTA); break;
		}
	}
	ss.clear();
	s.clear();
	tmp = player->attribute.AK;
	ss << tmp;
	ss >> s;
	putImageTransparent(&AK, 13 * Element_Length,2* Element_Length, Element_Length, Element_Length, MAGENTA);
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0':putImageTransparent(&N0, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '1':putImageTransparent(&N1, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '2':putImageTransparent(&N2, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '3':putImageTransparent(&N3, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '4':putImageTransparent(&N4, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '5':putImageTransparent(&N5, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '6':putImageTransparent(&N6, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '7':putImageTransparent(&N7, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '8':putImageTransparent(&N8, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '9':putImageTransparent(&N9, 15 * Element_Length + i * Number_size, 2*Element_Length, Number_size, Element_Length, MAGENTA); break;
		}
	}
	ss.clear();
	s.clear();
	tmp = player->attribute.DE;
	ss << tmp;
	ss >> s;
	putImageTransparent(&DE, 13 * Element_Length,3* Element_Length, Element_Length, Element_Length, MAGENTA);
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0':putImageTransparent(&N0, 15 * Element_Length + i * Number_size,3* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '1':putImageTransparent(&N1, 15 * Element_Length + i * Number_size, 3*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '2':putImageTransparent(&N2, 15 * Element_Length + i * Number_size,3* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '3':putImageTransparent(&N3, 15 * Element_Length + i * Number_size, 3*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '4':putImageTransparent(&N4, 15 * Element_Length + i * Number_size, 3*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '5':putImageTransparent(&N5, 15 * Element_Length + i * Number_size,3* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '6':putImageTransparent(&N6, 15 * Element_Length + i * Number_size, 3*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '7':putImageTransparent(&N7, 15 * Element_Length + i * Number_size, 3*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '8':putImageTransparent(&N8, 15 * Element_Length + i * Number_size, 3*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '9':putImageTransparent(&N9, 15 * Element_Length + i * Number_size, 3*Element_Length, Number_size, Element_Length, MAGENTA); break;
		}
	}
	ss.clear();
	s.clear();
	tmp = player->attribute.money;
	ss << tmp;
	ss >> s;
	putImageTransparent(&MONEY, 13 * Element_Length,4* Element_Length, Element_Length, Element_Length, MAGENTA);
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0':putImageTransparent(&N0, 15 * Element_Length + i * Number_size,4* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '1':putImageTransparent(&N1, 15 * Element_Length + i * Number_size,4* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '2':putImageTransparent(&N2, 15 * Element_Length + i * Number_size,4* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '3':putImageTransparent(&N3, 15 * Element_Length + i * Number_size,4* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '4':putImageTransparent(&N4, 15 * Element_Length + i * Number_size,4*Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '5':putImageTransparent(&N5, 15 * Element_Length + i * Number_size,4* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '6':putImageTransparent(&N6, 15 * Element_Length + i * Number_size,4* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '7':putImageTransparent(&N7, 15 * Element_Length + i * Number_size,4* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '8':putImageTransparent(&N8, 15 * Element_Length + i * Number_size,4* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '9':putImageTransparent(&N9, 15 * Element_Length + i * Number_size,4* Element_Length, Number_size, Element_Length, MAGENTA); break;
		}
	}
	ss.clear();
	s.clear();
	tmp = player->attribute.exp;
	ss << tmp;
	ss >> s;
	putImageTransparent(&EXP, 13 * Element_Length,5* Element_Length, Element_Length, Element_Length, MAGENTA);
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0':putImageTransparent(&N0, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '1':putImageTransparent(&N1, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '2':putImageTransparent(&N2, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '3':putImageTransparent(&N3, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '4':putImageTransparent(&N4, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '5':putImageTransparent(&N5, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '6':putImageTransparent(&N6, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '7':putImageTransparent(&N7, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '8':putImageTransparent(&N8, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '9':putImageTransparent(&N9, 15 * Element_Length + i * Number_size,5* Element_Length, Number_size, Element_Length, MAGENTA); break;
		}
	}
	ss.clear();
	s.clear();
	tmp = player->yellow_key;
	ss << tmp;
	ss >> s;
	putImageTransparent(&YK, 13 * Element_Length, 6 * Element_Length, Element_Length, Element_Length, MAGENTA);
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0':putImageTransparent(&N0, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '1':putImageTransparent(&N1, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '2':putImageTransparent(&N2, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '3':putImageTransparent(&N3, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '4':putImageTransparent(&N4, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '5':putImageTransparent(&N5, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '6':putImageTransparent(&N6, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '7':putImageTransparent(&N7, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '8':putImageTransparent(&N8, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '9':putImageTransparent(&N9, 15 * Element_Length + i * Number_size, 6 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		}
	}
	ss.clear();
	s.clear();
	tmp = player->blue_key;
	ss << tmp;
	ss >> s;
	putImageTransparent(&BK, 13 * Element_Length, 7 * Element_Length, Element_Length, Element_Length, MAGENTA);
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0':putImageTransparent(&N0, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '1':putImageTransparent(&N1, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '2':putImageTransparent(&N2, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '3':putImageTransparent(&N3, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '4':putImageTransparent(&N4, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '5':putImageTransparent(&N5, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '6':putImageTransparent(&N6, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '7':putImageTransparent(&N7, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '8':putImageTransparent(&N8, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '9':putImageTransparent(&N9, 15 * Element_Length + i * Number_size, 7 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		}
	}
	ss.clear();
	s.clear();
	tmp = player->red_key;
	ss << tmp;
	ss >> s;
	putImageTransparent(&RK, 13 * Element_Length, 8 * Element_Length, Element_Length, Element_Length, MAGENTA);
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0':putImageTransparent(&N0, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '1':putImageTransparent(&N1, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '2':putImageTransparent(&N2, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '3':putImageTransparent(&N3, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '4':putImageTransparent(&N4, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '5':putImageTransparent(&N5, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '6':putImageTransparent(&N6, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '7':putImageTransparent(&N7, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '8':putImageTransparent(&N8, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		case '9':putImageTransparent(&N9, 15 * Element_Length + i * Number_size, 8 * Element_Length, Number_size, Element_Length, MAGENTA); break;
		}
	}
	endPaint();
}
void DrawPlot(int ID2)
{
	beginPaint();
	switch (ID2)
	{
	case Npc:
		putImageTransparent(&P_Npc, 0, 0, Scene_Length, Scene_Length, MAGENTA);
		msgBox("游戏结束", "后续剧情开发中.....",0);
		break;
	case NPC_ATN:
		putImageTransparent(&P_NPC_ATN, 0, 0, Scene_Length, Scene_Length, MAGENTA);
		player->attribute.AK += DataBase[NPC_ATN].attribute.AK;
		break;
	case NPC_DEF:
		putImageTransparent(&P_NPC_DEF, 0, 0, Scene_Length, Scene_Length, MAGENTA);
		player->attribute.DE += DataBase[NPC_DEF].attribute.DE;
		break;
	case NPC_DOOR:
		putImageTransparent(&P_NPC_DOOR, 0, 0, Scene_Length, Scene_Length, MAGENTA);
		player->green_key++;
		break;
	case NPC_nature_merchat:
		putImageTransparent(&P_NPC_nature, 0, 0, Scene_Length, Scene_Length, MAGENTA);
		bbuynature = 1;
		break;
	case NPC_key_merchat:
		putImageTransparent(&P_NPC_Key, 0, 0, Scene_Length, Scene_Length, MAGENTA);
		bbuykey = 1;
		break;
	}
	endPaint();
}
void ClearDraw()
{
	beginPaint();
	clearDevice();
	endPaint();
}
void LoadData()
{
	Information information;
	Data DATe;
	int number[37];
	std::fstream goods1("L1.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 87; i++)
	{
		goods1 >> information.X;
		goods1 >> information.Y;
		goods1 >> information.ID1;
		goods1 >> information.ID2;
		L1.push_back(information);
	}
	goods1.close();
	std::fstream goods2("L2.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 92; i++)
	{
		goods2 >> information.X;
		goods2 >> information.Y;
		goods2 >> information.ID1;
		goods2 >> information.ID2;
		L2.push_back(information);
	}
	goods2.close();
	std::fstream goods3("L3.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 83; i++)
	{
		goods3 >> information.X;
		goods3 >> information.Y;
		goods3 >> information.ID1;
		goods3 >> information.ID2;
		L3.push_back(information);
	}
	goods3.close();
	std::fstream goods4("L4.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 87; i++)
	{
		goods4 >> information.X;
		goods4 >> information.Y;
		goods4 >> information.ID1;
		goods4 >> information.ID2;
		L4.push_back(information);
	}
	goods4.close();
	std::fstream goods5("L5.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 81; i++)
	{
		goods5 >> information.X;
		goods5 >> information.Y;
		goods5 >> information.ID1;
		goods5 >> information.ID2;
		L5.push_back(information);
	}
	goods5.close();
	std::fstream goods6("L6.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 27; i++)
	{
		goods6 >> information.X;
		goods6 >> information.Y;
		goods6 >> information.ID1;
		goods6 >> information.ID2;
		L6.push_back(information);
	}
	goods6.close();
	std::fstream Number("number.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 37; i++)
	{
		Number >> number[i];
	}
	Number.close();
	std::fstream Date("date.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 37; i++)
	{
		Date >> DATe.attribute.HP;
		Date >> DATe.attribute.AK;
		Date >> DATe.attribute.DE;
		Date >> DATe.attribute.money;
		Date >> DATe.attribute.exp;
		DataBase[number[i]] = DATe;
	}
	Date.close();
	loadImage("0.bmp", &N0);
	loadImage("1.bmp", &N1);
	loadImage("2.bmp", &N2);
	loadImage("3.bmp", &N3);
	loadImage("4.bmp", &N4);
	loadImage("5.bmp", &N5);
	loadImage("6.bmp", &N6);
	loadImage("7.bmp", &N7);
	loadImage("8.bmp", &N8);
	loadImage("9.bmp", &N9);

	loadImage("ATN.bmp", &DataBase[ATN].image);

	loadImage("Big_Bat.bmp", &DataBase[Big_Bat].image);
	loadImage("Black_Door.bmp", &DataBase[Black_Door].image);
	loadImage("Black_Shrek.bmp", &DataBase[Black_Shrek].image);
	loadImage("Blue_Door.bmp", &DataBase[Blue_Door].image);
	loadImage("Blue_drug.bmp", &DataBase[Blue_drug].image);
	loadImage("Blue_Key.bmp", &BK);
	loadImage("Blue_Key.bmp", &DataBase[Blue_Key].image);
	
	
	
	
	loadImage("DEF.bmp", &DataBase[DEF].image);

	loadImage("EXP.bmp", &EXP);

	loadImage("Green_Door.bmp", &DataBase[Green_Door].image);
	loadImage("Green_Shrek.bmp", &DataBase[Green_Shrek].image);

	loadImage("HP.bmp", &HP);
	loadImage("Human_skeleton.bmp", &DataBase[Human_skeleton].image);

	loadImage("Knight.bmp", &DataBase[Knight].image);

	loadImage("Red_Door.bmp", &DataBase[Red_Door].image);
	loadImage("Red_Key.bmp", &DataBase[Red_Key].image);
	loadImage("Red_Key.bmp", &RK);
	loadImage("Red_drug.bmp", &DataBase[Red_drug].image);
	
	loadImage("Yellow_Key.bmp", &DataBase[Yellow_Key].image);
	loadImage("Sword.bmp", &DataBase[Sword].image);
	loadImage("Shield.bmp", &DataBase[Shield].image);
	loadImage("Small_Bat.bmp", &DataBase[Small_Bat].image);
	
	
	loadImage("Npc.bmp", &DataBase[Npc].image);
	loadImage("NPC_key_merchat.bmp", &DataBase[NPC_key_merchat].image);
	loadImage("NPC_nature_merchat.bmp", &DataBase[NPC_nature_merchat].image);
	loadImage("NPC_ATN.bmp", &DataBase[NPC_ATN].image);
	loadImage("NPC_DEF.bmp", &DataBase[NPC_DEF].image);
	loadImage("NPC_DOOR.bmp", &DataBase[NPC_DOOR].image);
	loadImage("Red_Shrek.bmp", &DataBase[Red_Shrek].image);
	
	
	loadImage("Skeleton_Captain.bmp", &DataBase[Skeleton_Captain].image);
	loadImage("Wizard.bmp", &DataBase[Wizard].image);

	loadImage("Red_Bat.bmp", &DataBase[Red_Bat].image);
	

	loadImage("Swordman.bmp", &DataBase[Swordman].image);
	loadImage("Soldier.bmp", &DataBase[Soldier].image);
	loadImage("Store.bmp", &Store);
	loadImage("Shield_fighter.bmp", &DataBase[Shield_fighter].image);
	loadImage("Sword.bmp", &AK);
	loadImage("Shield.bmp", &DE);

	loadImage("P_W.bmp", &P_W);
	loadImage("P_A.bmp", &P_A);
	loadImage("P_S.bmp", &P_S);
	loadImage("P_D.bmp", &P_D);
	loadImage("P_Npc.bmp", &P_Npc);
	loadImage("P_NPC_ATN.bmp", &P_NPC_ATN);
	loadImage("P_NPC_DEF.bmp", &P_NPC_DEF);
	loadImage("P_NPC_DOOR.bmp", &P_NPC_DOOR);
	loadImage("P_NPC_Key.bmp", &P_NPC_Key);
	loadImage("P_NPC_nature.bmp", &P_NPC_nature);
	
	loadImage("MONEY.bmp", &MONEY);
	
	loadImage("Yellow_Key.bmp", &YK);
	loadImage("Yellow_Door.bmp", &DataBase[Yellow_Door].image);
	
	loadImage("Zombie.bmp", &DataBase[Zombie].image);
	
}