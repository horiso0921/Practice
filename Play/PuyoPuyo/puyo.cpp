/*********************************************************/
//  オブジェクト指向言語及び演習 課題8
//  2018/06/11 堀内颯太
//  puyo.cpp
//  入力：矢印キー
//  機能：プヨプヨをプレイ可能（ただしLinux環境下に限る）
//  コンパイル： g++ -o puyo puyo.cpp -lncurses -std=c++0x
/*********************************************************/

#include <curses.h>
#include <random>
#include <iostream>
#include <unistd.h>
#include <vector>

//ぷよの色を表すの列挙型
//NONEが無し，RED,BLUE,..が色を表す
enum puyocolor{NONE, RED, BLUE, GREEN, YELLOW};

//ぷよ1つのデータを格納する構造体
struct puyodata
{
	enum puyocolor color;	//色
	bool handling;	//操作中か否か

	//構造体のコンストラクタ
	//この構造体のインスタンス定義時に一度だけ実行される関数
	//ここでは変数の値を初期化する
	puyodata()
	{
		color = NONE;
		handling = false;
	}
};

/* Fieldクラスの既定*/
class Field
{
private:
  struct puyodata *field_array;
  unsigned int field_line;
  unsigned int field_column;

  //field_arrayのメモリ開放
  void Release()
  {
    if (field_array == NULL)
      {
	return;
      }
    
    delete[] field_array;
    field_array = NULL;
  }

public:
 
  //フィールドサイズ変更
  void ChangeSize(unsigned int line, unsigned int column)
  {
    Release();
    
    //新しいサイズでメモリ確保
    field_array = new struct puyodata[line*column];
    
    field_line = line;
    field_column = column;
  }
  
  //フィールドの指定された位置の値を返す
  struct puyodata GetValue(unsigned int y, unsigned int x)
  {
    if (y >= field_line || x >= field_column)
      {
	//引数の値が正しくない
	struct puyodata temp;
	return temp;
      }

    return field_array[y*field_column + x];
  }

  //フィールドの指定された位置に値を書き込む
  void SetValue(unsigned int y,unsigned int x, struct puyodata data)
  {
    if (y >= field_line || x >= field_column)
      {
	//引数の値が正しくない
	return;
      }
    
    field_array[y*field_column + x] = data;
  }

  Field() {
    field_array = NULL;
    field_line = 0;
    field_column = 0;
  };
  
  ~Field(){
    Release();
  };
  unsigned int GetLine(){return field_line;}
  unsigned int GetColumn(){return field_column;}
};

/* FieldControlクラスの基底*/
class FieldControl : public Field
{
private:
  int puyorotate;
public:
  std::vector< enum puyocolor > vpuyocolor;
  struct puyodata *newpuyo;
  int vpuyo_x;//ぷよの消去位置を記憶
  int vpuyo_y;

  void release()
  {
    if (newpuyo == NULL)
      {
        return;
      }

    delete[] newpuyo;
    newpuyo = NULL;
  }
  FieldControl():vpuyocolor(1){
    newpuyo = NULL;
    newpuyo = new struct puyodata[6];
    puyorotate = 0;
  };

