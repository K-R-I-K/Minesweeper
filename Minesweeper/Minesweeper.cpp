#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <queue>
#include <vector>
#include "windows.h"

#define is_bot 1

struct ans
{
	int x = 0;
	int y = 0;
	bool bomb;
	bool openAll = 0;
	std::vector <std::vector<int>> list;
	bool random = 0;
};

void newFild(int (&masView)[11][11])
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			masView[i][j] = 10;
		}
	}
}

void bombs(int (&masLogic)[11][11], int x0, int y0)
{
	for (int i = 0; i < 10; i++)
	{
		int x = rand() % 10 + 1;
		int y = rand() % 10 + 1;
		if (masLogic[x][y] != 9 && x!=x0 && y!=y0) masLogic[x][y] = 9;
		else i--;
	}
}

void createLogic(int (&masLogic)[11][11])
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (masLogic[i][j] == 9) continue;
			if (masLogic[i + 1][j] == 9) n++;
			if (masLogic[i][j + 1] == 9) n++;
			if (masLogic[i - 1][j] == 9) n++;
			if (masLogic[i][j - 1] == 9) n++;
			if (masLogic[i + 1][j + 1] == 9) n++;
			if (masLogic[i - 1][j - 1] == 9) n++;
			if (masLogic[i - 1][j + 1] == 9) n++;
			if (masLogic[i + 1][j - 1] == 9) n++;
			masLogic[i][j] = n;
		}
	}
}

void restart(int (&masView)[11][11], int(&masLogic)[11][11])
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			masView[i][j] = 0;
			masLogic[i][j] = 0;
		}
	}
	newFild(masView);
	//bombs(masLogic, x, y);
	//createLogic(masLogic);
}

void zeroNode(int (&masView)[11][11], int(&masLogic)[11][11], int x, int y)
{
	std::queue <std::pair <int, int> > masQueue;
	bool masUsed[11][11] = { 0 };

	masQueue.push(std::make_pair(x, y));
	masUsed[x][y] = 1;

	while (!masQueue.empty())
	{
		std::pair <int, int> tmp = std::make_pair(masQueue.front().first, masQueue.front().second);
		masQueue.pop();

		if (tmp.second != 1 && !masUsed[tmp.first][tmp.second - 1] && masLogic[tmp.first][tmp.second - 1] < 9)
		{
			if (!masLogic[tmp.first][tmp.second - 1]) masQueue.push(std::make_pair(tmp.first, tmp.second - 1));
			masUsed[tmp.first][tmp.second - 1] = 1;
			masView[tmp.first][tmp.second - 1] = masLogic[tmp.first][tmp.second - 1];
		}
		if (tmp.second != 10 && !masUsed[tmp.first][tmp.second + 1] && masLogic[tmp.first][tmp.second + 1] < 9)
		{
			if (!masLogic[tmp.first][tmp.second + 1]) masQueue.push(std::make_pair(tmp.first, tmp.second + 1));
			masUsed[tmp.first][tmp.second + 1] = 1;
			masView[tmp.first][tmp.second + 1] = masLogic[tmp.first][tmp.second + 1];
		}
		if (tmp.first != 1 && !masUsed[tmp.first - 1][tmp.second] && masLogic[tmp.first - 1][tmp.second] < 9)
		{
			if (!masLogic[tmp.first - 1][tmp.second]) masQueue.push(std::make_pair(tmp.first - 1, tmp.second));
			masUsed[tmp.first - 1][tmp.second] = 1;
			masView[tmp.first - 1][tmp.second] = masLogic[tmp.first - 1][tmp.second];
		}
		if (tmp.first != 10 && !masUsed[tmp.first + 1][tmp.second] && masLogic[tmp.first + 1][tmp.second] < 9)
		{
			if (!masLogic[tmp.first + 1][tmp.second]) masQueue.push(std::make_pair(tmp.first + 1, tmp.second));
			masUsed[tmp.first + 1][tmp.second] = 1;
			masView[tmp.first + 1][tmp.second] = masLogic[tmp.first + 1][tmp.second];
		}

		// + - +
		// - - -
		// + - +

		if (tmp.first != 1 && tmp.second != 1 && !masUsed[tmp.first - 1][tmp.second - 1] && masLogic[tmp.first - 1][tmp.second - 1] < 9)
		{
			if (!masLogic[tmp.first - 1][tmp.second - 1]) masQueue.push(std::make_pair(tmp.first - 1, tmp.second - 1));
			masUsed[tmp.first - 1][tmp.second - 1] = 1;
			masView[tmp.first - 1][tmp.second - 1] = masLogic[tmp.first - 1][tmp.second - 1];
		}
		if (tmp.first != 1 && tmp.second != 10 && !masUsed[tmp.first - 1][tmp.second + 1] && masLogic[tmp.first - 1][tmp.second + 1] < 9)
		{
			if (!masLogic[tmp.first - 1][tmp.second + 1]) masQueue.push(std::make_pair(tmp.first - 1, tmp.second + 1));
			masUsed[tmp.first - 1][tmp.second + 1] = 1;
			masView[tmp.first - 1][tmp.second + 1] = masLogic[tmp.first - 1][tmp.second + 1];
		}
		if (tmp.first != 10 && tmp.second != 1 && !masUsed[tmp.first + 1][tmp.second - 1] && masLogic[tmp.first + 1][tmp.second - 1] < 9)
		{
			if (!masLogic[tmp.first + 1][tmp.second - 1]) masQueue.push(std::make_pair(tmp.first + 1, tmp.second - 1));
			masUsed[tmp.first + 1][tmp.second - 1] = 1;
			masView[tmp.first + 1][tmp.second - 1] = masLogic[tmp.first + 1][tmp.second - 1];
		}
		if (tmp.first != 10 && tmp.second != 10 && !masUsed[tmp.first + 1][tmp.second + 1] && masLogic[tmp.first + 1][tmp.second + 1] < 9)
		{
			if (!masLogic[tmp.first + 1][tmp.second + 1]) masQueue.push(std::make_pair(tmp.first + 1, tmp.second + 1));
			masUsed[tmp.first + 1][tmp.second + 1] = 1;
			masView[tmp.first + 1][tmp.second + 1] = masLogic[tmp.first + 1][tmp.second + 1];
		}
	}
}

