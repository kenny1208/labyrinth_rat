//---------------------------------------------------------------------------
//copy copy
#include <vcl.h>
#pragma hdrstop
#include "stdio.h"
#include <stdlib.h> // 為了使用 srand 和 rand
#include <time.h>   // 為了使用 time
#include <algorithm>


#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


String in_string;

TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	Memo1->Font->Name = "Courier New"; // 設定等寬字體
	Memo1->Font->Size = 10; // 可依需求調整字體大小
}

// 定義4個可能的移動方向
# define S1 4

int flag=0;
enum directions { UP, DOWN, LEFT, RIGHT };
int m, p;
struct position * Stack;
// 定義2D坐標的數據結構
struct position
{
	int x, y;
	directions dir;
};


struct cood
{
	int dx, dy;
};
cood move[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int **maze;  // 迷宮地圖
int **mark;  // 記錄是否訪問過

// 定義存儲步驟、下一步和堆疊的數據結構
struct position step, next, stack[500];

int ** w;
int top = -1, d;
struct cood f1[S1];
struct cood f2[S1];
// 初始化偏移表
void initiation()
{
	w = new int*[m];
	for (int i = 0; i < m; ++i) {
		w[i] = new int[p];
		for (int j = 0; j < p; ++j) {
			if (i == 0 || i == m - 1 || j == 0 || j == p - 1) {
				w[i][j] = 2; // 外圍牆壁設置為 2
			} else {
				w[i][j] = 1; // 內部默認為牆壁
			}
		}
	}
	w[1][0]=0;
	w[m-2][p-1]=0;

	// 定義四個可能的移動方向：上、下、左、右
	f1[0].dx = 0; f1[0].dy = 1; // 上
	f1[1].dx = -1; f1[1].dy = 0; // 左
	f1[2].dx = 0; f1[2].dy = -1; // 下
	f1[3].dx = 1; f1[3].dy = 0; // 右
	// 定義兩步跳的偏移：上、下、左、右
	f2[0].dx = 0; f2[0].dy = 2; // 上
	f2[1].dx = -2; f2[1].dy = 0; // 左
	f2[2].dx = 0; f2[2].dy = -2; // 下
	f2[3].dx = 2; f2[3].dy = 0; // 右
}



void StackFull() {
	ShowMessage("Stack is full.");
}

void StackEmpty() {
	ShowMessage("Stack is empty.");
}

int NextMove(struct position step) {
	for (int i = 0; i < S1; i++) {
		int newX = step.x + f2[i].dx;
		int newY = step.y + f2[i].dy;

		// 邊界檢查
		if (newX >= 0 && newX < m && newY >= 0 && newY < p) {
			if (w[newX][newY] == 1) {
				return 1;
			}
		}
	   //	if(w[step.x+f2[i].dx][step.y+f2[i].dy==1]) return 1;
	}
	return 0;
}

void push (struct position data)
{
	if (top == (m*p-1)) StackFull();
	else stack[++top] = data;
}
struct position pop()
{
	if (top == -1) StackEmpty();
	else return stack[top--];
}

void showPath() {
	// 遍歷迷宮數組 w，輸出在Memo1
	for (int i = 0; i < m; i++) {
		String line = "";
		for (int j = 0; j < p; j++) {
			line += IntToStr(w[i][j]) + " ";
		}
		Form2->Memo1->Lines->Add(line);
	}
}

struct Predecessor {
	int x, y;
};


void backtrackPath(int m, int p, Predecessor **predecessor) {
	int x = m - 2, y = p - 1; // 終點

	while (x != 1 || y != 1) { // 起點在 (1, 1)

		w[x][y] = 4;

		// 更新 StringGrid
		Form2->StringGrid1->Cells[y][x] = "正確路徑";
		Form2->StringGrid1->Repaint();
		Sleep(10);

		// 回溯到前一個位置
		Predecessor pred = predecessor[x][y];
		x = pred.x;
		y = pred.y;
	}

	// 標記起點
	w[1][1] = 4;
	Form2->StringGrid1->Cells[1][1] = "正確路徑";

	Form2->StringGrid1->Refresh();


}


void path(int m, int p) {
	// 正確路徑
	bool **mark = new bool*[m];
	Predecessor **predecessor = new Predecessor*[m];
	for (int i = 0; i < m; i++) {
		mark[i] = new bool[p]();
		predecessor[i] = new Predecessor[p]();
	}

	// 初始位置
	struct position step = {1, 1, RIGHT};

	push(step);
	mark[step.x][step.y] = true; // 標記已訪問
	w[step.x][step.y] = 3;       // 走過路線

	while (top != -1) {
		step = pop();
		Form2->StringGrid1->Cells[step.y][step.x] = "探索"; // 顯示走過路線
		Form2->StringGrid1->Repaint(); // 立即重繪
		Sleep(5); // 速度

		// 輸出步驟
		Form2->Memo1->Lines->Add("Step to: (" + IntToStr(step.x) + ", " + IntToStr(step.y) + ")");

		int i = step.x;
		int j = step.y;

		if (i == m - 2 && j == p - 1) {
			flag=1;
			backtrackPath(m, p, predecessor);
			break;
		}


		for (int dir = 0; dir < 4; ++dir) {
			int u = i + move[dir].dx;
			int v = j + move[dir].dy;

		 if (u >= 0 && u < m && v >= 0 && v < p && w[u][v] == 0 && !mark[u][v]) {
				mark[u][v] = true;
				w[u][v] = 3;
				predecessor[u][v] = {i, j}; // 用 i 和 j 替代 current.x 和 current.y
				push({u, v, RIGHT});
			}
		}

	}
	if(flag!=1)
	{
		ShowMessage("無路可走");
	}
}


// 使用深度優先搜索生成迷宮
int **MazeDFS(struct position step) {

	w[step.x][step.y] = 0; // 起始點設為通道
	push(step);

	while (top != -1) {
		step = pop();

		while (NextMove(step)) {
			d = rand() % S1;
			next.x = step.x + f2[d].dx;
			next.y = step.y + f2[d].dy;

			// 確保下一步不會超出迷宮範圍
			if (next.x > 0 && next.x < m - 1 && next.y > 0 && next.y < p - 1) {
				if (w[next.x][next.y] == 1) {
					w[step.x + f1[d].dx][step.y + f1[d].dy] = 0;
					w[next.x][next.y] = 0;
					push(next);

					step = next;
				}
			}
		}
	}

	return w;
}


void ShowMazeInMemo() {
	for (int i = 0; i < m; i++) {
		String line = ""; // 用於存儲當前行的字符串
		for (int j = 0; j < p; j++) {
			line += IntToStr(w[i][j]) + " "; // 將每個元素轉換為字符串並添加到行字符串中
		}
		Form2->Memo1->Lines->Add(line); // 將行字符串添加到 Memo1
	}
	Form2->Memo1->Lines->Add("------------------------------------------------------");
}



//---------------------------------------------------------------------------


void __fastcall TForm2::Button3Click(TObject *Sender) {
    FILE *fp;
    AnsiString fname;
    int m1, p1, i, j;

    if (OpenDialog1->Execute()) {
        fname = OpenDialog1->FileName;
        fp = fopen(fname.c_str(), "r");

        if (fp != nullptr) {
			// 讀取行列
            fscanf(fp, "%d %d", &m1, &p1);
            Memo1->Lines->Add("m=" + IntToStr(m1));
            Memo1->Lines->Add("p=" + IntToStr(p1));

			// 初始化W
            w = new int*[m1];
            for (i = 0; i < m1; i++) {
                w[i] = new int[p1];
            }

			// 讀取迷宮
            for (i = 0; i < m1; i++) {
                for (j = 0; j < p1; j++) {
                    fscanf(fp, "%1d", &w[i][j]);
                }
            }

            fclose(fp);

            // 更新 StringGrid1
            StringGrid1->RowCount = m1;
            StringGrid1->ColCount = p1;
            for (i = 0; i < m1; i++) {
                for (j = 0; j < p1; j++) {
                    StringGrid1->Cells[j][i] = IntToStr(w[i][j]);
                }
            }
        } else {
			Memo1->Lines->Add("失敗。");
        }
    } else {
		Memo1->Lines->Add("沒有選擇。");
    }


    for (i = 0; i < m1; i++) {
        AnsiString line = "";
        for (j = 0; j < p1; j++) {
            line += IntToStr(w[i][j]) + " ";
        }
        Memo1->Lines->Add(line);
    }
}


//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
    // 從 Edit 控件獲取新的迷宮尺寸
	int new_m = StrToInt(Edit1->Text);  // 從 Edit1 獲取寬度
	int new_p = StrToInt(Edit2->Text); // 從 Edit2 獲取高度

	DoubleBuffered=true;

    // 確保新尺寸是有效的
    if (new_m <= 0 || new_p <= 0) {
        ShowMessage("迷宮尺寸必須是正整數。");
        return;
    }

	// 釋放之前的迷宮記憶體
    if (w != nullptr) {
		for (int i = 0; i < m; ++i) {
            delete[] w[i];
        }
        delete[] w;
        w = nullptr;
    }

	// 更新迷宮尺寸
    m = new_m;
	p = new_p;

	// 初始化迷宮
	initiation();

	// 創建迷宮
	struct position start = {1, 1};
	MazeDFS(start);

    // 顯示迷宮
	ShowMazeInMemo();

	// 設定 DrawGrid 和 StringGrid 的行列數量

    StringGrid1->RowCount = m;
	StringGrid1->ColCount = p;

    // 刷新這些控件以顯示更新

    StringGrid1->Invalidate();
}