  ~FieldControl(){
    release();
  };  
  //フィールドに新しいぷよ生成
  void GeneratePuyo()
  {
    std::random_device rand{};
    if (newpuyo[4].color == NONE)
      {
	newpuyo[4] = newpuyo[2];
	newpuyo[5] = newpuyo[3];
	newpuyo[2] = newpuyo[0];
	newpuyo[3] = newpuyo[1];
	for (int i = 0; i < 2; i++)
	  {
	    switch (rand()%4 )
	      {
	      case 0:
		newpuyo[i].color = RED;
		break;
	      case 1:
		newpuyo[i].color = BLUE;
		break;
	      case 2:
		newpuyo[i].color = GREEN;
		break;
	      case 3: 
		newpuyo[i].color = YELLOW;
		break;
	      }
	    newpuyo[i].handling = true;
	  }
	GeneratePuyo();
	puyorotate = 0;
	return;
      }
    SetValue(0, 2, newpuyo[4]);
    SetValue(0, 3, newpuyo[5]);
    newpuyo[4].color = NONE;
    newpuyo[5].color = NONE;
  }	
  //操作中ぷよの着地判定
  //着地判定があるとtrueを返す 
  bool LandingPuyo()
  {
    bool landed = false;
    unsigned int field_line = GetLine();
    unsigned int field_column = GetColumn();
    struct puyodata *field_array_ex;
    field_array_ex =  new struct puyodata[field_line*field_column];
    //下から見ることでぷよが縦になっている場合も対応できるようにした
    for (int y = field_line-1; y > -1; y--)
      {
	for (int x = 0; x < field_column; x++)
	  {
	    field_array_ex[y*field_column + x] = GetValue(y,x);
	    if (field_array_ex[y*field_column + x].handling == true)
	      {
		//地面についた場合
		if ( y == field_line-1 )
		  {
		    //操作中フラグをfalseにして着地状態にする
		    field_array_ex[y*field_column + x].handling = false;
		    landed = true;
		    SetValue(y, x, field_array_ex[y*field_column + x]);
		  }
		//地面についていない場合
		else
		  {
		    field_array_ex[(y+1)*field_column + x] = GetValue(y+1,x);
		    if (field_array_ex[(y+1)*field_column + x].color != NONE && field_array_ex[(y+1)*field_column + x].handling == false)
		      {
			field_array_ex[y*field_column + x+1] = GetValue(y,x+1);
			//操作中フラグをfalseにして着地状態にする
			field_array_ex[y*field_column + x].handling = false;
			//左右のぷよも着地状態にする
			field_array_ex[y*field_column + (x+1)].handling = false;
			field_array_ex[y*field_column + (x-1)].handling = false;		      
			landed = true;
			SetValue(y, x, field_array_ex[y*field_column + x]);
			SetValue(y, x+1, field_array_ex[y*field_column + (x+1)]);
			SetValue(y, x-1, field_array_ex[y*field_column + (x-1)]);
			
		      }
		  }
	      }
	  }
      }
    delete[] field_array_ex;
    return landed;
  }
  
  //下にプヨのないプヨを落とします  
  void FallPuyo()
  {
    unsigned int field_line = GetLine();
    unsigned int field_column = GetColumn();
    struct puyodata *field_array_ex;
    field_array_ex =  new struct puyodata[field_line*field_column];
    
    for (int y = field_line-2; y > -1; y--)
      {
	for (int x = 0; x < field_column; x++)
	  {
	    //プヨを獲得
	    field_array_ex[y*field_column + x] = GetValue(y,x);
	    field_array_ex[(y+1)*field_column + x] = GetValue(y+1,x);
	    
	    //プヨのに色があり、その下に色がないつまりプヨがない場合を獲得
	    if (field_array_ex[y*field_column + x].color != NONE && field_array_ex[(y+1)*field_column + x].color == NONE)
	      {
		//プヨより下を判別
		for (int z = y+1; z < field_line; z++)
		{
		  field_array_ex[z*field_column + x] = GetValue(z, x);
		  
		  //下のどこかにプヨがあればそのプヨより1つ上にそのプヨを持ってくる
		  if ( field_array_ex[z*field_column + x].color != NONE )
		    {
		      //初期化用
		      field_array_ex[z*field_column + x].color = NONE;
		      SetValue(z-1, x, field_array_ex[y*field_column + x]);
		      SetValue(y, x, field_array_ex[z*field_column + x]);
		      break;
		    }
		  else if(z == field_line-1)
		    {
		      //もし下にプヨがなかった場合の処理
		      SetValue(z, x, field_array_ex[y*field_column + x]);
		      SetValue(y, x, field_array_ex[z*field_column + x]);
		    }
		}
	      }
	  }
      }
    delete[] field_array_ex;
  }
  