ans botLog(int(&masView)[11][11], int(&botLogic)[11][11]) //, bool firstStep)
{
	//srand(time(0));

	//bool firstStep = 1;

	ans ans;
	ans.openAll = 0;

	/*for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			if (masView[i][j] != 10) firstStep = 0;
		}
	}

	if (firstStep)
	{
		ans.x = rand() % 10 + 1;
		ans.y = rand() % 10 + 1;
		ans.bomb = 0;
		return ans;
	}
	else
	{*/
		std::vector <std::vector<int>> list;
		int listcount = -1;
		//list.push_back(std::vector<int>());

		//create groups
		for (int i = 1; i <= 10; i++)
		{
			for (int j = 1; j <= 10; j++)
			{
				if (masView[i][j] == 0) botLogic[i][j] = 1;

				if (botLogic[i][j] != 1 && masView[i][j] != 10 && masView[i][j] != 11)
				{
					int n = 0;
					if (masView[i + 1][j] == 11) { n++; }
					if (masView[i][j + 1] == 11) { n++; }
					if (masView[i - 1][j] == 11) { n++; }
					if (masView[i][j - 1] == 11) { n++; }
					if (masView[i + 1][j + 1] == 11) { n++; }
					if (masView[i - 1][j - 1] == 11) { n++; }
					if (masView[i - 1][j + 1] == 11) { n++; }
					if (masView[i + 1][j - 1] == 11) { n++; }

					if (n == masView[i][j])
					{
						ans.x = i;
						ans.y = j;
						botLogic[i][j] = 1;
						ans.openAll = 1;
						ans.bomb = 0;
						return ans;
					}

					list.push_back(std::vector<int>());
					listcount++;
					list[listcount].push_back(masView[i][j] - n);

					if (masView[i + 1][j] == 10) { list[listcount].push_back((i) * 10 + j); }
					if (masView[i][j + 1] == 10) { list[listcount].push_back((i - 1) * 10 + j + 1); }
					if (masView[i - 1][j] == 10) { list[listcount].push_back((i - 2) * 10 + j); }
					if (masView[i][j - 1] == 10) { list[listcount].push_back((i - 1) * 10 + j - 1); }
					if (masView[i + 1][j + 1] == 10) { list[listcount].push_back((i) * 10 + j + 1); }
					if (masView[i - 1][j - 1] == 10) { list[listcount].push_back((i - 2) * 10 + j - 1); }
					if (masView[i - 1][j + 1] == 10) { list[listcount].push_back((i - 2) * 10 + j + 1); }
					if (masView[i + 1][j - 1] == 10) { list[listcount].push_back((i) * 10 + j - 1); }

					if (list[listcount][0] == list[listcount].size() - 1)
					{
						ans.x = i;
						ans.y = j;
						botLogic[i][j] = 1;
						ans.openAll = 1;
						ans.bomb = 1;
						return ans;
					}
				}
			}
		}
	//}

	//group logic
	bool repeat = 1;

	while (repeat)
	{
		repeat = 0;

		for (int i = 0; i < list.size(); i++)
		{
			for (int j = i + 1; j < list.size(); j++)
			{
				if (list[i].size() == list[j].size())
				{
					bool same, sameAll = 1;
					for (int lp = 0; lp < list[i].size(); lp++)
					{
						same = 0;
						for (int lc = 0; lc < list[j].size(); lc++)
						{
							if (list[i][lp] == list[j][lc])
							{
								same = 1;
								break;
							}
						}
						if (!same) { sameAll = 0; break; }
					}
					if (sameAll) list.erase(list.begin() + j);
				}
				else
				{
					int parent, child;
					bool same, sameAll;
					int someSame = 0;
					if (list[i].size() > list[j].size())
					{
						parent = i; child = j;
					}
					else
					{
						parent = j; child = i;
					}

					sameAll = 1; someSame = 0;

					for (int lc = 1; lc < list[child].size(); lc++)
					{
						same = 0;
						for (int lp = 1; lp < list[parent].size(); lp++)
						{
							if (list[child][lc] == list[parent][lp]) { same = 1; break; }
						}
						if (!same) { sameAll = 0; break; }
						else { someSame++; }
					}

					if (sameAll)
					{
						repeat = 1;
						list[parent][0] -= list[child][0];

						for (int lc = 1; lc < list[child].size(); lc++)
						{
							for (int lp = 1; lp < list[parent].size(); lp++)
							{
								if (list[parent][lp] == list[child][lc]) list[parent].erase(list[parent].begin() + lp);
							}
						}
					}
					else if (someSame)
					{
						int parentextra = list[parent].size() - 1 - someSame;
						int childextra = list[child].size() - 1 - someSame;
						int minSameMines = 0;
						//if (list[parent].size() - 1 - someSame >= list[parent][0] && list[child].size() - 1 - someSame >= list[child][0]) { continue; }
						if (parentextra < list[parent][0]) //&& childextra == list[child][0])
						{
							/*list.push_back(std::vector<int>());
							listcount++;
							list[listcount].push_back(list[parent][0] - );*/
							minSameMines = list[parent][0] - parentextra;
						}
						if (childextra < list[child][0]) //&& childextra == list[child][0])
						{
							minSameMines = std::max(minSameMines, list[parent][0] - parentextra);
						}

						if (minSameMines)
						{
							repeat = 1;

							list[parent][0] -= minSameMines;
							list[child][0] -= minSameMines;

							list.push_back(std::vector<int>());
							listcount++;
							list[listcount].push_back(minSameMines);
							for (int kc = 1; kc < list[child].size(); kc++)
							{
								for (int kp = 1; kp < list[parent].size(); kp++)
								{
									if (list[parent][kp] == list[child][kc])
									{
										list[listcount].push_back(list[parent][kp]);
										list[parent].erase(list[parent].begin() + kp);
										list[child].erase(list[child].begin() + kc);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//return ready list
	listcount = -1;
	for (int l = 0; l < list.size(); l++)
	{
		if (list[l][0] == 0 || list[l][0] == list[l].size() - 1)
		{
			ans.list.push_back(std::vector<int>());
			listcount++;
			for (int k = 0; k < list[l].size(); k++)
			{
				ans.list[listcount].push_back(list[l][k]);
			}
		}
	}

	if (ans.list.size() == 0)
	{
		ans.random = 1;
	}

	return ans;
}

int randomMove(int (&masView)[11][11])
{
	std::vector<int> tmpmas;

	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			if (masView[i][j] == 10) tmpmas.push_back((i-1) * 10 + j);
		}
	}

	return tmpmas[rand() % tmpmas.size()];
}

int main()
{
	srand(time(0));

	bool bot = is_bot;

	sf::RenderWindow app(sf::VideoMode(384, 416), "Minesweeper");
	app.setFramerateLimit(10);

	int w = 32;
	int masLogic[11][11] = {0};
	int masView[11][11];

	sf::Texture t;
	t.loadFromFile("tiles.jpg");
	sf::Sprite s(t);

	sf::Font font;
	font.loadFromFile("Fonts/FREESCPT.ttf");
	sf::Text text("Time:", font, 32);
	text.setFillColor(sf::Color::Black);

	sf::Clock clock;
	double sec = 0;

	/*for (int i = 1; i <= 10; i++)
	{
		for(int j=1;j<=10;j++)
		{
			masView[i][j] = 10;
		}
	}*/
	newFild(masView);

	/*for (int ii = 0; ii < 10; ii++)
	{
		int xx = rand() % 10 + 1;
		int yy = rand() % 10 + 1;
		if (masLogic[xx][yy] != 9) masLogic[xx][yy] = 9;
		else ii--;
	}*/
	//bombs(masLogic);

	/*for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (masLogic[i][j] == 9) continue;
			if (masLogic[i + 1][j] == 9) n++;
			if (masLogic[i][j + 1] == 9) n++;
			if (masLogic[i - 1][j] == 9) n++;
			if (masLogic[i][j - 1] == 9) n++;
			if (masLogic[i + 1][j + 1] == 9) n++;
			if (masLogic[i - 1][j - 1] == 9) n++;
			if (masLogic[i - 1][j + 1] == 9) n++;
			if (masLogic[i + 1][j - 1] == 9) n++;
			masLogic[i][j] = n;
		}
	}*/
	//createLogic(masLogic);

	bool gameOver = 0, firstStep = 1, fl = 1;
	int gameWin = 0, botLogic[11][11];

	while (app.isOpen())
	{
		sf::Vector2i pos = sf::Mouse::getPosition(app);
		
		//std::cout << "gameOver " << gameOver << std::endl;
		//std::cout << "gameWin " << gameWin << std::endl;

		if(!gameOver && gameWin != 10) sec += clock.getElapsedTime().asSeconds();
		clock.restart();

		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();
			if (e.type == sf::Event::MouseButtonPressed)
			{
				//std::cout << pos.x << " " << pos.y << std:: endl;

				if (e.key.code == sf::Mouse::Left && pos.x > 150 && pos.x < 240 && pos.y > 10 && pos.y < 35)
				{
					std::cout << "-----------------------Restart-----------------"<<std::endl;
					restart(masView, masLogic);
					gameOver = 0;
					gameWin = 0;
					sec = 0;
					firstStep = 1;
				}

				if (!bot)
				if (pos.y > 32 && gameWin != 10 && !gameOver)
				{
					int x = pos.x / w;
					int y = pos.y / w - 1;

					if (e.key.code == sf::Mouse::Left)
					{
						if (firstStep)
						{
							bombs(masLogic, x, y);
							createLogic(masLogic);
							firstStep = 0;
						}

						if (masView[x][y] == 11) masView[x][y] = 10;
						else masView[x][y] = masLogic[x][y];

						if (masLogic[x][y] == 9) gameOver = 1;

						if (masView[x][y] == 0)
						{
							/*std::queue <std::pair <int, int> > masQueue;
							bool masUsed[11][11] = { 0 };

							masQueue.push(std::make_pair(x, y));
							masUsed[x][y] = 1;

							while (!masQueue.empty())
							{
								std::pair <int, int> tmp = std::make_pair(masQueue.front().first, masQueue.front().second);
								masQueue.pop();

								if (tmp.second != 0 && !masUsed[tmp.first][tmp.second - 1] && masLogic[tmp.first][tmp.second - 1] < 9)
								{
									if (!masLogic[tmp.first][tmp.second - 1]) masQueue.push(std::make_pair(tmp.first, tmp.second - 1));
									masUsed[tmp.first][tmp.second - 1] = 1;
									masView[tmp.first][tmp.second - 1] = masLogic[tmp.first][tmp.second - 1];
								}
								if (tmp.second != 10 && !masUsed[tmp.first][tmp.second + 1] && masLogic[tmp.first][tmp.second + 1] < 9)
								{
									if (!masLogic[tmp.first][tmp.second + 1]) masQueue.push(std::make_pair(tmp.first, tmp.second + 1));
									masUsed[tmp.first][tmp.second + 1] = 1;
									masView[tmp.first][tmp.second + 1] = masLogic[tmp.first][tmp.second + 1];
								}
								if (tmp.first != 0 && !masUsed[tmp.first - 1][tmp.second] && masLogic[tmp.first - 1][tmp.second] < 9)
								{
									if (!masLogic[tmp.first - 1][tmp.second]) masQueue.push(std::make_pair(tmp.first - 1, tmp.second));
									masUsed[tmp.first - 1][tmp.second] = 1;
									masView[tmp.first - 1][tmp.second] = masLogic[tmp.first - 1][tmp.second];
								}
								if (tmp.first != 10 && !masUsed[tmp.first + 1][tmp.second] && masLogic[tmp.first + 1][tmp.second] < 9)
								{
									if (!masLogic[tmp.first + 1][tmp.second]) masQueue.push(std::make_pair(tmp.first + 1, tmp.second));
									masUsed[tmp.first + 1][tmp.second] = 1;
									masView[tmp.first + 1][tmp.second] = masLogic[tmp.first + 1][tmp.second];
								}

								// + - +
								// - - -
								// + - +

								if (tmp.first != 0 && tmp.second != 0 && !masUsed[tmp.first - 1][tmp.second - 1] && masLogic[tmp.first - 1][tmp.second - 1] < 9)
								{
									if (!masLogic[tmp.first - 1][tmp.second - 1]) masQueue.push(std::make_pair(tmp.first - 1, tmp.second - 1));
									masUsed[tmp.first - 1][tmp.second - 1] = 1;
									masView[tmp.first - 1][tmp.second - 1] = masLogic[tmp.first - 1][tmp.second - 1];
								}
								if (tmp.first != 0 && tmp.second != 10 && !masUsed[tmp.first - 1][tmp.second + 1] && masLogic[tmp.first - 1][tmp.second + 1] < 9)
								{
									if (!masLogic[tmp.first - 1][tmp.second + 1]) masQueue.push(std::make_pair(tmp.first - 1, tmp.second + 1));
									masUsed[tmp.first - 1][tmp.second + 1] = 1;
									masView[tmp.first - 1][tmp.second + 1] = masLogic[tmp.first - 1][tmp.second + 1];
								}
								if (tmp.first != 10 && tmp.second != 0 && !masUsed[tmp.first + 1][tmp.second - 1] && masLogic[tmp.first + 1][tmp.second - 1] < 9)
								{
									if (!masLogic[tmp.first + 1][tmp.second - 1]) masQueue.push(std::make_pair(tmp.first + 1, tmp.second - 1));
									masUsed[tmp.first + 1][tmp.second - 1] = 1;
									masView[tmp.first + 1][tmp.second - 1] = masLogic[tmp.first + 1][tmp.second - 1];
								}
								if (tmp.first != 10 && tmp.second != 10 && !masUsed[tmp.first + 1][tmp.second + 1] && masLogic[tmp.first + 1][tmp.second + 1] < 9)
								{
									if (!masLogic[tmp.first + 1][tmp.second + 1]) masQueue.push(std::make_pair(tmp.first + 1, tmp.second + 1));
									masUsed[tmp.first + 1][tmp.second + 1] = 1;
									masView[tmp.first + 1][tmp.second + 1] = masLogic[tmp.first + 1][tmp.second + 1];
								}
							}*/
							zeroNode(masView, masLogic, x, y);
						}
					}
					else if (e.key.code == sf::Mouse::Right)
					{
						if (masView[x][y] == 11) masView[x][y] = 10;
						else if (masView[x][y] == 10)masView[x][y] = 11;
					}
				}
			}
		}

		if (bot && gameWin != 10 && !gameOver)
		{
			ans tmp;

			if (firstStep)
			{
				for(int i = 1; i<11;i++)
					for(int j = 1; j<11;j++)
						botLogic[i][j] = 0;
				tmp.x = rand() % 10 + 1;
				tmp.y = rand() % 10 + 1;
				tmp.bomb = 0;
				bombs(masLogic, tmp.x, tmp.y);
				createLogic(masLogic);
				firstStep = 0;
			}
			else
			{
				tmp = botLog(masView, botLogic);
			}

			//if (fl) 
			{ std::cout << tmp.x << " " << tmp.y << " " << tmp.bomb << " " << tmp.openAll << std::endl; fl = 0; }

			if (!tmp.list.size() && !tmp.random)
			{
				if (tmp.openAll)
				{
					if (tmp.bomb)
					{
						if (tmp.x != 10 && masView[tmp.x + 1][tmp.y] == 10) { masView[tmp.x + 1][tmp.y] = 11; }
						if (tmp.y != 10 && masView[tmp.x][tmp.y + 1] == 10) { masView[tmp.x][tmp.y + 1] = 11; }
						if (tmp.x != 1 && masView[tmp.x - 1][tmp.y] == 10) { masView[tmp.x - 1][tmp.y] = 11; }
						if (tmp.y != 1 && masView[tmp.x][tmp.y - 1] == 10) { masView[tmp.x][tmp.y - 1] = 11; }
						if (tmp.x != 10 && tmp.y != 10 && masView[tmp.x + 1][tmp.y + 1] == 10) { masView[tmp.x + 1][tmp.y + 1] = 11; }
						if (tmp.x != 1 && tmp.y != 1 && masView[tmp.x - 1][tmp.y - 1] == 10) { masView[tmp.x - 1][tmp.y - 1] = 11; }
						if (tmp.x != 1 && tmp.y != 10 && masView[tmp.x - 1][tmp.y + 1] == 10) { masView[tmp.x - 1][tmp.y + 1] = 11; }
						if (tmp.x != 10 && tmp.y != 1 && masView[tmp.x + 1][tmp.y - 1] == 10) { masView[tmp.x + 1][tmp.y - 1] = 11; }
					}
					else
					{
						if (tmp.x != 10 && masView[tmp.x + 1][tmp.y] == 10) { masView[tmp.x + 1][tmp.y] = masLogic[tmp.x + 1][tmp.y]; if (masView[tmp.x + 1][tmp.y] == 0) zeroNode(masView, masLogic, tmp.x, tmp.y); }
						if (tmp.y != 10 && masView[tmp.x][tmp.y + 1] == 10) { masView[tmp.x][tmp.y + 1] = masLogic[tmp.x][tmp.y + 1]; if (masView[tmp.x][tmp.y + 1] == 0) zeroNode(masView, masLogic, tmp.x, tmp.y); }
						if (tmp.x != 1 && masView[tmp.x - 1][tmp.y] == 10) { masView[tmp.x - 1][tmp.y] = masLogic[tmp.x - 1][tmp.y];  if (masView[tmp.x - 1][tmp.y] == 0) zeroNode(masView, masLogic, tmp.x, tmp.y); }
						if (tmp.y != 1 && masView[tmp.x][tmp.y - 1] == 10) { masView[tmp.x][tmp.y - 1] = masLogic[tmp.x][tmp.y - 1];  if (masView[tmp.x][tmp.y - 1] == 0) zeroNode(masView, masLogic, tmp.x, tmp.y); }
						if (tmp.x != 10 && tmp.y != 10 && masView[tmp.x + 1][tmp.y + 1] == 10) { masView[tmp.x + 1][tmp.y + 1] = masLogic[tmp.x + 1][tmp.y + 1]; if (masView[tmp.x + 1][tmp.y + 1] == 0) zeroNode(masView, masLogic, tmp.x, tmp.y); }
						if (tmp.x != 1 && tmp.y != 1 && masView[tmp.x - 1][tmp.y - 1] == 10) { masView[tmp.x - 1][tmp.y - 1] = masLogic[tmp.x - 1][tmp.y - 1];   if (masView[tmp.x - 1][tmp.y - 1] == 0) zeroNode(masView, masLogic, tmp.x, tmp.y); }
						if (tmp.x != 1 && tmp.y != 10 && masView[tmp.x - 1][tmp.y + 1] == 10) { masView[tmp.x - 1][tmp.y + 1] = masLogic[tmp.x - 1][tmp.y + 1];  if (masView[tmp.x - 1][tmp.y + 1] == 0) zeroNode(masView, masLogic, tmp.x, tmp.y); }
						if (tmp.x != 10 && tmp.y != 1 && masView[tmp.x + 1][tmp.y - 1] == 10) { masView[tmp.x + 1][tmp.y - 1] = masLogic[tmp.x + 1][tmp.y - 1];  if (masView[tmp.x + 1][tmp.y - 1] == 0) zeroNode(masView, masLogic, tmp.x, tmp.y); }
					}
				}
				else
				{
					if (tmp.bomb)
					{
						masView[tmp.x][tmp.y] = 11;
					}
					else
					{
						masView[tmp.x][tmp.y] = masLogic[tmp.x][tmp.y];
						if (masView[tmp.x][tmp.y] == 0)
						{
							zeroNode(masView, masLogic, tmp.x, tmp.y);
						}
					}
				}
			}
			else if(!tmp.random)
			{
				std::cout << "List:" << std::endl;

				for (int i = 0; i < tmp.list.size(); i++)
				{
					if (tmp.list[i][0] == 0)
					{
						for (int j = 1; j < tmp.list[i].size(); j++)
						{
							std::cout << 0 << " " << tmp.list[i][j] << std::endl;
							if (tmp.list[i][j] % 10) { masView[tmp.list[i][j] / 10 + 1][tmp.list[i][j] % 10] = masLogic[tmp.list[i][j] / 10 + 1][tmp.list[i][j] % 10]; }
							else { masView[tmp.list[i][j] / 10][10] = masLogic[tmp.list[i][j] / 10][10]; }
						}
					}
					else
					{
						for (int j = 1; j < tmp.list[i].size(); j++)
						{
							std::cout << 1 << " " << tmp.list[i][j] << std::endl;
							if (tmp.list[i][j] % 10) { masView[tmp.list[i][j] / 10 + 1][tmp.list[i][j] % 10] = 11; }
							else { masView[tmp.list[i][j] / 10][10] = 11; }
						}
					}
				}

				std::cout << "end of list" << std::endl;
			}
			//random
			else
			{
				int randommove = randomMove(masView);
				if (randommove % 10) 
				{ 
					masView[randommove / 10 + 1][randommove % 10] = masLogic[randommove / 10 + 1][randommove % 10]; 
					if(masView[randommove / 10 + 1][randommove % 10] == 0) zeroNode(masView, masLogic, randommove / 10 + 1, randommove % 10);
				}
				else 
				{ 
					masView[randommove / 10][10] = masLogic[randommove / 10][10]; 
					if (masView[randommove / 10][10] == 0) zeroNode(masView, masLogic, randommove / 10, 10);
				}

				std::cout << "Random Move " << randommove << std::endl;
			}
		}

		app.clear(sf::Color::White);

		text.setPosition(32, 5);
		text.setString("Time: " + std::to_string(static_cast<int>(sec)));
		app.draw(text);

		text.setPosition(160, 5);
		text.setString("Restart");
		app.draw(text);
		

		gameWin = 0;

		//Sleep(100);

		for (int i = 1; i <= 10; i++)
		{
			for (int j = 1; j <= 10; j++)
			{
				if (masView[i][j] == 9) gameOver = 1;

				if (gameOver) masView[i][j] = masLogic[i][j];

				if (masView[i][j] == 10 || masView[i][j] == 11) gameWin++;

				s.setTextureRect(sf::IntRect(masView[i][j] * w, 0, w, w));
				s.setPosition(i * w, j * w + 32);
				app.draw(s);
			}
		}

		text.setPosition(320, 5);
		if (gameOver)
		{
			text.setString("Lose");
			app.draw(text);
		}
		else if (gameWin == 10)
		{
			text.setString("Win");
			app.draw(text);
		}

		app.display();
	}

	return 0;
}