//---------------------------------------------------------------------------


void __fastcall TForm2::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State) {
    TCanvas *canvas = StringGrid1->Canvas;

	if (ARow < m && ACol < p) { // 確保不越界
		// 根據迷宮數據決定顏色
		switch(w[ARow][ACol]) {
			case 1: // 牆壁
				canvas->Brush->Color = clSkyBlue;
                break;
			case 2: // 外圍
                canvas->Brush->Color = clFuchsia;
                break;
			case 3: // 探索路徑
                canvas->Brush->Color = clGreen;
                break;
			case 4: // 正確路徑
				canvas->Brush->Color = clRed;
                break;
			default: // 通道
				canvas->Brush->Color = clWhite;
				break;
		}

		// 填充單元格
        canvas->FillRect(Rect);
		// 繪製邊框
		//canvas->Pen->Color = clBlack;
		//canvas->Rectangle(Rect.Left, Rect.Top, Rect.Right, Rect.Bottom);
	}
}



//---------------------------------------------------------------------------


void __fastcall TForm2::FormResize(TObject *Sender) {
    int cellSize = std::min(StringGrid1->ClientWidth / StringGrid1->ColCount,
                            StringGrid1->ClientHeight / StringGrid1->RowCount);

    for (int i = 0; i < StringGrid1->RowCount; ++i) {
        StringGrid1->RowHeights[i] = cellSize;
    }

    for (int j = 0; j < StringGrid1->ColCount; ++j) {
        StringGrid1->ColWidths[j] = cellSize;
	}


}

//---------------------------------------------------------------------------

void __fastcall TForm2::Button4Click(TObject *Sender)
{
	int m = Edit1->Text.ToInt(); // 迷宮行數
	int p = Edit2->Text.ToInt(); // 迷宮列數

	DoubleBuffered=true;

	path(m,p);

	showPath();
}

//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender) {
    if (SaveDialog1->Execute()) {
        AnsiString filename = SaveDialog1->FileName;
        FILE *file = fopen(filename.c_str(), "w");

        if (file != nullptr) {

			fprintf(file, "%d %d\n", m, p);


			for (int i = 0; i < m; i++) {
				for (int j = 0; j < p; j++) {
                    int value = w[i][j];
                    if (value == 3 || value == 4) {
						value = 0;
                    }
                    fprintf(file, "%d", value);
                }
				fprintf(file, "\n");
            }
			fclose(file);
        } else {
			ShowMessage("打不開");
        }
    }
}


//---------------------------------------------------------------------------