  //回転
  //FieldControlクラスのprivateメンバ変数として int puyorotate を宣言し，これに回転状態を記憶させている．puyostateにはコンストラクタ及びGeneratePuyo関数で値0を代入する必要あり．
  int ControlRotate()
  {
    //handling==trueのぷよを発見する
    //フィールドをラスタ順に探索（最も上の行を左から右方向へチェックして，次に一つ下の行を左から右方向へチェックして，次にその下の行・・と繰り返す）し，先に発見される方をpuyo1, 次に発見される方をpuyo2に格納
    struct puyodata puyo1, puyo2, puyo3;
    int puyo1_x = 0;
    int puyo1_y = 0;
    int puyo2_x = 0;
    int puyo2_y = 0;
    
    bool findingpuyo1 = true;
    for (int y = 0; y < GetLine(); y++)
      {
	for (int x = 0; x < GetColumn(); x++)
	  {
	    if (GetValue(y, x).handling == true)
	      {
		if (findingpuyo1)
		  {
		    puyo1 = GetValue(y, x);
		    puyo1_x = x;
		    puyo1_y = y;
		    findingpuyo1 = false;
		  }
		else
		  {
		    puyo2 = GetValue(y, x);
		    puyo2_x = x;
		    puyo2_y = y;
		  }
	      }
	  }
      }
    
    if (puyo1.handling == false || puyo2.handling == false)
      {
	//handling==trueのぷよ2個が発見されなかった．フィールドの状態が正しくない？
	return 0;
      }
    
    //回転前のぷよを消す
    struct puyodata puyonasi;
    puyonasi.color = NONE;
    puyonasi.handling = false;
    SetValue(puyo1_y, puyo1_x, puyonasi);
    SetValue(puyo2_y, puyo2_x, puyonasi);
    
    
    //操作中ぷよの回転
    switch (puyorotate)
      {
      case 0:
	//回転パターン
	//RB -> R
	//      B
	//Rがpuyo1, Bがpuyo2
	//回転前のRの下にプヨがあるか地面のとき
	//     R
	//RB → B
	//--   -
	if ( puyo2_y >= GetLine() - 1 || GetValue(puyo1_y+1, puyo1_x).color != NONE)
	  {
	    SetValue(puyo1_y-1, puyo1_x, puyo1);
	    SetValue(puyo2_y, puyo2_x-1, puyo2);
	    puyorotate = 1;
	    break;
	  }
	
	//回転後の位置にぷよを置く
	SetValue(puyo1_y, puyo1_x, puyo1);
	SetValue(puyo2_y + 1, puyo2_x - 1, puyo2);
	//次の回転パターンの設定
	puyorotate = 1;
	break;

      case 1:
	//回転パターン
	//R -> BR
	//B
	//Rがpuyo1, Bがpuyo2, \がほかぷよか壁
	if (puyo2_x <= 0 || puyo2_y <= 0 || GetValue(puyo1_y, puyo1_x-1).color !=NONE)//もし左端なら
	  {
	    //|R\ →  |B\ 
	    //|B\    |R\ 
	    //
	    if(puyo2_x == GetColumn() - 1|| GetValue(puyo1_y, puyo1_x+1).color != NONE)
	      {
		SetValue(puyo1_y+1, puyo1_x, puyo1);
		SetValue(puyo2_y-1, puyo2_x, puyo2);
		puyorotate = 3;
		break;
	      }
	    //|R → |BR
	    //|B   |  
	    else
	      {
		SetValue(puyo1_y, puyo1_x+1, puyo1);
		SetValue(puyo2_y-1, puyo2_x, puyo2);
		puyorotate = 2;
		break;
	      }
	  }
	else
	  {
	    //回転後の位置にぷよを置く
	    SetValue(puyo1_y, puyo1_x, puyo1);
	    SetValue(puyo2_y - 1, puyo2_x - 1, puyo2);
	    
	    //次の回転パターンの設定
	    puyorotate = 2;
	    break;
	  }	
	
      case 2:
	//回転パターン
	//      B
	//BR -> R
	//Bがpuyo1, Rがpuyo2
	if ( puyo1_y <= 0)//もし回転した結果field_arrayの範囲外に出るなら回転しない
	  {
	    SetValue(puyo1_y, puyo1_x, puyo1);
	    SetValue(puyo2_y, puyo2_x, puyo2);
	    break;
	  }
	//回転後の位置にぷよを置く
	SetValue(puyo1_y-1, puyo1_x+1, puyo1);
	SetValue(puyo2_y, puyo2_x, puyo2);
	
	//次の回転パターンの設定
	puyorotate = 3;
	break;

      case 3:
	//回転パターン
	//B
	//R -> RB
	//Bがpuyo1, Rがpuyo2
	//
	//B      |
	//R → RB|
	if (puyo1_x >= GetColumn() - 1 || GetValue(puyo2_y, puyo2_x+1).color != NONE)
	  {
	    //\B|    \B|
	    //\R| → \R|
	    if (GetValue(puyo2_y, puyo2_x-1).color != NONE || puyo1_x <= 0)
	      {
		SetValue(puyo2_y-1, puyo2_x, puyo2);
		SetValue(puyo1_y+1, puyo1_x, puyo1);
		puyorotate = 1;
		break;
	      }
	    //B|      |
	    //R| → RB| 
	    else
	      {
		SetValue(puyo2_y, puyo2_x-1, puyo2);
		SetValue(puyo1_y+1, puyo1_x, puyo1);
		puyorotate = 0;
		break;
	      }
	  }
	else
	  {
	    //普通の回転
	    SetValue(puyo2_y, puyo2_x, puyo2);
	    SetValue(puyo1_y+1, puyo1_x+1, puyo1);
	    //次の回転パターンの設定
	    puyorotate = 0;
		break;
	  }
      default:
	break;
      }
    //ぷよが地面にいるか下にぷよがある（ぷよの状態で場合分け）とき1をかえしてLand判定をさせずZを押して回ることができるようにした
    if (puyo1_y == GetLine()-1 || puyo2_y == GetLine()-1  || (puyo1_y+1 == puyo2_y && GetValue(puyo1_y+1, puyo1_x).color != NONE && GetValue(puyo2_y+1, puyo2_x).color != NONE) || (puyo1_y == puyo2_y && (GetValue(puyo1_y+1, puyo1_x).color != NONE || GetValue(puyo2_y+1, puyo2_x).color != NONE))){return 1;}
    else{return 0;}
  }
  
  
  //下移動
  void ControlDown()
  {
    //一時的格納場所メモリ確保
    struct puyodata *field_array_temp;
    struct puyodata *field_array_ex;
    unsigned int field_line = GetLine();
    unsigned int field_column = GetColumn();
    field_array_temp = new struct puyodata[field_line*field_column];
    field_array_ex = new struct puyodata[field_line*field_column];
	//1つ下の位置にfield_arrayからfield_array_exへとコピーしてfield_array_tempへコピー
	for (int y = field_line-2; y > -1 ; y--)
	  {
	    for (int x = 0; x < field_column; x++)
	      {
		field_array_ex[y*field_column + x] = GetValue(y,x);
		if (field_array_ex[y*field_column + x].handling == true && GetValue(y+1,x).color == NONE)
		  {
		    field_array_ex[y*field_column + x + 1] = GetValue(y, x+1);
		    field_array_ex[(y+1)*field_column + x] = GetValue(y+1, x);
		    field_array_ex[(y+1)*field_column + x + 1] = GetValue(y+1, x+1);
		    if (puyorotate%2 == 0 &&  field_array_ex[(y+1)*field_column + x+1].color == NONE)
		      {
			field_array_temp[(y + 1)*field_column + x] = field_array_ex[y*field_column + x];
			field_array_temp[(y + 1)*field_column + x+1] = field_array_ex[y*field_column + x+1];
			field_array_ex[y*field_column + x].color = NONE;
			field_array_ex[y*field_column + x].handling = false;
			SetValue(y, x, field_array_ex[y*field_column + x]);
			SetValue(y, x+1, field_array_ex[y*field_column + x]);
		      }
		    else if(puyorotate%2 == 1)
		      {
			if (y != 0)
			  {
			    field_array_ex[(y-1)*field_column + x] = GetValue(y-1, x);
			    field_array_temp[y*field_column + x] = field_array_ex[(y - 1)*field_column + x];
			    field_array_temp[(y + 1)*field_column + x] = field_array_ex[y*field_column + x];
			    field_array_ex[y*field_column + x].color = NONE;
			    field_array_ex[y*field_column + x].handling = false;
			    SetValue(y, x, field_array_ex[y*field_column + x]);
			    SetValue(y-1, x, field_array_ex[y*field_column + x]);
			  }
		      }
		    else
		      {
			delete[] field_array_temp;
			delete[] field_array_ex;
			return;
		      }
		  }
	      }
	  }
  	//field_array_tempからfield_arrayへコピー
	for (int y = 0; y < field_line; y++)
	  {
	    for (int x = 0; x < field_column; x++)
	      {
		if (field_array_temp[y*field_column + x].handling == true)
		  {		   
		    SetValue(y, x ,field_array_temp[y*field_column + x]);
		  }
	      }
	  }
	//一時的格納場所メモリ解放
	delete[] field_array_temp;
	delete[] field_array_ex;
  }
  
  //左移動
  void ControlLeft()
  {
    unsigned int field_line = GetLine();
    unsigned int field_column = GetColumn();
    //一時的格納場所メモリ確保
    struct puyodata *field_array_temp;
    field_array_temp = new struct puyodata[field_line*field_column];
    struct puyodata *field_array_ex;
    field_array_ex = new struct puyodata[field_line*field_column];
    //1つ左の位置にfield_arrayからfield_array_tempへとコピー
    for (int y = field_line-1; y > -1; y--)
      {
	for (int x = 1; x < field_column; x++)
	  {
	    field_array_ex[y*field_column + x] = GetValue(y,x);
	    if (field_array_ex[y*field_column + x].handling == true && GetValue(y, x-1).color == NONE)
	      {
		if (puyorotate%2 == 0)
		  {
		    field_array_temp[y*field_column + (x - 1)] = field_array_ex[y*field_column + x];
		    field_array_temp[y*field_column + x] = GetValue(y, x+1);
		    //コピー後にfield_arrayのデータは消す
		    field_array_ex[y*field_column + x].color = NONE;
		    field_array_ex[y*field_column + x].handling = false;
		    SetValue(y, x, field_array_ex[y*field_column + x]);
		    SetValue(y, x+1, field_array_ex[y*field_column + x]);
		  } 
		else if(y != 0 && puyorotate%2 == 1)
		  {
		    if(GetValue(y-1,x-1).color == NONE)
		      {
			field_array_temp[y*field_column + (x - 1)] = field_array_ex[y*field_column + x];
			field_array_temp[(y-1)*field_column +(x-1)] = GetValue(y-1, x);
			field_array_ex[y*field_column + x].color = NONE;
                        field_array_ex[y*field_column + x].handling = false;
                        SetValue(y, x, field_array_ex[y*field_column + x]);
                        SetValue(y-1, x, field_array_ex[y*field_column + x]);
		      } 
		    else
		      {
			delete[] field_array_temp;
			delete[] field_array_ex;
			return;
		      }
		  }
		else
		  {
		    delete[] field_array_temp;
		    delete[] field_array_ex;
		    return;
		  }
	      }
	  }
      }
    
    //field_array_tempからfield_arrayへコピー
    for (int y = 0; y < field_line; y++)
      {
	for (int x = 0; x < field_column; x++)
	  {
	    if (field_array_temp[y*field_column + x].handling == true)
	      {
		SetValue(y, x, field_array_temp[y*field_column + x]);
	      }
	  }
      }
    
    //一時的格納場所メモリ解放
    delete[] field_array_ex;
    delete[] field_array_temp;
  }
  
  //右移動
  void ControlRight()
  { 
    unsigned int field_line = GetLine();
    unsigned int field_column = GetColumn();
    //一時的格納場所メモリ確保
    struct puyodata *field_array_temp;
    field_array_temp = new struct puyodata[field_line*field_column];
    struct puyodata *field_array_ex;
    field_array_ex = new struct puyodata[field_line*field_column];

    //1つ右の位置にfield_arrayからfield_array_tempへとコピー
    for (int y = 0; y < field_line; y++)
      {
	for (int x = field_column-2; x > -1; x--)
	  {
	    field_array_ex[y*field_column + x] = GetValue(y, x);
	    if (field_array_ex[y*field_column + x].handling == true && GetValue(y, x+1).color == NONE)
	      {
		if (puyorotate%2 == 0 )
		  {
		    field_array_temp[y*field_column + (x + 1)] = field_array_ex[y*field_column + x];
		    field_array_temp[y*field_column + x] = GetValue(y,x-1);
		    field_array_ex[y*field_column + x].color = NONE;
		    field_array_ex[y*field_column + x].handling = false;
		    SetValue(y, x, field_array_ex[y*field_column + x]);
		    SetValue(y, x-1, field_array_ex[y*field_column + x]);
		  }
		else if  (y != field_line-1){
		  if(puyorotate%2 == 1 && GetValue(y+1,x + 1).color == NONE)
		    {
		      field_array_temp[y*field_column + (x + 1)] = field_array_ex[y*field_column + x];
		      field_array_temp[(y+1)*field_column +(x +1)] = GetValue(y+1, x);
		      field_array_ex[y*field_column + x].color = NONE;
		      field_array_ex[y*field_column + x].handling = false;
		      SetValue(y, x, field_array_ex[y*field_column + x]);
		      SetValue(y+1, x, field_array_ex[y*field_column + x]);
		    }
		  else
		    {
		      delete[] field_array_temp;
		      delete[] field_array_ex;
		      return;
		    }
		}
		
		else
		  {
		    delete[] field_array_temp;
		    delete[] field_array_ex;
		    return;
		  }
		  
		}
	  }
      }
    
    //field_array_tempからfield_arrayへコピー
    for (int y = 0; y < field_line; y++)
      {
	for (int x = 0; x < field_column; x++)
	  {
	    if (field_array_temp[y*field_column + x].handling == true)
	      {
		SetValue(y, x, field_array_temp[y*field_column + x]);
	      }
	  }
      }
    
    //一時的格納場所メモリ解放
    delete[] field_array_ex;
    delete[] field_array_temp;
  }

  //ぷよ消滅処理を全座標で行う
  //消滅したぷよの数を返す
  int VanishPuyo()
  {
    int vanishednumber = 0;
    for (int y = 0; y < GetLine(); y++)
      {
	for (int x = 0; x < GetColumn(); x++)
	  {
	    vanishednumber += VanishPuyo(y, x);
	  }
      }
    
    return vanishednumber;
  }
  
  //ぷよ消滅処理を座標(x,y)で行う
  //消滅したぷよの数を返す
  int VanishPuyo(unsigned int y, unsigned int x)
  {
    //判定個所にぷよがなければ処理終了
    if (GetValue(y, x).color == NONE)
      {
	return 0;
      }
    
    
    //判定状態を表す列挙型
    //NOCHECK判定未実施，CHECKINGが判定対象，CHECKEDが判定済み
    enum checkstate{ NOCHECK, CHECKING, CHECKED };
    
    //判定結果格納用の配列
    enum checkstate *field_array_check;
    field_array_check = new enum checkstate[GetLine()*GetColumn()];
    
    //配列初期化
    for (int i = 0; i < GetLine()*GetColumn(); i++)
      {
	field_array_check[i] = NOCHECK;
      }
    
    //座標(x,y)を判定対象にする
    field_array_check[y*GetColumn() + x] = CHECKING;
    
    //判定対象が1つもなくなるまで，判定対象の上下左右に同じ色のぷよがあるか確認し，あれば新たな判定対象にする
    bool checkagain = true;
    while (checkagain)
      {
	checkagain = false;
	
	for (int y = 0; y < GetLine(); y++)
	  {
	    for (int x = 0; x < GetColumn(); x++)
	      {
		//(x,y)に判定対象がある場合
		if (field_array_check[y*GetColumn() + x] == CHECKING)
		  {
		    //(x+1,y)の判定
		    if (x < GetColumn() - 1)
		      {
			//(x+1,y)と(x,y)のぷよの色が同じで，(x+1,y)のぷよが判定未実施か確認
			if (GetValue(y, x + 1).color == GetValue(y, x).color && field_array_check[y*GetColumn() + (x + 1)] == NOCHECK)
			  {
			    //(x+1,y)を判定対象にする
			    field_array_check[y*GetColumn() + (x + 1)] = CHECKING;
			    checkagain = true;
			  }
		      }
		    
		    //(x-1,y)の判定
		    if (x > 0)
		      {
			if (GetValue(y, x - 1).color == GetValue(y, x).color && field_array_check[y*GetColumn() + (x - 1)] == NOCHECK)
			  {
			    field_array_check[y*GetColumn() + (x - 1)] = CHECKING;
			    checkagain = true;
			  }
		      }
		    
		    //(x,y+1)の判定
		    if (y < GetLine() - 1)
		      {
			if (GetValue(y + 1, x).color == GetValue(y, x).color && field_array_check[(y + 1)*GetColumn() + x] == NOCHECK)
			  {
			    field_array_check[(y + 1)*GetColumn() + x] = CHECKING;
			    checkagain = true;
			  }
		      }
		    
		    //(x,y-1)の判定
		    if (y > 0)
		      {
			if (GetValue(y - 1, x).color == GetValue(y, x).color && field_array_check[(y - 1)*GetColumn() + x] == NOCHECK)
			  {
			    field_array_check[(y - 1)*GetColumn() + x] = CHECKING;
			    checkagain = true;
			  }
		      }
		    
		    //(x,y)を判定済みにする
		    field_array_check[y*GetColumn() + x] = CHECKED;
		  }
	      }
	  }
      }
    
    //判定済みの数をカウント
    int puyocount = 0;
    for (int i = 0; i < GetLine()*GetColumn(); i++)
      {
	if (field_array_check[i] == CHECKED)
	  {
	    puyocount++;
	  }
      }
    
    //4個以上あれば，判定済み座標のぷよを消す
    int vanishednumber = 0;
    if (4 <= puyocount)
      {
	for (int y = GetLine()-1; y > -1; y--)
	  {
	    for (int x = GetColumn()-1; x > -1; x--)
	      {
		if (field_array_check[y*GetColumn() + x] == CHECKED)
		  {
		    struct puyodata data = GetValue(y, x);
		    for (int i = 0; i < vpuyocolor.size(); i++)
		      {
			if (vpuyocolor[i] == data.color)
			  {
			    break;
			  }
			if (i == vpuyocolor.size()-1)
			  {
			    vpuyocolor.push_back(data.color);
			    vpuyocolor.resize(vpuyocolor.size()+1);
			  }
		      }
		    data.color = NONE;
		    data.handling = false;
		    SetValue(y, x, data);
		    vanishednumber++;
		    vpuyo_x = x;
		    vpuyo_y = y;
		  }
	      }
	  }
      }
    
    //メモリ解放
    delete[] field_array_check;
    
    return vanishednumber;
  }
  //ぷよのゲームの終わり判定
  int PuyoEnd()
  {
    struct puyodata puyo1 =  GetValue(0, 2);
    struct puyodata puyo2 =  GetValue(0, 3);
    vpuyocolor.clear();
    vpuyocolor.resize(1);
    if ( puyo1.color != NONE || puyo2.color != NONE){
      attrset(COLOR_PAIR(1));
      mvaddstr(10, 25, "THE END!!");
      
      return 4;
      
    }
    else {
      GeneratePuyo();
      return 0;
    }
  }
  //ぷよのSCORE判定で用いるもの-連鎖数
  int Puyochain(int chain)
  {
    switch(chain)
      {
      case 1:
	return 0;
      case 2:
	return 8;
      case 3:
	return 16;
      case 4:
	return 32;
      case 5:
	return 64;
      case 6:
	return 96;
      case 7:     
	return 128;
      case 8:
	return 160;
      case 9:
	return 192;
      case 10:    
	return 224;
      case 11:
	return 256;
      case 12:
	return 288;
      case 13:
	return 320;
      case 14:
	return 352;
      case 15:
	return 384;
      case 16:
	return 416;
      case 17:
	return 448;
      case 18:
	return 480;
      case 19:
	return 512;
      default:
	return 0;
      }
  }
  //ぷよのSCOREで用いる物-連結
  int Puyocount(int count)
  {
    if (count == 4)
      {
	return 0;
      }
    else if(4 < count < 11)
      {
	return count -3;
      }
    else
      {
	return 10;
      }
  }
  //ぷよのSCOREで用いる物-色数
  int PuyoVcolor()
  {
    switch (vpuyocolor.size())
      {
      case 1:
	return 0;
      case 2:
	return 3;
      case 3:
	return 6;
      case 4:
	return 12;
      case 5:
	return 24;
      }
  }
    
  //ぷよのSCORE測定
  unsigned int PuyoScore(int count,int chain)
  {
    if (count == 4 && chain == 1 && vpuyocolor.size() == 1)
      {
	return count + 10;
      }
    return count*(Puyocount(count)+Puyochain(chain)+PuyoVcolor())*10;
  }    
};
//表示
void Display(FieldControl& field, int score, int coun, int chain)
{
  unsigned int field_line = field.GetLine();
  unsigned int field_column = field.GetColumn();
  //フィールド表示
    for (int y = 0; y < field_line; y++)
      {
	for (int x = 0; x < field_column; x++)
	  { 
	    switch (field.GetValue(y, x).color)
	      {
	      case NONE:
		mvaddch(y+1, x+1, ' ');
		break;
	      case RED:
		attrset(COLOR_PAIR(1));
		mvaddch(y+1, x+1, 'R');
		break;
	      case BLUE:
		attrset(COLOR_PAIR(2));
		mvaddch(y+1, x+1, 'B');
		break;
	      case GREEN:
		attrset(COLOR_PAIR(3));
		mvaddch(y+1, x+1, 'G');
		break;
	      case YELLOW:
		attrset(COLOR_PAIR(4));
		mvaddch(y+1, x+1, 'Y');
		break;
	      default:
		mvaddch(y+1, x+1, '?');
		break;
	      }
	    
	  }
      }
    
    
    //情報表示
    int count = 0;
    for (int y = 0; y < field_line; y++)
      {
	for (int x = 0; x < field_column; x++)
	  {
	    if (field.GetValue(y, x).color != NONE)
	      {
		count++;
	      }
	  }
      }
    
    char msg[256];	
    
    sprintf(msg, "Field: %d x %d, Puyo number: %03d", field_line, field_column, count);  
    attrset(COLOR_PAIR(5));
    mvaddstr(2, 25, msg);

    for(int i = 0;i < field_line; i++)
      {
	mvaddch(i+1, field_column+1 , ' ');
	mvaddch(i+1, field_column+1 , '|');
	mvaddch(i+1, 0 , ' ');
        mvaddch(i+1, 0 , '|');
      }
    for(int i = 0;i < field_column; i++)
      {
	mvaddch(field_line+1, i+1 , ' ');
	mvaddch(field_line+1, i+1 , '-');
	mvaddch(0, i+1 , ' ');
        mvaddch(0, i+1 , '-');
      }
    for (int i = 0; i < 4;i++){
      switch (i % 4)
	{
	case 0:
	case 1:
	  switch (field.newpuyo[i].color)
	    {
	    case NONE:
	      mvaddch(5+i, 10, '1');
	      break;
	    case RED:
	      attrset(COLOR_PAIR(1));
	      mvaddch(5+i, 10, 'R');
	      break;
	    case BLUE:
	      attrset(COLOR_PAIR(2));
	      mvaddch(5+i, 10, 'B');
	      break;
	    case GREEN:
	      attrset(COLOR_PAIR(3));
	      mvaddch(5+i, 10, 'G');
	      break;
	    case YELLOW:
	      attrset(COLOR_PAIR(4));
	      mvaddch(5+i, 10, 'Y');
	      break;
	    default:
	      mvaddch(5+i, 10, '?');
	      break;
	    }
	  break;
	case 2:
	case 3:
	  attrset(COLOR_PAIR(5));
	  mvaddstr(2, 12, "NEXT");
	  switch (field.newpuyo[i].color)
	    {
	    case NONE:
	      mvaddch(i, 10, '2');
	      break;
	    case RED:
	      attrset(COLOR_PAIR(1));
	      mvaddch(i, 10, 'R');
	      break;
	    case BLUE:
	      attrset(COLOR_PAIR(2));
	      mvaddch(i, 10, 'B');
	      break;
	    case GREEN:
	      attrset(COLOR_PAIR(3));
	      mvaddch(i, 10, 'G');
	      break;
	    case YELLOW:
	      attrset(COLOR_PAIR(4));
	      mvaddch(i, 10, 'Y');
	      break;
	    default:
	      mvaddch(i, 10, '?');
	      break;
	    }
	  break;
	}
    }
    if (coun > 3){
      char ch[256];
      sprintf(ch, "%d", chain);
      attrset(COLOR_PAIR(5));
      mvaddstr(field.vpuyo_y+1,field.vpuyo_x+1, ch);
    }
    char sc[256];	
      
    sprintf(sc, "SCORE: %u", score);
    attrset(COLOR_PAIR(5));
    mvaddstr(13, 25, sc);
    refresh();
}

//ここから実行される
int main(int argc, char **argv)
  {
  
  //画面の初期化
  initscr();
  //カラー属性を扱うための初期化
  start_color();
  init_pair(1,COLOR_RED,COLOR_BLACK);
  init_pair(2,COLOR_BLUE,COLOR_BLACK);
  init_pair(3,COLOR_GREEN,COLOR_BLACK);
  init_pair(4,COLOR_YELLOW,COLOR_BLACK);
  init_pair(5,COLOR_WHITE,COLOR_BLACK);
  
  //キーを押しても画面に表示しない
  noecho();
  //キー入力を即座に受け付ける
  cbreak();
  
  curs_set(0);
  //キー入力受付方法指定
  keypad(stdscr, TRUE);
  
  //キー入力非ブロッキングモード
  timeout(0);
  
  
  //初期化処理
  FieldControl field;
  field.ChangeSize(12, 6);	//フィールドは6*12にする
   field.GeneratePuyo(); //最初のぷよ生成  


  int delay = 0;
  int waitCount = 30000;
  int state = 0;
  int count;
  int puyorotate = 0;
  int chain = 0;
  unsigned int score = 0;
  //メイン処理ループ
  while (1)
    {
      //キー入力受付
      int ch;
      ch = getch();
      
      //Qの入力で終了
      if (ch == 'Q')
	{
	  break;
	}
      
      //入力キーごとの処理
      switch (ch)
	{
	case KEY_LEFT:
	  field.ControlLeft();
	  break;
	case KEY_RIGHT:
	  field.ControlRight();
	  break;
	case 'z':
	  puyorotate = field.ControlRotate();
	  break;
	case KEY_DOWN:
	  field.ControlDown();
	  break;
	default:
	  break;
	}
      
      //処理速度調整のためのif文
      if (delay%waitCount == waitCount-1){
	if (state == 0){
	  //ぷよ下に移動
	  field.ControlDown();
	  delay++;
	  state = 1;
	  
	}
	else if(state == 1){
	  if (puyorotate != 0)
	    {
	      puyorotate = 0;
	      state = 0;
	    }
	  else 
	    {
	      //ぷよの地面判定
	      if (field.LandingPuyo()){
		state = 2;
	      }
	      else {
		state = 0;
	      }
	    }
	}
	//DisplayしてからFall
	else if (state == 2){
	  field.FallPuyo();
	  //前回行動がぷよ消去の場合止める
	  if(count > 3){
	    usleep(5*100000);
	    count = 0;
	  }
	  state = 3;
	}
	//Fall後Displayしてぷよ消去
	else {
	  count = field.VanishPuyo();
	  //消去したらFallへQ
	  if(count > 3){
	    state = 2;
	    chain += 1;
            usleep(5*100000);
	    score += field.PuyoScore(count, chain);
	  }
	  //消去が無い場合ぷよ生成
	  else{
	    state = field.PuyoEnd();
	    chain = 0;
	  }
	}
      } 
      delay++;
      
      
      //表示
      Display(field,score,count,chain);
    }
  
  
  //画面をリセット
  endwin();
  
  return 0;
}